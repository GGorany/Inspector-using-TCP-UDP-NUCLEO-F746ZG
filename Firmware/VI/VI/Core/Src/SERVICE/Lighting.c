/*
 * Lighting.c
 *
 *  Created on: 2019. 11. 25.
 *      Author: DHKim
 */


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include "VI_Data.h"
#include "Lighting.h"

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/
void Lighting_Trigger_Control(Lighting_Type* lit);

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/
Lighting_Type lighting0 = { 100, 0, set_LIGHT_0 };
Lighting_Type lighting1 = { 100, 0, set_LIGHT_1 };
Lighting_Type lighting2 = { 100, 0, set_LIGHT_2 };
Lighting_Type lighting3 = { 100, 0, set_LIGHT_3 };


/*--------------------------------------------------------------------------*/
/* Name      | Lighting_Init                                                */
/*--------------------------------------------------------------------------*/
void Lighting_Init(void)
{
	lighting0.Position = setting_Data_1.w.CAM0_position - setting_Data_2.w.Lighting_Trigger_Position;
	lighting1.Position = setting_Data_1.w.CAM1_position - setting_Data_2.w.Lighting_Trigger_Position;
	lighting2.Position = setting_Data_1.w.CAM2_position - setting_Data_2.w.Lighting_Trigger_Position;
	lighting3.Position = setting_Data_1.w.CAM3_position - setting_Data_2.w.Lighting_Trigger_Position;

	lighting0.pSetLIGHT(Output_PIN_Low);
	lighting1.pSetLIGHT(Output_PIN_Low);
	lighting2.pSetLIGHT(Output_PIN_Low);
	lighting3.pSetLIGHT(Output_PIN_Low);
}

/*--------------------------------------------------------------------------*/
/* Name      | Lighting_Mian                                                */
/*--------------------------------------------------------------------------*/
void Lighting_Mian(void)
{
	if (setting_Data_2.w.Lighting_Trigger_Enable == 0x00)	// Keep Lighting
	{
		lighting0.pSetLIGHT(Output_PIN_High);
		lighting1.pSetLIGHT(Output_PIN_High);
		lighting2.pSetLIGHT(Output_PIN_High);
		lighting3.pSetLIGHT(Output_PIN_High);
	}
	else // (setting_Data_2.w.Lighting_Trigger_Enable == 0x01)	// using Trigger Time
	{
		Lighting_Trigger_Control(&lighting0);
		Lighting_Trigger_Control(&lighting1);
		Lighting_Trigger_Control(&lighting2);
		Lighting_Trigger_Control(&lighting3);
	}
}

/*--------------------------------------------------------------------------*/
/* Name      | Lighting_Trigger_ON                                          */
/*--------------------------------------------------------------------------*/
void Lighting_Trigger_ON(Lighting_Type* lit)
{
	if (setting_Data_2.w.Lighting_Trigger_Enable == 0x00)	// Keep Lighting
	{
		return;
	}

	lit->pSetLIGHT(Output_PIN_High);
	lit->TriggerONTime = setting_Data_2.w.Lighting_Trigger_ON_Time;
}

/*--------------------------------------------------------------------------*/
/* Name      | Lighting_Trigger_Control                                     */
/*--------------------------------------------------------------------------*/
void Lighting_Trigger_Control(Lighting_Type* lit)
{
	if (lit->TriggerONTime != 0)
	{
		lit->TriggerONTime--;
	}
	else	// (lit->TriggerONTime == 0)
	{
		lit->pSetLIGHT(Output_PIN_Low);
		lit->TriggerONTime = 0;
	}
}

