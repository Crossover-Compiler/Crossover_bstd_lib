//
// Created by manta on 11/10/22.
//

#ifndef CROSSOVER_PICUTILS_H
#define CROSSOVER_PICUTILS_H

#include "picture.h"

 /**
* todo: doc. Make sure it copies the arrays!
* @param bytes
* @param mask
* @param length
* @return
*/
bstd_Picture *bstd_picutils_of(char *bytes, char *mask, uint8_t length);

/**
* todo: doc. assigns picture to another
* @param asignee
* @param target
* @return
*/
bstd_Picture *bstd_picutils_assign(bstd_Picture *asignee, bstd_Picture *target);

/**
* todo: doc
* @param picture
* @return
*/
char *bstd_picutils_to_cstr(bstd_Picture *picture);

/**
* todo: doc
* @param c
* @param mask
* @return
*/
char bstd_picutils_mask_char(char c, char mask);

#endif //CROSSOVER_PICUTILS_H
