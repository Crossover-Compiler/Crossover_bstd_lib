#include <criterion/criterion.h>
#include "../include/picutils.h"

/*
 * bstd_picture_to_cstr
 */

Test(picture_tests, bstd_picture_to_cstr__text){

    // given a well-formed picture representing only text...
    unsigned char c[3] = { 'A', 'B', 'C' };
    char mask[3] = { 'X', 'X', 'X' };
    bstd_picture* pic = bstd_picture_of(c, mask, 3);

    // ... when we create a string representation of that picture...
    char* str = bstd_picture_to_cstr(pic);

    // ... then the string representation must equal the text in the picture.
    cr_assert_str_eq(str, "ABC");
}

Test(picture_tests, bstd_picture_to_cstr__numerical){

    // given a well-formed picture containing a numerical zero...
    unsigned char c[3] = { 'Q', 0, 'F' };
    char mask[3] = { 'X', '9', 'X' };
    bstd_picture* pic = bstd_picture_of(c, mask, 3);

    // ... when we create a string representation of that picture...
    char* str = bstd_picture_to_cstr(pic);

    // ... then the zero-value must show up as a character.
    cr_assert_str_eq(str, "Q0F");
}

Test(picture_tests, bstd_picture_to_cstr__copies) {

    // given a well-formed picture...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {'X', 'X', 'X'};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    // ... when we create a string representation of that picture...
    char* str = bstd_picture_to_cstr(picture);

    // ... then the picture bytes pointer and the string pointer may not be equal...
    cr_expect((void*)picture->bytes != str, "Expected bytes to be copied!");
    // ... and the picture bytes and the string must have the same content.
    cr_assert_arr_eq(picture->bytes, str, picture->length);
}

Test(picture_tests, bstd_picture_to_cstr__correct_length) {

    // given a well-formed picture...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {'X', 'X', 'X'};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    // ... when we create a string representation of that picture...
    char* str = bstd_picture_to_cstr(picture);
    size_t str_len = strlen(str);

    // ... then the length of that string representation must equal the length of the picture.
    cr_assert_eq(str_len, picture->length);
}

Test(picture_tests, bstd_picture_to_cstr__truncate_length) {

    // given an ill-formed picture where a numerical value is greater than a single digit...
    unsigned char c[3] = {'H', 'H', 42};
    char mask[3] = {'X', 'X', '9'};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    // ... when we create a string representation of that picture...
    char* str = bstd_picture_to_cstr(picture);
    size_t str_len = strlen(str);

    // ... then the length of that string representation must still equal the length of the picture.
    cr_assert_eq(str_len, picture->length);
}

Test(picture_tests, bstd_picture_to_cstr__numerical_truncates) {

    // given an ill-formed picture where a numerical value is greater than a single digit...
    unsigned char c[3] = {'H', 'H', 42};
    char mask[3] = {'X', 'X', '9'};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    // ... when we create a string representation of that picture...
    char* str = bstd_picture_to_cstr(picture);

    // ... then the numerical value should be truncated to show its least-significant digit.
    cr_assert_str_eq(str, "HH2");
}

/*
 * bstd_assign_bytes
 */

Test(picture_tests, bstd_assign_bytes__copies) {

    // given a picture and a buffer of equal length...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {'X', 'X', 'X'};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    unsigned char new_bytes[3] = {'D', 'E', 'F'};
    uint8_t size = 3;

    // ... when we assign that buffer to the picture...
    bstd_assign_bytes(picture, new_bytes, size);

    // ... then the picture bytes pointer and the buffer pointer may not be equal...
    cr_expect(picture->bytes != new_bytes, "Expected bytes to be copied!");
    // ... and the picture bytes and the buffer must have the same content.
    cr_assert_arr_eq(picture->bytes, new_bytes, size);
}

Test(picture_tests, bstd_assign_bytes__larger_buffer) {

    // given a picture and a buffer, where the buffer is larger...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {'X', 'X', 'X'};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    unsigned char new_bytes[5] = {'D', 'E', 'F', 'G', 'H'};
    uint8_t size = 5;

    // ... when we assign that buffer to the picture...
    bstd_assign_bytes(picture, new_bytes, size);

    // ... then we expect the bytes of the picture to match the last part of the buffer.
    // ( picture->bytes = ['F', 'G', 'H'] )
    int delta = size - picture->length;
    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], new_bytes[delta + i]);
    }
}

Test(picture_tests, bstd_assign_bytes__smaller_buffer) {

    // given a picture and a buffer, where the buffer is smaller...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {'X', 'X', 'X'};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    unsigned char new_bytes[2] = {'D', 'E'};
    uint8_t size = 2;

    // ... when we assign that buffer to the picture...
    bstd_assign_bytes(picture, new_bytes, size);

    // ... then we expect that the leading bytes of the picture are set to zero,
    // and the buffer to match the last part of the picture bytes.
    // ( picture->bytes = [0, 'D', 'E'] )
    int delta = picture->length - size;
    for (int i = 0; i < picture->length; ++i) {
        if (i < delta) {
            cr_assert_eq(picture->bytes[i], 0);
        } else {
            cr_assert_eq(picture->bytes[i], new_bytes[i - delta]);
        }
    }
}

/*
 * bstd_assign_str
 */

Test(picture_tests, bstd_assign_str__copy) {

    // given a picture and a string of equal length...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {'X', 'X', 'X'};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    char* str = "DEF";

    // ... when we assign that string to the picture...
    bstd_assign_str(picture, str);

    // ... then the picture bytes pointer and the string pointer may not be equal...
    cr_expect((void*)picture->bytes != str, "Expected bytes to be copied!");
    // ... and the picture bytes and the string must have the same content.
    cr_assert_arr_eq(picture->bytes, str, picture->length);
}

Test(picture_tests, bstd_assign_str__larger_string) {

    // given a picture and a string, where the string is larger...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {'X', 'X', 'X'};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    char* str = "DEFGH";
    size_t str_len = strlen(str);

    // ... when we assign that string to the picture...
    bstd_assign_str(picture, str);

    // ... then we expect the bytes of the picture to match the last part of the string.
    // ( picture->bytes = ['F', 'G', 'H'] )
    int delta = str_len - picture->length;
    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], str[delta + i]);
    }
}

Test(picture_tests, bstd_assign_str__smaller_string) {

    // given a picture and a string, where the string is smaller...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {'X', 'X', 'X'};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    char* str = "DE";
    size_t str_len = strlen(str);

    // ... when we assign that string to the picture...
    bstd_assign_str(picture, str);

    // ... then we expect that the leading bytes of the picture are set to zero,
    // and the string to match the last part of the picture bytes.
    // ( picture->bytes = [0, 'D', 'E'] )
    int delta = picture->length - str_len;
    for (int i = 0; i < picture->length; ++i) {
        if (i < delta) {
            cr_assert_eq(picture->bytes[i], 0);
        } else {
            cr_assert_eq(picture->bytes[i], str[i - delta]);
        }
    }
}

Test(picture_tests, bstd_assign_str__invertible) {

    // given a well-formed picture...
    unsigned char c[3] = {'H', 4, 2};
    char mask[3] = {'X', '9', '9'};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    // ... when we copy the bytes of that picture...
    unsigned char* bytes = (unsigned char*)malloc(sizeof(unsigned char) * picture->length);
    copy_buffer(picture->bytes, bytes, picture->length);
    // ... and then create a string representation of the picture...
    char* str = bstd_picture_to_cstr(picture);
    // ... and then re-assign that string to the same picture...
    bstd_assign_str(picture, str);

    // ... then we expect the content of the picture to be exactly what it originally was.
    cr_assert_arr_eq(picture->bytes, bytes, picture->length);
}
