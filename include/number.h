//
// Created by bruh on 10/17/22.
//

#ifndef CROSSOVER_NUMBER_H
#define CROSSOVER_NUMBER_H

#include <stdint.h>
#include <stdbool.h>

/**
 * todo: doc
 */
typedef struct bstd_Number {

    uint64_t value;
    uint64_t scale;
    uint8_t length;
    bool isSigned;
    bool positive;

} bstd_Number;

#endif //CROSSOVER_NUMBER_H
