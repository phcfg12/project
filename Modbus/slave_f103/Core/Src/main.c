/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t BUFF_2_R[256];
uint8_t RX[256];
uint8_t slaveAddress = 5;
uint8_t startAddress;
// gia tri thanh ghi
uint16_t registerValues[]={0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
													 0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
													 0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
													 0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
													 0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
													 0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
													 0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
													 0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
													 0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
													 0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
													 0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
													 0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
													 0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
													 0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
													 0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
													 0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
													 0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
													 0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
													 0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
													 0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
													 0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
													 0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
													 0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
													 0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
													 0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
													 0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
													 0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
													 0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
													 0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
													 0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
													 0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
													 0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040
													 };   // cac thanh ghi vi du de test
uint8_t numbyte;//so luong byte cua frame gui di
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
	
	HAL_UARTEx_ReceiveToIdle_IT(&huart2,BUFF_2_R,256);
	
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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
uint16_t CRC16_Check_B(uint8_t Num,uint8_t frame[]) //Ham CRC 16
{
    uint8_t x,y,i;
		uint16_t Crc; //Bien Cuc Bo

    Crc=0xFFFF; //Init 
    
    for(x=0;x<Num;++x) //Lap Vong 
    {        
       y=frame[x]; //Lay Byte Trong Bo Dem CRC 16
       Crc=Crc^y; //Calculate the CRC 
       
       for(i=8;i!=0;--i) //Shift Right
       {
          if((Crc&0x0001)!=0) //If the LSB is set
          { 
             Crc>>=1; //Shift right and XOR 0xA001
             Crc^=0xA001;
          }
          else //Else LSB is not set  
          {
             Crc>>=1; //Just shift right
          }   
       } 
    }
    //Swapping of the high and low CRC bytes      
    return Crc; //Tra Ve CRC_16 Tinh Duoc
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	//if(huart==&huart2){
	if(huart->Instance == USART2){
		if(slaveAddress==BUFF_2_R[0]){
			if(BUFF_2_R[1]==3){								// Read Holding Registers (FC=03H)
				uint8_t BUFF_2_T[((BUFF_2_R[4]<<8)|BUFF_2_R[5])*2];				
				startAddress=(BUFF_2_R[2]<<8)|BUFF_2_R[3];							// dia chi bat dau doc
				numbyte=BUFF_2_R[5]*2+5;							// so luong byte truyen di
				uint8_t frame[numbyte];
				uint16_t tinh_crc=CRC16_Check_B(6,BUFF_2_R);
				uint16_t crc=(uint16_t)(BUFF_2_R[7]<<8)|BUFF_2_R[6];
				if(tinh_crc==crc){
						uint8_t cnt=startAddress;
						for(int i=0;i<(BUFF_2_R[5]*2);i=i+2){
								BUFF_2_T[i]=(uint8_t)((registerValues[cnt]>>8)&0xFF);
								BUFF_2_T[i+1]=(uint8_t)(registerValues[cnt]&0xFF);
								cnt++;
						}
						frame[0] = slaveAddress;
						frame[1] = BUFF_2_R[1];
						frame[2] = ((BUFF_2_R[4]<<8)|BUFF_2_R[5])*2;

						for(int i=3;i<numbyte-2;i++){
								frame[i]=BUFF_2_T[i-3];
						}

						uint16_t check=CRC16_Check_B(numbyte-2,frame);
						frame[numbyte-2] = (uint8_t)(check&0xFF);
						frame[numbyte-1] = (uint8_t)((check>>8)&0xFF);
						HAL_UART_Transmit(&huart2, frame, numbyte, HAL_MAX_DELAY);
				}
			}
			if(BUFF_2_R[1]==16){							// Preset Multiple Registers (FC = 10H)
				numbyte=8;							// so luong byte truyen di
				uint8_t frame[numbyte];
				uint8_t num = (BUFF_2_R[4]<<8)|BUFF_2_R[5];
				uint16_t len=num*2+9;	// so byte du lieu
				uint16_t tinh_crc=CRC16_Check_B(len-2,BUFF_2_R);
				uint16_t crc=(uint16_t)((BUFF_2_R[len-1]<<8)|BUFF_2_R[len-2]);
				if(tinh_crc==crc){			// kiem tra CRC
					frame[0] = slaveAddress;
					frame[1] = (uint8_t) (BUFF_2_R[1]);
					frame[2] = (uint8_t) (BUFF_2_R[2]);
					frame[3] = (uint8_t) (BUFF_2_R[3]);
					frame[4] = (uint8_t) (BUFF_2_R[4]);
					frame[5] = (uint8_t) (BUFF_2_R[5]);

					uint16_t check=CRC16_Check_B(numbyte-2,frame);  // tinh CRC cho du lieu truyen di
					frame[numbyte-2] = (uint8_t)(check&0xFF);
					frame[numbyte-1] = (uint8_t)((check>>8)&0xFF);
					HAL_UART_Transmit(&huart2, frame, numbyte, HAL_MAX_DELAY);
					// bat tat led theo du lieu thanh ghi
					if(((BUFF_2_R[7]<<8)|BUFF_2_R[8])==0){
							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
					}
					if(((BUFF_2_R[7]<<8)|BUFF_2_R[8])==1){
							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
					}
					if(((BUFF_2_R[7]<<8)|BUFF_2_R[8])==2){
							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
					}
					if(((BUFF_2_R[7]<<8)|BUFF_2_R[8])==3){
							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
					}
				}
			}
		}
		HAL_UARTEx_ReceiveToIdle_IT(&huart2, BUFF_2_R, 256);
	}
}
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
