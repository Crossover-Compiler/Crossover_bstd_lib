//
// Created by bruh on 10/17/22.
//

#include "../include/arithmetic.h"
#include <stdlib.h>

int64_t ipow(int64_t base, int64_t exp)
{
    int64_t result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}
uint64_t max(uint64_t a, uint64_t b) {
    if (a > b) {
        return a;
    }
    return b;
}




bstd_Number* bstd_add(bstd_Number *lhs, bstd_Number *rhs) {
    uint64_t s = max(lhs->scale, rhs->scale);
    int64_t a = bstd_tosigned(lhs) * ipow(10, (int64_t)((-lhs->scale) + s));
    int64_t b = bstd_tosigned(rhs) * ipow(10, (int64_t)((-rhs->scale) + s));
    int64_t result = a + b;

    bstd_Number* number = (bstd_Number*)malloc(sizeof(bstd_Number));
    number->value = (uint64_t)labs(result);
    number->scale = s;
    number->positive = result >= 0;

    ///input of RHS dictates the following attributes of output
    if(!rhs->isSigned){
        number->isSigned=false;
    } else{
        number->isSigned = true;
    }

    number->length = rhs->length;



    return number;
}

int64_t bstd_tosigned(bstd_Number* n) {
    return n->positive ? (int64_t)n->value : (-1 * (int64_t) n->value);
}
