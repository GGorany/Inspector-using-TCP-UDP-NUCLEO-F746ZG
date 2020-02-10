/*
 * Camera.c
 *
 *  Created on: 2019. 11. 25.
 *      Author: DHKim
 */


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include "VI_Data.h"
#include "Camera.h"

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/
#define check_bit(field, loc)    (0 != ((field) & (0x1 << (loc))))

#define CameraTriggerONTime		20	// ms

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/
void Camera_Trigger_Control(CAMERA_Type* cam);

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/
CAMERA_Type cam0 = { &setting_Data_1.w.CAM0_Enable, CAM_STATUS_None, 0, 0, set_CAM_0 };
CAMERA_Type cam1 = { &setting_Data_1.w.CAM1_Enable, CAM_STATUS_None, 0, 0, set_CAM_1 };
CAMERA_Type cam2 = { &setting_Data_1.w.CAM2_Enable, CAM_STATUS_None, 0, 0, set_CAM_2 };
CAMERA_Type cam3 = { &setting_Data_1.w.CAM3_Enable, CAM_STATUS_None, 0, 0, set_CAM_3 };


/*--------------------------------------------------------------------------*/
/* Name      | Camera_Main                                                  */
/*--------------------------------------------------------------------------*/
void Camera_Main(void)
{
	Camera_Trigger_Control(&cam0);
	Camera_Trigger_Control(&cam1);
	Camera_Trigger_Control(&cam2);
	Camera_Trigger_Control(&cam3);
}

/*--------------------------------------------------------------------------*/
/* Name      | Camera_Trigger_ON                                            */
/*--------------------------------------------------------------------------*/
void Camera_Trigger_ON(CAMERA_Type* cam)
{
	if (*(cam->pEnable) != 1)
	{
		return;
	}

	cam->pSetCAM(Output_PIN_High);
	cam->TriggerONTime = CameraTriggerONTime;
	cam->status = CAM_STATUS_WaitingResult;
}

/*--------------------------------------------------------------------------*/
/* Name      | Camera_Trigger_Control                                       */
/*--------------------------------------------------------------------------*/
void Camera_Trigger_Control(CAMERA_Type* cam)
{
	if (cam->TriggerONTime != 0)
	{
		cam->TriggerONTime--;
	}
	else
	{
		cam->pSetCAM(Output_PIN_Low);
		cam->TriggerONTime = 0;
	}
}

