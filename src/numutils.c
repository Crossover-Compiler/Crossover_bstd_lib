#include <stdlib.h>
#include <stdio.h>
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
    int64_t mag2 = ipow(10, number->scale);
    int64_t shift = (int64_t)(value * mag2);
    int64_t mask = (int)((double)shift / mag1) * mag1;
    int64_t cropped_value = labs(shift - mask);

    number->positive = value >= 0;
    number->value = cropped_value;
}

// TODO: Sign does not get added here
char *bstd_number_to_cstr(bstd_number number) {
    double value = bstd_number_to_double(&number);
    char *raw_double = (char *) malloc(64);
    sprintf(raw_double, "%f", value);

    bool stringEnd = false;
    int k = 0;
    int str_length = 0;
    int digit_length = 0;
    while (!stringEnd) {
        if (raw_double[k] == '\00') {
            stringEnd = true;
            str_length = k;
        } else if (raw_double[k] == '.') {
            digit_length = k;
        }
        k++;
    }

    // Do int part
    char *int_part = (char *) malloc(64);
    int digits = number.length - number.scale;
    int i = 0;
    if (digits > digit_length) {
        int amount_of_front_0_to_go = digits - digit_length;
        while (amount_of_front_0_to_go > 0) {
            // front insert
            int_part[i] = '0';
            amount_of_front_0_to_go--;
            i++;

        }
        while (i < digits) {
            int_part[i] = raw_double[i - (digits - digit_length)];
            i++;
        }
    }

    if (digits == digit_length) {
        // just copy
        while (i < digits) {
            int_part[i] = raw_double[i];
            i++;
        }
    } else if (digits < digit_length) {
        int offset = digit_length - digits;
        // cut-off first amount_of_front_0_to_go amount, then just copy
        while (i < digits) {
            int_part[i] = raw_double[i + offset];
            i++;
        }
    }

    if (number.scale == 0) {
        // int
        int_part[i] = '\00';
        return int_part;
    }

    int_part[i] = '.';
    char* double_part = (char *) malloc(64);
    // start inserting decimals untill we run out of decimals, ten insert 0's
    int required_decimals = number.scale;
    int j = 0;
    while (j < required_decimals) {
        if (digit_length + 1 + j >= str_length) {
            double_part[j] = '0';
            int_part[i+1+j] = '0';
        } else {
            double_part[j] = raw_double[digit_length + 1 + j];
            int_part[i+1+j] = raw_double[digit_length + 1 + j];
        }
        j++;
    }
    int_part[i+1+j] = '\00';
    return int_part;
}

// TODO: Sign gets calculated here, but should be calculated in bstd_number_to_cstr!
void bstd_print_number(bstd_number number, bool advancing) {
    char *str = bstd_number_to_cstr(number);
    if (advancing) {
        if (number.positive && number.isSigned) {
            printf("+%s\r\n", str);
        } else {
            printf("%s\r\n", str);
        }
    } else {
        if (number.positive && number.isSigned) {
            printf("+%s", str);
        } else {
            printf("%s", str);
        }
    }
}