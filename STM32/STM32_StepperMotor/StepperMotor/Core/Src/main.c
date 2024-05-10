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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
uint8_t chieu_quay=1;		//0: quay thuan
												//1: quay nguoc
uint32_t X=6400;				//1 vong can 6400 buoc
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
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
float Steparray1[128]={9.8, 20, 29, 38, 47, 56, 63, 71, 77, 83, 88, 93, 95.6, 98, 99.5, 100, 
											99.5, 98, 95.6, 93, 88, 83, 77, 71, 63, 56, 47, 38, 29, 20, 9.8, 0,
											9.8, 20, 29, 38, 47, 56, 63, 71, 77, 83, 88, 93, 95.6, 98, 99.5, 100, 
											99.5, 98, 95.6, 93, 88, 83, 77, 71, 63, 56, 47, 38, 29, 20, 9.8, 0,
											9.8, 20, 29, 38, 47, 56, 63, 71, 77, 83, 88, 93, 95.6, 98, 99.5, 100, 
											99.5, 98, 95.6, 93, 88, 83, 77, 71, 63, 56, 47, 38, 29, 20, 9.8, 0,
											9.8, 20, 29, 38, 47, 56, 63, 71, 77, 83, 88, 93, 95.6, 98, 99.5, 100, 
											99.5, 98, 95.6, 93, 88, 83, 77, 71, 63, 56, 47, 38, 29, 20, 9.8, 0};
uint16_t duty=999;
void goc1(){
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 1);
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 0);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 1);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 0);
}
void goc2(){
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 0);
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 1);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 1);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 0);
}
void goc3(){
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 0);
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 1);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 0);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 1);
}
void goc4(){
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 1);
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 0);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 0);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 1);
}
void goc1t(){
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 1);
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 0);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 0);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 1);
}
void goc2t(){
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 0);
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 1);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 0);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 1);
}
void goc3t(){
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 0);
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 1);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 1);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 0);
}
void goc4t(){
	HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, 1);
	HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, 0);
	HAL_GPIO_WritePin(IN3_GPIO_Port, IN3_Pin, 1);
	HAL_GPIO_WritePin(IN4_GPIO_Port, IN4_Pin, 0);
}
void delay_us(uint32_t time){
	__HAL_TIM_SET_COUNTER(&htim1,0);
	while(__HAL_TIM_GET_COUNTER(&htim1)<time);
}


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
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	uint32_t n;
	
	//htim2.Instance->PSC=63;
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,999);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,0);
for(n=0;n<X;n++){
	if(chieu_quay==0){		//quay thuan
		if(n<32){
			goc1t();
		}
		if((n>=32)&&(n<64)){
			goc2t();
		}
		if((n>=64)&&(n<96)){
			goc3t();
		}
		if((n>=96)&&(n<128)){
			goc4t();
		}
	}
	
	if(chieu_quay==1){		//quay nguoc
		if(n<32){
			goc1();
		}
		if((n>=32)&&(n<64)){
			goc2();
		}
		if((n>=64)&&(n<96)){
			goc3();
		}
		if((n>=96)&&(n<128)){
			goc4();
		}
	}
	
	if(n<16){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,Steparray1[n]*duty/100);
	}
	if((n>=16)&&(n<32)){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,Steparray1[n]*duty/100);
	}
	if((n>=32)&&(n<48)){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,Steparray1[n]*duty/100);
	}
	if((n>=48)&&(n<64)){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,Steparray1[n]*duty/100);
	}
	if((n>=64)&&(n<80)){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,Steparray1[n]*duty/100);
	}
	if((n>=80)&&(n<96)){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,Steparray1[n]*duty/100);
	}
	if((n>=96)&&(n<112)){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,Steparray1[n]*duty/100);
	}
	if((n>=112)&&(n<128)){
		__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,Steparray1[n]*duty/100);
	}
	if(n>=128){
		n=0;
		X=X-128;
	}
	delay_us(200);
}

		
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 7;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 63;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 499;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, IN1_Pin|IN2_Pin|IN3_Pin|IN4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : IN1_Pin IN2_Pin IN3_Pin IN4_Pin */
  GPIO_InitStruct.Pin = IN1_Pin|IN2_Pin|IN3_Pin|IN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
