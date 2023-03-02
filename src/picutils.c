#include "../include/picutils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Deep copy of source array to target array.
 * @tparam T The array element type.
 * @param source
 * @param target
 * @param length
 * @return
 */
char* copy(const char* source, char* target, size_t length) {
    for (int i = 0; i < length; ++i) {
        target[i] = source[i];
    }
    return target;
}

bstd_picture* bstd_picutils_of(char* bytes, char* mask, uint8_t length) {

    char* b = (char*)malloc(sizeof(char) * length + 1);
    char* m = (char*)malloc(sizeof(char) * length + 1);

    bstd_picture* picture = (bstd_picture*)malloc(sizeof(bstd_picture));
    picture->bytes = copy(bytes, b, length + 1);
    picture->mask = copy(mask, m, length + 1);
    picture->length = length;

    return picture;
}

bstd_picture* bstd_picutils_assign(bstd_picture* assignee, bstd_picture* value) {
    // todo: implement
    return NULL;
}

char* bstd_picutils_to_cstr(bstd_picture* picture) {

    char* str = (char*)malloc(sizeof(char) * (picture->length + 1));
    str[picture->length] = '\0'; // null terminator

    for (int i = 0; i < picture->length; ++i) {
        char c = bstd_picutils_mask_char(picture->bytes[i], picture->mask[i]);
        str[i] = c;
    }

    return str;
}

char bstd_picutils_mask_char(char c, char mask) {

    int size;
    char* str;

    switch (mask) {
        case 'x':
        case 'X':
            return c;
        case '9':
            if (c == 0) {
                return '0';
            } else if (c == 1) {
                return '1';
            }
            size = (int)(ceil(log10(c)) + 1);
            str = (char*)malloc(sizeof(char) * size);
            sprintf(str, "%d", c);
            char result = str[size - 2];
            free(str);
            return result;
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