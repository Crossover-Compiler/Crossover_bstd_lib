#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * todo: doc
 */
typedef struct bstd_number_t {
    uint64_t value;                                 // 8    0x00                        0x00
    uint64_t scale;                                 // 8    0x08                        0x08
    uint8_t length;                                 // 1    0x10                        0x10
    bool isSigned; // todo: change bool to uint8_t  // 1    0x11
    bool positive;                                  // 1    0x12 for a loength of 19.
} bstd_number;

