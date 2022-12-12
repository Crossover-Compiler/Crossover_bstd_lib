//
// Created by bruh on 10/17/22.
//

#include "../include/arithmetic.h"
#include <math.h>
#include <stdlib.h>

uint64_t max(uint64_t a, uint64_t b) {
    if (a > b) {
        return a;
    }
    return b;
}

bstd_Number* bstd_add(bstd_Number *lhs, bstd_Number *rhs) {

    uint64_t s = max(lhs->scale, rhs->scale);
    int a = bstd_tosigned(lhs) * (int)pow(10, (-lhs->scale) + s);
    int b = bstd_tosigned(rhs) * (int)pow(10, (-rhs->scale) + s);
    int result = a + b;

    bstd_Number* number = (bstd_Number*)malloc(sizeof(bstd_Number));
    number->value = (uint64_t)abs(result);
    number->scale = s;
    number->positive = result >= 0;

    return number;
}

int bstd_tosigned(bstd_Number* n) {
    return n->positive ? n->value : (-1 * (int) n->value);
}
