#pragma once

#include "number.h"

uint64_t max(uint64_t a, uint64_t b);

int64_t ipow(int64_t base, uint64_t exp);

/**
 * Sums the specified left- and right-hand sides, and assigns the result to the specified left-hand side.
 * This function does not modify the right-hand side.
 * @param lhs The left-hand side of the addition.
 * @param rhs The right-hand side of the addition.
 */
void bstd_add(bstd_number *lhs, const bstd_number *rhs);

/**
 * Sums the specified left- and right-hand sides, and returns the result.
 * This function does not modify either of its parameters.
 * @param lhs The left-hand side of the addition.
 * @param rhs The right-hand side of the addition.
 */
bstd_number* bstd_sum(const bstd_number *lhs, const bstd_number *rhs);
