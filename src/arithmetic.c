#include "../include/arithmetic.h"
#include "../include/numutils.h"
#include <stdlib.h>
#include <math.h>

uint64_t max(uint64_t a, uint64_t b) {
    return a > b ? a : b;
}

int64_t ipow(int64_t base, uint64_t exp) {
    int64_t result = 1;

    for (;;) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

void bstd_add(bstd_number *lhs, const bstd_number *rhs) {
    const bstd_number* sum = bstd_sum(lhs, rhs);
    bstd_assign_number(lhs, sum);
    free((void*)sum);
}

void bstd_subtract(bstd_number *lhs, const bstd_number *rhs) {
    bstd_number rhs_copy = *rhs;
    rhs_copy.isSigned = true;
    if (rhs_copy.positive == 0) {
        rhs_copy.positive = 1;
    } else {
        rhs_copy.positive = 0;
    }

    const bstd_number* sum = bstd_sum(lhs, &rhs_copy);
    bstd_assign_number(lhs, sum);
    free((void*)sum);
}

bstd_number* bstd_sum(const bstd_number *lhs, const bstd_number *rhs) {

    uint64_t s = max(lhs->scale, rhs->scale);
    int64_t a = bstd_number_to_int(lhs) * ipow(10, (int64_t)((-lhs->scale) + s));
    int64_t b = bstd_number_to_int(rhs) * ipow(10, (int64_t)((-rhs->scale) + s));
    int64_t result = a + b;
    uint64_t length = result == 0 ? 1 : (uint64_t)ceill(log10l(labs(result)));

    if (length > 18){
        int overflow = ((int)length) - 18;
        length = 18;
        result = result % (int64_t)ipow(10, floor(log10((double)result) - overflow + 1));
    }

    bstd_number* number = (bstd_number*)malloc(sizeof(bstd_number));
    number->value = (uint64_t)labs(result);
    number->scale = s;
    number->positive = result >= 0;
    number->isSigned = !number->positive;
    number->length = length;

    return number;
}

void bstd_add_int(bstd_number *lhs, int64_t rhs) {

    if (bstd_number_is_integer(lhs)) {

        const int64_t current = bstd_number_to_int(lhs);
        const int64_t sum = current + rhs;

        bstd_assign_int64(lhs, sum);

    } else {

        const double current = bstd_number_to_double(lhs);
        const double sum = current + rhs;

        bstd_assign_double(lhs, sum);
    }
}

void bstd_subtract_int(bstd_number *lhs, int64_t rhs) {

    if (bstd_number_is_integer(lhs)) {

        const int64_t current = bstd_number_to_int(lhs);
        const int64_t difference = current - rhs;

        bstd_assign_int64(lhs, difference);

    } else {

        const double current = bstd_number_to_double(lhs);
        const double difference = current - rhs;

        bstd_assign_double(lhs, difference);
    }
}

void bstd_add_double(bstd_number *lhs, double rhs) {

    if (bstd_number_is_integer(lhs)) {

        const int64_t current = bstd_number_to_int(lhs);
        const int64_t sum = current + rhs;

        bstd_assign_int64(lhs, sum);

    } else {

        const double current = bstd_number_to_double(lhs);
        const double sum = current + rhs;

        bstd_assign_double(lhs, sum);
    }
}

void bstd_subtract_double(bstd_number *lhs, double rhs) {

    if (bstd_number_is_integer(lhs)) {

        const int64_t current = bstd_number_to_int(lhs);
        const int64_t difference = current - rhs;

        bstd_assign_int64(lhs, difference);

    } else {

        const double current = bstd_number_to_double(lhs);
        const double difference = current - rhs;

        bstd_assign_double(lhs, difference);
    }
}
