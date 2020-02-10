/*
 * Outputs.c
 *
 *  Created on: Jan 24, 2020
 *      Author: DHKim
 */


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include "main.h"
#include "Outputs.h"
#include "stm32f7xx_hal.h"

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/

/*--------------------------------------------------------------------------*/
/* Name      | CAM Triggers                                                 */
/*--------------------------------------------------------------------------*/
void set_CAM_0(OutputPinState state)
{
	HAL_GPIO_WritePin(CAM_0_GPIO_Port, CAM_0_Pin, (GPIO_PinState)state);
}

void set_CAM_1(OutputPinState state)
{
	HAL_GPIO_WritePin(CAM_1_GPIO_Port, CAM_1_Pin, (GPIO_PinState)state);
}

void set_CAM_2(OutputPinState state)
{
	HAL_GPIO_WritePin(CAM_2_GPIO_Port, CAM_2_Pin, (GPIO_PinState)state);
}

void set_CAM_3(OutputPinState state)
{
	HAL_GPIO_WritePin(CAM_3_GPIO_Port, CAM_3_Pin, (GPIO_PinState)state);
}

/*--------------------------------------------------------------------------*/
/* Name      | Light Triggers                                               */
/*--------------------------------------------------------------------------*/
void set_LIGHT_0(OutputPinState state)
{
	HAL_GPIO_WritePin(LIGHT_0_GPIO_Port, LIGHT_0_Pin, (GPIO_PinState)state);
}

void set_LIGHT_1(OutputPinState state)
{
	HAL_GPIO_WritePin(LIGHT_1_GPIO_Port, LIGHT_1_Pin, (GPIO_PinState)state);
}

void set_LIGHT_2(OutputPinState state)
{
	HAL_GPIO_WritePin(LIGHT_2_GPIO_Port, LIGHT_2_Pin, (GPIO_PinState)state);
}

void set_LIGHT_3(OutputPinState state)
{
	HAL_GPIO_WritePin(LIGHT_3_GPIO_Port, LIGHT_3_Pin, (GPIO_PinState)state);
}

/*--------------------------------------------------------------------------*/
/* Name      | Sol Valves                                                   */
/*--------------------------------------------------------------------------*/
void set_SOL_OK(OutputPinState state)
{
	HAL_GPIO_WritePin(SOL_OK_GPIO_Port, SOL_OK_Pin, (GPIO_PinState)state);
}

void set_SOL_NG1(OutputPinState state)
{
	HAL_GPIO_WritePin(SOL_NG1_GPIO_Port, SOL_NG1_Pin, (GPIO_PinState)state);
}

void set_SOL_NG2(OutputPinState state)
{
	HAL_GPIO_WritePin(SOL_NG2_GPIO_Port, SOL_NG2_Pin, (GPIO_PinState)state);
}

void set_SOL_UNTREAT(OutputPinState state)
{
	HAL_GPIO_WritePin(SOL_UNTREAT_GPIO_Port, SOL_UNTREAT_Pin, (GPIO_PinState)state);
}

/*--------------------------------------------------------------------------*/
/* Name      | Extras                                                       */
/*--------------------------------------------------------------------------*/
void set_LINE_FEEDER(OutputPinState state)
{
	HAL_GPIO_WritePin(LINE_FEEDER_GPIO_Port, LINE_FEEDER_Pin, (GPIO_PinState)state);
}

void set_HOPPER(OutputPinState state)
{
	HAL_GPIO_WritePin(HOPPER_GPIO_Port, HOPPER_Pin, (GPIO_PinState)state);
}

void set_CONVEYOR(OutputPinState state)
{
	HAL_GPIO_WritePin(CONVEYOR_GPIO_Port, CONVEYOR_Pin, (GPIO_PinState)state);
}

void set_SERVO_READY(OutputPinState state)
{
	HAL_GPIO_WritePin(SERVO_READY_GPIO_Port, SERVO_READY_Pin, (GPIO_PinState)state);
}

void set_SERVO_EMG(OutputPinState state)
{
	HAL_GPIO_WritePin(SERVO_EMG_GPIO_Port, SERVO_EMG_Pin, (GPIO_PinState)state);
}

void set_START_BUTTON_LAMP(OutputPinState state)
{
	HAL_GPIO_WritePin(START_BUTTON_LAMP_GPIO_Port, START_BUTTON_LAMP_Pin, (GPIO_PinState)state);
}

void set_STOP_BUTTON_LAMP(OutputPinState state)
{
	HAL_GPIO_WritePin(STOP_BUTTON_LAMP_GPIO_Port, STOP_BUTTON_LAMP_Pin, (GPIO_PinState)state);
}

void set_TOWER_LAMP_GREEN(OutputPinState state)
{
	HAL_GPIO_WritePin(TOWER_LAMP_GREEN_GPIO_Port, TOWER_LAMP_GREEN_Pin, (GPIO_PinState)state);
}

void set_TOWER_LAMP_RED(OutputPinState state)
{
	HAL_GPIO_WritePin(TOWER_LAMP_RED_GPIO_Port, TOWER_LAMP_RED_Pin, (GPIO_PinState)state);
}

