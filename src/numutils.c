#include <stdlib.h>
#include <stdio.h>
#include "../include/numutils.h"
#include "../include/arithmetic.h"

bstd_number* bstd_number_from_int(int value, uint64_t length, bool isSigned) {

    bstd_number* number = malloc(sizeof(bstd_number));

    (*number) = (bstd_number) {
        .value = 0,
        .scale = 0,
        .length = length,
        .isSigned = isSigned,
        .positive = false
    };

    bstd_assign_int(number, value);

    return number;
}

int bstd_number_is_integer(const bstd_number* number) {
    return !number->scale;
}

static int64_t number_to_signed_value(const bstd_number* number) {
    return !number->positive && number->isSigned ? -number->value : number->value;
}

int64_t bstd_number_to_int(const bstd_number* number) {

    if (bstd_number_is_integer(number)) {
        return number_to_signed_value(number);
    }

    return (int64_t) bstd_number_to_double(number);
}

double bstd_number_to_double(const bstd_number* number) {
    return number_to_signed_value(number) / (double)ipow(10, number->scale);
}

void bstd_assign_number(bstd_number* assignee, const bstd_number* value) {

    if (bstd_number_is_integer(value)) {

        const int64_t value_conv = bstd_number_to_int(value);

        if (bstd_number_is_integer(assignee)) {
            bstd_assign_int64(assignee, value_conv);
        } else {
            bstd_assign_double(assignee, (double)value_conv);
        }

    } else {

        const double value_conv = bstd_number_to_double(value);

        if (bstd_number_is_integer(assignee)) {
            bstd_assign_int64(assignee, (int64_t)value_conv);
        } else {
            bstd_assign_double(assignee, value_conv);
        }
    }
}

void bstd_assign_int(bstd_number* number, const int value) {
    bstd_assign_int64(number, value);
}

void bstd_assign_int64(bstd_number* number, const int64_t value) {

    int64_t abs_value = labs(value);
    int64_t mag = ipow(10, number->length - number->scale);
    int64_t mask = (abs_value / mag) * mag;
    int64_t cropped_value = (abs_value - mask) * ipow(10, number->scale);

    number->positive = !number->isSigned || value >= 0;
    number->value = cropped_value;
}

void bstd_assign_double(bstd_number* number, const double value) {

    int64_t mag1 = ipow(10, number->length);
    int64_t mag2 = ipow(10, number->scale);
    int64_t shift = (int64_t)(value * mag2);
    int64_t mask = (int64_t)((double)shift / mag1) * mag1;
    int64_t cropped_value = labs(shift - mask);

    number->positive = value >= 0;
    number->value = cropped_value;
}

bool bstd_greater_than(const bstd_number* lhs, const bstd_number* rhs) {

    const int64_t lhsInt = bstd_number_to_int(lhs);
    const int64_t rhsInt = bstd_number_to_int(rhs);

    return lhsInt > rhsInt;
}

bool bstd_less_than(const bstd_number* lhs, const bstd_number* rhs) {

    const int64_t lhsInt = bstd_number_to_int(lhs);
    const int64_t rhsInt = bstd_number_to_int(rhs);

    return lhsInt < rhsInt;
}

bool bstd_number_equals(const bstd_number* lhs, const bstd_number* rhs) {

    const int64_t lhsInt = bstd_number_to_int(lhs);
    const int64_t rhsInt = bstd_number_to_int(rhs);

    return lhsInt == rhsInt;
}

// TODO: Sign should be included in the string
char *bstd_number_to_cstr(bstd_number number) {

    char format[9];
    char* result;


    if (bstd_number_is_integer(&number)) {

        sprintf(format, "%%ld");
        result = malloc(sizeof(char*) * (number.length + 1));

        const int64_t value = bstd_number_to_int(&number);
        sprintf(result, format, value);

    } else {

        sprintf(format, "%%0%d.%ldf", (int)number.length + 1, number.scale);
        result = malloc(sizeof(char*) * (number.length + 2));

        const double value = bstd_number_to_double(&number);
        sprintf(result, format, value);
    }

    return result;
}

// TODO: Sign gets calculated here, but should be calculated in bstd_number_to_cstr!
void bstd_print_number(bstd_number number, bool spacer) {
    char *str = bstd_number_to_cstr(number);
    if (spacer) {
        if (number.positive && number.isSigned) {
            printf(" +%s", str);
        } else {
            printf(" %s", str);
        }
    } else {
        if (number.positive && number.isSigned) {
            printf("+%s", str);
        } else {
            printf("%s", str);
        }
    }
}
