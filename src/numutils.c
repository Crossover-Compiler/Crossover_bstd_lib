#include <stdlib.h>
#include <stdio.h>
#include "../include/numutils.h"
#include "../include/arithmetic.h"

void bstd_assign_int(bstd_Number *number, int value) {
    bool positive = value >= 0;

    int64_t mag = ipow(10, number->length);
    int mask = ((int) value / mag) * mag;
    int cropped_value = abs(value) - mask;

    number->positive = positive;
    number->value = cropped_value;
}

void bstd_assign_double(bstd_Number *number, double value) {
    bool positive = value >= 0;

    int64_t mag1 = ipow(10, number->length);
    int64_t mag2 = ipow(10, number->length - 1);
    int shift = (int) (value * mag2);
    int mask = (int) ((double) shift / mag1) * mag1;
    int cropped_value = abs(shift - mask);

    number->positive = positive;
    number->value = cropped_value;
}

double bstd_get_double(bstd_Number *number) {
    int64_t value = (int64_t) number->value;
    if (number->isSigned) {
        if (!number->positive) {
            value = (-1 * value);
        }
    }
    int64_t scale_divisor = ipow(10, number->scale);
    double double_value =  (double) value / (double) scale_divisor;
    return double_value;
}

int64_t bstd_get_int(bstd_Number *number) {
    int64_t value = (int64_t) number->value;
    if (number->isSigned) {
        if (!number->positive) {
            value = (-1 * value);
        }
    }
    int64_t scale_divisor = ipow(10, number->scale);
    int64_t int_value = (int64_t) (value / scale_divisor);
    return int_value;
}