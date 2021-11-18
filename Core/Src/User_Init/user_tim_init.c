#include "user_tim_init.h"

Status TIM1_User_Init()
{
	TIM1->BDTR |= 1<<15; //MOE bit set to 1
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
}

Status TIM2_User_Init()
{
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
}