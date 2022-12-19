#include <criterion/criterion.h>
#include "../include/arithmetic.h"
#include "../include/number.h"
#include "../include/numutils.h"
#include "../include/picture.h"
#include "../include/picutils.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

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

int aux_random_uint8_t (int lower, int upper)
{
    uint8_t num = (rand() % (upper - lower + 1)) + lower;
    return num;
}


/**
 * Test for to_cstr (basic)
 */
Test(bstd_tests, picture_bstd_tocstr_basic){
    char c[3] = { 'Q', 0, 'F' };
    char mask[3] = { 'X', '9', 'X' };
    bstd_Picture* pic = bstd_picutils_of(c, mask, 3);

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
    srand(0x007734); // seed rng for reproducibility
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
        char* expected_value = (char*)malloc(sizeof(char) * (picture_size + 1));/// printable string of the input
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
                    const char misc_chars[] = "!@#$%^&*()[]{};:/\\.,><?|`~+-_='\"";
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

        bstd_Picture* pic = bstd_picutils_of(value, mask, picture_size);
        char* cstrval = bstd_picutils_to_cstr(pic);

        ///debug
        printf(" iter: %d\n", i);
        printf("  out: %s\n", cstrval);
        printf("  exp: %s\n", expected_value);


        ///test equality
        cr_assert_str_eq(expected_value, cstrval);
        free(expected_value);
    }
}



