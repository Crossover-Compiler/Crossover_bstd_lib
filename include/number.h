#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * todo: doc
 */
typedef struct bstd_number_t {
    uint64_t value;
    uint64_t scale;
    uint8_t length;
    bool isSigned; // todo: change bool to uint8_t
    bool positive;
} bstd_number;

