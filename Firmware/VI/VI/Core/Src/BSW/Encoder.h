/*
 * Encoder.h
 *
 *  Created on: Oct 20, 2019
 *      Author: DHKim
 */

#ifndef SERVO_ENCODER_H_
#define SERVO_ENCODER_H_


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include <stdio.h>
#include "main.h"

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/
#define A_Z_RATIO	176

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/
void Encoder_Init(void);

uint32_t Encoder_Get_A_Counter(void);

void Encoder_Clear_Z_Counter(void);
void Encoder_Clear_A_Counter(void);

void Encoder_Z_Pin_EXTI_Callback(GPIO_PinState pinState);


void Encoder_Test_Count_Up(void);



#endif /* SERVO_ENCODER_H_ */