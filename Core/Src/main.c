/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "bsp.h"
#include "multi_button.h"
#include "btn.h"
#include "ui.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define SAMPLE_TIMES 10
#define CHANNELS     3
#define GAIN         0.0024414f
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
uint16_t ADC_Value[SAMPLE_TIMES][CHANNELS];

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    uint8_t i = 0;
    uint16_t sum1, sum2, sum3;
    float ch1_val, ch2_val, ch3_val;

    if (hadc->Instance == ADC1)
    {
        for (i = 0; i < 10; i++)
        {
            sum1 = sum1 + ADC_Value[i][0];
            sum2 = sum2 + ADC_Value[i][1];
            sum3 = sum3 + ADC_Value[i][2];
        }
        ch1_val = 100 - sum1 * GAIN;
        ch2_val = sum2 * GAIN;
        ch3_val = 100.0 - sum3 * GAIN;
        //LCD_Update();
//        U1_Printf("ch1=%.3f\r\n", ch1_val);
//        U1_Printf("ch2=%.3f\r\n", ch2_val);
//        U1_Printf("ch3=%.3f\r\n", ch3_val);
    }
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();
    MX_SPI1_Init();
    MX_ADC1_Init();
    MX_SPI2_Init();
    MX_USART2_UART_Init();
    MX_TIM3_Init();
    MX_TIM6_Init();
    /* USER CODE BEGIN 2 */


    My_Button_Init();
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *) ADC_Value, SAMPLE_TIMES * CHANNELS);
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim6);
    ST7789_Init();
    UI_Home();
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        if (U1_RX_Struct.RX_Out != U1_RX_Struct.RX_In)
        {
            //U1_Printf("Receive %d data\r\n", U1_RX_Struct.RX_Out->end - U1_RX_Struct.RX_Out->start + 1);
            HAL_UART_Transmit(&huart2, U1_RX_Struct.RX_Out->start,
                              U1_RX_Struct.RX_Out->end - U1_RX_Struct.RX_Out->start + 1, 0xff);
            U1_RX_Struct.RX_Out++;
            if (U1_RX_Struct.RX_Out == U1_RX_Struct.RX_End)
                U1_RX_Struct.RX_Out = &U1_RX_Struct.SE_Buffer[0];
        }
        if (U2_RX_Struct.RX_Out != U2_RX_Struct.RX_In)
        {
            HAL_UART_Transmit(&huart1, U2_RX_Struct.RX_Out->start,
                              U2_RX_Struct.RX_Out->end - U2_RX_Struct.RX_Out->start + 1, 0xff);
            U2_RX_Struct.RX_Out++;
            if (U2_RX_Struct.RX_Out == U2_RX_Struct.RX_End)
                U2_RX_Struct.RX_Out = &U2_RX_Struct.SE_Buffer[0];
        }
//        HAL_ADC_Start_DMA(&hadc1, (uint32_t *) ADC_Value, 3);
//        HAL_Delay(5);
//        sprintf(adc_ch1_data,"channel1:%d",ADC_Value[0]);
//        sprintf(adc_ch2_data,"channel2:%d",ADC_Value[1]);
//        sprintf(adc_ch3_data,"channel3:%d",ADC_Value[2]);
//
//        LCD_ShowString(0,0,(uint8_t*)adc_ch1_data,WHITE,DARKBLUE,24,0);
//        LCD_ShowString(0,24,(uint8_t*)adc_ch2_data,WHITE,DARKBLUE,24,0);
//        LCD_ShowString(0,48,(uint8_t*)adc_ch3_data,WHITE,DARKBLUE,24,0);
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
