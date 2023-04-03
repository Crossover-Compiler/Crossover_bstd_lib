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

bstd_number* bstd_sum(const bstd_number *lhs, const bstd_number *rhs) {

    uint64_t s = max(lhs->scale, rhs->scale);
    int64_t a = bstd_number_to_int(lhs) * ipow(10, (int64_t)((-lhs->scale) + s));
    int64_t b = bstd_number_to_int(rhs) * ipow(10, (int64_t)((-rhs->scale) + s));
    int64_t result = a + b;
    uint64_t length = result == 0 ? 1 : (uint64_t)ceill(log10l(labs(result)));

    bstd_number* number = (bstd_number*)malloc(sizeof(bstd_number));
    number->value = (uint64_t)labs(result);
    number->scale = s;
    number->positive = result >= 0;
    number->isSigned = !number->positive;
    number->length = (length <= 18) ? length : 18;

    return number;
}
