#include <criterion/criterion.h>
#include "../include/numutils.h"
#include "../include/arithmetic.h"

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
