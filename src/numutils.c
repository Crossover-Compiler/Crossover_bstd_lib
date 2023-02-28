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

    int mag = ipow(10, number->length);
    int mask = ((int)value / mag) * mag;
    int cropped_value = abs(value) - mask;

    number->positive = value >= 0;

    // todo: what to do when the number is negative, but the number is unsigned?

    number->value = cropped_value;
}

void bstd_assign_double(bstd_number* number, const double value) {

    int mag1 = ipow(10, number->length);
    int mag2 = ipow(10, number->length - 1);
    int shift = (int)(value * mag2);
    int mask = (int)((double)shift / mag1) * mag1;
    int cropped_value = abs(shift - mask);

    number->positive = value >= 0;
    number->value = cropped_value;
}
