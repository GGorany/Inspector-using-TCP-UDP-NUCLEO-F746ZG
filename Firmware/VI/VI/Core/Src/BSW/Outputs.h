/*
 * Outputs.h
 *
 *  Created on: Jan 24, 2020
 *      Author: DHKim
 */

#ifndef SRC_BSW_OUTPUTS_H_
#define SRC_BSW_OUTPUTS_H_


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/
typedef enum
{
	Output_PIN_Low     = 0U,
	Output_PIN_High    = 1U
}OutputPinState;

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/
void set_CAM_0(OutputPinState state);
void set_CAM_1(OutputPinState state);
void set_CAM_2(OutputPinState state);
void set_CAM_3(OutputPinState state);

void set_LIGHT_0(OutputPinState state);
void set_LIGHT_1(OutputPinState state);
void set_LIGHT_2(OutputPinState state);
void set_LIGHT_3(OutputPinState state);

void set_SOL_OK(OutputPinState state);
void set_SOL_NG1(OutputPinState state);
void set_SOL_NG2(OutputPinState state);
void set_SOL_UNTREAT(OutputPinState state);

void set_LINE_FEEDER(OutputPinState state);
void set_HOPPER(OutputPinState state);
void set_CONVEYOR(OutputPinState state);
void set_SERVO_READY(OutputPinState state);
void set_SERVO_EMG(OutputPinState state);
void set_START_BUTTON_LAMP(OutputPinState state);
void set_STOP_BUTTON_LAMP(OutputPinState state);
void set_TOWER_LAMP_GREEN(OutputPinState state);
void set_TOWER_LAMP_RED(OutputPinState state);

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/


#endif /* SRC_BSW_OUTPUTS_H_ */
