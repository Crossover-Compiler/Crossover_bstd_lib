#include <criterion/criterion.h>
#include "../include/numutils.h"
#include "../include/arithmetic.h"

#ifndef BSTD_NUMBER_TEST_EPSILON
#define BSTD_NUMBER_TEST_EPSILON 1E-6
#endif

/**
 * Test for bstd_number addition (basic)
 */
Test(number_tests, number_addition_basic){
    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 2;
    n.positive = true;
    n.value = 777;

    bstd_number m;
    m.isSigned = true;
    m.length = 3;
    m.scale = 2;
    m.positive = true;
    m.value = 33;

    bstd_number o = *bstd_add(&n, &m);

    bstd_number expected;
    expected.length = 3;
    expected.scale = 2;
    expected.isSigned = true;
    expected.positive = true;
    expected.value = 810;

    cr_assert_eq(o.length,expected.length);
    cr_assert_eq(o.scale, expected.scale);
    cr_assert_eq(o.isSigned, expected.isSigned);
    cr_assert_eq(o.positive, expected.positive);
    cr_assert_eq(o.value, expected.value);
}


/**
 * A more interesting test for bstd_number addition
 */
Test(number_tests, number_addition){
    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 2;
    n.positive = true;
    n.value = 777;

    bstd_number m;
    m.isSigned = true;
    m.length = 3;
    m.scale = 2;
    m.positive = false;
    m.value = 33;

    bstd_number o = *bstd_add(&n, &m);

    bstd_number expected;
    expected.length = 3;
    expected.scale = 2;
    expected.isSigned = true;
    expected.positive = true;
    expected.value = 744;

    cr_assert_eq(o.length,expected.length);
    cr_assert_eq(o.scale, expected.scale);
    cr_assert_eq(o.isSigned, expected.isSigned);
    cr_assert_eq(o.positive, expected.positive);
    cr_assert_eq(o.value, expected.value);
}

/**
 * A more interesting test for bstd_number addition
 */
Test(number_tests, number_addition_negative_lhs){
    bstd_number n;
    n.isSigned = true;
    n.length = 3;
    n.scale = 2;
    n.positive = false;
    n.value = 777;

    bstd_number m;
    m.isSigned = true;
    m.length = 3;
    m.scale = 2;
    m.positive = true;
    m.value = 33;

    bstd_number o = *bstd_add(&n, &m);

    bstd_number expected;
    expected.length = 3;
    expected.scale = 2;
    expected.isSigned = true;
    expected.positive = false;
    expected.value = 744;

    cr_assert_eq(o.length,expected.length);
    cr_assert_eq(o.scale, expected.scale);
    cr_assert_eq(o.isSigned, expected.isSigned);
    cr_assert_eq(o.positive, expected.positive);
    cr_assert_eq(o.value, expected.value);
}


/**
 * A more interesting test for bstd_number addition
 */
Test(number_tests, number_addition_negative_lhs_unsigned_rhs){
    bstd_number n;
    n.isSigned = true;
    n.length = 3;
    n.scale = 2;
    n.positive = false;
    n.value = 777;

    bstd_number m;
    m.isSigned = false;
    m.length = 3;
    m.scale = 2;
    m.positive = true;
    m.value = 33;

    bstd_number o = *bstd_add(&n, &m);

    bstd_number expected;
    expected.length = 3;
    expected.scale = 2;
    expected.isSigned = false;
    expected.positive = false;
    expected.value = 744;

    cr_assert_eq(o.length,expected.length);
    cr_assert_eq(o.scale, expected.scale);
    cr_assert_eq(o.isSigned, expected.isSigned);
    cr_assert_eq(o.positive, expected.positive);
    cr_assert_eq(o.value, expected.value);
}

/*
 * bstd_assign_double
 */

Test(number_tests, number_assign_double__same_cardinality){

    // given a well-formed number and a constant double of the same cardinality...
    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 1;
    n.positive = true;
    n.value = 0;

    const double expected = 12.3;

    // ... when we assign that double to the number...
    bstd_assign_double(&n, expected);

    // ... then the decimal representation of the number must equal the constant double we assigned.
    const double result = bstd_number_to_double(&n);
    cr_assert_float_eq(result, expected, BSTD_NUMBER_TEST_EPSILON, "result: %f | expected: %f", result, expected);
}

Test(number_tests, number_assign_double__larger_integer_part){

    // given a well-formed number and a constant double of a larger cardinality in the integer part...
    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 1;
    n.positive = true;
    n.value = 0;

    const double in = 1234.5;

    // ... when we assign that double to the number...
    bstd_assign_double(&n, in);

    // ... then the decimal representation of the number must equal the last part of the larger integer part.
    const double result = bstd_number_to_double(&n);
    const double expected = 34.5;
    cr_assert_float_eq(result, expected, BSTD_NUMBER_TEST_EPSILON, "result: %f | expected: %f", result, expected);
}

Test(number_tests, number_assign_double__larger_decimal_part){

    // given a well-formed number and a constant double of a larger cardinality in the decimal part...
    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 1;
    n.positive = true;
    n.value = 0;

    const double in = 12.345;

    // ... when we assign that double to the number...
    bstd_assign_double(&n, in);

    // ... then the decimal representation of the number must equal the first part of the larger decimal part.
    const double result = bstd_number_to_double(&n);
    const double expected = 12.3;
    cr_assert_float_eq(result, expected, BSTD_NUMBER_TEST_EPSILON, "result: %f | expected: %f", result, expected);
}
