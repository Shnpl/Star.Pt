#include "command.h"
#include <math.h>

/*
@Test command
@using L298N
@test on Tank
*/

uint8_t direct_command_0x01(int8_t motor_spd1,int8_t motor_spd2)
{
	if(motor_spd1>100 ||
		motor_spd1<-100||
		motor_spd2>100 ||
		motor_spd2<-100)
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