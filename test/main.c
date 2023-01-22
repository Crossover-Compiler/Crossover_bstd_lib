//
// use for debugging of failed tests
//

#include "../include/arithmetic.h"
#include "../include/number.h"
#include "../include/numutils.h"
#include "../include/picture.h"
#include "../include/picutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double aux_number_to_double(bstd_Number n){
    double res = (double)bstd_tosigned(&n) / pow(10, (double)n.scale);
    return res;
};

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


int main() {
    srand(0x088888);  /// seed rng for reproducibility



    bstd_Number n;
    n.value = 734;
    n.scale = 9;
    n.length = 1;
    n.isSigned = 1;
    n.positive = 1;

    double fn = aux_number_to_double(n);
    printf("res: %e", fn);

//    for(int i = 0; i < 2; i++){
//        bstd_Number n;
//        n.value = aux_random_uint64_t(0, 1000);
//        n.scale = aux_random_uint64_t(0, 10);
//        n.length = aux_random_uint8_t(0, 10);
//        n.isSigned = aux_random_int(0, 1);
//        if(n.isSigned) {
//            n.positive = aux_random_int(0, 1);
//        } else{
//            n.positive = true;
//        }
//
//        bstd_Number m;
//        m.value = aux_random_uint64_t(0, 1000);
//        m.scale = aux_random_uint64_t(0, 10);
//        m.length = aux_random_uint8_t(0, 10);
//        m.isSigned = aux_random_int(0, 1);
//        if(m.isSigned){
//            m.positive = aux_random_int(0, 1);
//        } else{
//            m.positive = true;
//        }
//
//
//        bstd_Number o = *bstd_add(&n, &m);
//
//        double fn = aux_number_to_double(n);
//        double fm = aux_number_to_double(m);
//        double fo = aux_number_to_double(o);
//
//        double ex = fn + fm;
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
//        printf("n as double (fn): %f\n", fn);
//        printf("m as double (fm): %f\n", fm);
//        printf("o as double (fo): %f\n", fo);
//        printf("ex = fn + fm: %f\n", fo);
//        printf("Fuzzy equality test (fabs(fo - ex) <= 1E-6): %d\n", dbg);
//        printf("Fuzzy equality test (fabs(ex - fo) <= 1E-6): %d\n", dbginf);
//    };

    return 0;
}