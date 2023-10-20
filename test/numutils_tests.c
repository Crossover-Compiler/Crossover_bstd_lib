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
    number.length = 1;
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
 * number.length = 9;
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
    number.scale = 0;
    number.length = 9;
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
    number.value = 5;
    number.scale = 0;
    number.length = 1;
    number.isSigned = false;
    number.positive = true;


    uint64_t res = bstd_number_to_int(&number);

    cr_assert_eq(5, res);

}

/*
 * testing boundary value number.length = 9
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
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
    number.scale = 0;
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
    number.length = 1;
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


/**
 * Tests for char *bstd_number_to_cstr(const bstd_number number)
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
 * "5.555"
 *
 */
Test(numutils_tests, bstd_number_to_cstr__pos_unsigned){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;


    char* res = bstd_number_to_cstr(number);

    cr_assert_str_eq("5.555", res);

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
 * "5.555"
 *
 */
Test(numutils_tests, bstd_number_to_cstr__signed_pos){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;

    char* res = bstd_number_to_cstr(number);

    cr_assert_str_eq(res, "+5.555");
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
 * "5.555"
 *
 */
Test(numutils_tests, bstd_number_to_cstr__signed_neg){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = true;
    number.positive = false;

    char* res = bstd_number_to_cstr(number);

    cr_assert_str_eq(res, "-5.555");
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
 * "0.000"
 */
Test(numutils_tests, bstd_number_to_cstr__number_value_eq_0){
    bstd_number number;
    number.value = 0;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    char* res = bstd_number_to_cstr(number);

    cr_assert_str_eq("0.000", res);
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
 * "9.999"
 */
Test(numutils_tests, bstd_number_to_cstr__number_value_eq_max){
    bstd_number number;
    number.value = 999999999;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    char* res = bstd_number_to_cstr(number);
    cr_assert_str_eq("9.999" , res);
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
 * "5555"
 *
 */
Test(numutils_tests, bstd_number_to_cstr__number_scale_eq_0){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    char* res = bstd_number_to_cstr(number);
    cr_assert_str_eq("5555", res);
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
Test(numutils_tests, bstd_number_to_cstr__number_scale_eq_9){
    bstd_number number;
    number.value = 5555;
    number.scale = 9;
    number.length = 9;
    number.isSigned = false;
    number.positive = true;

    char* res = bstd_number_to_cstr(number);
    cr_assert_str_eq(res, ".000005555");

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
 * "5"
 */
Test(numutils_tests, bstd_number_to_cstr__number_length_eq_1){
    bstd_number number;
    number.value = 5;
    number.scale = 0;
    number.length = 1;
    number.isSigned = false;
    number.positive = true;

    char* res = bstd_number_to_cstr(number);
    cr_assert_str_eq("5", res);
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
 * "000005.555"
 *
 */
Test(numutils_tests, bstd_number_to_cstr__number_length_eq_9){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 9;
    number.isSigned = false;
    number.positive = true;

    char* res = bstd_number_to_cstr(number);
    cr_assert_str_eq(res, "000005.555");
}



/**
 * Tests for void bstd_assign_number(bstd_number* assignee, const bstd_number* value)
 *
 * Equivalence classes:
 * +----------------------------+----------------------------------+------------------------------------------------+
 * |         Condition          |              Valid               |                    Invalid                     |
 * +----------------------------+----------------------------------+------------------------------------------------+
 * | Value of assignee.value    | 0 <= assignee.value <= 999999999 | assignee.value < 0, assignee.value > 999999999 |
 * | Value of assignee.scale    | 0 <= assignee.scale <= 9         | assignee.scale < 0, assignee.scale > 9         |
 * | Value of assignee.length   | 1 <= assignee.length <= 9        | assignee.length < 0, assignee.length > 9       |
 * | Value of assignee.isSigned | assignee.isSigned = false,       |                                                |
 * |                            | assignee.isSigned = true         |                                                |
 * | Value of assignee.positive | assignee.positive = false,       |                                                |
 * |                            | assignee.positive = true         |                                                |
 * | Relation                   | assignee.isSigned = true &&      | assignee.isSigned = false &&                   |
 * |                            | assignee.positive = false,       | assignee.positive = false                      |
 * |                            | assignee.isSigned = false &&     |                                                |
 * |                            | assignee.positive = true,        |                                                |
 * |                            | assignee.isSigned = true &&      |                                                |
 * |                            | assignee.positive = true         |                                                |
 * | Value of value.value       |  0 <= value.value <= 999999999   | value.value < 0, value.value > 999999999       |
 * | Value of value.scale       | 1 <= value.scale <= 9            | value.scale < 0, value.scale > 9               |
 * | Value of value.length      | 1 <= value.length <= 9           | value.length < 0, value.length > 9             |
 * | Value of value.isSigned    | value.isSigned = false,          |                                                |
 * |                            | value.isSigned = true            |                                                |
 * | Value of value.positive    | value.positive = false,          |                                                |
 * |                            | value.positive = true            |                                                |
 * | Relation                   | assignee.isSigned = true &&      | value.isSigned = false &&                      |
 * |                            | assignee.positive = false,       | value.positive = false                         |
 * |                            | assignee.isSigned = false &&     |                                                |
 * |                            | assignee.positive = true,        |                                                |
 * |                            | assignee.isSigned = true &&      |                                                |
 * |                            | assignee.positive = true         |                                                |
 * +----------------------------+----------------------------------+------------------------------------------------+
 *
*/

//valid classes tests

/*
 * Testing valid conditions:
 *
 * 0 <= assignee.value <= 999999999,
 * 0 <= assignee.scale <= 9,
 * 1 <= assignee.length <= 9,
 * assignee.isSigned = false,
 * assignee.positive = true,
 * assignee.isSigned = false && assignee.positive = true
 *
 * 0 <= value.value <= 999999999,
 * 0 <= value.scale <= 9,
 * 1 <= value.length <= 9,
 * value.isSigned = false,
 * value.positive = true,
 * value.isSigned = false && value.positive = true
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * assignee.value = 1;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_number__pos_unsigned){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 1;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, assignee.value);
    cr_assert_eq(ex.scale, assignee.scale);
    cr_assert_eq(ex.length, assignee.length);
    cr_assert_eq(ex.isSigned, assignee.isSigned);
    cr_assert_eq(ex.positive, assignee.positive);
}

/*
 * Testing valid conditions:
 *
 * 0 <= assignee.value <= 999999999,
 * 0 <= assignee.scale <= 9,
 * 1 <= assignee.length <= 9,
 * assignee.isSigned = true,
 * assignee.positive = true,
 * assignee.isSigned = true && assignee.positive = true
 *
 *  0 <= value.value <= 999999999,
 * 0 <= value.scale <= 9,
 * 1 <= value.length <= 9,
 * value.isSigned = true,
 * value.positive = true,
 * value.isSigned = true && value.positive = true
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = true;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = true;
 * value.positive = true;
 *
 * expected:
 * ex.value = 1;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_number__pos_signed_pos){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = true;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 7;
    value.isSigned = true;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 1;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = true;


    cr_assert_eq(ex.value, assignee.value);
    cr_assert_eq(ex.scale, assignee.scale);
    cr_assert_eq(ex.length, assignee.length);
    cr_assert_eq(ex.isSigned, assignee.isSigned);
    cr_assert_eq(ex.positive, assignee.positive);
}

/*
 * Testing valid conditions:
 *
 * 0 <= assignee.value <= 999999999,
 * 0 <= assignee.scale <= 9,
 * 1 <= assignee.length <= 9,
 * assignee.isSigned = true,
 * assignee.positive = false,
 * assignee.isSigned = true && assignee.positive = false
 *
 * 0 <= value.value <= 999999999,
 * 0 <= value.scale <= 9,
 * 1 <= value.length <= 9,
 * value.isSigned = true,
 * value.positive = false,
 * value.isSigned = true && value.positive = false
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = true;
 * assignee.positive = false;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = true;
 * value.positive = false;
 *
 * expected:
 * ex.value = 1;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(numutils_tests, bstd_assign_number__pos_signed_neg){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = true;
    assignee.positive = false;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 7;
    value.isSigned = true;
    value.positive = false;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 1;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = false;


    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);
}

/*
 * Testing valid conditions:
 *
 * 0 <= assignee.value <= 999999999,
 * 0 <= assignee.scale <= 9,
 * 1 <= assignee.length <= 9,
 * assignee.isSigned = true,
 * assignee.positive = true,
 * assignee.isSigned = true && assignee.positive = true
 *
 * 0 <= value.value <= 999999999,
 * 0 <= value.scale <= 9,
 * 1 <= value.length <= 9,
 * value.isSigned = true,
 * value.positive = false,
 * value.isSigned = true && value.positive = false
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = true;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = true;
 * value.positive = false;
 *
 * expected:
 * ex.value = 1;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(numutils_tests, bstd_assign_number__assignee_pos_value_neg){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = true;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 7;
    value.isSigned = true;
    value.positive = false;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 1;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = false;


    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);
}

/*
 * Testing valid conditions:
 *
 * 0 <= assignee.value <= 999999999,
 * 0 <= assignee.scale <= 9,
 * 1 <= assignee.length <= 9,
 * assignee.isSigned = true,
 * assignee.positive = false,
 * assignee.isSigned = true && assignee.positive = false
 *
 * 0 <= value.value <= 999999999,
 * 0 <= value.scale <= 9,
 * 1 <= value.length <= 9,
 * value.isSigned = true,
 * value.positive = true,
 * value.isSigned = true && value.positive = true
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = true;
 * assignee.positive = false;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = true;
 * value.positive = true;
 *
 * expected:
 * ex.value = 1;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_number__assignee_neg_value_pos){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = true;
    assignee.positive = false;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 7;
    value.isSigned = true;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 1;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = true;


    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);

}

// boundary value analysis for assignee

/*
 *
 * testing boundary value assignee.value = 0
 *
 * in:
 * assignee.value = 0;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
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
Test(numutils_tests, bstd_assign_number__assignee_value_eq_0){
    bstd_number assignee;
    assignee.value = 0;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 1;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);
}

/*
 *
 * testing boundary value assignee.value = 9(9) with values using differing scales.
 *
 * in:
 * assignee.value = 999999999;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
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
Test(numutils_tests, bstd_assign_number__assignee_value_eq_max_differing_scales){
    bstd_number assignee;
    assignee.value = 999999999;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 1;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);
}

/*
 *
 * testing boundary value assignee.value = 9(9) with values using same scales.
 *
 * in:
 * assignee.value = 999999999;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 3;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(numutils_tests, bstd_assign_number__assignee_value_eq_max_same_scales){
    bstd_number assignee;
    assignee.value = 999999999;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 3;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);
}

/*
 * testing boundary value assignee.scale = 0
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 0;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * ex.value = 0;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_number__assignee_scale_eq_0){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 0;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 0;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);

}

/*
 * testing boundary value assignee.scale = 9
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 9;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * ex.value = 4000;
 * ex.scale = 9;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_number__assignee_scale_eq_9){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 9;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 4000;
    ex.scale = 9;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);
}

/*
 * testing boundary value assignee.length = 1
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 1;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * ex.value = 1;
 * ex.scale = 3;
 * ex.length = 1;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_number__assignee_length_eq_1){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 1;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 1;
    ex.scale = 3;
    ex.length = 1;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);

}

/*
 * testing boundary value assignee.length = 9
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 9;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * ex.value = 1;
 * ex.scale = 3;
 * ex.length = 9;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_number__assignee_length_eq_9){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 9;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 1;
    ex.scale = 3;
    ex.length = 9;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);

}

// boundary value analysis for value

/*
 *
 * testing boundary value value.value = 0
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 0;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * ex.value = 0;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(numutils_tests, bstd_assign_number__value_value_eq_0){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 0;
    value.scale = 6;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 0;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);

}

/*
 *
 * testing boundary value assignee.value = 9(9) with values using differing scales.
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 999999999;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * ex.value = 9999;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(numutils_tests, bstd_assign_number__value_value_eq_max_differing_scales){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 999999999;
    value.scale = 6;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 9999;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);

}

/*
 *
 * testing boundary value assignee.value = 9(9) with values using same scales.
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 999999999;
 * value.scale = 6;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * ex.value = 9999;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(numutils_tests, bstd_assign_number__value_value_eq_max_same_scales){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 999999999;
    value.scale = 3;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 9999;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);

}

/*
 * testing boundary value value.scale = 0
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 0;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * ex.value = 4000;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_number__value_scale_eq_0){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 0;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 4000;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);

}

/*
 * testing boundary value assignee.scale = 9
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 9;
 * value.length = 7;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * ex.value = 0;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_number__value_scale_eq_9){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 9;
    value.length = 7;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 0;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);

}

/*
 * testing boundary value value.length = 1
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 1;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * ex.value = 1;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_number__value_length_eq_1){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 1;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 1;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);

}

/*
 * testing boundary value value.length = 9
 *
 * in:
 * assignee.value = 5555;
 * assignee.scale = 3;
 * assignee.length = 4;
 * assignee.isSigned = false;
 * assignee.positive = true;
 *
 * value.value = 1234;
 * value.scale = 6;
 * value.length = 9;
 * value.isSigned = false;
 * value.positive = true;
 *
 * expected:
 * ex.value = 1;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_number__value_length_eq_9){
    bstd_number assignee;
    assignee.value = 5555;
    assignee.scale = 3;
    assignee.length = 4;
    assignee.isSigned = false;
    assignee.positive = true;

    bstd_number value;
    value.value = 1234;
    value.scale = 6;
    value.length = 9;
    value.isSigned = false;
    value.positive = true;

    bstd_assign_number(&assignee, &value);

    bstd_number ex;
    ex.value = 1;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      assignee.value);
    cr_assert_eq(ex.scale,      assignee.scale);
    cr_assert_eq(ex.length,     assignee.length);
    cr_assert_eq(ex.isSigned,   assignee.isSigned);
    cr_assert_eq(ex.positive,   assignee.positive);

}




/**
 * Tests for void bstd_assign_int(bstd_number* number, const int value)
 *
 * +--------------------------+----------------------------------+--------------------------------------------+
 * |        Condition         |              Valid               |                  Invalid                   |
 * +--------------------------+----------------------------------+--------------------------------------------+
 * | Value of number.value    | 0 <= number.value <= 999999999   | number.value < 0, number.value > 999999999 |
 * | Value of number.scale    | number.scale = 0                 | number.scale < 0, number.scale > 0         |
 * | Value of number.length   | 1 <= number.length <= 9          | number.length < 0, number.length > 9       |
 * | Value of number.isSigned | number.isSigned = false,         |                                            |
 * |                          | number.isSigned = true           |                                            |
 * | Value of number.positive | number.positive = false,         |                                            |
 * |                          | number.positive = true           |                                            |
 * | Relation                 | number.isSigned = true &&        | number.isSigned = false &&                 |
 * |                          | number.positive = false,         | number.positive = false                    |
 * |                          | number.isSigned = false &&       |                                            |
 * |                          | number.positive = true,          |                                            |
 * |                          | number.isSigned = true &&        |                                            |
 * |                          | number.positive = true           |                                            |
 * | Value of value           | -999999999 <= value <= 999999999 | value < -999999999, value > 999999999      |
 * +--------------------------+----------------------------------+--------------------------------------------+
 *
 */


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
 * -999999999 <= value <= 999999999
 *
 * in:
 * number.value = 0;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * value = 5
 *
 * expected:
 * number.value = 5;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int__pos_unsigned){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    int value = 5;

    bstd_assign_int(&number, value);

    bstd_number ex;
    ex.value = 5;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, number.value);
    cr_assert_eq(ex.scale, number.scale);
    cr_assert_eq(ex.length, number.length);
    cr_assert_eq(ex.isSigned, number.isSigned);
    cr_assert_eq(ex.positive, number.positive);
}

/*
 * Testing valid conditions:
 *
 * 0 <= number.value <= 999999999,
 * number.scale <= 0,
 * 1 <= number.length <= 9,
 * number.isSigned = true,
 * number.positive = true,
 * number.isSigned = true && number.positive = true
 *
 * -999999999 <= value <= 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = true;
 *
 * value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int__pos_signed_pos){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;

    int value = 1234;
    bstd_assign_int(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = true;


    cr_assert_eq(ex.value, number.value);
    cr_assert_eq(ex.scale, number.scale);
    cr_assert_eq(ex.length, number.length);
    cr_assert_eq(ex.isSigned, number.isSigned);
    cr_assert_eq(ex.positive, number.positive);
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
 * -999999999 <= value <= 999999999
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = false;
 *
 * value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(numutils_tests, bstd_assign_int__pos_signed_neg){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = true;
    number.positive = false;

    int value = -1234;

    bstd_assign_int(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = false;


    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);
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
 * -999999999 <= value <= 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = true;
 *
 * value = 1234;
 *
 *
 * expected:
 * ex.value = -1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(numutils_tests, bstd_assign_int__number_pos_value_neg){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;

    int value = -1234;


    bstd_assign_int(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = false;


    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);
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
 * -999999999 <= value <= 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = false;
 *
 * value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int__number_neg_value_pos){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = true;
    number.positive = false;

    int value = 1234;

    bstd_assign_int(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = true;


    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

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
 * value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(numutils_tests, bstd_assign_int__number_value_eq_0){
    bstd_number number;
    number.value = 0;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    int value = 1234;

    bstd_assign_int(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);
}

/*
 *
 * testing boundary value number.value = 9(9) with values using differing scales.
 *
 * in:
 * number.value = 999999999;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int__number_value_eq_max){
    bstd_number number;
    number.value = 999999999;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    int value = 1234;

    bstd_assign_int(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);
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
 * value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int__number_scale_eq_0){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    int value = 1234;

    bstd_assign_int(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

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
 * value = 1234;
 *
 * expected:
 * ex.value = 1;
 * ex.scale = 0;
 * ex.length = 1;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int__number_length_eq_1){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 1;
    number.isSigned = false;
    number.positive = true;

    int value = 1234;

    bstd_assign_int(&number, value);

    bstd_number ex;
    ex.value = 4;
    ex.scale = 0;
    ex.length = 1;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

}

/*
 * testing boundary value number.length = 9
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 9;
 * number.isSigned = false;
 * number.positive = true;
 *
 * value.value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 9;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int__number_length_eq_9){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 9;
    number.isSigned = false;
    number.positive = true;

    int value = 1234;

    bstd_assign_int(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 9;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

}

// boundary value analysis for value


/*
 * testing boundary value 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * value = 999999999;
 *
 * expected:
 * ex.value = 9999;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int__value_eq_999999999){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    int value = 999999999;

    bstd_assign_int(&number, value);

    bstd_number ex;
    ex.value = 9999;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

}


/*
 * testing boundary value 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = true;
 *
 * value = -999999999;
 *
 * expected:
 * ex.value = 9999;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(numutils_tests, bstd_assign_int__value_eq_negative_999999999){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;

    int value = -999999999;

    bstd_assign_int(&number, value);

    bstd_number ex;
    ex.value = 9999;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = false;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

}



/**
 * Tests for void bstd_assign_int64(bstd_number* number, const int64_t value)
 *
 * +--------------------------+----------------------------------+--------------------------------------------+
 * |        Condition         |              Valid               |                  Invalid                   |
 * +--------------------------+----------------------------------+--------------------------------------------+
 * | Value of number.value    | 0 <= number.value <= 999999999   | number.value < 0, number.value > 999999999 |
 * | Value of number.scale    | number.scale = 0                 | number.scale < 0, number.scale > 0         |
 * | Value of number.length   | 1 <= number.length <= 9          | number.length < 0, number.length > 9       |
 * | Value of number.isSigned | number.isSigned = false,         |                                            |
 * |                          | number.isSigned = true           |                                            |
 * | Value of number.positive | number.positive = false,         |                                            |
 * |                          | number.positive = true           |                                            |
 * | Relation                 | number.isSigned = true &&        | number.isSigned = false &&                 |
 * |                          | number.positive = false,         | number.positive = false                    |
 * |                          | number.isSigned = false &&       |                                            |
 * |                          | number.positive = true,          |                                            |
 * |                          | number.isSigned = true &&        |                                            |
 * |                          | number.positive = true           |                                            |
 * | Value of value           | -999999999 <= value <= 999999999 | value < -999999999, value > 999999999      |
 * +--------------------------+----------------------------------+--------------------------------------------+
 *
 */


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
 * -999999999 <= value <= 999999999
 *
 * in:
 * number.value = 0;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * value = 5
 *
 * expected:
 * number.value = 5;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int64__pos_unsigned){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    int64_t value = 5;

    bstd_assign_int64(&number, value);

    bstd_number ex;
    ex.value = 5;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, number.value);
    cr_assert_eq(ex.scale, number.scale);
    cr_assert_eq(ex.length, number.length);
    cr_assert_eq(ex.isSigned, number.isSigned);
    cr_assert_eq(ex.positive, number.positive);
}

/*
 * Testing valid conditions:
 *
 * 0 <= number.value <= 999999999,
 * number.scale <= 0,
 * 1 <= number.length <= 9,
 * number.isSigned = true,
 * number.positive = true,
 * number.isSigned = true && number.positive = true
 * -999999999 <= value <= 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = true;
 *
 * value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int64__pos_signed_pos){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;

    int64_t value = 1234;
    bstd_assign_int64(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = true;


    cr_assert_eq(ex.value, number.value);
    cr_assert_eq(ex.scale, number.scale);
    cr_assert_eq(ex.length, number.length);
    cr_assert_eq(ex.isSigned, number.isSigned);
    cr_assert_eq(ex.positive, number.positive);
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
 * -999999999 <= value <= 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = false;
 *
 * value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(numutils_tests, bstd_assign_int64__pos_signed_neg){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = true;
    number.positive = false;

    int64_t value = -1234;

    bstd_assign_int64(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = false;


    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);
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
 * -999999999 <= value <= 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = true;
 *
 * value = 1234;
 *
 *
 * expected:
 * ex.value = -1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(numutils_tests, bstd_assign_int64__number_pos_value_neg){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;

    int64_t value = -1234;


    bstd_assign_int64(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = false;


    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);
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
 * -999999999 <= value <= 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = false;
 *
 * value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int64__number_neg_value_pos){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = true;
    number.positive = false;

    int64_t value = 1234;

    bstd_assign_int64(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = true;


    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

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
 * value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(numutils_tests, bstd_assign_int64__number_value_eq_0){
    bstd_number number;
    number.value = 0;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    int64_t value = 1234;

    bstd_assign_int64(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);
}

/*
 *
 * testing boundary value number.value = 9(9) with values using differing scales.
 *
 * in:
 * number.value = 999999999;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int64__number_value_eq_max){
    bstd_number number;
    number.value = 999999999;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    int64_t value = 1234;

    bstd_assign_int64(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);
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
 * value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int64__number_scale_eq_0){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    int64_t value = 1234;

    bstd_assign_int64(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

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
 * value = 1234;
 *
 * expected:
 * ex.value = 1;
 * ex.scale = 0;
 * ex.length = 1;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int64__number_length_eq_1){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 1;
    number.isSigned = false;
    number.positive = true;

    int64_t value = 1234;

    bstd_assign_int64(&number, value);

    bstd_number ex;
    ex.value = 4;
    ex.scale = 0;
    ex.length = 1;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

}

/*
 * testing boundary value number.length = 9
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 9;
 * number.isSigned = false;
 * number.positive = true;
 *
 * value.value = 1234;
 *
 * expected:
 * ex.value = 1234;
 * ex.scale = 0;
 * ex.length = 9;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int64__number_length_eq_9){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 9;
    number.isSigned = false;
    number.positive = true;

    int64_t value = 1234;

    bstd_assign_int64(&number, value);

    bstd_number ex;
    ex.value = 1234;
    ex.scale = 0;
    ex.length = 9;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

}

// boundary value analysis for value


/*
 * testing boundary value 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * value = 999999999;
 *
 * expected:
 * ex.value = 9999;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_int64__value_eq_999999999){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    int64_t value = 999999999;

    bstd_assign_int64(&number, value);

    bstd_number ex;
    ex.value = 9999;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

}


/*
 * testing boundary value 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 0;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = true;
 *
 * value = -999999999;
 *
 * expected:
 * ex.value = 9999;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(numutils_tests, bstd_assign_int64__value_eq_negative_999999999){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;

    int64_t value = -999999999;

    bstd_assign_int64(&number, value);

    bstd_number ex;
    ex.value = 9999;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = false;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

}

/**
 * Tests for void bstd_assign_double(bstd_number* number, const int value)
 *
 * +--------------------------+--------------------------------------+--------------------------------------------+
 * |        Condition         |                Valid                 |                  Invalid                   |
 * +--------------------------+--------------------------------------+--------------------------------------------+
 * | Value of number.value    | 0 <= number.value <= 999999999       | number.value < 0, number.value > 999999999 |
 * | Value of number.scale    | 0 <= number.scale = 9                | number.scale < 0,  number.scale > 9        |
 * | Value of number.length   | 1 <= number.length <= 9              | number.length < 0, number.length > 9       |
 * | Value of number.isSigned | number.isSigned = false,             |                                            |
 * |                          | number.isSigned = true               |                                            |
 * | Value of number.positive | number.positive = false,             |                                            |
 * |                          | number.positive = true               |                                            |
 * | Relation                 | number.isSigned = true &&            | number.isSigned = false &&                 |
 * |                          | number.positive = false,             | number.positive = false                    |
 * |                          | number.isSigned = false &&           |                                            |
 * |                          | number.positive = true,              |                                            |
 * |                          | number.isSigned = true &&            |                                            |
 * |                          | number.positive = true               |                                            |
 * | Value of value           | -999999999.0 <= value <= 999999999.0 | value < -999999999.0, value > 999999999.0  |
 * +--------------------------+--------------------------------------+--------------------------------------------+
 *
 *
 */


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
 * -999999999.0 <= value <= 999999999.0
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * value = 5.5
 *
 * expected:
 * number.value = 5500;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_double__pos_unsigned){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    double value = 5.5;

    bstd_assign_double(&number, value);

    bstd_number ex;
    ex.value = 5500;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value, number.value);
    cr_assert_eq(ex.scale, number.scale);
    cr_assert_eq(ex.length, number.length);
    cr_assert_eq(ex.isSigned, number.isSigned);
    cr_assert_eq(ex.positive, number.positive);
}

/*
 * Testing valid conditions:
 *
 * 0 <= number.value <= 999999999,
 * number.scale <= 0,
 * 1 <= number.length <= 9,
 * number.isSigned = true,
 * number.positive = true,
 * number.isSigned = true && number.positive = true
 *
 * -999999999 <= value <= 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = true;
 *
 * value = 1234;
 *
 * expected:
 * ex.value = 2340;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_double__pos_signed_pos){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;

    double value = 12.34;
    bstd_assign_double(&number, value);

    bstd_number ex;
    ex.value = 2340;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = true;


    cr_assert_eq(ex.value, number.value);
    cr_assert_eq(ex.scale, number.scale);
    cr_assert_eq(ex.length, number.length);
    cr_assert_eq(ex.isSigned, number.isSigned);
    cr_assert_eq(ex.positive, number.positive);
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
 * -999999999 <= value <= 999999999
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = false;
 *
 * value = 12.34;
 *
 * expected:
 * ex.value = 2340;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_double__pos_signed_neg){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = true;
    number.positive = false;

    double value = 12.34;

    bstd_assign_double(&number, value);

    bstd_number ex;
    ex.value = 2340;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = true;


    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);
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
 * -999999999 <= value <= 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = true;
 *
 * value = 1234;
 *
 *
 * expected:
 * ex.value = -1234;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(numutils_tests, bstd_assign_double__number_pos_value_neg){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;

    double value = -12.34;


    bstd_assign_double(&number, value);

    bstd_number ex;
    ex.value = 2340;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = false;


    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);
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
 * -999999999 <= value <= 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = false;
 *
 * value = 12.34;
 *
 * expected:
 * ex.value = 2340;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_double__number_neg_value_pos){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = true;
    number.positive = false;

    double value = 12.34;

    bstd_assign_double(&number, value);

    bstd_number ex;
    ex.value = 2340;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = true;


    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

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
 * value = 12.34;
 *
 * expected:
 * ex.value = 2340;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 *
 *
 */
Test(numutils_tests, bstd_assign_double__number_value_eq_0){
    bstd_number number;
    number.value = 0;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    double value = 12.34;

    bstd_assign_double(&number, value);

    bstd_number ex;
    ex.value = 2340;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);
}

/*
 *
 * testing boundary value number.value = 9(9) with values using differing scales.
 *
 * in:
 * number.value = 999999999;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * value = 1234;
 *
 * expected:
 * ex.value = 2340;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_double__number_value_eq_max){
    bstd_number number;
    number.value = 999999999;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    double value = 12.34;

    bstd_assign_double(&number, value);

    bstd_number ex;
    ex.value = 2340;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);
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
 * value = 12.34;
 *
 * expected:
 * ex.value = 12;
 * ex.scale = 0;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_double__number_scale_eq_0){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    double value = 12.34;

    bstd_assign_double(&number, value);

    bstd_number ex;
    ex.value = 12;
    ex.scale = 0;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

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
 * value = 12.34;
 *
 * expected:
 * ex.value = 2;
 * ex.scale = 0;
 * ex.length = 1;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_double__number_length_eq_1){
    bstd_number number;
    number.value = 5555;
    number.scale = 0;
    number.length = 1;
    number.isSigned = false;
    number.positive = true;

    double value = 12.34;

    bstd_assign_double(&number, value);

    bstd_number ex;
    ex.value = 2;
    ex.scale = 0;
    ex.length = 1;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

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
 * value.value = 12.34;
 *
 * expected:
 * ex.value = 12340;
 * ex.scale = 3;
 * ex.length = 9;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_double__number_length_eq_9){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 9;
    number.isSigned = false;
    number.positive = true;

    double value = 12.34;

    bstd_assign_double(&number, value);

    bstd_number ex;
    ex.value = 12340;
    ex.scale = 3;
    ex.length = 9;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

}

// boundary value analysis for value


/*
 * testing boundary value 999999999.0
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = false;
 * number.positive = true;
 *
 * value = 999999999.0;
 *
 * expected:
 * ex.value = 999999000;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = false;
 * ex.positive = true;
 *
 */
Test(numutils_tests, bstd_assign_double__value_eq_999999999){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = false;
    number.positive = true;

    double value = 999999999.0;

    bstd_assign_double(&number, value);

    bstd_number ex;
    ex.value = 9000;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = false;
    ex.positive = true;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

}


/*
 * testing boundary value 999999999
 *
 * in:
 * number.value = 5555;
 * number.scale = 3;
 * number.length = 4;
 * number.isSigned = true;
 * number.positive = true;
 *
 * value = -999999999.0;
 *
 * expected:
 * ex.value = 999999000;
 * ex.scale = 3;
 * ex.length = 4;
 * ex.isSigned = true;
 * ex.positive = false;
 *
 */
Test(numutils_tests, bstd_assign_double__value_eq_negative_999999999){
    bstd_number number;
    number.value = 5555;
    number.scale = 3;
    number.length = 4;
    number.isSigned = true;
    number.positive = true;

    double value = -999999999.0;

    bstd_assign_double(&number, value);

    bstd_number ex;
    ex.value = 9000;
    ex.scale = 3;
    ex.length = 4;
    ex.isSigned = true;
    ex.positive = false;

    cr_assert_eq(ex.value,      number.value);
    cr_assert_eq(ex.scale,      number.scale);
    cr_assert_eq(ex.length,     number.length);
    cr_assert_eq(ex.isSigned,   number.isSigned);
    cr_assert_eq(ex.positive,   number.positive);

}