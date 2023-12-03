/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */
#define RX_BUFFER_SIZE 2048
#define RX_MAX    512

typedef struct
{
    uint8_t *start;
    uint8_t *end;
}SE_Ptr;

typedef struct
{
    uint32_t RX_Counter;
    SE_Ptr SE_Buffer[10];
    SE_Ptr *RX_In;
    SE_Ptr *RX_Out;
    SE_Ptr *RX_End;
}U1_RX_CB;


typedef struct
{
    uint32_t RX_Counter;
    SE_Ptr SE_Buffer[10];
    SE_Ptr *RX_In;
    SE_Ptr *RX_Out;
    SE_Ptr *RX_End;
}U2_RX_CB;

extern uint8_t U1_RX_Buffer[RX_BUFFER_SIZE];
extern uint8_t U2_TX_Buffer[100];
extern uint8_t U2_RX_Buffer[RX_BUFFER_SIZE];
extern U1_RX_CB U1_RX_Struct;
extern U2_RX_CB U2_RX_Struct;
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void U1_Printf(char *format,...);
void U1_CB_Init();
void U2_CB_Init();
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

