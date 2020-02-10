/*
 * VI_Data.h
 *
 *  Created on: Oct 22, 2019
 *      Author: DHKim
 */

#ifndef ASW_VI_DATA_H_
#define ASW_VI_DATA_H_


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include <stdio.h>

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/
#define Mem_ADDR_Setting_Data_1			0x0100
#define Mem_ADDR_Setting_Data_2			0x0200
#define DataLength_Setting_Data_1		40
#define DataLength_Setting_Data_2		26
#define DataLength_Status_Data_Type		36

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/
typedef union
{
	struct
	{
		uint8_t CAM0_Enable;				// 0x1: 사용  0x0: 미사용
		uint8_t CAM1_Enable;				// 0x1: 사용  0x0: 미사용
		uint8_t CAM2_Enable;				// 0x1: 사용  0x0: 미사용
		uint8_t CAM3_Enable;				// 0x1: 사용  0x0: 미사용
		uint32_t CAM0_position;				// 입력 센서와 CAM 0 사이의 Encoder 카운팅
		uint32_t CAM1_position;				// 입력 센서와 CAM 1 사이의 Encoder 카운팅
		uint32_t CAM2_position;				// 입력 센서와 CAM 2 사이의 Encoder 카운팅
		uint32_t CAM3_position;				// 입력 센서와 CAM 3 사이의 Encoder 카운팅
		uint32_t OK_Expose_position;		// 입력 센서와 OK 배출 사이의 Encoder 카운팅
		uint32_t NG1_Expose_position;		// 입력 센서와 NG1 배출 사이의 Encoder 카운팅
		uint32_t NG2_Expose_position;		// 입력 센서와 NG2 배출 사이의 Encoder 카운팅
		uint32_t UNTREAT_Expose_position;	// 입력 센서와 미처리 배출 사이의 Encoder 카운팅
		uint16_t Servo_Motor_Speed;			// 10 ~ 10000 Hz	값으로는 1 ~ 1000 (MAX 650)
		uint16_t dummy1;
	} w;
	uint8_t Data[DataLength_Setting_Data_1];
} Setting_Data_1_Type;

typedef union
{
	struct
	{
		uint16_t CAMResult_WaitTime;		// default 1000 ms
		uint16_t OK_Expose_Time;			// default 200 ms
		uint16_t NG1_Expose_Time;			// default 200 ms
		uint16_t NG2_Expose_Time;			// default 200 ms
		uint16_t UNTREAT_Expose_Time;		// default 200 ms
		uint16_t STOP_DelayTime_After_STOPBUTTON;		// 스탑 버튼 눌러진 이후 진짜 stop 까지의 딜레이 시간
		uint16_t START_DelayTime_After_STARTBUTTON;		// 스타트 버튼 눌러진 이후 진짜 start 까지의 딜레이 시간
		uint16_t Input_DelayTime;			// 정해진 시간동안 입력 센서 감지가 안될 경우 알람 발생.
		uint16_t Input_DelayTime_to_Stop;	// Supply_DelayTime 이후 장비 정지 시간
		uint8_t Lighting_Trigger_Enable;	// 조명 트리거 사용 여부   0: 사용 안함(계속 ON)   1: 트리거 시간 사용
		uint8_t dummy0;
		uint32_t Lighting_Trigger_Position; // 조명 켜지는 위치 : 해당 CAM 위치와의 차이 값. CAM position 의 이전.
		uint16_t Lighting_Trigger_ON_Time; // 조명이 켜진 후 XXX Ms 이후 조명이 꺼짐.
	} w;
	uint8_t Data[DataLength_Setting_Data_2];
} Setting_Data_2_Type;

typedef union
{
	struct
	{
		uint32_t CAM0_Trigger_Count;	// CAM 0 를 동작시킨 트리거 횟수
		uint32_t CAM1_Trigger_Count;	// CAM 1 를 동작시킨 트리거 횟수
		uint32_t CAM2_Trigger_Count;	// CAM 2 를 동작시킨 트리거 횟수
		uint32_t CAM3_Trigger_Count;	// CAM 3 를 동작시킨 트리거 횟수
		uint32_t Input_Sensing_Count;	// 제품 입력 센싱의 횟수
		uint32_t OK_Expose_Count;		// Total OK expose
		uint32_t NG1_Expose_Count;		// Total NG1 expose
		uint32_t NG2_Expose_Count;		// Total NG2 expose
		uint32_t UNTREAT_Expose_Count;	// Total Untreated expose
	} w;
	uint8_t Data[DataLength_Status_Data_Type];
} Status_Data_Type;

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/
void VI_Data_Status_Data_Reset(void);
void VI_Data_Setting_Data_Read_from_E2P(void);

void VI_Data_Setting_Data_1_Write_to_E2P(void);
void VI_Data_Setting_Data_2_Write_to_E2P(void);

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/
extern Setting_Data_1_Type setting_Data_1;
extern Setting_Data_2_Type setting_Data_2;
extern Status_Data_Type status_Data;

extern uint8_t Is_Prohibit_Expose;
extern uint8_t Is_StartInspection;

extern uint8_t Is_JogMode;


#endif /* ASW_VI_DATA_H_ */
