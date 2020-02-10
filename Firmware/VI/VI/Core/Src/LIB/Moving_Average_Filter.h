/*
 * Moving_Average_Filter.h
 *
 *  Created on: Nov 29, 2019
 *      Author: DH.Kim
 */

#ifndef LIB_MOVING_AVERAGE_FILTER_H_
#define LIB_MOVING_AVERAGE_FILTER_H_


/**********************************************************************************************************************
* MODULES USED
**********************************************************************************************************************/
#include <stdio.h>

/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/
typedef struct movingAverage_s
{
    uint16_t *buffer;      /**< Data buffer pointer */
    uint16_t size;        /**< Size of filter buffer */
    uint16_t index;       /**< Current location in buffer */
    uint16_t fill;        /**< Buffer filled level */
    uint32_t sum;          /**< Cumulative value of buffer */
    uint16_t filtered;     /**< Filtered output */
} movingAverage_t;

/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/
void moving_average_create(movingAverage_t *context, uint16_t *buffer, uint8_t bufferSize);
void moving_average_filter(movingAverage_t *context, uint16_t data);

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/


#endif /* LIB_MOVING_AVERAGE_FILTER_H_ */
