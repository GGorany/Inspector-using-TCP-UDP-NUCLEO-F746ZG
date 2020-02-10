/*
 * Servo.c
 *
 *  Created on: 2019. 11. 26.
 *      Author: DHKim
 */


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include "../BSW/Encoder.h"

#include "../ASW/TaskTCP.h"

#include "StateMachine.h"
#include "VI_Data.h"
#include "Servo.h"

#include "../LIB/Bytearray.h"
#include "../LIB/PID.h"

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/
#define Kp		0.25
#define Ki		0.05
#define Kd		0.09
#define CONTROLLER_INTERVAL		50	// ms

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/
struct PID_DATA controller;
uint16_t countInterval = 0;

Direction_Type direction = Forward;

uint16_t jogSpeed = 0;


/*--------------------------------------------------------------------------*/
/* Name      | Servo_Init                                                   */
/*--------------------------------------------------------------------------*/
void Servo_Init(void)
{
	initializePID(&controller, Kp, Ki, Kd);
}

/*--------------------------------------------------------------------------*/
/* Name      | Servo_Main                                                   */
/*--------------------------------------------------------------------------*/
void Servo_Main(void)
{
	static uint16_t desiredSpeed = 0;
	static uint16_t currentSpeed = 0;

	desiredSpeed = (uint16_t)(setting_Data_1.w.Servo_Motor_Speed / 10);

	if (countInterval++ >= CONTROLLER_INTERVAL)
	{
		currentSpeed = (uint16_t)stepPID(&controller, (float)currentSpeed, (float)desiredSpeed);
		countInterval = 0;
	}

	switch (Get_VI_state())
	{
	case STATE_STOP:
		desiredSpeed = 0;

		if (currentSpeed < 10)
		{
			currentSpeed = 0;
			PWM_Set(Forward, 0);
		}

		break;

	case STATE_RUN:
	case STATE_STOPPING:
		PWM_Set(Forward, (uint16_t)(currentSpeed));
		break;

	case STATE_JOG_FINDING:
		PWM_Set(Forward, jogSpeed);
		break;

	case STATE_JOG_RUN:
		PWM_Set(direction, jogSpeed);
		break;

	default:
		break;
	}
}


/*--------------------------------------------------------------------------*/
/* Name      | Servo_SetJOG                                                 */
/*--------------------------------------------------------------------------*/
void Servo_SetJOG(Direction_Type dir, uint16_t speed)
{
	direction = dir;
	jogSpeed = speed;
}

