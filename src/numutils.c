//
// Created by bruh on 11/28/22.
//
#include <stdlib.h>
#include "../include/numutils.h"
#include "../include/arithmetic.h"

/**
 * Creates an integer representation for the specified bstd_number. The representation is an independent copy.
 * Note that instances of the type bstd_number can represent values much larger than a regular integer can,
 * which may lead to unexpected behaviour when this narrowing conversion is done.
 *
 * @param number The number to create a representation of.
 * @return Returns an integer representation of the specified number.
 */
int bstd_number_to_int(bstd_number* number) {
    const int value_abs = (int)number->value * ipow(10, (int)number->scale);
    return number->positive ? value_abs : -value_abs;
}

void bstd_assign_int(bstd_number* number, const int value) {

    int mag = ipow(10, number->length);
    int mask = ((int)value / mag) * mag;
    int cropped_value = abs(value) - mask;

    number->positive = value >= 0;
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
