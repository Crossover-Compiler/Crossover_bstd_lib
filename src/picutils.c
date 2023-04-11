#include "../include/picutils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bstd_picture* bstd_create_picture(char *mask_str) {

    uint8_t length = strlen(mask_str);
    unsigned char *bytes = (unsigned char *) malloc(sizeof(unsigned char) * length);

    // bytes can contain garbage, we will initialize the picture shortly
    bstd_picture *picture = bstd_picture_of(bytes, mask_str, length);

    free(bytes); // byte contents were copied, we should release the memory

    // initialize picture bytes to the default value under its mask_str
    bstd_picture_init(picture);

    return picture;
}

bstd_picture *bstd_picture_of(unsigned char *bytes, char *mask, uint8_t length) {

    unsigned char *b = (unsigned char *) malloc(sizeof(unsigned char) * length);
    char *m = (char *) malloc(sizeof(char) * length);

    bstd_picture *picture = (bstd_picture *) malloc(sizeof(bstd_picture));
    picture->bytes = memcpy(b, bytes, length);
    picture->mask = memcpy(m, mask, length);
    picture->length = length;

    // todo: ensure that the bytes do not violate the mask

    return picture;
}

/**
 * Initializes the content of this picture with the appropriate default values for its mask from start (inclusive) to end (exclusive).
 * @param picture The picture to initialize.
 * @param start The starting index of the values to initialize (inclusive).
 * @param end The end index of the values to initialize (exclusive). May not exceed the picture length.
 */
static void bstd_picture_init_range(bstd_picture* picture, size_t start, size_t end) {

    for (unsigned int i = start; i < end; ++i) {
        picture->bytes[i] = bstd_default_value(picture->mask[i]);
    }
}

void bstd_picture_init(bstd_picture* picture) {
    bstd_picture_init_range(picture, 0, picture->length);
}

void bstd_assign_picture(bstd_picture *assignee, const bstd_picture *value) {

    // the number of bytes to copy
    uint8_t n; // = min(assignee->length, buf_size)

    if (assignee->length < value->length) {
        // assignee length is smaller than value length
        n = assignee->length;
    } else {
        // value is smaller than or equal to assignee length
        n = value->length;
        // ensure any trailing picture bytes are their default value
        bstd_picture_init_range(assignee, value->length, assignee->length);
    }

    // assign values left-to-right
    for (int i = 0; i < n; ++i) {
        const char c = bstd_mask(value->bytes[i], value->mask[i]);
        assignee->bytes[i] = bstd_unmask(c, assignee->mask[i]);
    }
}

char *bstd_picture_to_cstr(const bstd_picture *picture) {

    char *str = (char *) malloc(sizeof(char) * (picture->length + 1));
    str[picture->length] = '\0'; // null terminator

    for (int i = 0; i < picture->length; ++i) {
        str[i] = bstd_mask(picture->bytes[i], picture->mask[i]);
    }

    return str;
}

void bstd_assign_str(bstd_picture *assignee, const char *str) {

    const size_t str_len = strlen(str);

    // the number of bytes to copy
    uint8_t n;

    if (assignee->length < str_len) {
        // picture is smaller than string length
        n = assignee->length;
    } else {
        // buffer is smaller than picture
        n = str_len;
        // ensure any trailing picture bytes are their default value
        bstd_picture_init_range(assignee, str_len, assignee->length);
    }

    // unmask and store characters left-to-right
    for (int i = 0; i < n; ++i) {
        assignee->bytes[i] = bstd_unmask(str[i], assignee->mask[i]);
    }
}

unsigned char bstd_default_value(char mask) {

    switch(mask) {
        case BSTD_MASK_9:
            return 0;
        case BSTD_MASK_X:
        case BSTD_MASK_A:
            return BSTD_SPACE;
        default:
            return 0;
    }
}

char bstd_mask(unsigned char byte, char mask) {

    /*
     * 'X' => byte
     * 'A' => isalpha(byte) ? byte : SPACE
     * '9' => least_significant_digit(byte)
     */

    int size;
    char *str;

    switch (mask) {
        case BSTD_MASK_X:
            return (char) byte;
        case BSTD_MASK_A:
            if (isalpha(byte)) {
                return (char) byte;
            }
            return BSTD_SPACE;
        case BSTD_MASK_9:
            if (byte == 0) {
                return '0';
            } else if (byte == 1) {
                return '1';
            }
            size = (int) (ceil(log10(byte)) + 1);
            str = (char *) malloc(sizeof(char) * size);
            sprintf(str, "%d", byte);
            char result = str[size - 2];
            free(str);
            return result;
        default:
            // todo: warn of unknown mask
            return (char) byte;
    }
}

unsigned char bstd_unmask(char c, char mask) {

    switch (mask) {
        case BSTD_MASK_X:
            return c;
        case BSTD_MASK_A:
            if (isalpha(c)) {
                return c;
            }
            return BSTD_SPACE;
        case BSTD_MASK_9:
            if (c >= '0' && c <= '9') {
                // we can parse this character to a digit
                return c - '0';
            }
            // this character does not represent a digit
            return 0;
        default:
            // todo: warn of unknown mask
            return c;
    }
}

// TODO: Add optional delimiter
void bstd_print_picture(bstd_picture picture, bool spacer) {
    if (spacer) {
        if (picture.length == 0) {
            printf(" ");
        } else {
            printf(" %s", bstd_picture_to_cstr(&picture));
        }
    } else {
        printf("%s", bstd_picture_to_cstr(&picture));
    }
}
