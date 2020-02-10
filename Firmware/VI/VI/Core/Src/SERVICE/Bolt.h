/*
 * Bolt.h
 *
 *  Created on: Oct 20, 2019
 *      Author: DHKim
 */

#ifndef ASW_BOLT_H_
#define ASW_BOLT_H_


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include <stdio.h>
#include "main.h"

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/
typedef enum {
    CAM_NG1		= 1,
	CAM_NG2		= 2,
	CAM_NG3		= 3,
	CAM_OK		= 4,
	NONE		= 0xFF
} CamResult;

typedef enum {
    NOT_YET			= 0,
	DONE			= 1,
	WAITING_RESULT	= 2
} GlassProcessResult;

typedef struct {
	GlassProcessResult cam[4];
	GlassProcessResult lighting[4];
	GlassProcessResult expose_OK;
	GlassProcessResult expose_NG1;
	GlassProcessResult expose_NG2;
	GlassProcessResult expose_UNTREAT;
} Process;

typedef struct {
    uint32_t number;
    uint32_t inputposition;
    CamResult cam[4];
    Process process;
} Bolt;

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/
void Bolt_Init(void);

void Bolt_Add(uint32_t number, uint32_t inputposition);
void Bolt_Remove(Bolt* bolt);
uint16_t Bolt_Get_Count(void);

// Iterator
Bolt* Bolt_Get_OnebyOne(void);

// Bolt Input Pin
uint8_t Bolt_Get_Input(void);

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/


#endif /* ASW_BOLT_H_ */
