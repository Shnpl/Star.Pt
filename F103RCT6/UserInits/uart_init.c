#include "uart_init.h"

#define UART4_RXBUFFERSIZE 64
uint8_t UART4_RX_BUF[UART4_RXBUFFERSIZE];




uint8_t  UART4_HAL_RxBuffer[UART4_RXBUFFERSIZE];

void USER_UART4_Init(void)
{
	//HAL_UART_Receive_IT(&huart4, UART4_HAL_RxBuffer, UART4_RXBUFFERSIZE);
}

uint8_t UART4_RX_0X0D_FLAG = 0;
uint8_t UART4_RX_0X0A_FLAG = 0;

uint8_t UART4_RX_NUM = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==UART4)
	{
		if(UART4_RX_0X0A_FLAG == 0)//
		{
			if(UART4_RX_0X0D_FLAG == 1)//Received 0X0D
			{
				if(UART4_HAL_RxBuffer[0]!=0x0a)
				{
					UART4_RX_0X0A_FLAG = 0;
					UART4_RX_0X0D_FLAG = 0;
					UART4_RX_NUM = 0;
				}
				else
				{
					UART4_RX_BUF[UART4_RX_NUM-1] = '\0';
					UART4_RX_0X0A_FLAG = 1;
					UART4_RX_0X0D_FLAG = 0;
					UART4_RX_NUM = 0;
					
				}
			}
			else //Not received 0X0D
			{	
				if(UART4_HAL_RxBuffer[0]==0x0d)
				{
					UART4_RX_0X0D_FLAG = 1;
				}
				else
				{
					UART4_RX_BUF[UART4_RX_NUM]=UART4_HAL_RxBuffer[0] ;
					UART4_RX_NUM++;
					if(UART4_RX_NUM>(UART4_RXBUFFERSIZE-1))
					{
						UART4_RX_0X0A_FLAG = 0;
						UART4_RX_0X0D_FLAG = 0;
						UART4_RX_NUM = 0;
					} 
				}		 
			}
		}

	}
}