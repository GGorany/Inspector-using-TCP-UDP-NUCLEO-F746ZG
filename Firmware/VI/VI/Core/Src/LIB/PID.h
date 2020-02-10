/*
 * qPIDs.h
 *
 *  Created on: 2020. 2. 4.
 *      Author: DHKim
 */

#ifndef LIB_PID_H_
#define LIB_PID_H_


#define DEFAULT_MAXERROR 10e8
#define DEFAULT_MAXSUMERROR 10e12


#include <math.h>


struct PID_DATA{
	float lastValue;
	float Kp;
	float Ki;
	float Kd;
	float sumError;
	float maxError;
	float maxSumError;
};

void initializePID(struct PID_DATA *pid, float p, float i, float d);

int16_t stepPID(struct PID_DATA *pid, float value, float reference);

void resetSumError(struct PID_DATA *pid);



#endif /* LIB_PID_H_ */
