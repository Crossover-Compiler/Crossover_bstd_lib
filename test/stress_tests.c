#include <criterion/criterion.h>
#include <stdint.h>
#include <math.h>
#include "../include/picutils.h"
#include "../include/numutils.h"
#include "../include/arithmetic.h"

#ifndef BSTD_STRESS_TEST_EPSILON
#define BSTD_STRESS_TEST_EPSILON 1E-6
#endif

int aux_random_int(int lower, int upper) {
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

uint8_t aux_random_uint8_t(int lower, int upper) {
    uint8_t num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

uint64_t aux_random_uint64_t (int lower, int upper)
{
    uint64_t num = (rand() % (upper - lower + 1)) + lower;
    return num;
}


/**
 * Test for to_cstr (stress test)
 *
 * populate 10,000 PICs of a nontrivial size (5 - 255) with 9s and Xs randomly and check if output matches input when
 * running to_cstr.
 *
 */

Test(stress_tests, bstd_picture_to_cstr__stress) {
    srand(0x007734); /// seed rng for reproducibility
    for (int i = 0; i < 10000; i++) {
        ///generate picture size
        uint8_t picture_size = aux_random_uint8_t(5, 255);

        /// generating the mask
        char mask[picture_size];
        for (int i = 0; i < picture_size; i++) {
            int flip = aux_random_int(0, 1);
            if (flip == 1) {
                mask[i] = 'X';
            } else {
                mask[i] = '9';
            }
        }

        ///generating the value
        unsigned char value[picture_size];
        char *expected_value = (char *) malloc(sizeof(char) * (picture_size + 1)); /// printable string of the input
        expected_value[picture_size] = '\0';

        for (int i = 0; i < picture_size; i++) {
            if (mask[i] == 'X') {
                int flip = aux_random_int(0, 1);
                if (flip == 1) {
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
                } else {
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

        bstd_picture *pic = bstd_picture_of(value, mask, picture_size);
        char *cstrval = bstd_picture_to_cstr(pic);

        ///test equality
        cr_assert_str_eq(expected_value, cstrval);
        free(expected_value);
    }
}

/**
 * fuzzing addition
 */
Test(stress_tests, number_addition_fuzz){
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


        bstd_number o = *bstd_sum(&n, &m);

        double fn = bstd_number_to_double(&n);
        double fm = bstd_number_to_double(&m);
        double fo = bstd_number_to_double(&o);

        double ex = fn + fm;
//        bool dbg = (fabs(fo - ex) <= 1E-6);
//        bool dbginf = (fabs(ex - fo) <= 1E-6);
//
//        printf("========================================\n");
//        printf("                iter: %d                \n", i);
//        printf("========================================\n");
//        printf("----------------------------------------\n");
//        printf("                 Input:                 \n");
//        printf("----------------------------------------\n");
//        printf("Number n:\n - value = %lu\n - scale = %lu \n - length = %d\n - isSigned = %d\n - positive = %d\n",n.value, n.scale, n.length, n.isSigned, n.positive);
//        printf("Number m:\n - value = %lu\n - scale = %lu \n - length = %d\n - isSigned = %d\n - positive = %d\n",m.value, m.scale, m.length, m.isSigned, m.positive);
//        printf("----------------------------------------\n");
//        printf("                output:                 \n");
//        printf("----------------------------------------\n");
//        printf("Number o:\n - value = %lu\n - scale = %lu \n - length = %d\n - isSigned = %d\n - positive = %d\n",o.value, o.scale, o.length, o.isSigned, o.positive);
//        printf("----------------------------------------\n");
//        printf("              validation:               \n");
//        printf("----------------------------------------\n");
//        printf("n as double (fn): %e\n", fn);
//        printf("m as double (fm): %e\n", fm);
//        printf("o as double (fo): %e\n", fo);
//        printf("ex = fn + fm: %e\n", ex);
//        printf("Fuzzy equality test (fabs(fo - ex) <= 1E-6): %d\n", dbg);
//        printf("Fuzzy equality test (fabs(ex - fo) <= 1E-6): %d\n", dbginf);

        cr_assert_float_eq(fo, ex, BSTD_STRESS_TEST_EPSILON);
    }
}
