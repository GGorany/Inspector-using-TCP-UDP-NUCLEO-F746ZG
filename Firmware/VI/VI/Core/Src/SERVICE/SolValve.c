/*
 * SolValve.c
 *
 *  Created on: Nov 22, 2019
 *      Author: DHKim
 */


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include "VI_Data.h"
#include "SolValve.h"

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/
void SolValve_Control(SolValve_Type* sol);

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/
SolValve_Type solValve_OK = { &setting_Data_1.w.OK_Expose_position, &setting_Data_2.w.OK_Expose_Time, 0, set_SOL_OK };
SolValve_Type solValve_NG1 = { &setting_Data_1.w.NG1_Expose_position, &setting_Data_2.w.NG1_Expose_Time, 0, set_SOL_NG1 };
SolValve_Type solValve_NG2 = { &setting_Data_1.w.NG2_Expose_position, &setting_Data_2.w.NG2_Expose_Time, 0, set_SOL_NG2 };
SolValve_Type solValve_UNTREAT = { &setting_Data_1.w.UNTREAT_Expose_position, &setting_Data_2.w.UNTREAT_Expose_Time, 0, set_SOL_UNTREAT };

/*--------------------------------------------------------------------------*/
/* Name      | SolValve_Init                                                */
/*--------------------------------------------------------------------------*/
void SolValve_Init(void)
{
	solValve_OK.pSetSOL(Output_PIN_Low);
	solValve_NG1.pSetSOL(Output_PIN_Low);
	solValve_NG2.pSetSOL(Output_PIN_Low);
	solValve_UNTREAT.pSetSOL(Output_PIN_Low);
}

/*--------------------------------------------------------------------------*/
/* Name      | SolValve_Main                                                */
/*--------------------------------------------------------------------------*/
void SolValve_Main(void)
{
	SolValve_Control(&solValve_OK);
	SolValve_Control(&solValve_NG1);
	SolValve_Control(&solValve_NG2);
	SolValve_Control(&solValve_UNTREAT);
}

/*--------------------------------------------------------------------------*/
/* Name      | SolValve_Activate                                            */
/*--------------------------------------------------------------------------*/
void SolValve_Activate(SolValve_Type* sol)
{
	sol->pSetSOL(Output_PIN_High);
	sol->ONTime = *(sol->pSettingTime);
}

/*--------------------------------------------------------------------------*/
/* Name      | SolValve_Control                                             */
/*--------------------------------------------------------------------------*/
void SolValve_Control(SolValve_Type* sol)
{
	if (sol->ONTime != 0)
	{
		sol->ONTime--;
	}
	else	// (sol->ONTime == 0)
	{
		sol->pSetSOL(Output_PIN_Low);
		sol->ONTime = 0;
	}
}

