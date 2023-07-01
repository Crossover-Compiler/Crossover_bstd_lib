#pragma once

#include <stdbool.h>
#include "picture.h"
#include <stddef.h>

#ifndef BSTD_PICTURE_MASKS
#define BSTD_PICTURE_MASKS
#define BSTD_MASK_A 'A'
#define BSTD_MASK_X 'X'
#define BSTD_MASK_9 '9'
#endif

#ifndef BSTD_SPACE
#define BSTD_SPACE ' '
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Creates a new bstd_picture struct with a copy of the specified mask string.
 * The new bstd_picture's bytes are initialized with default values under its mask.
 * Note: the caller still owns the mask string.
 * @param mask The mask for which to create the picture.
 * @return Returns a new bstd_picture struct with default bytes under the specified mask.
 */
bstd_picture* bstd_create_picture(char *mask_str);

 /**
* Creates a new bstd_picture struct containing direct copies of the specified bytes and mask parameters.
* Bytes are copied directly and are not checked of their validity under the specified mask.
* Note: The caller still owns the bytes and mask pointers and they may safely be freed (the picture contains copies).
* @param bytes The bytes to copy into the new bstd_picture.
* @param mask The mask to copy into the new bstd_picture.
* @param length The length of the new bstd_picture.
* @return Returns a new bstd_picture struct populated with direct copies of the specified bytes and mask.
*/
bstd_picture *bstd_picture_of(unsigned char *bytes, char *mask, uint8_t length);

/**
 * Initializes the content of this picture with the appropriate default values for its mask.
 * @param picture The picture to initialize.
 */
void bstd_picture_init(bstd_picture* picture);

/**
* Copies the content of the specified value picture to the specified assignee.
* TODO: Should ensure that the representation of both pictures is correct under their mask.
* @param assignee The picture to copy the contents of the specified picture to.
* @param target The picture whose content to copy into the specified assignee.
*/
void bstd_assign_picture(bstd_picture *assignee, const bstd_picture *value);

/**
* Creates a C-style string representation of the specified picture.
* The created representation is formatted according to the specified picture's constraints.
* @param picture The picture to create a C-style string representation of.
* @return Returns a C-style string representation of the specified picture.
*/
char *bstd_picture_to_cstr(const bstd_picture *picture); // todo: rename to bstd_picture_to_str

/**
* Assigns the specified c-style string to the specified picture.
* Assigned strings are converted according to the picture's constraints. This is the inverse of bstd_picture_to_cstr.
* @param assignee The picture to assign the specified string to.
* @param str The c-style string to copy_buffer to the specified picture. Must be null-terminated.
*/
void bstd_assign_str(bstd_picture *assignee, const char *str);

/**
 * Gets the default value for the specified mask.
 * @param mask The mask for which to get the default value.
 * @return Returns the default value for the specified mask.
 */
unsigned char bstd_default_value(char mask);

/**
* Creates a character representation of the specified byte under the specified mask.
* This follows the BabyCobol PICTURE format specification.
* @param byte The byte to create a representation of.
* @param mask The mask to apply to the specified byte.
* @return Returns a character representation of the specified byte under the specified mask.
*/
char bstd_mask(unsigned char byte, char mask);

/**
* Creates a byte representation of the specified character under the specified mask.
* For legal values under a specified mask, this is the inverse function of bstd_mask.
* @param c The character to create a representation of.
* @param mask The mask to apply to the specified byte.
* @return Returns a character representation of the specified byte under the specified mask.
*/
unsigned char bstd_unmask(char c, char mask);

/**
 *  todo: remove; bstd_picture_to_cstr is sufficient.
 * @param picture
 * @param advancing
 */
void bstd_print_picture(bstd_picture picture, bool advancing);

#ifdef __cplusplus
}
#endif // __cplusplus
