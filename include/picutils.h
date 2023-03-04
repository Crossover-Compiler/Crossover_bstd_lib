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
bstd_picture *bstd_picture_of(char *bytes, char *mask, uint8_t length);

/**
* todo: doc. assigns picture to another
* @param assignee
* @param target
* @return
*/
void bstd_assign_picture(bstd_picture *assignee, bstd_picture *value);

/**
* Copies the specified byte buffer into the specified picture.
* @param assignee The picture to copy the specified bytes to.
* @param bytes The byte buffer to copy to the specified picture.
* @param size The size of the specified byte buffer.
*/
void bstd_assign_bytes(bstd_picture *assignee, const char *bytes, uint8_t size);

/**
* Creates a C-style string representation of the specified picture.
* The created representation is formatted according to the specified picture's constraints.
* @param picture The picture to create a C-style string representation of.
* @return Returns a C-style string representation of the specified picture.
*/
char *bstd_picture_to_cstr(bstd_picture *picture);

/**
* Creates a character representation of the specified byte under the specified mask.
* This follows the BabyCobol PICTURE format specification.
* @param byte The byte to create a representation of.
* @param mask The mask to apply to the specified byte.
* @return Returns a character representation of the specified byte under the specified mask.
*/
char bstd_picture_mask_char(char byte, char mask);

#endif //CROSSOVER_PICUTILS_H
