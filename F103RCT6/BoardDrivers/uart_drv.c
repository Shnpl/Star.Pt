#include "uart_drv.h"

uint8_t UART4_RX_Buffer[UART4_RXBUFFERSIZE];
uint8_t UART4_HAL_RxBuffer;


uint8_t UART4_RX_0x0D_FLAG = 0;// \r
uint8_t UART4_RX_Ready = 0;// Received ready

uint8_t UART4_RX_Num = 0;

void USER_UART4_Init(void)
{
	HAL_UART_Receive_IT(&huart4, &UART4_HAL_RxBuffer, 1);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==UART4)
	{
		if(UART4_RX_0x0D_FLAG == 1)//Received \r
		{
			if(UART4_HAL_RxBuffer == 0x0A)//Received \n
			{
				UART4_RX_Ready = 1;
				UART4_RX_Buffer[UART4_RX_Num] = '\0';
				
			}
			else //Received \r while losing \n
			{
				UART4_ResetFlags();
			}
		}
		else //Not received \r
		{	
			if(UART4_HAL_RxBuffer == 0x0D)//Received \r this time
			{
				UART4_RX_0x0D_FLAG = 1;
			}
			else
			{
				UART4_RX_Buffer[UART4_RX_Num]=UART4_HAL_RxBuffer;
				UART4_RX_Num++;
				if(UART4_RX_Num>UART4_RXBUFFERSIZE)
				{
					UART4_ResetFlags();
				} 
			}		 
		}//Not received \r end
	}
}
void USER_UART4_IRQHandler(void)
{
	//HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
	
//	if(UART4_RX_Ready == 1)//Last message has bot been handled yet
//	{
//		return;
//	}
	
	
	
	
}

void USER_UART4_IRQHandler_Post(void)
{
	HAL_UART_Receive_IT(&huart4,&UART4_HAL_RxBuffer,1);
}

//Reset flags and nums
void UART4_ResetFlags(void)
{
	UART4_RX_Ready = 0;
	UART4_RX_0x0D_FLAG = 0;
	UART4_RX_Num = 0;
}
