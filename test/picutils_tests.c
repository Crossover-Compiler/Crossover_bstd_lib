#include <criterion/criterion.h>
#include "../include/picutils.h"

/**
 * Tests for unsigned char bstd_default_value(char mask)
 *
 * Equivalence classes:
 * +---------------+--------------+-----------------+
 * |   Condition   |    Valid     |     Invalid     |
 * +---------------+--------------+-----------------+
 * | Value of mask | mask == ‘9’, | (mask != ‘A’ || |
 * |               | mask == ‘X’, | mask != ‘X’ ||  |
 * |               | mask == ‘A’  | mask != ‘9’)    |
 * |               |              |                 |
 * +---------------+--------------+-----------------+
 *
 */

// valid classes tests


/*
 * testing valid conditions mask == ‘X’
 *
 * in: mask = ‘X’
 * expected = ' '
 *
 */
Test(picutils_tests, bstd_default_value__X){
    unsigned char res = bstd_default_value(BSTD_MASK_X);

    cr_assert_eq(res, ' ');
}

/*
 * testing valid conditions mask == ‘9’
 *
 * in: mask = ‘9’
 * expected = 0
 *
 */
Test(picutils_tests, bstd_default_value__9){
    unsigned char res = bstd_default_value(BSTD_MASK_9);

    cr_assert_eq(res, 0);
}

/*
 * testing valid conditions mask == ‘A’
 *
 * in: mask = ‘A’
 * expected = ' '
 *
 */
Test(picutils_tests, bstd_default_value__A){
    unsigned char res = bstd_default_value(BSTD_MASK_A);

    cr_assert_eq(res, ' ');
}

// invalid classes tests

/*
 * testing valid conditions mask == ‘55’
 *
 * in: mask = ‘55’
 * expected = 0
 *
 */
Test(picutils_tests, bstd_default_value__55){
    unsigned char res = bstd_default_value(55);

    cr_assert_eq(res, 0);
}

/**
 * Tests for char bstd_mask(unsigned char byte, char mask)
 *
 * Equivalence classes:
 * +---------------+------------------------------------------+------------------+
 * |   Condition   |                  Valid                   |     Invalid      |
 * +---------------+------------------------------------------+------------------+
 * | Value of byte | 0 <= byte <= 127                         | byte < 0,        |
 * |               |                                          | byte > 127       |
 * | Value of mask | mask == ‘9’,                             | mask != ‘A’ ||   |
 * |               | mask == ‘X’,                             | mask != ‘X’ ||   |
 * |               | mask == ‘A’                              | mask != ‘9’      |
 * |               |                                          |                  |
 * | Relation      | Mask == ‘A’ &&                           | mask ==‘A’ &&    |
 * |               | (65 <= byte <= 90 || 97 <= byte <= 122), | (byte < 65       |
 * |               |                                          | || byte >122 ||  |
 * |               | mask ==‘X’ &&                            | 90 < byte < 97), |
 * |               | 0 <= byte <= 127,                        |                  |
 * |               |                                          | mask ==‘X’ &&    |
 * |               | mask == ‘9’ &&                           | (byte < 0        |
 * |               | 0 <=byte <= 9                            | || byte >127),   |
 * |               |                                          |                  |
 * |               |                                          | mask == ‘9’ &&   |
 * |               |                                          | (byte < 0        |
 * |               |                                          | || byte >9),     |
 * +---------------+------------------------------------------+------------------+
 *
 *
 */

// valid classes tests

/*
 * testing valid conditions
 * 0 <= byte <= 127
 * mask == ‘9’
 * mask == ‘9’ && 0 <= byte <= 9
 *
 * in: mask = ‘9’ , byte = 5
 * expected = '5'
 *
 */
Test(picutils_tests, bstd_mask__mask_9_byte_5){
    char res = bstd_mask(5, BSTD_MASK_9);

    cr_assert_eq(res, '5');
}

/*
 * testing valid conditions
 * 0 <= byte <= 127
 * mask == ‘X’
 * mask == ‘X’ && 0 <= byte <= 127
 *
 * in: mask = ‘X’, byte = '$'
 * expected = '$'
 *
 */
Test(picutils_tests, bstd_mask__mask_X_byte_char_$){
    char res = bstd_mask('$', BSTD_MASK_X);

    cr_assert_eq(res, '$');
}

/*
 * testing valid conditions
 * 0 <= byte <= 127
 * mask == ‘A’
 * Mask == ‘A’ && (65 <= byte <= 90 || 97 <= byte <= 122)
 *
 * in: mask = ‘A’, byte = 'F'
 * expected = 'F'
 *
 */
Test(picutils_tests, bstd_mask__mask_A_byte_char_F){
    char res = bstd_mask('F', BSTD_MASK_A);

    cr_assert_eq(res, 'F');
}

/*
 * testing valid conditions
 * 0 <= byte <= 127
 * mask == ‘A’
 * Mask == ‘A’ && (65 <= byte <= 90 || 97 <= byte <= 122)
 *
 * in: mask = ‘A’, byte = 'f'
 * expected = 'f'
 *
 */
Test(picutils_tests, bstd_mask__mask_A_byte_char_f){
    char res = bstd_mask('f', BSTD_MASK_A);

    cr_assert_eq(res, 'f');
}

// boundary value analysis

/*
 * testing boundary value for byte = 0 with mask = '9'
 *
 * in: mask = ‘9’ , byte = 0
 * expected = '0'
 *
 */
Test(picutils_tests, bstd_mask__mask_9_byte_0){
    char res = bstd_mask(0, BSTD_MASK_9);

    cr_assert_eq(res, '0');
}

/*
 * testing boundary value for byte = 9 with mask = '9'
 *
 * in: mask = ‘9’ , byte = 9
 * expected = '0'
 *
 */
Test(picutils_tests, bstd_mask__mask_9_byte_9){
    char res = bstd_mask(9, BSTD_MASK_9);

    cr_assert_eq(res, '9');
}

/*
 * testing boundary value byte = 0 with mask = 'X'
 *
 * in: mask = ‘X’, byte = 0
 * expected = '\000' (NULL)
 *
 */
Test(picutils_tests, bstd_mask__mask_X_byte_0){
    char res = bstd_mask(0, BSTD_MASK_X);

    cr_assert_eq(res, '\000');
}

/*
 * testing boundary value byte = 127 with mask = 'X'
 *
 * in: mask = ‘X’, byte = 127
 * expected = '\177' (DEL)
 *
 */
Test(picutils_tests, bstd_mask__mask_X_byte_127){
    char res = bstd_mask(127, BSTD_MASK_X);

    cr_assert_eq(res, '\177');
}

/*
 * testing boundary value byte = 65 with mask = 'A'
 *
 * in: mask = ‘A’, byte = 65
 * expected = 'A'
 *
 */
Test(picutils_tests, bstd_mask__mask_A_byte_65){
    char res = bstd_mask(65, BSTD_MASK_A);

    cr_assert_eq(res, 'A');
}

/*
 * testing boundary value byte = 90 with mask = 'A'
 *
 * in: mask = ‘A’, byte = 90
 * expected = 'Z'
 *
 */
Test(picutils_tests, bstd_mask__mask_A_byte_90){
    char res = bstd_mask(90, BSTD_MASK_A);

    cr_assert_eq(res, 'Z');
}

/*
 * testing boundary value byte = 65 with mask = 'A'
 *
 * in: mask = ‘A’, byte = 97
 * expected = 'a'
 *
 */
Test(picutils_tests, bstd_mask__mask_A_byte_97){
    char res = bstd_mask(97, BSTD_MASK_A);

    cr_assert_eq(res, 'a');
}

/*
 * testing boundary value byte = 65 with mask = 'A'
 *
 * in: mask = ‘A’, byte = 122
 * expected = 'z'
 *
 */
Test(picutils_tests, bstd_mask__mask_A_byte_122){
    char res = bstd_mask(122, BSTD_MASK_A);

    cr_assert_eq(res, 'z');
}

/**
 *
 * Tests for unsigned char bstd_unmask(char c, char mask)
 *
 * Equivalence classes:
 * +---------------+------------------------------------+----------------+
 * |   Condition   |               Valid                |    Invalid     |
 * +---------------+------------------------------------+----------------+
 * | Value of c    | 0 <= c <= 127                      | byte < 0,      |
 * |               |                                    | byte > 127     |
 * | Value of mask | mask == ‘9’,                       | mask != ‘A’ || |
 * |               | mask == ‘X’,                       | mask != ‘X’ || |
 * |               | mask == ‘A’                        | mask != ‘9’    |
 * |               |                                    |                |
 * | Relation      | Mask == ‘A’ &&                     | mask ==‘A’ &&  |
 * |               | (65 <= c <= 90 || 97 <= c <= 122), | (c < 65        |
 * |               |                                    | || c >122 ||   |
 * |               | mask ==‘X’ &&                      | 90 < c < 97),  |
 * |               | 0 <= c <= 127,                     |                |
 * |               |                                    | mask ==‘X’ &&  |
 * |               | mask == ‘9’ &&                     | (c < 0         |
 * |               | 0 <=c <= 9                         | || c >127),    |
 * |               |                                    |                |
 * |               |                                    | mask == ‘9’ && |
 * |               |                                    | (c < ‘0’       |
 * |               |                                    | || c > ’9’),   |
 * +---------------+------------------------------------+----------------+
 *
 */

// valid classes tests

/*
 * testing valid conditions
 * 0 <= byte <= 127
 * mask == ‘9’
 * mask == ‘9’ && '0' <= c <= '9'
 *
 * in: mask = ‘9’ , c = '5'
 * expected = 5
 *
 */
Test(picutils_tests, bstd_unmask__mask_9_c_char_5){
    unsigned char res = bstd_unmask('5', BSTD_MASK_9);

    cr_assert_eq(res, 5);
}

/*
 * testing valid conditions
 * 0 <= byte <= 127
 * mask == ‘X’
 * mask == ‘X’ && 0 <= c <= 127
 *
 * in: mask = ‘X’, c = '$'
 * expected = 36
 *
 */
Test(picutils_tests, bstd_unmask__mask_X_c_char_$){
    unsigned char res = bstd_unmask('$', BSTD_MASK_X);

    cr_assert_eq(res, 36);
}

/*
 * testing valid conditions
 * 0 <= byte <= 127
 * mask == ‘A’
 * Mask == ‘A’ && (65 <= c <= 90 || 97 <= c <= 122)
 *
 * in: mask = ‘A’, c = 'F'
 * expected = 70
 *
 */
Test(picutils_tests, bstd_unmask__mask_A_c_char_F){
    unsigned char res = bstd_mask('F', BSTD_MASK_A);

    cr_assert_eq(res, 70);
}

/*
 * testing valid conditions
 * 0 <= byte <= 127
 * mask == ‘A’
 * Mask == ‘A’ && (65 <= byte <= 90 || 97 <= byte <= 122)
 *
 * in: mask = ‘A’, byte = 'f'
 * expected = 102
 *
 */
Test(picutils_tests, bstd_unmask__mask_A_c_char_f){
    unsigned char res = bstd_unmask('f', BSTD_MASK_A);

    cr_assert_eq(res, 102);
}

// boundary value analysis

/*
 * testing boundary value for c = '0' with mask = '9'
 *
 * in: mask = ‘9’ , c = '0'
 * expected = 0
 *
 */
Test(picutils_tests, bstd_unmask__mask_9_c_char_0){
    unsigned char res = bstd_unmask('0', BSTD_MASK_9);

    cr_assert_eq(res, 0);
}

/*
 * testing boundary value for c = 9 with mask = '9'
 *
 * in: mask = ‘9’ , c = '9'
 * expected = 9
 *
 */
Test(picutils_tests, bstd_unmask__mask_9_c_char_9){
    unsigned char res = bstd_unmask('9', BSTD_MASK_9);

    cr_assert_eq(res, 9);
}

/*
 * testing boundary value c = '\000' with mask = 'X'
 *
 * in: mask = ‘X’, c = '\000' (NULL)
 * expected = 0
 *
 */
Test(picutils_tests, bstd_unmask__mask_X_c_char_NULL){
    unsigned char res = bstd_unmask('\000', BSTD_MASK_X);

    cr_assert_eq(res, 0);
}

/*
 * testing boundary value c = '\177' with mask = 'X'
 *
 * in: mask = ‘X’, c = '\177' (DEL)
 * expected = 127
 *
 */
Test(picutils_tests, bstd_unmask__mask_X_c_char_DEL){
    unsigned char res = bstd_unmask('\177', BSTD_MASK_X);

    cr_assert_eq(res, 127);
}

/*
 * testing boundary value c = 'A' with mask = 'A'
 *
 * in: mask = ‘A’, c = 'A'
 * expected = 65
 *
 */
Test(picutils_tests, bstd_unmask__mask_A_c_char_A){
    unsigned char res = bstd_unmask('A', BSTD_MASK_A);

    cr_assert_eq(res, 65);
}

/*
 * testing boundary value c = 'Z' with mask = 'A'
 *
 * in: mask = ‘A’, c = 'Z'
 * expected = 90
 *
 */
Test(picutils_tests, bstd_unmask__mask_A_c_char_Z){
    unsigned char res = bstd_unmask('Z', BSTD_MASK_A);

    cr_assert_eq(res, 90);
}

/*
 * testing boundary value c = 'a' with mask = 'A'
 *
 * in: mask = ‘A’, c = 'a'
 * expected = 97
 *
 */
Test(picutils_tests, bstd_unmask__mask_A_c_char_a){
    unsigned char res = bstd_unmask('a', BSTD_MASK_A);

    cr_assert_eq(res, 97);
}

/*
 * testing boundary value c = 'z' with mask = 'A'
 *
 * in: mask = ‘A’, c = 'z'
 * expected = 122
 *
 */
Test(picutils_tests, bstd_unmask__mask_A_byte_c_char_z){
    char res = bstd_mask('z', BSTD_MASK_A);

    cr_assert_eq(res, 122);
}

/**
 * Tests for void bstd_picture_init(bstd_picture* picture)
 *
 * Equivalence classes:
 * +-------------------------+--------------------------------------------------------------+-------------------------------------------------------------------+
 * |        Condition        |                            Valid                             |                              Invalid                              |
 * +-------------------------+--------------------------------------------------------------+-------------------------------------------------------------------+
 * | Value of picture.bytes  | unsigned char* containing a combination of byte values 0-127 | unsigned char* containing a combination of byte values <0 or >127 |
 * | Value of picture.mask   | char* containing ‘A’, ‘X’ and ‘9’ s                          | char* containing anything other than ‘A’, ‘X’ and ‘9’s            |
 * | Value of picture.length | 0 <= picture.length <= 255                                   | picture.length < 0,                                               |
 * |                         |                                                              | picture.length  > 255                                             |
 * | Relation                | picture.length ==                                            | picture.length !=                                                 |
 * |                         | length of picture.bytes == length of picture.mask            | length of picture.bytes != length of picture.mask                 |
 * | Relation                | picture.mask[i] ==‘A’ &&                                     | picture.mask[i] ==‘A’ &&                                          |
 * |                         | 65 <= picture.bytes[i] <= 90 ||                              | (picture.bytes[i] < 65                                            |
 * |                         | 97 <= picture.bytes[i] <= 122,                               | || picture.bytes[i] >122||                                        |
 * |                         |                                                              | 90 < picture.bytes[i] < 97),                                      |
 * |                         |                                                              |                                                                   |
 * |                         | picture.mask[i] ==‘X’ &&                                     | picture.mask[i] ==‘X’ &&                                          |
 * |                         | 0 <= picture.bytes[i] <= 127,                                | (picture.bytes[i] < 0                                             |
 * |                         |                                                              | || picture.bytes[i] >127),                                        |
 * |                         |                                                              |                                                                   |
 * |                         | picture.mask[i] == ‘9’ &&                                    | picture.mask[i] == ‘9’ &&                                         |
 * |                         | 0 <= picture.bytes[i] <= 9                                   | (picture.bytes[i] < 0                                             |
 * |                         |                                                              | || picture.bytes[i] >9)                                           |
 * +-------------------------+--------------------------------------------------------------+-------------------------------------------------------------------+
 *
 */


/*
 * testing valid conditions:
 * unsigned char* containing a combination of byte values 0-127
 * char* containing ‘A’, ‘X’ and ‘9’ s
 * 0 <= picture.length <= 255
 * picture.length == length of picture.bytes == length of picture.mask
 * picture.mask[i] ==‘A’ && 65 <= picture.bytes[i] <= 90,
 * picture.mask[i] ==‘X’ && 0 <= picture.bytes[i] <= 127,
 * picture.mask[i] == ‘9’ && 0 <= picture.bytes[i] <= 9
 *
 * in:
 * bytes = {'}', 'B', 3}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 * ex:
 * bytes = {' ', ' ', 0}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 *
 */
Test(picutils_tests, bstd_picture_init__mask_XA9_bytes_char_curlybracketright_char_B_3) {
    unsigned char c[3] = {'}', 'B', 3};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    bstd_picture_init(picture);

    bstd_picture ex;
    ex.length = 3;
    char ex_mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    ex.mask = ex_mask;
    unsigned char ex_c[3] = {' ', ' ', 0};
    ex.bytes = ex_c;

    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], ex.bytes[i]);
    }
}

/*
 * testing valid conditions:
 * unsigned char* containing a combination of byte values 0-127
 * char* containing ‘A’, ‘X’ and ‘9’ s
 * 0 <= picture.length <= 255
 * picture.length == length of picture.bytes == length of picture.mask
 * picture.mask[i] ==‘A’ && 75 <= picture.bytes[i] <= 122,
 * picture.mask[i] ==‘X’ && 0 <= picture.bytes[i] <= 127,
 * picture.mask[i] == ‘9’ && 0 <= picture.bytes[i] <= 9
 *
* in:
 * bytes = {'}', 'b', 3}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 * ex:
 * bytes = {' ', ' ', 0}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 */
Test(picutils_tests, bstd_picture_init__mask_XA9_bytes_char_curlybracketright_char_b_3) {
    unsigned char c[3] = {'}', 'b', 3};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    bstd_picture_init(picture);

    bstd_picture ex;
    ex.length = 3;
    char ex_mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    ex.mask = ex_mask;
    unsigned char ex_c[3] = {' ', ' ', 0};
    ex.bytes = ex_c;

    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], ex.bytes[i]);
    }
}

// boundary value analysis

/*
 * testing boundary values:
 *
 * in:
 * bytes = {0, 65, 0}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 * ex:
 * bytes = {' ', ' ', 0}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 */
Test(picutils_tests, bstd_picture_init__mask_XA9_min_values_uppercase_A) {
    unsigned char c[3] = {0, 65, 0};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    bstd_picture_init(picture);

    bstd_picture ex;
    ex.length = 3;
    char ex_mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    ex.mask = ex_mask;
    unsigned char ex_c[3] = {' ', ' ', 0};
    ex.bytes = ex_c;

    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], ex.bytes[i]);
    }
}

/*
 * testing boundary values:
 *
 * in:
 * bytes = {0, 97, 0}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 * ex:
 * bytes = {' ', ' ', 0}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 */
Test(picutils_tests, bstd_picture_init__mask_XA9_min_values_lowercase_a) {
    unsigned char c[3] = {0, 97, 0};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    bstd_picture_init(picture);

    bstd_picture ex;
    ex.length = 3;
    char ex_mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    ex.mask = ex_mask;
    unsigned char ex_c[3] = {' ', ' ', 0};
    ex.bytes = ex_c;

    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], ex.bytes[i]);
    }
}

/*
 * testing boundary values:
 *
 * in:
 * bytes = {127, 90, 9}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 * ex:
 * bytes = {' ', ' ', 0}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 */
Test(picutils_tests, bstd_picture_init__mask_XA9_max_values_uppercase_Z) {
    unsigned char c[3] = {127, 90, 9};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    bstd_picture_init(picture);

    bstd_picture ex;
    ex.length = 3;
    char ex_mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    ex.mask = ex_mask;
    unsigned char ex_c[3] = {' ', ' ', 0};
    ex.bytes = ex_c;

    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], ex.bytes[i]);
    }
}

/*
 * testing boundary values:
 *
 * in:
 * bytes = {127, 122, 9}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 * ex:
 * bytes = {' ', ' ', 0}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 */
Test(picutils_tests, bstd_picture_init__mask_XA9_max_values_lowercase_z) {
    unsigned char c[3] = {127, 122, 9};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    bstd_picture_init(picture);

    bstd_picture ex;
    ex.length = 3;
    char ex_mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    ex.mask = ex_mask;
    unsigned char ex_c[3] = {' ', ' ', 0};
    ex.bytes = ex_c;

    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], ex.bytes[i]);
    }
}

/*
 * testing boundary value length =0
 *
 * in:
 * bytes = {}
 * mask = {}
 * length = 0
 *
 * ex:
 * bytes = {}
 * mask = {}
 * length = 0
 *
 *
 */
Test(picutils_tests, bstd_picture_init__min_length) {
    unsigned char c[0] = {};
    char mask[0] = {};
    bstd_picture *picture = bstd_picture_of(c, mask, 0);

    bstd_picture_init(picture);

    bstd_picture ex;
    ex.length = 0;
    char ex_mask[0] = {};
    ex.mask = ex_mask;
    unsigned char ex_c[0] = {};
    ex.bytes = ex_c;

    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], ex.bytes[i]);
    }
}

/*
 * testing boundary value length = 255
 *
 * in:
 * * bytes = {'}', 'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 255
 *
 * ex:
 * bytes = {}
 * mask = {}
 * length = 255
 *
 *
 */
Test(picutils_tests, bstd_picture_init__max_length) {
    unsigned char c[255] = {'}', 'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3};
    char mask[255] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 255);

    bstd_picture_init(picture);

    bstd_picture ex;
    ex.length = 255;
    char ex_mask[255] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};;
    ex.mask = ex_mask;
    unsigned char ex_c[255] = {' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0};
    ex.bytes = ex_c;

    for (int i = 0; i < picture->length; ++i) {
        cr_assert_eq(picture->bytes[i], ex.bytes[i]);
    }
}

/**
 * Tests for void bstd_picture_to_cstr(bstd_picture* picture)
 *
 * Equivalence classes:
 * +-------------------------+--------------------------------------------------------------+-------------------------------------------------------------------+
 * |        Condition        |                            Valid                             |                              Invalid                              |
 * +-------------------------+--------------------------------------------------------------+-------------------------------------------------------------------+
 * | Value of picture.bytes  | unsigned char* containing a combination of byte values 0-127 | unsigned char* containing a combination of byte values <0 or >127 |
 * | Value of picture.mask   | char* containing ‘A’, ‘X’ and ‘9’ s                          | char* containing anything other than ‘A’, ‘X’ and ‘9’s            |
 * | Value of picture.length | 0 <= picture.length <= 255                                   | picture.length < 0,                                               |
 * |                         |                                                              | picture.length  > 255                                             |
 * | Relation                | picture.length ==                                            | picture.length !=                                                 |
 * |                         | length of picture.bytes == length of picture.mask            | length of picture.bytes != length of picture.mask                 |
 * | Relation                | picture.mask[i] ==‘A’ &&                                     | picture.mask[i] ==‘A’ &&                                          |
 * |                         | 65 <= picture.bytes[i] <= 90 ||                              | (picture.bytes[i] < 65                                            |
 * |                         | 97 <= picture.bytes[i] <= 122,                               | || picture.bytes[i] >122||                                        |
 * |                         |                                                              | 90 < picture.bytes[i] < 97),                                      |
 * |                         |                                                              |                                                                   |
 * |                         | picture.mask[i] ==‘X’ &&                                     | picture.mask[i] ==‘X’ &&                                          |
 * |                         | 0 <= picture.bytes[i] <= 127,                                | (picture.bytes[i] < 0                                             |
 * |                         |                                                              | || picture.bytes[i] >127),                                        |
 * |                         |                                                              |                                                                   |
 * |                         | picture.mask[i] == ‘9’ &&                                    | picture.mask[i] == ‘9’ &&                                         |
 * |                         | 0 <= picture.bytes[i] <= 9                                   | (picture.bytes[i] < 0                                             |
 * |                         |                                                              | || picture.bytes[i] >9)                                           |
 * +-------------------------+--------------------------------------------------------------+-------------------------------------------------------------------+
 *
 */


/*
 * testing valid conditions:
 * unsigned char* containing a combination of byte values 0-127
 * char* containing ‘A’, ‘X’ and ‘9’ s
 * 0 <= picture.length <= 255
 * picture.length == length of picture.bytes == length of picture.mask
 * picture.mask[i] ==‘A’ && 65 <= picture.bytes[i] <= 90,
 * picture.mask[i] ==‘X’ && 0 <= picture.bytes[i] <= 127,
 * picture.mask[i] == ‘9’ && 0 <= picture.bytes[i] <= 9
 *
 * in:
 * bytes = {'}', 'B', 3}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 * ex = "}B3"
 *
 *
 */
Test(picutils_tests, bstd_picture_to_cstr__mask_XA9_bytes_char_curlybracketright_char_B_3) {
    unsigned char c[3] = {'}', 'B', 3};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    char* res = bstd_picture_to_cstr(picture);

    char* ex = "}B3";

    cr_assert_str_eq(ex,res);
}

/*
 * testing valid conditions:
 * unsigned char* containing a combination of byte values 0-127
 * char* containing ‘A’, ‘X’ and ‘9’ s
 * 0 <= picture.length <= 255
 * picture.length == length of picture.bytes == length of picture.mask
 * picture.mask[i] ==‘A’ && 75 <= picture.bytes[i] <= 122,
 * picture.mask[i] ==‘X’ && 0 <= picture.bytes[i] <= 127,
 * picture.mask[i] == ‘9’ && 0 <= picture.bytes[i] <= 9
 *
 * in:
 * bytes = {'}', 'B', 3}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 * ex = "}b3"
 */
Test(picutils_tests, bstd_picture_to_cstr__mask_XA9_bytes_char_curlybracketright_char_b_3) {
    unsigned char c[3] = {'}', 'b', 3};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    char* res = bstd_picture_to_cstr(picture);

    char* ex = "}b3";

    cr_assert_str_eq(ex,res);
}

// boundary value analysis

/*
 * testing boundary values:
 *
 * in:
 * bytes = {0, 65, 0}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 * ex = "\000"
 */
Test(picutils_tests, bstd_picture_to_cstr__mask_XA9_min_values_uppercase_A) {
    unsigned char c[3] = {0, 65, 0};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    char* res = bstd_picture_to_cstr(picture);

    char* ex = "\000"; // since we start with NULL the other chars are ignored

    cr_assert_str_eq(ex,res);
}

/*
 * testing boundary values:
 *
 * in:
 * bytes = {0, 97, 0}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 * ex = "\000"
 */
Test(picutils_tests, bstd_picture_to_cstr__mask_XA9_min_values_lowercase_a) {
    unsigned char c[3] = {0, 97, 0};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    char* res = bstd_picture_to_cstr(picture);

    char* ex = "\000"; // since we start with NULL the other chars are ignored

    cr_assert_str_eq(ex,res);
}

/*
 * testing boundary values:
 *
 * in:
 * bytes = {127, 90, 9}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 * ex = "\177Z9"
 */
Test(picutils_tests, bstd_picture_to_cstr__mask_XA9_max_values_uppercase_Z) {
    unsigned char c[3] = {127, 90, 9};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    char* res = bstd_picture_to_cstr(picture);

    char* ex = "\177Z9";

    cr_assert_str_eq(ex,res);
}

/*
 * testing boundary values:
 *
 * in:
 * bytes = {127, 122, 9}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 3
 *
 * ex = "\177z9"
 */
Test(picutils_tests, bstd_picture_to_cstr__mask_XA9_max_values_lowercase_z) {
    unsigned char c[3] = {127, 122, 9};
    char mask[3] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 3);

    char* res = bstd_picture_to_cstr(picture);

    char* ex = "\177z9";

    cr_assert_str_eq(ex,res);
}

/*
 * testing boundary value length = 0
 *
 * in:
 * bytes = {}
 * mask = {}
 * length = 0
 *
 * ex = ""
 *
 *
 */
Test(picutils_tests, bstd_picture_to_cstr__min_length) {
    unsigned char c[0] = {};
    char mask[0] = {};
    bstd_picture *picture = bstd_picture_of(c, mask, 0);

    char* res = bstd_picture_to_cstr(picture);

    char* ex = "";

    cr_assert_str_eq(ex,res);
}

/*
 * testing boundary value length = 255
 *
 * in:
 * bytes = {'}', 'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3}
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 255
 *
 * ex:
 * bytes = {' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0,' ', ' ', 0,' ', ' ', 0,
                               ' ', ' ', 0};
 * mask = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                         BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                         BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                         BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9}
 * length = 255
 *
 *
 */
Test(picutils_tests, bstd_picture_to_cstr__max_length) {
    unsigned char c[255] = {'}', 'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3,'}', 'B', 3,'}', 'B', 3,'}',
                            'B', 3};
    char mask[255] = {BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,
                      BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A,
                      BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X,
                      BSTD_MASK_A, BSTD_MASK_9,BSTD_MASK_X, BSTD_MASK_A, BSTD_MASK_9};
    bstd_picture *picture = bstd_picture_of(c, mask, 255);

    char* res = bstd_picture_to_cstr(picture);

    char* ex = "}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}"
               "B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}"
               "B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3}B3";

    cr_assert_str_eq(ex,res);
}

///todo test remaining three functions
