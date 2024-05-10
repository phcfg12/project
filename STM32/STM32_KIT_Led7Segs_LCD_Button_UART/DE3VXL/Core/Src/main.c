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
#include <stdio.h>
#include "LCD.h"

struct __FILE
{
  int handle;
};
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

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
#define UART 0
#define LCD 1
uint8_t Print_Device = 0;
FILE __stdout;
int fputc(int ch, FILE *f) 
{
	if (Print_Device == UART) HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,100);
	else if (Print_Device == LCD) LCD_PutChar(ch);
  return ch;
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void LED_pos(uint8_t pos) {
	#define LED_POS_0		1<<7
	#define LED_POS_1		1<<6
	#define LED_POS_2		1<<5
	#define LED_POS_3		1<<4
	#define LED_POS_4		1<<3
	for (int8_t i=7;i>=0;i--) { 
		HAL_GPIO_WritePin(MOSI_GPIO_Port,MOSI_Pin, (GPIO_PinState)(pos&(1<<i)));
		HAL_GPIO_WritePin(SCK_GPIO_Port,SCK_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(SCK_GPIO_Port,SCK_Pin,GPIO_PIN_RESET);
	}
}

void LED_decode(uint8_t LED_Num) {
	const uint8_t LEDCODE[] = {0xAF, 0xA0, 0x6E, 0xEA, 0xE1, 0xCB, 0xCF, 0xA2, 0xEF, 0xEB, 0x00, 0x40, 0xE5, 0x4F, 0x0D};
	for (int8_t i=7;i>=0;i--) { 
		HAL_GPIO_WritePin(MOSI_GPIO_Port,MOSI_Pin, (GPIO_PinState)(LEDCODE[LED_Num]&(1<<i)));
		HAL_GPIO_WritePin(SCK_GPIO_Port,SCK_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(SCK_GPIO_Port,SCK_Pin,GPIO_PIN_RESET);
	}
	HAL_GPIO_WritePin(RCK_GPIO_Port,RCK_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(RCK_GPIO_Port,RCK_Pin,GPIO_PIN_RESET);
}

uint8_t ButtonRead(void) {
	uint8_t ButtonData = 0;
		// LOAD pulse
		HAL_GPIO_WritePin(SCK_GPIO_Port,SCK_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LOAD_GPIO_Port,LOAD_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LOAD_GPIO_Port,LOAD_Pin,GPIO_PIN_SET);
		ButtonData = 0;
		for (uint8_t i=0;i<8;i++) {
			HAL_GPIO_WritePin(SCK_GPIO_Port,SCK_Pin,GPIO_PIN_SET);
			ButtonData = (ButtonData<<1)|HAL_GPIO_ReadPin(MISO_GPIO_Port,MISO_Pin);
			HAL_GPIO_WritePin(SCK_GPIO_Port,SCK_Pin,GPIO_PIN_RESET);
		}
		return ButtonData;
}

uint8_t ButtonData = 0;
uint8_t n=0;
uint16_t LED_Display_Number=0;
		uint8_t h=23;
		uint8_t m=59;
		uint8_t s=55;
uint16_t i=0;
		uint8_t state1=0;
		uint8_t state2=0;
		uint8_t state3=0;
uint8_t state4=0;
char ch[20];
void Scan_B1(){
if(LED_Display_Number == 224){
				state1=1;
			}
		}
void Scan_B2(){
if(LED_Display_Number == 193){
				state2=1;
			}
		}
void Scan_B3(){
	
	if((LED_Display_Number == 161)&&(state3==0)){
		state3=1;
	}
	if((LED_Display_Number != 161)&&(state3==1)){
		state3=2;
	}
	if((LED_Display_Number == 161)&&(state3==2)){
		state3=3;
	}
	if((LED_Display_Number != 161)&&(state3==3)){
		state3=0;
	}

}
void Scan_B4(){
	
	if((LED_Display_Number == 97)&&(state4==0)){
		state4=1;
	}
	if((LED_Display_Number != 97)&&(state4==1)){
		state4=2;
	}
	if((LED_Display_Number == 97)&&(state4==3)){
		state4=4;
	}
	if((LED_Display_Number != 97)&&(state4==4)){
		state4=0;
	}

}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	
	if (htim == &htim1 ) {
		LED_Display_Number = ButtonRead();
		Scan_B1();
		Scan_B3();
		Scan_B2();
		Scan_B4();
		
		if(state2!=1){
		if (i==0) {
				LED_pos(LED_POS_4);
				LED_decode(10);
				LED_pos(LED_POS_0);
				LED_decode(0);
			}
			else if (i==1) {
				LED_pos(LED_POS_0);
				LED_decode(10);
				LED_pos(LED_POS_1);
				LED_decode(14);			
			}
			else if (i==2) {
				LED_pos(LED_POS_1);
				LED_decode(10);
				LED_pos(LED_POS_2);
				LED_decode(14);	
			}
			else if (i==3) {
				LED_pos(LED_POS_2);
				LED_decode(10);
				LED_pos(LED_POS_3);
				LED_decode(13);	
			}
			else if (i==4) {
				LED_pos(LED_POS_3);
				LED_decode(10);
				LED_pos(LED_POS_4);
				LED_decode(12);
			}
			if (i<4) i = i + 1;
			else i = 0;
		}
		
		
		
	
		if(state2==1){
		if (n==0) {
			LED_pos(LED_POS_4);
			LED_decode(10);
			LED_pos(LED_POS_0);
			LED_decode(s%10);
		}
		else if (n==1) {
			LED_pos(LED_POS_0);
			LED_decode(10);
			LED_pos(LED_POS_1);
			LED_decode(s/10);			
		}
		else if (n==2) {
			LED_pos(LED_POS_1);
			LED_decode(10);
			LED_pos(LED_POS_2);
			LED_decode(11);	
		}
		else if (n==3) {
			LED_pos(LED_POS_2);
			LED_decode(10);
			LED_pos(LED_POS_3);
			LED_decode(m%10);	
		}
		else if (n==4) {
			LED_pos(LED_POS_3);
			LED_decode(10);
			LED_pos(LED_POS_4);
			LED_decode((m/10)%10);
		}
		if (n<4) n = n + 1;
		else n = 0;
	}
	} // end of if (htim == &htim1 )
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
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_GPIO_WritePin(RCK_GPIO_Port,RCK_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RCL_GPIO_Port,RCL_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SCK_GPIO_Port,SCK_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LOAD_GPIO_Port, LOAD_Pin, GPIO_PIN_SET);	
		
	HAL_GPIO_WritePin(RCK_GPIO_Port,RCK_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(RCK_GPIO_Port,RCK_Pin,GPIO_PIN_RESET);
	
	//HAL_TIM_Base_Start_IT(&htim1);
	LCD_Init();
	Print_Device = LCD;
	LCD_GotoXY(0,0);
	
	printf("Phung Hieu Cuong");
	LCD_GotoXY(0,1);
	printf("21146540");
	
  while (1)
  {
		
		
    HAL_TIM_Base_Start_IT(&htim1);
		
		if((state4==1)||(state4==2)){
			uint16_t cnt=0;
			Print_Device = UART;
			printf("%02u:%02u:%02u\r",h,m,s);
			cnt++;
			if(cnt>cnt-1){
				Print_Device = LCD;
				state4=3;
			}
		}
		
		if(state1==1){
			
			LCD_clear();
			LCD_NoCursor();
			LCD_GotoXY(0,0);
			Print_Device = LCD;
			printf("%02u:%02u:%02u",h,m,s);
			
			HAL_Delay(1000);
			
			if((state3!=1)&&(state3!=2)){
				s++;
			if(s==60){
				m++;
				s=0;
				if(m==60){
					h++;
					m=0;
					if(h==24){
						h=0;
					}
					}
				}
			}
		}
	
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
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
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 5999;
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
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, RCL_Pin|RCK_Pin|LOAD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin
                          |LCD_LED_Pin|LCD_E_Pin|LCD_RW_Pin|LCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SCK_Pin|MOSI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RCL_Pin RCK_Pin LOAD_Pin */
  GPIO_InitStruct.Pin = RCL_Pin|RCK_Pin|LOAD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D4_Pin LCD_D5_Pin LCD_D6_Pin LCD_D7_Pin
                           LCD_LED_Pin LCD_E_Pin LCD_RW_Pin LCD_RS_Pin */
  GPIO_InitStruct.Pin = LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin
                          |LCD_LED_Pin|LCD_E_Pin|LCD_RW_Pin|LCD_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : SCK_Pin MOSI_Pin */
  GPIO_InitStruct.Pin = SCK_Pin|MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : MISO_Pin */
  GPIO_InitStruct.Pin = MISO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MISO_GPIO_Port, &GPIO_InitStruct);

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
