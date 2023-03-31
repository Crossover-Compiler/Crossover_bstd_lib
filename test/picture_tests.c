#include <criterion/criterion.h>
#include "../include/picutils.h"

/*
 * bstd_picture_to_cstr
 */

Test(picture_tests, bstd_picture_to_cstr__text){

    // given a well-formed picture representing only text...
    unsigned char c[3] = { 'A', 'B', 'C' };
    char mask[3] = { BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X };
    bstd_picture* pic = bstd_picture_of(c, mask, 3);

    // ... when we create a string representation of that picture...
    char* str = bstd_picture_to_cstr(pic);

    // ... then the string representation must equal the text in the picture.
    cr_assert_str_eq(str, "ABC");
}

Test(picture_tests, bstd_picture_to_cstr__numerical){

    // given a well-formed picture containing a numerical zero...
    unsigned char c[3] = { 'Q', 0, 'F' };
    char mask[3] = { BSTD_MASK_X, BSTD_MASK_9, BSTD_MASK_X };
    bstd_picture* pic = bstd_picture_of(c, mask, 3);

    // ... when we create a string representation of that picture...
    char* str = bstd_picture_to_cstr(pic);

    // ... then the zero-value must show up as a character.
    cr_assert_str_eq(str, "Q0F");
}

Test(picture_tests, bstd_picture_to_cstr__null_byte_under_x_allowed){

    // given a well-formed picture containing a null-byte under an BSTD_MASK_X mask...
    unsigned char c[3] = { 'Q', 0, 'F' };
    char mask[3] = { BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X };
    bstd_picture* pic = bstd_picture_of(c, mask, 3);

    // ... when we create a string representation of that picture...
    char* str = bstd_picture_to_cstr(pic);

    // ... then the null-byte must end the c-style string.
    cr_assert_str_eq(str, "Q");
}

Test(picture_tests, bstd_picture_to_cstr__null_byte_under_a_as_space){

    // given a well-formed picture containing a null-byte under an A mask...
    unsigned char c[3] = { 'Q', 0, 'F' };
    char mask[3] = { BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_X };
    bstd_picture* pic = bstd_picture_of(c, mask, 3);

    // ... when we create a string representation of that picture...
    char* str = bstd_picture_to_cstr(pic);

    // ... then the null-byte must show up as a space under the A mask.
    cr_assert_str_eq(str, "Q F");
}

Test(picture_tests, bstd_picture_to_cstr__copies) {

    // given a well-formed picture...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X};
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
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X};
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
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_9};
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
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    // ... when we create a string representation of that picture...
    char* str = bstd_picture_to_cstr(picture);

    // ... then the numerical value should be truncated to show its least-significant digit.
    cr_assert_str_eq(str, "HH2");
}

/*
 * bstd_assign_picture
 */

Test(picture_tests, bstd_assign_picture__copies) {

    // given two pictures of equal length...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    unsigned char c2[3] = {'D', 'E', 'F'};
    char mask2[3] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X};
    bstd_picture *picture2 = bstd_picture_of(c2, mask2, 3);

    // ... when we assign one picture to the other...
    bstd_assign_picture(picture, picture2);

    // ... then the picture bytes pointers may not be equal...
    cr_expect(picture->bytes != picture2->bytes, "Expected bytes to be copied!");
    // ... and the picture bytes and the buffer must have the same content.
    cr_assert_arr_eq(picture->bytes, picture2->bytes, picture->length);
}

Test(picture_tests, bstd_assign_picture__larger_assignee) {

    // given two pictures of different lengths...
    unsigned char c[4] = {'A', 'B', 'C', 'D'};
    char mask[4] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X};
    bstd_picture *picture = bstd_picture_of(c, mask, 4);

    unsigned char c2[3] = {'E', 'F', 'G'};
    char mask2[3] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X};
    bstd_picture *picture2 = bstd_picture_of(c2, mask2, 3);

    // ... when we assign the smaller picture to the larger...
    bstd_assign_picture(picture, picture2);

    // ... then we expect that the trailing bytes of the larger picture are set to their default value,
    // and the smaller picture to match the first part of larger the picture's bytes.
    // ( picture->bytes = ['E', 'F', 'G', ' '] )
    for (int i = 0; i < picture->length; ++i) {
        if (i < picture2->length) {
            cr_assert_eq(picture->bytes[i], picture2->bytes[i]);
        } else {
            cr_assert_eq(picture->bytes[i], bstd_default_value(picture->mask[i]));
        }
    }
}

Test(picture_tests, bstd_assign_picture__smaller_assignee) {

    // given two pictures of different lengths...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    unsigned char c2[4] = {'D', 'E', 'F', 'G'};
    char mask2[4] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X};
    bstd_picture *picture2 = bstd_picture_of(c2, mask2, 4);

    // ... when we assign the larger picture to the smaller...
    bstd_assign_picture(picture, picture2);

    // ... then we expect the bytes of the smaller picture to match the first part of the larger picture.
    // ( picture->bytes = ['D', 'E´, 'F'] )
    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], picture2->bytes[i]);
    }
}

/*
 * bstd_assign_str
 */

Test(picture_tests, bstd_assign_str__copy) {

    // given a picture and a string of equal length...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X};
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
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    char* str = "DEFGH";
    size_t str_len = strlen(str);

    // ... when we assign that string to the picture...
    bstd_assign_str(picture, str);

    // ... then we expect the bytes of the picture to match the first part of the string.
    // ( picture->bytes = ['D', 'E', 'F'] )
    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], str[i]);
    }
}

Test(picture_tests, bstd_assign_str__smaller_string) {

    // given a picture and a string, where the string is smaller...
    unsigned char c[3] = {'A', 'B', 'C'};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_X, BSTD_MASK_X};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    char* str = "DE";
    size_t str_len = strlen(str);

    // ... when we assign that string to the picture...
    bstd_assign_str(picture, str);

    // ... then we expect that the trailing bytes of the picture are set to their default value,
    // and the string to match the first part of the picture bytes.
    // ( picture->bytes = ['D', 'E', ' '] )
    for (int i = 0; i < picture->length; ++i) {
        if (i < str_len) {
            cr_assert_eq(picture->bytes[i], str[i]);
        } else {
            cr_assert_eq(picture->bytes[i], bstd_default_value(picture->mask[i]));
        }
    }
}

Test(picture_tests, bstd_assign_str__invertible) {

    // given a well-formed picture...
    unsigned char c[3] = {'H', 4, 2};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_9, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    // ... when we copy the bytes of that picture...
    unsigned char* bytes = (unsigned char*)malloc(sizeof(unsigned char) * picture->length);
    for (int i = 0; i < picture->length; ++i) {
        bytes[i] = picture->bytes[i];
    }
    // ... and then create a string representation of the picture...
    char* str = bstd_picture_to_cstr(picture);
    // ... and then re-assign that string to the same picture...
    bstd_assign_str(picture, str);

    // ... then we expect the content of the picture to be exactly what it originally was.
    cr_assert_arr_eq(picture->bytes, bytes, picture->length);
}

/*
 * bstd_picture_default_value
 */

Test(picture_tests, bstd_default_value__correct) {

    // given all possible picture masks...
    char masks[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};

    // ... when we obtain the default values for those masks...
    unsigned char defaults[3];
    for (int i = 0; i < 3; ++i) {
        defaults[i] = bstd_default_value(masks[i]);
    }

    // ... then we expect the default values to be correct.
    unsigned char expected[3] = {' ', ' ', 0};
    for (int i = 0; i < 3; ++i) {
        cr_assert_eq(defaults[i], expected[i]);
    }
}

/*
 * bstd_picture_init
 */

Test(picture_tests, bstd_picture_init__correct) {

    // given a picture containing non-default values
    unsigned char c[3] = {'A', 'B', 3};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    // ... when we initialize the values for that picture...
    bstd_picture_init(picture);

    // ... then we expect the values of the picture to be set to its mask's default value.
    // ( picture->bytes = [' ', ' ', 0] )
    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], bstd_default_value(picture->mask[i]));
    }
}
