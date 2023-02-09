#include <math.h>
#include <stdlib.h>
#include "../include/numutils.h"

void bstd_assign_int(bstd_Number *number, int value) {
    bool positive = value >= 0;

    int mag = (int) pow(10, number->length);
    int mask = ((int) value / mag) * mag;
    int cropped_value = abs(value) - mask;

    number->positive = positive;
    number->value = cropped_value;
}

void bstd_assign_double(bstd_Number *number, double value) {
    bool positive = value >= 0;

    double mag1 = pow(10, number->length);
    double mag2 = pow(10, number->length - 1);
    int shift = (int) (value * mag2);
    int mask = (int) ((double) shift / mag1) * mag1;
    int cropped_value = abs(shift - mask);

    number->positive = positive;
    number->value = cropped_value;
}

double bstd_get_double(bstd_Number *number) {
    int64_t value = number->positive ? (int64_t) number->value : (-1 * (int64_t) number->value);
    double scale_divisor = pow(10, number->scale);
    double double_value = value / scale_divisor;
    return double_value;
}

int64_t bstd_get_int(bstd_Number *number) {
    int64_t value = number->positive ? (int64_t) number->value : (-1 * (int64_t) number->value);
    double scale_divisor = pow(10, number->scale);
    int64_t int_value = (int64_t) (value / scale_divisor);
    return int_value;
}