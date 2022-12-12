#include <criterion/criterion.h>
#include "../include/arithmetic.h"
#include "../include/number.h"
#include "../include/numutils.h"
#include "../include/picture.h"
#include "../include/picutils.h"
#include <stdio.h>
/**
 * Test for checking if criterion works
 */
Test(cr, passing) {
    cr_assert(1);
}

/**
 * Test for to_cstr
 */
Test(bstd_tests, picture_bstd_tocstr_0){
    char c[3] = { 'Q', 0, 'F' };
    char mask[3] = { 'X', '9', 'X' };
    bstd_Picture* pic = bstd_picutils_of(c, mask, 3);

    char* cstrval = bstd_picutils_to_cstr(pic);
    char* expected = "Q0F";

    cr_assert_str_eq(expected, cstrval);
}
