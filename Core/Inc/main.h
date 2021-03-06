/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DCMI_PWDN_Pin GPIO_PIN_11
#define DCMI_PWDN_GPIO_Port GPIOG
#define DCMI_RST_Pin GPIO_PIN_12
#define DCMI_RST_GPIO_Port GPIOG
#define MOTOR_DIR_2_Pin GPIO_PIN_10
#define MOTOR_DIR_2_GPIO_Port GPIOA
#define MOTOR_DIR_1_Pin GPIO_PIN_9
#define MOTOR_DIR_1_GPIO_Port GPIOA
#define MOTOR_1_Pin GPIO_PIN_1
#define MOTOR_1_GPIO_Port GPIOK
#define MOTOR_2_Pin GPIO_PIN_11
#define MOTOR_2_GPIO_Port GPIOJ
#define SCCB_SCL_Pin GPIO_PIN_10
#define SCCB_SCL_GPIO_Port GPIOB
#define SCCB_SDA_Pin GPIO_PIN_11
#define SCCB_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
