#include "user_motor_init.h"

Delta_PID_TypeDef M1;

Status M1_Init(void);


Status Motor_Init()
{
	M1_Init();
	return 0;
}

Status M1_Init()
{
	//Possible value 1{1000,6000,0.01}
	M1.Kp = 1000;
	M1.Ki = 6000;
	M1.Kd = 0.01;
	M1.target_speed = 0;
	return 0;
}
