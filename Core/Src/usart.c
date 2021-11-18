/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
uint8_t USART_RX_BUF[USART_REC_LEN];     //Recieve buffer,max length : USART_REC_LEN.
//Receive status
//bit15�?	接收完成标志
//bit14�?	接收�?0x0d
//bit13~0�?	接收到的有效字节数目
uint16_t USART_RX_STA=0;       //接收状�?�标�?	

uint8_t aRxBuffer[RXBUFFERSIZE];//HAL库使用的串口接收缓冲

//重定向fputc

int fputc(int ch, FILE *f)
{      
	while((UART7->ISR&0X40)==0);//循环发�??,直到发�?�完�?   
	UART7->TDR = (uint8_t) ch;      
	return ch;
}


/* USER CODE END 0 */

UART_HandleTypeDef huart7;

/* UART7 init function */
void MX_UART7_Init(void)
{

  /* USER CODE BEGIN UART7_Init 0 */

  /* USER CODE END UART7_Init 0 */

  /* USER CODE BEGIN UART7_Init 1 */

  /* USER CODE END UART7_Init 1 */
  huart7.Instance = UART7;
  huart7.Init.BaudRate = 9600;
  huart7.Init.WordLength = UART_WORDLENGTH_8B;
  huart7.Init.StopBits = UART_STOPBITS_1;
  huart7.Init.Parity = UART_PARITY_NONE;
  huart7.Init.Mode = UART_MODE_TX_RX;
  huart7.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart7.Init.OverSampling = UART_OVERSAMPLING_16;
  huart7.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart7.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart7.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart7) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart7, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart7, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart7) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART7_Init 2 */
	HAL_UART_Receive_IT(&huart7,(uint8_t*)aRxBuffer,RXBUFFERSIZE);
  /* USER CODE END UART7_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(uartHandle->Instance==UART7)
  {
  /* USER CODE BEGIN UART7_MspInit 0 */

  /* USER CODE END UART7_MspInit 0 */
  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART7;
    PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* UART7 clock enable */
    __HAL_RCC_UART7_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**UART7 GPIO Configuration
    PA15 (JTDI)     ------> UART7_TX
    PA8     ------> UART7_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF11_UART7;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* UART7 interrupt Init */
    HAL_NVIC_SetPriority(UART7_IRQn, 3, 3);
    HAL_NVIC_EnableIRQ(UART7_IRQn);
  /* USER CODE BEGIN UART7_MspInit 1 */

  /* USER CODE END UART7_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==UART7)
  {
  /* USER CODE BEGIN UART7_MspDeInit 0 */

  /* USER CODE END UART7_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART7_CLK_DISABLE();

    /**UART7 GPIO Configuration
    PA15 (JTDI)     ------> UART7_TX
    PA8     ------> UART7_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_15|GPIO_PIN_8);

    /* UART7 interrupt Deinit */
    HAL_NVIC_DisableIRQ(UART7_IRQn);
  /* USER CODE BEGIN UART7_MspDeInit 1 */

  /* USER CODE END UART7_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
//!! THERE ARE SOME ERRORS IN PCB DESIGN WHICH MADE IT IMPOSSIBLE TO USE USART1 NOW
//AFTER FIXING THE PROBLEM THE PROGRAM WOULD USE USART1
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==UART7)//if UART 7 
	{
		if((USART_RX_STA&0x8000)==0)//N FINISH
		{
			if(USART_RX_STA&0x4000)//received 0x0d
			{
				if(aRxBuffer[0]!=0x0a)USART_RX_STA=0;//error while recieving
				else USART_RX_STA|=0x8000;	//接收完成�? 
			}
			else //还没收到0X0D
			{	
				if(aRxBuffer[0]==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=aRxBuffer[0] ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新�?始接�?	  
				}		 
			}
		}

	}
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
