/*
 * TaskUDP.c
 *
 *  Created on: 2020. 1. 24.
 *      Author: DHKim
 */


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include <string.h>

#include "lwip/api.h"
#include "lwip/udp.h"
#include "ip_addr.h"

#include "TaskUDP.h"
#include "IP_Info.h"

#include "../BSW/Encoder.h"

#include "../SERVICE/Bolt.h"
#include "../SERVICE/VI_Data.h"
#include "../SERVICE/Version.h"
#include "../SERVICE/LED.h"
#include "../SERVICE/StateMachine.h"

#include "../LIB/Bytearray.h"

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/
#define sendDataLen		512

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/
static struct netconn *udpconn;
static struct netbuf *sentbuf;
ip_addr_t des_udpaddr;

uint8_t sendData[sendDataLen];


/*--------------------------------------------------------------------------*/
/* Name      | TaskUDP_Init                                                 */
/*--------------------------------------------------------------------------*/
void TaskUDP_Init(void)
{
	udpconn = netconn_new(NETCONN_UDP);

	IP4_ADDR(&des_udpaddr, IP0, IP1, IP2, IP3);

	(void)netconn_bind(udpconn, IP_ADDR_ANY, PORT_UDP_SERVER);
	(void)netconn_connect(udpconn, &des_udpaddr, PORT_UDP_SERVER);

	memset(sendData, 0, sendDataLen);
}

/*--------------------------------------------------------------------------*/
/* Name      | TaskUDP_Main                                                 */
/*--------------------------------------------------------------------------*/
void TaskUDP_Main(void)
{
	int dataNum = 0;
	uint16_t boltNum = 0;
	Bolt* bolt = NULL;
	err_t err;

	if (udpconn != NULL)
	{
		// version - 4 byte
		sendData[0] = version_0;
		sendData[1] = version_1;
		sendData[2] = version_2;
		sendData[3] = version_3;
		dataNum += 4;

		// status Data - 36 byte
		uint32_to_bytearray(status_Data.w.CAM0_Trigger_Count, &sendData[4]);
		uint32_to_bytearray(status_Data.w.CAM1_Trigger_Count, &sendData[8]);
		uint32_to_bytearray(status_Data.w.CAM2_Trigger_Count, &sendData[12]);
		uint32_to_bytearray(status_Data.w.CAM3_Trigger_Count, &sendData[16]);
		uint32_to_bytearray(status_Data.w.Input_Sensing_Count, &sendData[20]);
		uint32_to_bytearray(status_Data.w.OK_Expose_Count, &sendData[24]);
		uint32_to_bytearray(status_Data.w.NG1_Expose_Count, &sendData[28]);
		uint32_to_bytearray(status_Data.w.NG2_Expose_Count, &sendData[32]);
		uint32_to_bytearray(status_Data.w.UNTREAT_Expose_Count, &sendData[36]);
		dataNum += 36;

		// MODE - 1 byte
		sendData[dataNum] = (uint8_t)Get_VI_state();
		dataNum += 1;

		// Encoder Count - 4 byte
		uint32_to_bytearray(Encoder_Get_A_Counter(), &sendData[dataNum]);
		dataNum += 4;

		// bolt number - 2 byte
		boltNum = Bolt_Get_Count();
		uint16_to_bytearray(boltNum, &sendData[dataNum]);
		dataNum += 2;

		// bolt Instances
		if (boltNum != 0)
		{
			while(NULL != (bolt = (Bolt*)Bolt_Get_OnebyOne()))
			{
				// number - 4 byte
				uint32_to_bytearray(bolt->number, &sendData[dataNum]);
				dataNum += 4;

				// inputposition - 4 byte
				uint32_to_bytearray(bolt->inputposition, &sendData[dataNum]);
				dataNum += 4;

				// cam0 - 1 byte
				sendData[dataNum] = (uint8_t)bolt->cam[0];
				dataNum += 1;

				// cam1 - 1 byte
				sendData[dataNum] = (uint8_t)bolt->cam[1];
				dataNum += 1;

				// cam1 - 1 byte
				sendData[dataNum] = (uint8_t)bolt->cam[2];
				dataNum += 1;

				// cam1 - 1 byte
				sendData[dataNum] = (uint8_t)bolt->cam[3];
				dataNum += 1;
			}
		}

		sentbuf = netbuf_new();
		netbuf_alloc(sentbuf, dataNum);
		sentbuf->p->payload = (void*)sendData;
		//buf->addr.addr = 0;

		err = netconn_send(udpconn, sentbuf);

		if (err == ERR_OK)
			led_GREEN.pSetLED(LED_ON);

		netbuf_delete(sentbuf);
	}
}

