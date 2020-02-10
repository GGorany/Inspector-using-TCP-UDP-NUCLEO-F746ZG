/*
 * Message.h
 *
 *  Created on: 2020. 2. 1.
 *      Author: DHKim
 */

#ifndef SRC_ASW_MESSAGE_H_
#define SRC_ASW_MESSAGE_H_



// Identifier
#define ID_Setting_1					0xA0A0
#define ID_Setting_2					0xA1A1

#define ID_Request_CAMResult			0xC0C0
#define ID_Answer_CAMResult				0xC1C1		// send

#define ID_Command_StartInspection		0xD0D0
#define ID_Command_Expose				0xD1D1
#define ID_Command_Reset				0xD2D2
#define ID_Command_JogModeSet			0xD3D3
#define ID_Command_JogPosition			0xD4D4

#define ID_Board_Message				0xE0E0		// send



#endif /* SRC_ASW_MESSAGE_H_ */
