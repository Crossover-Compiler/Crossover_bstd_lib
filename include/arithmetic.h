//
// Created by bruh on 10/17/22.
//

#ifndef CROSSOVER_ARITHMETIC_H
#define CROSSOVER_ARITHMETIC_H

#include "number.h"

bstd_Number *bstd_add(bstd_Number *lhs, bstd_Number *rhs);

int64_t bstd_tosigned(bstd_Number* n);

int64_t ipow(int64_t base, int64_t exp);
#endif //CROSSOVER_ARITHMETIC_H
