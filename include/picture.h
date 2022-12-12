//
// Created by manta on 11/10/22.
//

#ifndef CROSSOVER_PICTURE_H
#define CROSSOVER_PICTURE_H

#include <stdint.h>

typedef struct bstd_Picture {
    char *bytes;
    char *mask;
    uint8_t length;
} bstd_Picture;

#endif //CROSSOVER_PICTURE_H
