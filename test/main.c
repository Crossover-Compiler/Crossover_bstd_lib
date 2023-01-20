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

float aux_number_to_float(bstd_Number n){
    double res = (double) bstd_tosigned(&n) / pow(10, (n.scale));
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

int aux_random_uint8_t (int lower, int upper)
{
    uint8_t num = (rand() % (upper - lower + 1)) + lower;
    return num;
}
int aux_random_uint64_t (int lower, int upper)
{
    uint64_t num = (rand() % (upper - lower + 1)) + lower;
    return num;
}


int main() {
    srand(0x07734); /// seed rng for reproducibility

    for(int i = 0; i < 10; i++){
        bstd_Number n;
        n.value = aux_random_uint64_t(0, 1000);
        n.scale = aux_random_uint64_t(0, 10);
        n.length = aux_random_uint8_t(0, 10);
        n.isSigned = aux_random_int(0, 1);
        if(n.isSigned) {
            n.positive = aux_random_int(0, 1);
        } else{
            n.positive = true;
        }

        bstd_Number m;
        m.value = aux_random_uint64_t(0, 1000);
        m.scale = aux_random_uint64_t(0, 10);
        m.length = aux_random_uint8_t(0, 10);
        m.isSigned = aux_random_int(0, 1);
        if(m.isSigned){
            m.positive = aux_random_int(0, 1);
        } else{
            m.positive = true;
        }


        bstd_Number o = *bstd_add(&n, &m);

        float fn = aux_number_to_float(n);
        float fm = aux_number_to_float(m);
        float fo = aux_number_to_float(o);

        float ex = fn + fm;
        bool dbg = (fabs(fo - ex) <= 1E-6);
        bool dbginf = (fabs(ex - fo) <= 1E-6);

        printf(" iter: %d\n", i);
        printf("  out: %d\n", dbg);
        printf("  exp: %d\n", dbginf);
    };

    return 0;
}