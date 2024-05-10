#include <stdint.h>
#include "main.h"
void LCD_WriteNibble(uint8_t LCDCode) { 
	// 4 bits protocol
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_D4_GPIO_Port,LCD_D4_Pin,(GPIO_PinState)(LCDCode&0x01));
	HAL_GPIO_WritePin(LCD_D5_GPIO_Port,LCD_D5_Pin,(GPIO_PinState)(LCDCode&0x02));
	HAL_GPIO_WritePin(LCD_D6_GPIO_Port,LCD_D6_Pin,(GPIO_PinState)(LCDCode&0x04));
	HAL_GPIO_WritePin(LCD_D7_GPIO_Port,LCD_D7_Pin,(GPIO_PinState)(LCDCode&0x08));
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin,GPIO_PIN_RESET);
}
void LCD_WriteByte(uint8_t LCDByte) { 
	// 4 bits protocol
	LCD_WriteNibble(LCDByte>>4);
	LCD_WriteNibble(LCDByte);
	HAL_Delay(1);
}
void LCD_PutChar(uint8_t ch)
{
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,(GPIO_PinState)1);
	LCD_WriteByte(ch);
}
void LCD_GotoXY(uint8_t x, uint8_t y)
{
	uint8_t DDR_addr = 0x40 * y + x + 0x80;
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,(GPIO_PinState)0);
	LCD_WriteByte(DDR_addr);
}
void LCD_printf(uint8_t *s) {
	uint8_t i=0;
	while(*(s+i) != 0) {
		LCD_PutChar(*(s+i));
		HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,(GPIO_PinState)1);
		i++;
	}
}
void LCD_Init(void){
    // LCD init 4 bit
		HAL_GPIO_WritePin(LCD_LED_GPIO_Port, LCD_LED_Pin,(GPIO_PinState)1);
		HAL_Delay(100);
		HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LCD_RW_GPIO_Port,LCD_RW_Pin,GPIO_PIN_RESET);
		LCD_WriteNibble(3); // 3 = 0011 D7=0 D6=0 D5=0 D4=0
		HAL_Delay(5);
		const uint8_t LCD_INIT_4BIT[]={3,3,2,2,8,0,8,0,1,0,6};
		for (uint8_t i=0;i<11;i++) {
			LCD_WriteNibble(LCD_INIT_4BIT[i]);
			HAL_Delay(1);
		}
		LCD_WriteByte(0x0F); // Display ON
												//  BLINK ON
		HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,(GPIO_PinState)1);
	}
void LCD_clear(void){
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,(GPIO_PinState)0);
	LCD_WriteByte(0x01);
	HAL_Delay(1);
}
void LCD_NoCursor(void){
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,(GPIO_PinState)0);
	LCD_WriteByte(0x0C);
	HAL_Delay(1);
}