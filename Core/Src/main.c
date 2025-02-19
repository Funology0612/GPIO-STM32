/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stdio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// su dung vong lap for - cung port
void LedOn1(void)
{
	
	for(int8_t i = 6; i >= 0; i--){
		if(i % 2 == 0){
			HAL_GPIO_WritePin(GPIOA, 1 << i, 0);
			HAL_Delay(500);
			HAL_GPIO_WritePin(GPIOA, 1 << i, 1);
		}
	}
		HAL_Delay(1000);
	for(int8_t i = 0; i <= 7; i++){
		if(i % 2 == 0){
			HAL_GPIO_WritePin(GPIOA, 1 << i, 0);
			HAL_Delay(500);
			HAL_GPIO_WritePin(GPIOA, 1 << i, 1);
		}
	}
}

// su dung con tro - cung port
void LedOn2(void)
{
	uint16_t led_pin[] = {1 << 0, 1 << 2, 1 << 4, 1 << 6};
	uint16_t *ptr;
	for(ptr = led_pin; ptr <= &led_pin[3]; ptr++){
		HAL_GPIO_WritePin(GPIOA, *ptr, 0);
			HAL_Delay(200);
			HAL_GPIO_WritePin(GPIOA, *ptr, 1);
	} 
	HAL_Delay(500);
	for(ptr = &led_pin[3]; ptr >= led_pin; ptr--){
		HAL_GPIO_WritePin(GPIOA, *ptr, 0);
			HAL_Delay(200);
			HAL_GPIO_WritePin(GPIOA, *ptr, 1);
	} 
	HAL_Delay(500);
}



// *************************************************************************
// su dung struct, union cung port - khac port

// struct de luu PORT va PIN
typedef struct 
	{
		GPIO_TypeDef *GPIOx;
		uint16_t pin;
	} Led_t;
	
	// union dieu khien led: truy cap theo mang hoac tung led rieng biet
	typedef union
		{
//			struct 
//			{
//				Led_t LED_1, LED_2, LED_3, LED_4;
//			};
			Led_t leds[4];
		} Led_Control_t;
		
	Led_Control_t Led_Control = {
		
			.leds = {
				{GPIOA, GPIO_PIN_0},
				{GPIOA, GPIO_PIN_2},
				{GPIOB, GPIO_PIN_10},
				{GPIOB, GPIO_PIN_11}
			}
		};
	
	// led sang tu trai sang phai va nguoc lai
	void right_left(void)
	{
	Led_t *ptr;
		for(ptr = Led_Control.leds; ptr <= &Led_Control.leds[3]; ptr++){
			HAL_GPIO_WritePin(ptr->GPIOx, ptr->pin, 0);
			HAL_Delay(500);
			HAL_GPIO_WritePin(ptr->GPIOx, ptr->pin, 1);
		} 
		HAL_Delay(1000);
		for(ptr = &Led_Control.leds[3]; ptr >= Led_Control.leds; ptr--){
			HAL_GPIO_WritePin(ptr->GPIOx, ptr->pin, 0);
			HAL_Delay(500);
			HAL_GPIO_WritePin(ptr->GPIOx, ptr->pin, 1);
		} 
	}
	
	
void don(void)
{
	for(int i=3;i>=0;i--){
		for(int k=0;k<=i;k++){
			Led_t exe = Led_Control.leds[k];
			HAL_GPIO_WritePin(exe.GPIOx, exe.pin, 0);
			HAL_Delay(500);
			HAL_GPIO_WritePin(exe.GPIOx, exe.pin, 1);
			if(k == i)
			{
				HAL_GPIO_WritePin(exe.GPIOx, exe.pin, 0);
			}
		}
	}
}
// *************************************************************************
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) 
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		don();
		//right_left();
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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
