/*
 * Bytearray.c
 *
 *  Created on: 2020. 2. 1.
 *      Author: DHKim
 */


#include "Bytearray.h"


void uint32_to_bytearray(uint32_t src, uint8_t* result)
{
	result[3] = (uint8_t)((src >> 24) & 0x000000FF);
	result[2] = (uint8_t)((src >> 16) & 0x000000FF);
	result[1] = (uint8_t)((src >> 8) & 0x000000FF);
	result[0] = (uint8_t)(src & 0x000000FF);
}

void uint16_to_bytearray(uint16_t src, uint8_t* result)
{
	result[1] = (uint8_t)((src >> 8) & 0x00FF);
	result[0] = (uint8_t)(src & 0xFF);
}

uint32_t bytearray_to_uint32(uint8_t* src)
{
	uint32_t value = 0x00000000;

	value = (uint32_t)((src[3] << 24) & 0xFF000000);
	value += (uint32_t)((src[2] << 16) & 0x00FF0000);
	value += (uint32_t)((src[1] << 8) & 0x0000FF00);
	value += (uint32_t)(src[0] & 0x000000FF);

	return value;
}

uint16_t bytearray_to_uint16(uint8_t* src)
{
	uint16_t value = 0x0000;

	value = (uint16_t)((src[1] << 8) & 0xFF00);
	value += (uint16_t)(src[0] & 0x00FF);

	return value;
}

