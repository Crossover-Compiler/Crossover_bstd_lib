#pragma once

#include "number.h"

/**
 * Determines whether the specified number represents an integer or not.
 * (A bstd_number is an integer iff its scale is equal to zero.)
 * @param number The number to evaluate.
 * @return Returns one iff the specified number represents an integer. Otherwise, returns zero.
 */
int bstd_number_is_integer(const bstd_number* number);

/**
 * Creates an integer representation for the specified bstd_number. The representation is an independent copy (setting it does not affect the specified bstd_number).
 * Note that instances of the type bstd_number can represent values much larger than a regular integer may be able to,
 * which may lead to unexpected behaviour when this narrowing conversion is done.
 *
 * @param number The number to create a representation of.
 * @return Returns an integer representation of the specified number.
 */
int64_t bstd_number_to_int(const bstd_number* number);

/**
 * Creates a number representation for the specified bstd_number. The representation is an independent copy (setting it does not affect the specified bstd_number).
 * Note that instances of the type bstd_number can represent values much larger than a regular double may be able to,
 * which may lead to unexpected behaviour when this narrowing conversion is done.
 *
 * @param number The number to create a representation of.
 * @return Returns a double representation of the specified number.
 */
double bstd_number_to_double(const bstd_number* number);

/**
 * Assigns the specified value to the specified assignee. If the numbers' constraints do not match, the assignee's constraints are leading.
 * @param assignee
 * @param value
 */
void bstd_assign_number(bstd_number* assignee, const bstd_number* value);

/**
 * Assigns the specified integer to the specified bstd_number, following the BabyCobol assignment specifications.
 * @param number The number to assign the specified integer to.
 * @param value The integer to assign to the specified number.
 */
void bstd_assign_int(bstd_number* number, int value);

/**
 * Assigns the specified 64-bit integer to the specified bstd_number, following the BabyCobol assignment specifications.
 * @param number The number to assign the specified integer to.
 * @param value The integer to assign to the specified number.
 */
void bstd_assign_int64(bstd_number* number, int64_t value);

/**
 * Assigns the specified double to the specified bstd_number, following the BabyCobol assignment specifications.
 * @param number The number to assign the specified double to.
 * @param value The double to assign to the specified number.
 */
void bstd_assign_double(bstd_number* number, double value);

/**
 * todo: doc
 * @param number
 * @param advancing
 */
void bstd_print_number(bstd_number number, bool advancing);

/**
 * todo: doc
 * @param number
 * @return
 */
char* bstd_number_to_cstr(bstd_number number);