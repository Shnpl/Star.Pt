#ifndef __PID_H__
#define __PID_H__

#include "main.h"
#include "general.h"

typedef struct
{
    float target_speed;   
    
	float proportion;
	float integral;
	float derivative;
	
	float err;
    float err_last;
	float err_last_2;
    
    float Kp,Ki,Kd;

    int32_t delta;
    int32_t PWM;   
}Delta_PID_TypeDef;

Status Delta_PID(Delta_PID_TypeDef* Object);
#endif
