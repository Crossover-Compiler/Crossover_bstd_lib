//
// Created by manta on 11/10/22.
//

#include "../include/picutils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

bstd_picture* bstd_picture_of(char* bytes, char* mask, uint8_t length) {

    char* b = (char*)malloc(sizeof(char) * length + 1);
    char* m = (char*)malloc(sizeof(char) * length + 1);

    bstd_picture* picture = (bstd_picture*)malloc(sizeof(bstd_picture));
    picture->bytes = copy(bytes, b, length + 1);
    picture->mask = copy(mask, m, length + 1);
    picture->length = length;

    return picture;
}

void bstd_assign_picture(bstd_picture* assignee, bstd_picture* value) {
    // todo: implement
}

void bstd_assign_bytes(bstd_picture *assignee, const char *bytes, uint8_t buf_size) {

    // the number of bytes to copy
    uint8_t n; // = min(assignee->length, buf_size)

    if (assignee->length < buf_size) {
        // picture is smaller than buffer size
        n = assignee->length;
    } else {
        // buffer is smaller than picture
        n = buf_size;
        // ensure any leading picture bytes are zero
        memset(assignee->bytes, 0, assignee->length - buf_size); // todo: we can get away with setting (size - length) bytes.
    }

    // copy bytes right-to-left
    for (int i = 0; i < n; ++i) {
        assignee->bytes[assignee->length - 1 - i] = bytes[buf_size - 1 - i];
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

char bstd_picture_mask_char(char byte, char mask) {

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
