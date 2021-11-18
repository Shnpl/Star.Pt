#include "encoder.h"

uint32_t encoder_M1_count_last;
uint32_t encoder_M1_count;

float M1_speed;

uint32_t encoder_M1_count_per;

Status Get_M1_SPD()
{
	static uint32_t cnt = 0;
	//per 100ms TIM16 10Khz
	if(cnt < 1000)
	{
		cnt++;
	}
	else
	{
		cnt = 0;
		encoder_M1_count = __HAL_TIM_GET_COUNTER(&htim2);
		encoder_M1_count_per = encoder_M1_count - encoder_M1_count_last;
		encoder_M1_count_last = encoder_M1_count;
		
		M1_speed = (float)encoder_M1_count_per*10/64/50;//50 for gearbox(120rpm),64 pulse per 
	}
	return 0;
}