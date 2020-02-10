/*
 * LED.c
 *
 *  Created on: 2020. 2. 2.
 *      Author: DHKim
 */

/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include "LED.h"
#include "main.h"

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/
#define LED_ON_TIME		10	// ms

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/
void LED_Trigger_Control(LED_Type* led);
void LED_GREEN(LED_State_Type status);
void LED_BLUE(LED_State_Type status);
void LED_RED(LED_State_Type status);

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/
LED_Type led_GREEN = { 0, LED_GREEN };
LED_Type led_BLUE = { 0, LED_BLUE };
LED_Type led_RED = { 0, LED_RED };


/*--------------------------------------------------------------------------*/
/* Name      | LED_Main                                                     */
/*--------------------------------------------------------------------------*/
void LED_Main(void)
{
	LED_Trigger_Control(&led_GREEN);
	LED_Trigger_Control(&led_BLUE);
	LED_Trigger_Control(&led_RED);
}

/*--------------------------------------------------------------------------*/
/* Name      | LED_Trigger_Control                                          */
/*--------------------------------------------------------------------------*/
void LED_Trigger_Control(LED_Type* led)
{
	if (led->TriggerONTime != 0)
	{
		led->TriggerONTime--;
	}
	else	// (led->TriggerONTime == 0)
	{
		led->pSetLED(LED_OFF);
		led->TriggerONTime = 0;
	}
}


void LED_GREEN(LED_State_Type status)
{
	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, (GPIO_PinState)status);
	led_GREEN.TriggerONTime = LED_ON_TIME;
}

void LED_BLUE(LED_State_Type status)
{
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, (GPIO_PinState)status);
	led_BLUE.TriggerONTime = LED_ON_TIME;
}

void LED_RED(LED_State_Type status)
{
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, (GPIO_PinState)status);
	led_RED.TriggerONTime = LED_ON_TIME;
}

