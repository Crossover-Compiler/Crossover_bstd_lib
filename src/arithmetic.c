//
// Created by bruh on 10/17/22.
//

#include "../include/arithmetic.h"
#include <stdlib.h>

// todo: this is broken. behaviour of right-shift operator for negative integers is undefined. Change argument types to uint64_t.
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
    return a > b ? a : b;
}

bstd_number* bstd_add(bstd_number *lhs, bstd_number *rhs) {
    uint64_t s = max(lhs->scale, rhs->scale);
    int64_t a = bstd_tosigned(lhs) * ipow(10, (int64_t)((-lhs->scale) + s));
    int64_t b = bstd_tosigned(rhs) * ipow(10, (int64_t)((-rhs->scale) + s));
    int64_t result = a + b;

    bstd_number* number = (bstd_number*)malloc(sizeof(bstd_number));
    number->value = (uint64_t)labs(result);
    number->scale = s;
    number->positive = result >= 0;

    ///input of RHS dictates the following attributes of output
    number->isSigned = rhs->isSigned;
    number->length = rhs->length;

    return number;
}

int64_t bstd_tosigned(bstd_number* n) {
    return n->positive ? (int64_t)n->value : (-1 * (int64_t) n->value);
}
