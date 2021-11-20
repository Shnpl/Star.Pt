#include "user_tim_init.h"

Status TIM1_User_Init()
{
	TIM1->BDTR |= 1<<15; //MOE bit set to 1
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	return 0;
}

Status TIM2_User_Init()
{
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
	return 0;
}

Status TIM15_User_Init()
{
	
	HAL_TIM_PWM_Start(&htim15,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim15,TIM_CHANNEL_2);
	
	TIM15->CCR1 = 1500;
	TIM15->CCR2 = 1500;
	return 0;
}
Status TIM16_User_Init()
{
	HAL_TIM_Base_Start_IT(&htim16); //Enable TIM16 and the IRQ of TIM16
    return 0;
}

Status TIM17_User_Init()
{
	HAL_TIM_Base_Start_IT(&htim17); //Enable TIM17 and the IRQ of TIM17
    return 0;
}

