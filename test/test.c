#include <criterion/criterion.h>
#include "../include/arithmetic.h"
#include "../include/number.h"
#include "../include/numutils.h"
#include "../include/picture.h"
#include "../include/picutils.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * helper function: generate random int in interval
 * @param lower
 * @param upper
 * @return random int
 */
int aux_random_int (int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}
/**
* helper function: generate random unsigned 8bit int in interval
* @param lower
* @param upper
* @return random int
*/
uint8_t aux_random_uint8_t (int lower, int upper)
{
    uint8_t num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

uint64_t aux_random_uint64_t (int lower, int upper)
{
    uint64_t num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

double aux_number_to_double(bstd_number n){
    double res = (double)bstd_number_to_int(&n) / pow(10, (double)n.scale);
    return res;
};

/**
 * Test for to_cstr (basic)
 */
Test(bstd_tests, picture_bstd_tocstr_basic){
    char c[3] = { 'Q', 0, 'F' };
    char mask[3] = { 'X', '9', 'X' };
    bstd_picture* pic = bstd_picutils_of(c, mask, 3);

    char* cstrval = bstd_picutils_to_cstr(pic);
    char* expected = "Q0F";

    cr_assert_str_eq(expected, cstrval);
}

/**
 * Test for to_cstr (stress test)
 *
 * populate 10,000 PICs of a nontrivial size (5 - 1000) with 9s and Xs randomly and check if output matches input when
 * running to_cstr.
 *
 */
Test(bstd_tests, picture_bstd_tocstr_advanced){
    srand(0x007734); /// seed rng for reproducibility
    for(int i = 0; i < 10000; i++){
        ///generate picture size
        uint8_t picture_size = aux_random_uint8_t(5, 1000);

        /// generating the mask
        char mask[picture_size];
        for (int i =0; i < picture_size; i++){
            int flip = aux_random_int(0,1);
            if (flip == 1){
                mask[i] = 'X';
            } else{
                mask[i] = '9';
            }
        }

        ///generating the value
        char value[picture_size];
        char* expected_value = (char*)malloc(sizeof(char) * (picture_size + 1)); /// printable string of the input
        expected_value[picture_size] = '\0';

        for (int i =0; i < picture_size; i++){
            if (mask[i] == 'X'){
                int flip = aux_random_int(0,1);
                if(flip == 1) {
                    /// case alphabetical
                    /// flip for lower or upper
                    int flip_case = aux_random_int(0, 1);
                    if (flip_case == 1) {
                        char random_upper = 'A' + (random() % 26);
                        value[i] = random_upper;
                        expected_value[i] = random_upper;
                    } else {
                        char random_lower = 'a' + (random() % 26);
                        value[i] = random_lower;
                        expected_value[i] = random_lower;
                    }
                } else{
                    ///case misc chars
                    const char misc_chars[] = "     !@#$%^&*()[]{};:/\\.,><?|`~+-_='\"";
                    char random_misc = misc_chars[rand() % (sizeof(misc_chars) - 1)];
                    value[i] = random_misc;
                    expected_value[i] = random_misc;
                }
            } else {
                int rand_int = aux_random_int(0, 9);
                value[i] = rand_int;
                expected_value[i] = rand_int + '0';
            }
        }

        ///convert to pic

        bstd_picture* pic = bstd_picutils_of(value, mask, picture_size);
        char* cstrval = bstd_picutils_to_cstr(pic);

        ///debug
//        printf(" iter: %d\n", i);
//        printf("  out: %s\n", cstrval);
//        printf("  exp: %s\n", expected_value);


        ///test equality
        cr_assert_str_eq(expected_value, cstrval);
        free(expected_value);
    }
}


/**
 * Test for bstd_number addition (basic)
 */
Test(bstd_tests, number_addition_basic){
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
Test(bstd_tests, number_addition){
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
Test(bstd_tests, number_addition_negative_lhs){
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
Test(bstd_tests, number_addition_negative_lhs_unsigned_rhs){
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


/**
 * fuzzing addition
 */
Test(bstd_tests, number_addition_fuzz){
    srand(0x007734); /// seed rng for reproducibility
    for(int i = 0; i < 10000; i++){
        bstd_number n;
        n.value = aux_random_uint64_t(0, 1000);
        n.scale = aux_random_uint64_t(0, 10);
        n.length = aux_random_uint8_t(0, 10);
        n.isSigned = aux_random_int(0, 1);
        if(n.isSigned) {
            n.positive = aux_random_int(0, 1);
        } else{
            n.positive = true;
        }

        bstd_number m;
        m.value = aux_random_uint64_t(0, 1000);
        m.scale = aux_random_uint64_t(0, 10);
        m.length = aux_random_uint8_t(0, 10);
        m.isSigned = aux_random_int(0, 1);
        if(m.isSigned){
            m.positive = aux_random_int(0, 1);
        } else{
            m.positive = true;
        }


        bstd_number o = *bstd_add(&n, &m);

        double fn = aux_number_to_double(n);
        double fm = aux_number_to_double(m);
        double fo = aux_number_to_double(o);

        double ex = fn + fm;
        bool dbg = (fabs(fo - ex) <= 1E-6);
        bool dbginf = (fabs(ex - fo) <= 1E-6);

        printf("========================================\n");
        printf("                iter: %d                \n", i);
        printf("========================================\n");
        printf("----------------------------------------\n");
        printf("                 Input:                 \n");
        printf("----------------------------------------\n");
        printf("Number n:\n - value = %lu\n - scale = %lu \n - length = %d\n - isSigned = %d\n - positive = %d\n",n.value, n.scale, n.length, n.isSigned, n.positive);
        printf("Number m:\n - value = %lu\n - scale = %lu \n - length = %d\n - isSigned = %d\n - positive = %d\n",m.value, m.scale, m.length, m.isSigned, m.positive);
        printf("----------------------------------------\n");
        printf("                output:                 \n");
        printf("----------------------------------------\n");
        printf("Number o:\n - value = %lu\n - scale = %lu \n - length = %d\n - isSigned = %d\n - positive = %d\n",o.value, o.scale, o.length, o.isSigned, o.positive);
        printf("----------------------------------------\n");
        printf("              validation:               \n");
        printf("----------------------------------------\n");
        printf("n as double (fn): %e\n", fn);
        printf("m as double (fm): %e\n", fm);
        printf("o as double (fo): %e\n", fo);
        printf("ex = fn + fm: %e\n", fo);
        printf("Fuzzy equality test (fabs(fo - ex) <= 1E-6): %d\n", dbg);
        printf("Fuzzy equality test (fabs(ex - fo) <= 1E-6): %d\n", dbginf);

        cr_assert_float_eq(fo, ex, 1E-6);
    }
}




