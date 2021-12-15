#ifndef __TIM_DRV__
#define __TIM_DRV__
#include "main.h"
#include "tim.h"
#include "uart_drv.h"
#include "command.h"
void USER_TIM1_Init(void);
void USER_TIM6_Init(void);

void USER_TIM6_IRQHandler(void);
#endif
