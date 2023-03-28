#pragma once

#include <stdbool.h>
#include "picture.h"
#include <stddef.h>

/**
 * Deep copies the content of the specified source buffer to the specified target buffer.
 * The specified buffers must be of equal length.
 * @param source The buffer whose content to copy_buffer.
 * @param target The buffer to copy_buffer into.
 * @param length The length of the buffers.
 * @return Returns a reference to the target buffer.
 */
unsigned char* copy_buffer(const unsigned char* source, unsigned char* target, size_t length);

 /**
* todo: doc. Make sure it copies the arrays!
* @param bytes
* @param mask
* @param length
* @return
*/
bstd_picture *bstd_picture_of(unsigned char *bytes, char *mask, uint8_t length);

/**
* Copies the content of the specified value picture to the specified assignee.
* TODO: Should ensure that the representation of both pictures is correct under their mask.
* @param assignee The picture to copy the contents of the specified picture to.
* @param target The picture whose content to copy into the specified assignee.
*/
void bstd_assign_picture(bstd_picture *assignee, bstd_picture *value);

/**
* Copies the specified byte buffer into the specified picture.
* TODO: Should ensure that the representation of the assignee is correct under its mask after assigning the bytes.
* @param assignee The picture to copy the specified bytes to.
* @param bytes The byte buffer to copy to the specified picture.
* @param size The size of the specified byte buffer.
*/
void bstd_assign_bytes(bstd_picture *assignee, const unsigned char *bytes, uint8_t size);

/**
* Assigns the specified c-style string to the specified picture.
* Assigned strings are converted according to the picture's constraints. This is the inverse of bstd_picture_to_cstr.
* @param assignee The picture to assign the specified string to.
* @param str The c-style string to copy_buffer to the specified picture. Must be null-terminated.
*/
void bstd_assign_str(bstd_picture *assignee, char *str);

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
char bstd_picture_mask_char(unsigned char byte, char mask);

/**
* Creates a byte representation of the specified character under the specified mask.
* This is the inverse of bstd_picture_mask_char.
* @param c The character to create a representation of.
* @param mask The mask to apply to the specified byte.
* @return Returns a character representation of the specified byte under the specified mask.
*/
unsigned char bstd_picture_unmask_char(char c, char mask);

/**
 *  todo: doc
 * @param picture
 * @param advancing
 */
void bstd_print_picture(bstd_picture picture, bool advancing);