#pragma once

#include <stdint.h>
#include <stdbool.h>

#define BSTD_NUMBER_MAX_LENGTH 19

/**
 * This is a complete representation of a BabyCobol numeric value.
 */
typedef struct bstd_number_t {
    uint64_t value;
    uint64_t scale;
    uint8_t length;
    bool isSigned;
    bool positive;
} bstd_number;

