/*
 * Bolt.c
 *
 *  Created on: Oct 20, 2019
 *      Author: DHKim
 */


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include "Bolt.h"
#include <stdlib.h>
#include "../LIB/emlist.h"

#include "../BSW/Inputs.h"

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
LinkedList* listBolt = NULL;
LinkedListIterator iterator = {NULL};
uint8_t Is_Bolt_Getting = 0;

/*--------------------------------------------------------------------------*/
/* Name      | Bolt_Init                                                    */
/*--------------------------------------------------------------------------*/
void Bolt_Init(void)
{
	if (listBolt != NULL)
	{
		emlist_destroy(listBolt);
	}

	listBolt = emlist_create();
	iterator.next = NULL;
	Is_Bolt_Getting = 0;
}

/*--------------------------------------------------------------------------*/
/* Name      | Bolt_Add                                                     */
/*--------------------------------------------------------------------------*/
void Bolt_Add(uint32_t number, uint32_t inputposition)
{
	Bolt* bolt = (Bolt*)LIST_MALLOC(sizeof(Bolt));

	bolt->number = number;
	bolt->inputposition = inputposition;

	bolt->cam[0] = NONE;
	bolt->cam[1] = NONE;
	bolt->cam[2] = NONE;
	bolt->cam[3] = NONE;

	bolt->process.cam[0] = NOT_YET;
	bolt->process.cam[1] = NOT_YET;
	bolt->process.cam[2] = NOT_YET;
	bolt->process.cam[3] = NOT_YET;
	bolt->process.lighting[0] = NOT_YET;
	bolt->process.lighting[1] = NOT_YET;
	bolt->process.lighting[2] = NOT_YET;
	bolt->process.lighting[3] = NOT_YET;
	bolt->process.expose_OK = NOT_YET;
	bolt->process.expose_NG1 = NOT_YET;
	bolt->process.expose_NG2 = NOT_YET;
	bolt->process.expose_UNTREAT = NOT_YET;

	(void)emlist_insert(listBolt, (void*)bolt);
}

/*--------------------------------------------------------------------------*/
/* Name      | Bolt_Remove                                                  */
/*--------------------------------------------------------------------------*/
void Bolt_Remove(Bolt* bolt)
{
	(void)emlist_remove(listBolt, (void*)bolt);

	LIST_FREE(bolt);
}

/*--------------------------------------------------------------------------*/
/* Name      | matchBolt                                                    */
/*--------------------------------------------------------------------------*/
int matchBolt(void *a, void *b)
{
	if (a == b)
		return 1;

	return 0;
}

/*--------------------------------------------------------------------------*/
/* Name      | Bolt_Get_OnebyOne                                            */
/*--------------------------------------------------------------------------*/
Bolt* Bolt_Get_OnebyOne(void)
{
	LinkedListElement* node = NULL;

	if ((iterator.next == NULL) && (Is_Bolt_Getting == 0))
	{
		iterator = emlist_iterator(listBolt);
		Is_Bolt_Getting = 1;
	}

	node = emlist_iterator_next(&iterator);

	if (node == NULL)
	{
		Is_Bolt_Getting = 0;
		return NULL;
	}

	return (Bolt*)(node->value);
}

/*--------------------------------------------------------------------------*/
/* Name      | Bolt_Get_Count                                               */
/*--------------------------------------------------------------------------*/
uint16_t Bolt_Get_Count(void)
{
	return (uint16_t)emlist_size(listBolt);
}

/*--------------------------------------------------------------------------*/
/* Name      | Bolt_Get_Input                                               */
/*--------------------------------------------------------------------------*/
uint8_t Bolt_Get_Input(void)
{
	if (read_BOLTINPUT() == Input_PIN_High)
	{
		set_BOLTINPUT(Input_PIN_Low);
		return 1;
	}

	return 0;
}

