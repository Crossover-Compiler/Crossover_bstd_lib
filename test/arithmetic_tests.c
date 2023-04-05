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
 * | Value of base | MININT64 <= base <= MAXINT64 | base < MININT64 , base > MAXINT64 |
 * | Value of exp  | exp >= 0                     | exp < 0, exp > MAXUINT64          |
 * +---------------+------------------------------+-----------------------------------+
 *
 * Note: output overflows are expected behaviour
*/

/*
 * testing valid conditions MININT64 =< base =< MAXINT64 and exp >= 0
 *
 * in: base = 2, exp = 5
 * expected = 32
 *
 */
Test(arithmetic_tests, ipow__2_pow_5){
    uint64_t res = ipow(2,5);
    uint64_t ex = 32;
    cr_assert_eq(res, ex);
}

/*
 * testing invalid condition base < MININT64, using boundary value MININT64-1
 *
 * in: base = -9223372036854775809, exp = 1
 * expected = 9223372036854775807
 *
 */
Test(arithmetic_tests, ipow__base_lt_min){
    uint64_t res = ipow(-9223372036854775809,1);
    uint64_t ex = 9223372036854775807;
    cr_assert_eq(res, ex);
}

/*
 * testing invalid condition base > MININT64, using boundary value MININT64+1
 *
 * in: base = 9223372036854775808, exp = 1
 * expected = -9223372036854775808
 *
 */
Test(arithmetic_tests, ipow__base_gt_max){
    uint64_t res = ipow(9223372036854775808,1);
    uint64_t ex = -9223372036854775808;
    cr_assert_eq(res, ex);
}

/*
 * testing invalid condition exp < 0, using boundry value -1
 *
 * in: base = 1, exp = -1
 * expected = 1
 *
 */
Test(arithmetic_tests, ipow__exp_lt_0){
    uint64_t res = ipow(1, -1);
    uint64_t ex = 1;
    cr_assert_eq(res, ex);
}

/*
 * testing invalid condition exp > MAXUINT64, using boundry value MINUINT64+1
 *
 * in: base = 5, exp = 18446744073709551616
 * expected = 1
 *
 */
Test(arithmetic_tests, ipow__exp_gt_max){
    uint64_t res = ipow(5, 18446744073709551616);
    uint64_t ex = 1;
    cr_assert_eq(res, ex);
}

/*
 * testing boundry value base = MAXINT64
 *
 * in: base = 9223372036854775807, exp = 1
 * expected = 9223372036854775807
 *
 */
Test(arithmetic_tests, ipow__base_eq_max){
    uint64_t res = ipow(9223372036854775807,1);
    uint64_t ex = 9223372036854775807;
    cr_assert_eq(res, ex);
}

/*
 * testing boundry value base = MININT64
 *
 * in: base = -9223372036854775808, exp = 1
 * expected = -9223372036854775808
 *
 */
Test(arithmetic_tests, ipow__base_eq_min){
    uint64_t res = ipow(-9223372036854775808,1);
    uint64_t ex = -9223372036854775808;
    cr_assert_eq(res, ex);
}

/*
 * testing boundry value exp = 0
 *
 * in: base = 5, exp = 0
 * expected = 1
 *
 */
Test(arithmetic_tests, ipow__exp_eq_0){
    uint64_t res = ipow(5,0);
    uint64_t ex = 1;
    cr_assert_eq(res, ex);
}

/*
 * testing boundry value exp = 0
 *
 * in: base = 1, exp = 18446744073709551615
 * expected = 1
 *
 */
Test(arithmetic_tests, ipow__exp_eq_max){
    uint64_t res = ipow(1,18446744073709551615);
    uint64_t ex = 1;
    cr_assert_eq(res, ex);
}


/**
 * Tests for bstd_number* bstd_sum(bstd_number *lhs, const bstd_number *rhs)
 *
 * Equivalence classes:
 * +-----------------------+-------------------------+--------------------------------------+
 * |       Condition       |          Valid          |               Invalid                |
 * +-----------------------+-------------------------+--------------------------------------+
 * | Value of lhs.value    | 0 <= lhs.value <= 9(9)  | lhs.value < 0, lhs.value > 9(9)      |
 * | Value of lhs.scale    | 0 <= lhs.scale <= 9     | lhs.scale < 0, lhs.scale > 9         |
 * | Value of lhs.length   | 1 <= lhs.length <= 9    | lhs.length < 0, lhs.length > 9       |
 * | Value of lhs.isSigned | lhs.isSigned = false,   |                                      |
 * |                       | lhs.isSigned = true     |                                      |
 * | Value of lhs.positive | lhs.positive = false,   |                                      |
 * |                       | lhs.positive = true     |                                      |
 * | Relation              | lhs.isSigned = true &&  | lhs.isSigned = false &&              |
 * |                       | lhs.positive = false,   | lhs.positive = false                 |
 * |                       | lhs.isSigned = false && |                                      |
 * |                       | lhs.positive = true,    |                                      |
 * |                       | lhs.isSigned = true &&  |                                      |
 * |                       | lhs.positive = true     |                                      |
 * | Value of rhs.value    | 0 <= rhs.value <= 9(9)  | rhs.value < 0, rhs.value > 9(9)      |
 * | Value of rhs.scale    | 0 <= rhs.scale <= 9     | rhs.scale < 0, rhs.scale > 9         | 
 * | Value of rhs.length   | 1 <= rhs.length <= 9    | rhs.length < 0, rhs.length > 9       |
 * | Value of rhs.isSigned | rhs.isSigned = false,   |                                      |
 * |                       | rhs.isSigned = true     |                                      |
 * | Value of rhs.positive | rhs.positive = false,   |                                      |
 * |                       | rhs.positive = true     |                                      |
 * | Relation              | lhs.isSigned = true &&  | rhs.isSigned = false &&              |
 * |                       | lhs.positive = false,   | rhs.positive = false                 |
 * |                       | lhs.isSigned = false && |                                      |
 * |                       | lhs.positive = true,    |                                      |
 * |                       | lhs.isSigned = true &&  |                                      |
 * |                       | lhs.positive = true     |                                      |
 * +-----------------------+-------------------------+--------------------------------------+
 *
*/

//valid classes tests

/*
 * Testing valid conditions:
 *
 * 0 <= lhs.value <= 999999999,
 * 0 <= lhs.scale <= 9,
 * 1 <= lhs.length <= 9,
 * lhs.isSigned = false,
 * lhs.positive = true,
 * lhs.isSigned = false && lhs.positive = true
 *
 * 0 <= rhs.value <= 999999999,
 * 0 <= rhs.scale <= 9,
 * 1 <= rhs.length <= 9,
 * rhs.isSigned = false,
 * rhs.positive = true,
 * rhs.isSigned = false && rhs.positive = true
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5556234;
 * ex.scale = 6;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_sum__pos_unsigned){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556234;
    ex.scale = 6;
    ex.length = 7;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 * Testing valid conditions:
 *
 * 0 <= lhs.value <= 999999999,
 * 0 <= lhs.scale <= 9,
 * 1 <= lhs.length <= 9,
 * lhs.isSigned = true,
 * lhs.positive = true,
 * lhs.isSigned = true && lhs.positive = true
 *
 *  0 <= rhs.value <= 999999999,
 * 0 <= rhs.scale <= 9,
 * 1 <= rhs.length <= 9,
 * rhs.isSigned = true,
 * rhs.positive = true,
 * rhs.isSigned = true && rhs.positive = true
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = true;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = true;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5556234;
 * ex.scale = 6;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_sum__pos_signed_pos){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = true;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = true;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556234;
    ex.scale = 6;
    ex.length = 7;
    ex.isSigned = false;
    ex.positive = true;


    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 * Testing valid conditions:
 *
 * 0 <= lhs.value <= 999999999,
 * 0 <= lhs.scale <= 9,
 * 1 <= lhs.length <= 9,
 * lhs.isSigned = true,
 * lhs.positive = false,
 * lhs.isSigned = true && lhs.positive = false
 *
 * 0 <= rhs.value <= 999999999,
 * 0 <= rhs.scale <= 9,
 * 1 <= rhs.length <= 9,
 * rhs.isSigned = true,
 * rhs.positive = false,
 * rhs.isSigned = true && rhs.positive = false
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = true;
 * lhs.positive = false;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = true;
 * rhs.positive = false;
 *
 * expected:
 * ex.value = 5556234;
 * ex.scale = 6;
 * ex.length = 7;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(arithmetic_tests, bstd_sum__pos_signed_neg){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = true;
    lhs.positive = false;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = true;
    rhs.positive = false;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556234;
    ex.scale = 6;
    ex.length = 7;
    ex.isSigned = true;
    ex.positive = false;


    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 * Testing valid conditions:
 *
 * 0 <= lhs.value <= 999999999,
 * 0 <= lhs.scale <= 9,
 * 1 <= lhs.length <= 9,
 * lhs.isSigned = true,
 * lhs.positive = true,
 * lhs.isSigned = true && lhs.positive = true
 *
 * 0 <= rhs.value <= 999999999,
 * 0 <= rhs.scale <= 9,
 * 1 <= rhs.length <= 9,
 * rhs.isSigned = true,
 * rhs.positive = false,
 * rhs.isSigned = true && rhs.positive = false
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = true;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = true;
 * rhs.positive = false;
 *
 * expected:
 * ex.value = 5553766;
 * ex.scale = 6;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_sum__lhs_pos_rhs_neg){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = true;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = true;
    rhs.positive = false;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5553766;
    ex.scale = 6;
    ex.length = 7;
    ex.isSigned = false;
    ex.positive = true;


    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 * Testing valid conditions:
 *
 * 0 <= lhs.value <= 999999999,
 * 0 <= lhs.scale <= 9,
 * 1 <= lhs.length <= 9,
 * lhs.isSigned = true,
 * lhs.positive = false,
 * lhs.isSigned = true && lhs.positive = false
 *
 * 0 <= rhs.value <= 999999999,
 * 0 <= rhs.scale <= 9,
 * 1 <= rhs.length <= 9,
 * rhs.isSigned = true,
 * rhs.positive = true,
 * rhs.isSigned = true && rhs.positive = true
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = true;
 * lhs.positive = false;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = true;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5553766;
 * ex.scale = 6;
 * ex.length = 7;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(arithmetic_tests, bstd_sum__lhs_neg_rhs_pos){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = true;
    lhs.positive = false;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = true;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5553766;
    ex.scale = 6;
    ex.length = 7;
    ex.isSigned = true;
    ex.positive = false;


    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

// boundary value analysis for lhs

/*
 *
 * testing boundary value lhs.value = 0
 *
 * in:
 * lhs.value = 0;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 6;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(arithmetic_tests, bstd_sum__lhs_value_eq_0){
    bstd_number lhs;
    lhs.value = 0;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 6;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 *
 * testing boundary value lhs.value = 9(9) with values using differing scales.
 *
 * in:
 * lhs.value = 999999999;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 0;
 * ex.scale = 3;
 * ex.length = 13;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(arithmetic_tests, bstd_sum__lhs_value_eq_max_differing_scales){
    bstd_number lhs;
    lhs.value = 999999999;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 1000000000234;
    ex.scale = 6;
    ex.length = 13;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 *
 * testing boundary value lhs.value = 9(9) with values using same scales.
 *
 * in:
 * lhs.value = 999999999;
 * lhs.scale = 3;
 * lhs.length = 9;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 3;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 1000001233;
 * ex.scale = 3;
 * ex.length = 10;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(arithmetic_tests, bstd_sum__lhs_value_eq_max_same_scales){
    bstd_number lhs;
    lhs.value = 999999999;
    lhs.scale = 3;
    lhs.length = 9;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 3;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 1000001233;
    ex.scale = 3;
    ex.length = 10;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 * testing boundary value lhs.scale = 0
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 0;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5555001234;
 * ex.scale = 6;
 * ex.length = 10;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_sum__lhs_scale_eq_0){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 0;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5555001234;
    ex.scale = 6;
    ex.length = 10;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 * testing boundary value lhs.scale = 9
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 9;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 1239555;
 * ex.scale = 9;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_sum__lhs_scale_eq_9){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 9;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 1239555;
    ex.scale = 9;
    ex.length = 7;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 * testing boundary value lhs.length = 1
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 1;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5556234;
 * ex.scale = 6;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_sum__lhs_length_eq_1){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 0;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556234;
    ex.scale = 6;
    ex.length = 7;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 * testing boundary value lhs.length = 9
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 9;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5556234;
 * ex.scale = 6;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_sum__lhs_length_eq_9){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 9;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556234;
    ex.scale = 6;
    ex.length = 7;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

// boundary value analysis for rhs

/*
 *
 * testing boundary value rhs.value = 0
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 0;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5555000;
 * ex.scale = 6;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(arithmetic_tests, bstd_sum__rhs_value_eq_0){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 0;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5555000;
    ex.scale = 6;
    ex.length = 7;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 *
 * testing boundary value lhs.value = 9(9) with values using differing scales.
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 999999999;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 1005554999;
 * ex.scale = 6;
 * ex.length = 10;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(arithmetic_tests, bstd_sum__rhs_value_eq_max_differing_scales){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 999999999;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 1005554999;
    ex.scale = 6;
    ex.length = 10;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 *
 * testing boundary value rhs.value = 9(9) with values using same scales.
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 9;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 9999999999;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 1000005554;
 * ex.scale = 3;
 * ex.length = 10;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(arithmetic_tests, bstd_sum__rhs_value_eq_max_same_scales){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 999999999;
    rhs.scale = 3;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 1000005554;
    ex.scale = 3;
    ex.length = 10;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 * testing boundary value lhs.scale = 0
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 0;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 1239555;
 * ex.scale = 3;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_sum__rhs_scale_eq_0){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 0;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 1239555;
    ex.scale = 3;
    ex.length = 7;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 * testing boundary value lhs.scale = 9
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 9;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5555001234;
 * ex.scale = 9;
 * ex.length = 10;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_sum__rhs_scale_eq_9){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 9;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5555001234;
    ex.scale = 9;
    ex.length = 10;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 * testing boundary value rhs.length = 1
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 1;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5556234;
 * ex.scale = 6;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_sum__rhs_length_eq_1){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 1;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556234;
    ex.scale = 6;
    ex.length = 7;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}

/*
 * testing boundary value rhs.length = 9
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 9;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5556234;
 * ex.scale = 6;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_sum__rhs_length_eq_9){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 9;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_number* res = bstd_sum(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556234;
    ex.scale = 6;
    ex.length = 7;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, res->value);
    cr_assert_eq(ex.scale, res->scale);
    cr_assert_eq(ex.length, res->length);
    cr_assert_eq(ex.isSigned, res->isSigned);
    cr_assert_eq(ex.positive, res->positive);

    free(res);
}



/**
 * Tests for void bstd_add(bstd_number *lhs, const bstd_number *rhs)
 *
 * Equivalence classes:
 * +-----------------------+-------------------------+--------------------------------------+
 * |       Condition       |          Valid          |               Invalid                |
 * +-----------------------+-------------------------+--------------------------------------+
 * | Value of lhs.value    | 0 <= lhs.value <= 9(9)  | lhs.value < 0, lhs.value > 9(9)      |
 * | Value of lhs.scale    | 0 <= lhs.scale <= 9     | lhs.scale < 0, lhs.scale > 9         |
 * | Value of lhs.length   | 1 <= lhs.length <= 9    | lhs.length < 0, lhs.length > 9       |
 * | Value of lhs.isSigned | lhs.isSigned = false,   |                                      |
 * |                       | lhs.isSigned = true     |                                      |
 * | Value of lhs.positive | lhs.positive = false,   |                                      |
 * |                       | lhs.positive = true     |                                      |
 * | Relation              | lhs.isSigned = true &&  | lhs.isSigned = false &&              |
 * |                       | lhs.positive = false,   | lhs.positive = false                 |
 * |                       | lhs.isSigned = false && |                                      |
 * |                       | lhs.positive = true,    |                                      |
 * |                       | lhs.isSigned = true &&  |                                      |
 * |                       | lhs.positive = true     |                                      |
 * | Value of rhs.value    | 0 <= rhs.value <= 9(9)  | rhs.value < 0, rhs.value > 9(9)      |
 * | Value of rhs.scale    | 0 <= rhs.scale <= 9     | rhs.scale < 0, rhs.scale > 9         |
 * | Value of rhs.length   | 1 <= rhs.length <= 9    | rhs.length < 0, rhs.length > 9       |
 * | Value of rhs.isSigned | rhs.isSigned = false,   |                                      |
 * |                       | rhs.isSigned = true     |                                      |
 * | Value of rhs.positive | rhs.positive = false,   |                                      |
 * |                       | rhs.positive = true     |                                      |
 * | Relation              | lhs.isSigned = true &&  | rhs.isSigned = false &&              |
 * |                       | lhs.positive = false,   | rhs.positive = false                 |
 * |                       | lhs.isSigned = false && |                                      |
 * |                       | lhs.positive = true,    |                                      |
 * |                       | lhs.isSigned = true &&  |                                      |
 * |                       | lhs.positive = true     |                                      |
 * +-----------------------+-------------------------+--------------------------------------+
 *
*/

//valid classes tests

/*
 * Testing valid conditions:
 *
 * 0 <= lhs.value <= 999999999,
 * 0 <= lhs.scale <= 9,
 * 1 <= lhs.length <= 9,
 * lhs.isSigned = false,
 * lhs.positive = true,
 * lhs.isSigned = false && lhs.positive = true
 *
 * 0 <= rhs.value <= 999999999,
 * 0 <= rhs.scale <= 9,
 * 1 <= rhs.length <= 9,
 * rhs.isSigned = false,
 * rhs.positive = true,
 * rhs.isSigned = false && rhs.positive = true
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * lhs.value = 5556;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 */
Test(arithmetic_tests, bstd_add__pos_unsigned){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, lhs.value);
    cr_assert_eq(ex.scale, lhs.scale);
    cr_assert_eq(ex.length, lhs.length);
    cr_assert_eq(ex.isSigned, lhs.isSigned);
    cr_assert_eq(ex.positive, lhs.positive);
}

/*
 * Testing valid conditions:
 *
 * 0 <= lhs.value <= 999999999,
 * 0 <= lhs.scale <= 9,
 * 1 <= lhs.length <= 9,
 * lhs.isSigned = true,
 * lhs.positive = true,
 * lhs.isSigned = true && lhs.positive = true
 *
 *  0 <= rhs.value <= 999999999,
 * 0 <= rhs.scale <= 9,
 * 1 <= rhs.length <= 9,
 * rhs.isSigned = true,
 * rhs.positive = true,
 * rhs.isSigned = true && rhs.positive = true
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = true;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = true;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5556;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_add__pos_signed_pos){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = true;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = true;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = true;


    cr_assert_eq(ex.value, lhs.value);
    cr_assert_eq(ex.scale, lhs.scale);
    cr_assert_eq(ex.length, lhs.length);
    cr_assert_eq(ex.isSigned, lhs.isSigned);
    cr_assert_eq(ex.positive, lhs.positive);
}

/*
 * Testing valid conditions:
 *
 * 0 <= lhs.value <= 999999999,
 * 0 <= lhs.scale <= 9,
 * 1 <= lhs.length <= 9,
 * lhs.isSigned = true,
 * lhs.positive = false,
 * lhs.isSigned = true && lhs.positive = false
 *
 * 0 <= rhs.value <= 999999999,
 * 0 <= rhs.scale <= 9,
 * 1 <= rhs.length <= 9,
 * rhs.isSigned = true,
 * rhs.positive = false,
 * rhs.isSigned = true && rhs.positive = false
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = true;
 * lhs.positive = false;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = true;
 * rhs.positive = false;
 *
 * expected:
 * ex.value = 5556;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(arithmetic_tests, bstd_add__pos_signed_neg){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = true;
    lhs.positive = false;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = true;
    rhs.positive = false;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = false;


    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);
}

/*
 * Testing valid conditions:
 *
 * 0 <= lhs.value <= 999999999,
 * 0 <= lhs.scale <= 9,
 * 1 <= lhs.length <= 9,
 * lhs.isSigned = true,
 * lhs.positive = true,
 * lhs.isSigned = true && lhs.positive = true
 *
 * 0 <= rhs.value <= 999999999,
 * 0 <= rhs.scale <= 9,
 * 1 <= rhs.length <= 9,
 * rhs.isSigned = true,
 * rhs.positive = false,
 * rhs.isSigned = true && rhs.positive = false
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = true;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = true;
 * rhs.positive = false;
 *
 * expected:
 * ex.value = 5553;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_add__lhs_pos_rhs_neg){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = true;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = true;
    rhs.positive = false;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5553;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = true;


    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);
}

/*
 * Testing valid conditions:
 *
 * 0 <= lhs.value <= 999999999,
 * 0 <= lhs.scale <= 9,
 * 1 <= lhs.length <= 9,
 * lhs.isSigned = true,
 * lhs.positive = false,
 * lhs.isSigned = true && lhs.positive = false
 *
 * 0 <= rhs.value <= 999999999,
 * 0 <= rhs.scale <= 9,
 * 1 <= rhs.length <= 9,
 * rhs.isSigned = true,
 * rhs.positive = true,
 * rhs.isSigned = true && rhs.positive = true
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = true;
 * lhs.positive = false;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = true;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5553;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(arithmetic_tests, bstd_add__lhs_neg_rhs_pos){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = true;
    lhs.positive = false;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = true;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5553;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = false;


    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);

}

// boundary value analysis for lhs

/*
 *
 * testing boundary value lhs.value = 0
 *
 * in:
 * lhs.value = 0;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 1;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(arithmetic_tests, bstd_add__lhs_value_eq_0){
    bstd_number lhs;
    lhs.value = 0;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 1;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);
}

/*
 *
 * testing boundary value lhs.value = 9(9) with values using differing scales.
 *
 * in:
 * lhs.value = 999999999;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 0;
 * ex.scale = 3;
 * ex.length = 13;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(arithmetic_tests, bstd_add__lhs_value_eq_max_differing_scales){
    bstd_number lhs;
    lhs.value = 999999999;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 0;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);
}

/*
 *
 * testing boundary value lhs.value = 9(9) with values using same scales.
 *
 * in:
 * lhs.value = 999999999;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 3;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 1233;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(arithmetic_tests, bstd_add__lhs_value_eq_max_same_scales){
    bstd_number lhs;
    lhs.value = 999999999;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 3;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 1233;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);
}

/*
 * testing boundary value lhs.scale = 0
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 0;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5555;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_add__lhs_scale_eq_0){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 0;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5555;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);

}

/*
 * testing boundary value lhs.scale = 9
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 9;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 9555;
 * ex.scale = 9;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_add__lhs_scale_eq_9){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 9;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 9555;
    ex.scale = 9;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);
}

/*
 * testing boundary value lhs.length = 0
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 1;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 6;
 * ex.scale = 3;
 * ex.length = 1;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_add__lhs_length_eq_1){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 1;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 6;
    ex.scale = 3;
    ex.length = 1;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);

}

/*
 * testing boundary value lhs.length = 9
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 9;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5556;
 * ex.scale = 3;
 * ex.length = 9;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_add__lhs_length_eq_9){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 9;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556;
    ex.scale = 3;
    ex.length = 9;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);

}

// boundary value analysis for rhs

/*
 *
 * testing boundary value rhs.value = 0
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 0;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5555000;
 * ex.scale = 6;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(arithmetic_tests, bstd_add__rhs_value_eq_0){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 0;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5555;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);

}

/*
 *
 * testing boundary value lhs.value = 9(9) with values using differing scales.
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 999999999;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5554;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(arithmetic_tests, bstd_add__rhs_value_eq_max_differing_scales){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 999999999;
    rhs.scale = 6;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5554;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);

}

/*
 *
 * testing boundary value lhs.value = 9(9) with values using same scales.
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 999999999;
 * rhs.scale = 6;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5554;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(arithmetic_tests, bstd_add__rhs_value_eq_max_same_scales){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 999999999;
    rhs.scale = 3;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5554;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);

}

/*
 * testing boundary value rhs.scale = 0
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 0;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 9555;
 * ex.scale = 3;
 * ex.length = 7;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_add__rhs_scale_eq_0){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 0;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 9555;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);

}

/*
 * testing boundary value lhs.scale = 9
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 9;
 * rhs.length = 7;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5555;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_add__rhs_scale_eq_9){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 9;
    rhs.length = 7;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5555;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);

}

/*
 * testing boundary value rhs.length = 0
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 0;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5556;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_add__rhs_length_eq_1){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 0;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);

}

/*
 * testing boundary value rhs.length = 9
 *
 * in:
 * lhs.value = 5555;
 * lhs.scale = 3;
 * lhs.length = 4;
 * lhs.isSigned = false;
 * lhs.positive = true;
 *
 * rhs.value = 1234;
 * rhs.scale = 6;
 * rhs.length = 9;
 * rhs.isSigned = false;
 * rhs.positive = true;
 *
 * expected:
 * ex.value = 5556;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(arithmetic_tests, bstd_add__rhs_length_eq_9){
    bstd_number lhs;
    lhs.value = 5555;
    lhs.scale = 3;
    lhs.length = 4;
    lhs.isSigned = false;
    lhs.positive = true;

    bstd_number rhs;
    rhs.value = 1234;
    rhs.scale = 6;
    rhs.length = 9;
    rhs.isSigned = false;
    rhs.positive = true;

    bstd_add(&lhs, &rhs);

    bstd_number ex;
    ex.value = 5556;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      lhs.value);
    cr_assert_eq(ex.scale,      lhs.scale);
    cr_assert_eq(ex.length,     lhs.length);
    cr_assert_eq(ex.isSigned,   lhs.isSigned);
    cr_assert_eq(ex.positive,   lhs.positive);

}