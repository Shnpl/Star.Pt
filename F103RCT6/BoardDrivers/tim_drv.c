#include "tim_drv.h"
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
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;
	TIM1->CCR4 = 0;
}
/*
@ TIM6 Init
@ 
@ clock 72Mhz produce 10KHz irq?
@ period 100
*/
void USER_TIM6_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim6);
}
void USER_TIM6_IRQHandler(void)
{
	
	if(UART4_RX_Ready == 1)
	{
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		
		//Reset flags and num;
		UART4_ResetFlags();
	}
}
