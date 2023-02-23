//
// Created by bruh on 10/17/22.
//

#ifndef CROSSOVER_ARITHMETIC_H
#define CROSSOVER_ARITHMETIC_H

#include "number.h"

int64_t ipow(int64_t base, int64_t exp);

bstd_number *bstd_add(bstd_number *lhs, bstd_number *rhs);

// todo: rename to something like "toint"
int64_t bstd_tosigned(bstd_number* n);

#endif //CROSSOVER_ARITHMETIC_H
