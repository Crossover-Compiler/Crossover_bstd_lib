#include "../include/picutils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char* copy_buffer(const unsigned char* source, unsigned char* target, size_t length) {
    for (int i = 0; i < length; ++i) {
        target[i] = source[i];
    }
    return target;
}

bstd_picture* bstd_picture_of(unsigned char *bytes, char *mask, uint8_t length) {

    unsigned char* b = (unsigned char*)malloc(sizeof(unsigned char) * length + 1);
    char* m = (char*)malloc(sizeof(char) * length + 1);

    bstd_picture* picture = (bstd_picture*)malloc(sizeof(bstd_picture));
    picture->bytes = copy_buffer(bytes, b, length + 1);
    picture->mask = copy_buffer(mask, m, length + 1);
    picture->length = length;

    // todo: ensure that the bytes do not violate the mask

    return picture;
}

void bstd_assign_picture(bstd_picture* assignee, bstd_picture* value) {
    // todo: implement
}

void bstd_assign_bytes(bstd_picture *assignee, const unsigned char *bytes, uint8_t buf_size) {

    // the number of bytes to copy
    uint8_t n; // = min(assignee->length, buf_size)

    if (assignee->length < buf_size) {
        // picture is smaller than buffer size
        n = assignee->length;
    } else {
        // buffer is smaller than picture
        n = buf_size;
        // ensure any leading picture bytes are zero
        memset(assignee->bytes, 0, assignee->length - buf_size);
    }

    // copy bytes right-to-left
    for (int i = 0; i < n; ++i) {
        assignee->bytes[assignee->length - 1 - i] = bytes[buf_size - 1 - i];
    }
}

void bstd_assign_str(bstd_picture *assignee, char *str) {

    size_t str_len = strlen(str);

    // the number of bytes to copy
    uint8_t n;

    if (assignee->length < str_len) {
        // picture is smaller than string length
        n = assignee->length;
    } else {
        // buffer is smaller than picture
        n = str_len;
        // ensure any leading picture bytes are zero
        memset(assignee->bytes, 0, assignee->length - str_len);
    }

    // unmask and store characters right-to-left
    for (int i = 0; i < n; ++i) {
        char c = str[str_len - 1 - i];
        uint8_t pic_index = assignee->length - 1 - i;
        char mask = assignee->mask[pic_index];
        assignee->bytes[pic_index] = bstd_picture_unmask_char(c, mask);
    }
}

char* bstd_picture_to_cstr(bstd_picture* picture) {

    char* str = (char*)malloc(sizeof(char) * (picture->length + 1));
    str[picture->length] = '\0'; // null terminator

    for (int i = 0; i < picture->length; ++i) {
        char c = bstd_picture_mask_char(picture->bytes[i], picture->mask[i]);
        str[i] = c;
    }

    return str;
}

char bstd_picture_mask_char(unsigned char byte, char mask) {

    /*
     * 'X' => character(byte)
     * '9' => least_significant_digit(byte)
     */

    int size;
    char* str;

    switch (mask) {
        case 'x':
        case 'X':
            return byte;
        case '9':
            if (byte == 0) {
                return '0';
            } else if (byte == 1) {
                return '1';
            }
            size = (int)(ceil(log10(byte)) + 1);
            str = (char*)malloc(sizeof(char) * size);
            sprintf(str, "%d", byte);
            char result = str[size - 2];
            free(str);
            return result;
        default:
            // todo: warn of unknown mask
            return byte;
    }
}

unsigned char bstd_picture_unmask_char(char c, char mask) {

    switch (mask) {
        case 'x':
        case 'X':
            return c;
        case '9':
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
void bstd_print_picture(bstd_picture picture, bool advancing) {
    if (advancing) {
        if (picture.bytes[0] == '\0') {
            printf("\r\n");
        } else {
            printf("%s\r\n", picture.bytes);
        }
    } else {
        printf("%s", picture.bytes);
    }
}