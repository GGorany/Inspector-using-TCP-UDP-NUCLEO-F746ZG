/*
 * VI_Data.c
 *
 *  Created on: Oct 22, 2019
 *      Author: DHKim
 */


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include "VI_Data.h"
#include "../BSW/E2P.h"

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
Setting_Data_1_Type setting_Data_1;
Setting_Data_2_Type setting_Data_2;
Status_Data_Type status_Data;

uint8_t Is_Prohibit_Expose = 0;
uint8_t Is_StartInspection = 0;

uint8_t Is_JogMode = 0;

/*--------------------------------------------------------------------------*/
/* Name      | VI_Data_Status_Data_Reset                                    */
/*--------------------------------------------------------------------------*/
void VI_Data_Status_Data_Reset(void)
{
	status_Data.w.CAM0_Trigger_Count = 0;
	status_Data.w.CAM1_Trigger_Count = 0;
	status_Data.w.CAM2_Trigger_Count = 0;
	status_Data.w.CAM3_Trigger_Count = 0;
	status_Data.w.Input_Sensing_Count = 0;
	status_Data.w.OK_Expose_Count = 0;
	status_Data.w.NG1_Expose_Count = 0;
	status_Data.w.NG2_Expose_Count = 0;
	status_Data.w.UNTREAT_Expose_Count = 0;
}

/*--------------------------------------------------------------------------*/
/* Name      | VI_Data_Setting_Data_Read_from_E2P                           */
/*--------------------------------------------------------------------------*/
void VI_Data_Setting_Data_Read_from_E2P(void)
{
	(void)E2P_Read(Mem_ADDR_Setting_Data_1, setting_Data_1.Data, DataLength_Setting_Data_1);
	(void)E2P_Read(Mem_ADDR_Setting_Data_2, setting_Data_2.Data, DataLength_Setting_Data_2);
}

/*--------------------------------------------------------------------------*/
/* Name      | VI_Data_Setting_Data_1_Write_to_E2P                          */
/*--------------------------------------------------------------------------*/
void VI_Data_Setting_Data_1_Write_to_E2P(void)
{
	(void)E2P_Write(Mem_ADDR_Setting_Data_1, setting_Data_1.Data, DataLength_Setting_Data_1);
}

/*--------------------------------------------------------------------------*/
/* Name      | VI_Data_Setting_Data_2_Write_to_E2P                          */
/*--------------------------------------------------------------------------*/
void VI_Data_Setting_Data_2_Write_to_E2P(void)
{
	(void)E2P_Write(Mem_ADDR_Setting_Data_2, setting_Data_2.Data, DataLength_Setting_Data_2);
}
