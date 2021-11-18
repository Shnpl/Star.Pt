#include <stdio.h>
#include <math.h>

#include "command.h"
#include "encoder.h"
#include "PID.h"
#include "user_motor_init.h"

/*
@Test command
@using L298N
@test on Tank
*/

uint8_t direct_command_0x01(int32_t motor_spd1,int32_t motor_spd2)
{
	if(motor_spd1>1000 ||
		motor_spd1<-1000||
		motor_spd2>1000 ||
		motor_spd2<-1000)
	{
		return 1;
	}
	if(motor_spd1 >= 0)// motor1 forward
	{
		HAL_GPIO_WritePin(MOTOR_DIR_1_GPIO_Port,MOTOR_DIR_1_Pin,GPIO_PIN_RESET);
	}
	else//motor1 backward
	{
		HAL_GPIO_WritePin(MOTOR_DIR_1_GPIO_Port,MOTOR_DIR_1_Pin,GPIO_PIN_SET);
	}
	
	if(motor_spd2 >= 0)// motor2 forward
	{
		HAL_GPIO_WritePin(MOTOR_DIR_2_GPIO_Port,MOTOR_DIR_2_Pin,GPIO_PIN_RESET);
	}
	else//motor2 backward
	{
		HAL_GPIO_WritePin(MOTOR_DIR_2_GPIO_Port,MOTOR_DIR_2_Pin,GPIO_PIN_SET);
	}
	
	TIM1->CCR1 = abs(motor_spd1);
	TIM1->CCR2 = abs(motor_spd2);
	
	return 0;
}

/*
@Get_Current_Spd
*/
Status Get_Current_Spd(uint8_t target)
{
	if(target == 0x01)
	{
		printf("\r\nM1 SPEED:%f\r\n",M1_speed);
	}
	return 0;
}

Status Change_M1_Spd(int8_t target1000)
{
	M1.target_speed = (float)target1000/1000;	
	//PrintPID();
	return 0;
}
Status PrintPID()
{
	printf("\r\n");
	
	printf("\r\n  \
	Target:%f\r\n \
	Current speed:%f\r\n",M1.target_speed,M1_speed);
	
	printf("        \
	PWM:%d\r\n      \
	Error  0:%f\r\n \
	Error -1:%f\r\n \
	Error -2:%f\r\n \
	Delta   :%d\r\n \
	Ur      :%f%%\r\n",M1.PWM,M1.err,M1.err_last,M1.err_last_2,M1.delta,M1.err/M1.target_speed*100);
	
	printf("   \
	Kp:%f\r\n  \
	Ki:%f\r\n  \
	Kd:%f\r\n  \
	CCR2:%d\r\n",M1.Kp,M1.Ki,M1.Kd,TIM1->CCR2);
	return 0;
}

Status Change_M1_PID(int8_t Kp1000,int8_t Ki1000,int8_t Kd1000)
{
	M1.Kp = (float)Kp1000/1000;
	M1.Ki = (float)Ki1000/1000;
	M1.Kd = (float)Kd1000/1000;
	return 0;
}
