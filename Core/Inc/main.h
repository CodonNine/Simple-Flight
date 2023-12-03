/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

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
#define RS_Pin GPIO_PIN_4
#define RS_GPIO_Port GPIOC
#define RST_Pin GPIO_PIN_5
#define RST_GPIO_Port GPIOC
#define CS_Pin GPIO_PIN_0
#define CS_GPIO_Port GPIOB
#define K_L2_Pin GPIO_PIN_10
#define K_L2_GPIO_Port GPIOB
#define K_L1_Pin GPIO_PIN_11
#define K_L1_GPIO_Port GPIOB
#define CS2_Pin GPIO_PIN_12
#define CS2_GPIO_Port GPIOB
#define K_UP_Pin GPIO_PIN_12
#define K_UP_GPIO_Port GPIOA
#define K_L_Pin GPIO_PIN_15
#define K_L_GPIO_Port GPIOA
#define K_DOWN_Pin GPIO_PIN_10
#define K_DOWN_GPIO_Port GPIOC
#define K_R_Pin GPIO_PIN_11
#define K_R_GPIO_Port GPIOC
#define K_BACK_Pin GPIO_PIN_2
#define K_BACK_GPIO_Port GPIOD
#define K_B_Pin GPIO_PIN_3
#define K_B_GPIO_Port GPIOB
#define K_A_Pin GPIO_PIN_4
#define K_A_GPIO_Port GPIOB
#define K_X_Pin GPIO_PIN_5
#define K_X_GPIO_Port GPIOB
#define K_Y_Pin GPIO_PIN_6
#define K_Y_GPIO_Port GPIOB
#define K_MENU_Pin GPIO_PIN_7
#define K_MENU_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
