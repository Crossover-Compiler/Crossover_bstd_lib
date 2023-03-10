#include <criterion/criterion.h>
#include "../include/numutils.h"
#include "../include/arithmetic.h"

/*
 * bstd_assign_int
 */

Test(number_tests, number_assign_int__integer_to_number_int){

    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 0;
    n.positive = true;
    n.value = 123;

    const int expected = 456;

    bstd_assign_int(&n, expected);

    const int result = bstd_number_to_int(&n);

    cr_assert_eq(result, expected, "result: %d, | expected: %d", result, expected);
}

Test(number_tests, number_assign_int__integer_to_number_dec){

    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 1;
    n.positive = true;
    n.value = 123;

    const int in = 456;

    bstd_assign_int(&n, in);

    const double result = bstd_number_to_double(&n);
    const double expected = 45.6;

    cr_assert_float_eq(result, expected, 1E-6, "result: %f, | expected: %f", result, expected);
}

/*
 * bstd_assign_double
 */

Test(number_tests, number_assign_double__double_to_number_dec){

    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 1;
    n.positive = true;
    n.value = 123;

    const double expected = 45.6;

    bstd_assign_double(&n, expected);

    const double result = bstd_number_to_double(&n);

    cr_assert_float_eq(result, expected, 1E-6, "result: %f, | expected: %f", result, expected);
}

Test(number_tests, number_assign_double__double_to_number_int){

    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 0;
    n.positive = true;
    n.value = 123;

    const double in = 45.6;

    bstd_assign_double(&n, in);

    const int result = bstd_number_to_int(&n);
    const int expected = 45;

    cr_assert_eq(result, expected, "result: %d, | expected: %d", result, expected);
}

Test(number_tests, number_assign_double__smaller_double_to_number_dec){

    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 1;
    n.positive = true;
    n.value = 123;

    const double expected = 9;

    bstd_assign_double(&n, expected);

    const double result = bstd_number_to_double(&n);

    cr_assert_float_eq(result, expected, 1E-6, "result: %f, | expected: %f", result, expected);
}

/**
 * Test for bstd_number sum (basic)
 */
Test(number_tests, number_sum_basic){
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

    bstd_number o = *bstd_sum(&n, &m);

    bstd_number expected;
    expected.length = 3;
    expected.scale = 2;
    expected.isSigned = false;
    expected.positive = true;
    expected.value = 810;

    cr_assert_eq(o.length,expected.length);
    cr_assert_eq(o.scale, expected.scale);
    cr_assert_eq(o.isSigned, expected.isSigned);
    cr_assert_eq(o.positive, expected.positive);
    cr_assert_eq(o.value, expected.value);
}

Test(number_tests, number_sum_different_scale) {
    
    // given two numbers of a different scale...
    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 2;
    n.positive = true;
    n.value = 777;
    
    bstd_number m;
    m.isSigned = false;
    m.length = 3;
    m.scale = 1;
    m.positive = true;
    m.value = 33;
    
    // ... when we add one number the other...
    bstd_number o = *bstd_sum(&n, &m);
    
    // ... then we expect the resulting value to be correct.
    bstd_number expected;
    expected.length = 4;
    expected.scale = 2;
    expected.isSigned = false;
    expected.positive = true;
    expected.value = 1107;

    cr_assert_eq(o.length, expected.length);
    cr_assert_eq(o.scale, expected.scale);
    cr_assert_eq(o.isSigned, expected.isSigned);
    cr_assert_eq(o.positive, expected.positive);
    cr_assert_eq(o.value, expected.value);
}

/**
 * A more interesting test for bstd_number sum
 */
Test(number_tests, number_sum){
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

    bstd_number o = *bstd_sum(&n, &m);

    bstd_number expected;
    expected.length = 3;
    expected.scale = 2;
    expected.isSigned = false;
    expected.positive = true;
    expected.value = 744;

    cr_assert_eq(o.length,expected.length);
    cr_assert_eq(o.scale, expected.scale);
    cr_assert_eq(o.isSigned, expected.isSigned);
    cr_assert_eq(o.positive, expected.positive);
    cr_assert_eq(o.value, expected.value);
}

/**
 * A more interesting test for bstd_number sum
 */
Test(number_tests, number_sum_negative_lhs){
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

    bstd_number o = *bstd_sum(&n, &m);

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
 * A more interesting test for bstd_number sum
 */
Test(number_tests, number_sum_negative_lhs_unsigned_rhs){
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

    bstd_number o = *bstd_sum(&n, &m);

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

/*
 * bstd_add
 */

Test(number_tests, number_add__same_length){

    // given two numbers of the same constraints...
    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 2;
    n.positive = true;
    n.value = 777;

    bstd_number m;
    m.isSigned = false;
    m.length = 3;
    m.scale = 2;
    m.positive = true;
    m.value = 33;

    // ... when we add one number to another...
    bstd_add(&n, &m);

    // ... then we expect the right-hand side number to be added to the left-hand side number, maintaining the left-hand side's constraints.
    bstd_number expected;
    expected.length = 3;
    expected.scale = 2;
    expected.isSigned = false;
    expected.positive = true;
    expected.value = 810;

    cr_assert_eq(n.length,expected.length);
    cr_assert_eq(n.scale, expected.scale);
    cr_assert_eq(n.isSigned, expected.isSigned);
    cr_assert_eq(n.positive, expected.positive);
    cr_assert_eq(n.value, expected.value);
}

Test(number_tests, number_add__different_scale){

    // given two numbers of a different scale...
    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 2;
    n.positive = true;
    n.value = 777;

    bstd_number m;
    m.isSigned = false;
    m.length = 3;
    m.scale = 1;
    m.positive = true;
    m.value = 33;

    // ... when we add one number the other...
    bstd_add(&n, &m);

    // ... then we expect the right-hand side number to be added to the left-hand side number, maintaining the left-hand side's constraints.
    bstd_number expected;
    expected.length = 3;
    expected.scale = 2;
    expected.isSigned = false;
    expected.positive = true;
    expected.value = 107;

    cr_assert_eq(n.length,expected.length);
    cr_assert_eq(n.scale, expected.scale);
    cr_assert_eq(n.isSigned, expected.isSigned);
    cr_assert_eq(n.positive, expected.positive);
    cr_assert_eq(n.value, expected.value, "result: %ld | expected: %ld", n.value, expected.value);
}

Test(number_tests, number_add__different_length){

    // given two numbers of a different length...
    bstd_number n;
    n.isSigned = false;
    n.length = 2;
    n.scale = 2;
    n.positive = true;
    n.value = 77;

    bstd_number m;
    m.isSigned = false;
    m.length = 3;
    m.scale = 2;
    m.positive = true;
    m.value = 33;

    // ... when we add one number the other...
    bstd_add(&n, &m);

    // ... then we expect the right-hand side number to be added to the left-hand side number, maintaining the left-hand side's constraints.
    bstd_number expected;
    expected.length = 2;
    expected.scale = 2;
    expected.isSigned = false;
    expected.positive = true;
    expected.value = 10;

    cr_assert_eq(n.length,expected.length);
    cr_assert_eq(n.scale, expected.scale);
    cr_assert_eq(n.isSigned, expected.isSigned);
    cr_assert_eq(n.positive, expected.positive);
    cr_assert_eq(n.value, expected.value);
}

/*
 * bstd_assign_number
 */

Test(number_tests, assign_number__same_constraints){

    // given two numbers of the same constraints...
    bstd_number n;
    n.isSigned = false;
    n.length = 3;
    n.scale = 2;
    n.positive = true;
    n.value = 777;

    bstd_number m;
    m.isSigned = false;
    m.length = 3;
    m.scale = 2;
    m.positive = true;
    m.value = 33;

    // ... when we assign one number the other...
    bstd_assign_number(&n, &m);

    // ... then we expect the right-hand side number to be assigned to the left-hand side number, maintaining the left-hand side's constraints.
    bstd_number expected;
    expected.length = 3;
    expected.scale = 2;
    expected.isSigned = false;
    expected.positive = true;
    expected.value = 33;

    cr_assert_eq(n.length,expected.length);
    cr_assert_eq(n.scale, expected.scale);
    cr_assert_eq(n.isSigned, expected.isSigned);
    cr_assert_eq(n.positive, expected.positive);
    cr_assert_eq(n.value, expected.value);
}

Test(number_tests, assign_number__different_length){

    // todo: implement
//
//    // given two numbers of the same constraints...
//    bstd_number n;
//    n.isSigned = false;
//    n.length = 3;
//    n.scale = 2;
//    n.positive = true;
//    n.value = 777;
//
//    bstd_number m;
//    m.isSigned = false;
//    m.length = 3;
//    m.scale = 2;
//    m.positive = true;
//    m.value = 33;
//
//    // ... when we assign one number the other...
//    bstd_assign_number(&n, &m);
//
//    // ... then we expect the right-hand side number to be assigned to the left-hand side number, maintaining the left-hand side's constraints.
//    bstd_number expected;
//    expected.length = 3;
//    expected.scale = 2;
//    expected.isSigned = false;
//    expected.positive = true;
//    expected.value = 33;
//
//    cr_assert_eq(n.length,expected.length);
//    cr_assert_eq(n.scale, expected.scale);
//    cr_assert_eq(n.isSigned, expected.isSigned);
//    cr_assert_eq(n.positive, expected.positive);
//    cr_assert_eq(n.value, expected.value);
}
