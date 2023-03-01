//
// Created by bruh on 11/28/22.
//
#include <stdlib.h>
#include "../include/numutils.h"
#include "../include/arithmetic.h"

int bstd_number_is_integer(bstd_number* number) {
    return !number->scale;
}

int bstd_number_to_int(bstd_number* number) {
    return !number->positive && number->isSigned ? -number->value : number->value;
}

double bstd_number_to_double(bstd_number* number) {
    return bstd_number_to_int(number) / (double)ipow(10, number->scale);
}

void bstd_assign_number(bstd_number* assignee, bstd_number* value) {
    // todo: implement this.
}

void bstd_assign_int(bstd_number* number, const int value) {

    int abs_value = abs(value);
    int64_t mag = ipow(10, number->length);
    int64_t mask = (abs_value / mag) * mag;
    int64_t cropped_value = abs_value - mask;

    number->positive = !number->isSigned || value >= 0;
    number->value = cropped_value;
}

void bstd_assign_double(bstd_number* number, const double value) {

    int64_t mag1 = ipow(10, number->length);
    int64_t mag2 = ipow(10, number->length - 1);
    int64_t shift = (int64_t)(value * mag2);
    int64_t mask = (int)((double)shift / mag1) * mag1;
    int64_t cropped_value = labs(shift - mask);

    number->positive = value >= 0;
    number->value = cropped_value;
}
