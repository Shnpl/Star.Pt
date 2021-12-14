#include "tim_init.h"
/*
@ TIM1 Init 
@ 4 channel PWM
@ clock 72Mhz PWM 1KHz
@ period 1000
*/
void USER_TIM1_Init(void)
{
	TIM1->BDTR |= 1<<15; //MOE bit set to 1 ,for Advanced TIM
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	
	TIM1->CCR1 = 100;
	TIM1->CCR2 = 100;
	TIM1->CCR3 = 100;
	TIM1->CCR4 = 100;
}
