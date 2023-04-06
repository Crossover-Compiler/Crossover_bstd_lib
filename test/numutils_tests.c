#include <criterion/criterion.h>
#include "../include/numutils.h"

#ifndef BSTD_NUMBER_TEST_EPSILON
#define BSTD_NUMBER_TEST_EPSILON 1E-6
#endif


/**
 * Tests for int bstd_number_is_integer(const bstd_number* number)
 *
 * Equivalence classes:
 * +--------------------------+--------------------------------+--------------------------------------------+
 * | Condition                | Valid                          | Invalid                                    |
 * +--------------------------+--------------------------------+--------------------------------------------+
 * | Value of number.value    | 0 <= number.value <= 999999999 | number.value < 0, number.value > 999999999 |
 * | Value of number.scale    | 0 <= number.scale <= 9         | number.scale < 0, number.scale > 9         |
 * | Value of number.length   | 1 <= number.length <= 9        | number.length < 0, number.length > 9       |
 * | Value of number.isSigned | number.isSigned = false,       |                                            |
 * |                          | number.isSigned = true         |                                            |
 * | Value of number.positive | number.positive = false,       |                                            |
 * |                          | number.positive = true         |                                            |
 * | Relation                 | number.isSigned = true &&      | number.isSigned = false &&                 |
 * |                          | number.positive = false,       | number.positive = false                    |
 * |                          | number.isSigned = false &&     |                                            |
 * |                          | number.positive = true,        |                                            |
 * |                          | number.isSigned = true &&      |                                            |
 * |                          | number.positive = true         |                                            |
 * +--------------------------+--------------------------------+--------------------------------------------+
 *
 * */

//valid classes tests

/*
 * Testing valid conditions:
 *
 * 0 <= number.value <= 999999999,
 * 0 <= number.scale <= 9,
 * 1 <= number.length <= 9,
 * number.isSigned = false,
 * number.positive = true,
 * number.isSigned = false && number.positive = true
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * expected:
 * false
 *
 */
Test(numutils_tests, bstd_number_is_integer__pos_unsigned){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;
    
    
    bool res = bstd_number_is_integer(&number);
    
    cr_assert_eq(false, res);

}

/*
 * Testing valid conditions:
 *
 * 0 <= number.value <= 999999999,
 * 0 <= number.scale <= 9,
 * 1 <= number.length <= 9,
 * number.isSigned = true,
 * number.positive = true,
 * number.isSigned = true && number.positive = true
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = true;
 *
 * expected:
 * false
 *
 */
Test(numutils_tests, bstd_number_is_integer__signed_pos){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;
    
    bool res = bstd_number_is_integer(&number);

    cr_assert_eq(false, res);
}

/*
 * Testing valid conditions:
 *
 * 0 <= number.value <= 999999999,
 * 0 <= number.scale <= 9,
 * 1 <= number.length <= 9,
 * number.isSigned = true,
 * number.positive = false,
 * number.isSigned = true && number.positive = false
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = false;
 *
 *
 * expected:
 * false
 *
 */
Test(numutils_tests, bstd_number_is_integer__signed_neg){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = true;
    number.positive = false;

    bool res = bstd_number_is_integer(&number);

    cr_assert_eq(false, res);
}


// boundary value analysis for number

/*
 *
 * testing boundary value number.value = 0
 *
 * in:
 * number.value = 0;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * expected:
 * false
 */
Test(numutils_tests, bstd_number_is_integer__number_value_eq_0){
bstd_number number;
number.value = 0;
number.scale = 3;
number.length = 4;
number.isSigned = false;
number.positive = true;

bool res = bstd_number_is_integer(&number);

cr_assert_eq(false, res);
}

/*
 *
 * testing boundary value number.value = 9(9)
 *
 * in:
 * number.value = 999999999;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 *
 * expected:
 * false
 */
Test(numutils_tests, bstd_number_is_integer__number_value_eq_max){
bstd_number number;
number.value = 999999999;
number.scale = 3;
number.length = 4;
number.isSigned = false;
number.positive = true;


bool res = bstd_number_is_integer(&number);


cr_assert_eq(false, res);

}


/*
 * testing boundary value number.scale = 0
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 *
 * expected:
 * true
 *
 */
Test(numutils_tests, bstd_number_is_integer__number_scale_eq_0){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;


    bool res = bstd_number_is_integer(&number);


    cr_assert_eq(true, res);

}

/*
 * testing boundary value number.scale = 9
 *
 * in:
 * number.value = 5555;
 * number.scale = 9;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 *
 * expected:
 * false
 *
 */
Test(numutils_tests, bstd_number_is_integer__number_scale_eq_9){
bstd_number number;
number.value = 5555;
number.scale = 9;
number.length = 4;
number.isSigned = false;
number.positive = true;


bool res = bstd_number_is_integer(&number);


cr_assert_eq(false, res);

}

/*
 * testing boundary value number.length = 1
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 1;
 * number.isSigned = false;
 * number.positive = true;

 *
 * expected:
 * false
 */
Test(numutils_tests, bstd_number_is_integer__number_length_eq_1){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 0;
    number.isSigned = false;
    number.positive = true;


    bool res = bstd_number_is_integer(&number);

    cr_assert_eq(false, res);

}

/*
 * testing boundary value number.length = 9
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 9;
 * number.isSigned = false;
 * number.positive = true;
 *
 * expected:
 * false
 *
 */
Test(numutils_tests, bstd_number_is_integer__number_length_eq_9){
bstd_number number;
number.value = 5555;
number.scale = 3;
number.length = 9;
number.isSigned = false;
number.positive = true;


bool res = bstd_number_is_integer(&number);


cr_assert_eq(false, res);
}


/**
 * Tests for int64_t bstd_number_to_int(const bstd_number* number)
 *
 * Equivalence classes:
 * +--------------------------+--------------------------------+--------------------------------------------+
 * | Condition                | Valid                          | Invalid                                    |
 * +--------------------------+--------------------------------+--------------------------------------------+
 * | Value of number.value    | 0 <= number.value <= 999999999 | number.value < 0, number.value > 999999999 |
 * | Value of number.scale    | number.scale = 0               | number.scale < 0,                          |
 * |                          |                                | 1 <= number.scale <= 9                     |
 * | Value of number.length   | 1 <= number.length <= 9        | number.length < 0, number.length > 9       |
 * | Value of number.isSigned | number.isSigned = false,       |                                            |
 * |                          | number.isSigned = true         |                                            |
 * | Value of number.positive | number.positive = false,       |                                            |
 * |                          | number.positive = true         |                                            |
 * | Relation                 | number.isSigned = true &&      | number.isSigned = false &&                 |
 * |                          | number.positive = false,       | number.positive = false                    |
 * |                          | number.isSigned = false &&     |                                            |
 * |                          | number.positive = true,        |                                            |
 * |                          | number.isSigned = true &&      |                                            |
 * +--------------------------+--------------------------------+--------------------------------------------+
 * */

//valid classes tests

/*
 * Testing valid conditions:
 *
 * 0 <= number.value <= 999999999,
 * number.scale = 0,
 * 1 <= number.length <= 9,
 * number.isSigned = false,
 * number.positive = true,
 * number.isSigned = false && number.positive = true
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * expected:
 * 5555
 *
 */
Test(numutils_tests, bstd_number_to_int__pos_unsigned){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;


    int64_t res = bstd_number_to_int(&number);

    cr_assert_eq(5555, res);

}

/*
 * Testing valid conditions:
 *
 * 0 <= number.value <= 999999999,
 * number.scale = 0,
 * 1 <= number.length <= 9,
 * number.isSigned = true,
 * number.positive = true,
 * number.isSigned = true && number.positive = true
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = true;
 *
 * expected:
 * false
 *
 */
Test(numutils_tests, bstd_number_to_int__signed_pos){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;

    int64_t res = bstd_number_to_int(&number);

    cr_assert_eq(5555, res);
}

/*
 * Testing valid conditions:
 *
 * 0 <= number.value <= 999999999,
 * number.scale = 0,
 * 1 <= number.length <= 9,
 * number.isSigned = true,
 * number.positive = false,
 * number.isSigned = true && number.positive = false
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = false;
 *
 *
 * expected:
 * 5555
 *
 */
Test(numutils_tests, bstd_number_to_int__signed_neg){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = true;
    number.positive = false;

    int64_t res = bstd_number_to_int(&number);

    cr_assert_eq(-5555, res);
}

// boundary value analysis for number

/*
 *
 * testing boundary value number.value = 0
 *
 * in:
 * number.value = 0;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * expected:
 * 0
 */
Test(numutils_tests, bstd_number_to_int__number_value_eq_0){
    bstd_number number;
    number.value = 0;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    int64_t res = bstd_number_to_int(&number);

    cr_assert_eq(0, res);
}

/*
 *
 * testing boundary value number.value = 9(9)
 *
 * in:
 * number.value = 999999999;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 *
 * expected:
 * 999999999
 */
Test(numutils_tests, bstd_number_to_int__number_value_eq_max){
    bstd_number number;
    number.value = 999999999;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    uint64_t res = bstd_number_to_int(&number);
    cr_assert_eq(999999999, res);
}

/*
 * testing boundary value number.length = 1
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 1;
 * number.isSigned = false;
 * number.positive = true;

 *
 * expected:
 * 5
 */
Test(numutils_tests, bstd_number_to_int__number_length_eq_1){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 0;
    number.isSigned = false;
    number.positive = true;


    uint64_t res = bstd_number_to_int(&number);

    cr_assert_eq(5555, res);

}

/*
 * testing boundary value number.length = 9
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 9;
 * number.isSigned = false;
 * number.positive = true;
 *
 * expected:
 * false
 *
 */
Test(numutils_tests, bstd_number_to_int__number_length_eq_9){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 9;
    number.isSigned = false;
    number.positive = true;

    uint64_t res = bstd_number_to_int(&number);
    cr_assert_eq(5555, res);
}

/**
 * Tests for double bstd_number_to_double(const bstd_number* number)
 *
 * Equivalence classes:
 * +--------------------------+--------------------------------+--------------------------------------------+
 * | Condition                | Valid                          | Invalid                                    |
 * +--------------------------+--------------------------------+--------------------------------------------+
 * | Value of number.value    | 0 <= number.value <= 999999999 | number.value < 0, number.value > 999999999 |
 * | Value of number.scale    | 0 <= number.scale <= 9         | number.scale < 0, number.scale > 9         |
 * | Value of number.length   | 1 <= number.length <= 9        | number.length < 0, number.length > 9       |
 * | Value of number.isSigned | number.isSigned = false,       |                                            |
 * |                          | number.isSigned = true         |                                            |
 * | Value of number.positive | number.positive = false,       |                                            |
 * |                          | number.positive = true         |                                            |
 * | Relation                 | number.isSigned = true &&      | number.isSigned = false &&                 |
 * |                          | number.positive = false,       | number.positive = false                    |
 * |                          | number.isSigned = false &&     |                                            |
 * |                          | number.positive = true,        |                                            |
 * |                          | number.isSigned = true &&      |                                            |
 * |                          | number.positive = true         |                                            |
 * +--------------------------+--------------------------------+--------------------------------------------+
 *
 * */


//valid classes tests

/*
 * Testing valid conditions:
 *
 * 0 <= number.value <= 999999999,
 * 0 <= number.scale <= 9,
 * 1 <= number.length <= 9,
 * number.isSigned = false,
 * number.positive = true,
 * number.isSigned = false && number.positive = true
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * expected:
 * 5.555
 *
 */
Test(numutils_tests, bstd_number_to_double__pos_unsigned){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;


    double res = bstd_number_to_double(&number);

    cr_assert_float_eq(5.555, res, BSTD_NUMBER_TEST_EPSILON);

}

/*
 * Testing valid conditions:
 *
 * 0 <= number.value <= 999999999,
 * 0 <= number.scale <= 9,
 * 1 <= number.length <= 9,
 * number.isSigned = true,
 * number.positive = true,
 * number.isSigned = true && number.positive = true
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = true;
 *
 * expected:
 * 5.555
 *
 */
Test(numutils_tests, bstd_number_to_double__signed_pos){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;

    double res = bstd_number_to_double(&number);

    cr_assert_float_eq(5.555, res, BSTD_NUMBER_TEST_EPSILON);
}

/*
 * Testing valid conditions:
 *
 * 0 <= number.value <= 999999999,
 * 0 <= number.scale <= 9,
 * 1 <= number.length <= 9,
 * number.isSigned = true,
 * number.positive = false,
 * number.isSigned = true && number.positive = false
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = false;
 *
 *
 * expected:
 * -5.555
 *
 */
Test(numutils_tests, bstd_number_to_double__signed_neg){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = true;
    number.positive = false;

    double res = bstd_number_to_double(&number);

    cr_assert_float_eq(-5.555, res, BSTD_NUMBER_TEST_EPSILON);
}


// boundary value analysis for number

/*
 *
 * testing boundary value number.value = 0
 *
 * in:
 * number.value = 0;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * expected:
 * false
 */
Test(numutils_tests, bstd_number_to_double__number_value_eq_0){
    bstd_number number;
    number.value = 0;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    double res = bstd_number_to_double(&number);

    cr_assert_float_eq(0, res, BSTD_NUMBER_TEST_EPSILON);
}

/*
 *
 * testing boundary value number.value = 9(9)
 *
 * in:
 * number.value = 999999999;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 *
 * expected:
 * 999999.999
 */
Test(numutils_tests, bstd_number_to_double__number_value_eq_max){
    bstd_number number;
    number.value = 999999999;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    double res = bstd_number_to_double(&number);
    cr_assert_float_eq(999999.999, res, BSTD_NUMBER_TEST_EPSILON);
}


/*
 * testing boundary value number.scale = 0
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 *
 * expected:
 * 5555.0
 *
 */
Test(numutils_tests, bstd_number_to_double__number_scale_eq_0){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    double res = bstd_number_to_double(&number);
    cr_assert_float_eq(5555.0, res, BSTD_NUMBER_TEST_EPSILON);
}

/*
 * testing boundary value number.scale = 9
 *
 * in:
 * number.value = 5555;
 * number.scale = 9;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 *
 * expected:
 * 0.000005555
 *
 */
Test(numutils_tests, bstd_number_to_double__number_scale_eq_9){
    bstd_number number;
    number.value = 5555;
    number.scale = 9;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    double res = bstd_number_to_double(&number);
    cr_assert_float_eq(0.000005555, res, BSTD_NUMBER_TEST_EPSILON);

}

/*
 * testing boundary value number.length = 1
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 1;
 * number.isSigned = false;
 * number.positive = true;

 *
 * expected:
 * 5.555
 */
Test(numutils_tests, bstd_number_to_double__number_length_eq_1){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 0;
    number.isSigned = false;
    number.positive = true;

    double res = bstd_number_to_double(&number);
    cr_assert_float_eq(5.555, res, BSTD_NUMBER_TEST_EPSILON);
}

/*
 * testing boundary value number.length = 9
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 9;
 * number.isSigned = false;
 * number.positive = true;
 *
 * expected:
 * 5.555
 *
 */
Test(numutils_tests, bstd_number_to_double__number_length_eq_9){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 9;
    number.isSigned = false;
    number.positive = true;

    double res = bstd_number_to_double(&number);
    cr_assert_float_eq(5.555, res, BSTD_NUMBER_TEST_EPSILON);
}