/*
 * Bytearray.h
 *
 *  Created on: 2020. 2. 1.
 *      Author: DHKim
 */

#ifndef SRC_LIB_BYTEARRAY_H_
#define SRC_LIB_BYTEARRAY_H_


#include <stdio.h>


void uint32_to_bytearray(uint32_t src, uint8_t* result);
void uint16_to_bytearray(uint16_t src, uint8_t* result);
uint32_t bytearray_to_uint32(uint8_t* src);
uint16_t bytearray_to_uint16(uint8_t* src);



#endif /* SRC_LIB_BYTEARRAY_H_ */
