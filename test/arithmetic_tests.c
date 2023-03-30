#include <criterion/criterion.h>
#include "../include/arithmetic.h"

/**
 * Tests for max(uint64_t a, uint64_t b)
 *
 * Equivalence classes:
 * +------------+--------+----------------------+
 * | Condition  | Valid  |       Invalid        |
 * +------------+--------+----------------------+
 * | Value of a | a >= 0 | a < 0, a > MAXUINT64 |
 * | Value of b | b >= 0 | b < 0, b > MAXUINT64 |
 * | Relation   | a == b |                      |
 * | Relation   | a > b  |                      |
 * | Relation   | a < b  |                      |
 * +------------+--------+----------------------+
 *
*/

/*
 * testing valid conditions a >= 0, b >=0 and a == b
 *
 * in: a = 5, b = 5
 * expected = 5
 *
 */
Test(arithmetic_tests, max__equal){
    uint64_t res = max(5,5);
    uint64_t ex = 5;
    cr_assert_eq(res, ex);
}

/*
 * testing valid conditions a >= 0, b >=0 and a > b
 *
 * in: a = 6, b = 5
 * expected = 6
 *
 */
Test(arithmetic_tests, max__a_gt_b){
    uint64_t res = max(6,5);
    uint64_t ex = 6;
    cr_assert_eq(res, ex);
}

/*
 * testing valid conditions a >= 0, b >=0 and a < b
 *
 * in: a = 5, b = 6
 * expected = 6
 *
 */
Test(arithmetic_tests, max__a_lt_b){
    uint64_t res = max(5,6);
    uint64_t ex = 6;
    cr_assert_eq(res, ex);
}

/*
 * testing invalid condition a < 0 using boundry value -1
 *
 * in: a = -1, b = 6
 * expected = 18446744073709551615
 *
 */
Test(arithmetic_tests, max__a_lt_0){
    uint64_t res = max(-1,6);
    uint64_t ex  = 18446744073709551615;
    cr_assert_eq(res, ex);
}

/*
 * testing invalid condition b < 0 using boundry value -1
 *
 * in: a = 0, b = -1
 * expected = 18446744073709551615
 *
 */
Test(arithmetic_tests, max__b_lt_0){
    uint64_t res = max(6,-1);
    uint64_t ex  = 18446744073709551615;
    cr_assert_eq(res, ex);
}

/*
 * testing invalid condition a > MAXUINT64, using boundry value MAXUINT64+1
 *
 * in: a = 18446744073709551616, b = 5
 * expected = 5
 *
 */
Test(arithmetic_tests, max__a_gt_max){
    uint64_t res = max(18446744073709551616,5);
    uint64_t ex  = 5;

    cr_assert_eq(res, ex);
}

/*
 * testing invalid condition b > MAXUINT64, using boundry value MAXUINT64+1
 *
 * in: a = 5, b = 18446744073709551616
 * expected = 5
 *
 */
Test(arithmetic_tests, max__b_gt_max){
    uint64_t res = max(5,18446744073709551616);
    uint64_t ex  = 5;

    cr_assert_eq(res, ex);
}

/*
 * boundary value analysis for a >= 0, eq 0
 *
 * in: a = 0, b = 5
 * expected = 5
 *
 */
Test(arithmetic_tests, max__a_eq_0){
    uint64_t res = max(0,5);
    uint64_t ex  = 5;

    cr_assert_eq(res, ex);
}

/*
 * boundary value analysis for a >= 0, eq max
 *
 * in: a = 18446744073709551615, b = 5
 * expected = 5
 *
 */
Test(arithmetic_tests, max__a_eq_max){
    uint64_t res = max(18446744073709551615,5);
    uint64_t ex  = 18446744073709551615;

    cr_assert_eq(res, ex);
}

/*
 * boundary value analysis for b >= 0, eq 0
 *
 * in: a = 5, b = 0
 * expected = 5
 *
 */
Test(arithmetic_tests, max__b_eq_0){
    uint64_t res = max(5,0);
    uint64_t ex  = 5;

    cr_assert_eq(res, ex);
}

/*
 * boundary value analysis for b >= 0, eq max
 *
 * in: a = 5, b = 18446744073709551615
 * expected = 5
 *
 */
Test(arithmetic_tests, max__b_eq_max){
    uint64_t res = max(5,18446744073709551615);
    uint64_t ex  = 18446744073709551615;

    cr_assert_eq(res, ex);
}


/**
 * Tests for int64_t ipow(int64_t base, uint64_t exp)
 *
 * Equivalence classes:
 * +---------------+------------------------------+-----------------------------------+
 * |   Condition   |            Valid             |              Invalid              |
 * +---------------+------------------------------+-----------------------------------+
 * | Value of base | MININT64 =< base =< MAXINT64 | base < MININT64 , base > MAXINT64 |
 * | Value of exp  | exp >= 0                     | exp < 0, exp > MAXUINT64          |
 * +---------------+------------------------------+-----------------------------------+
 *
*/