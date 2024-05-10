#include <stdint.h>
#include "main.h"
void LCD_WriteNibble(uint8_t LCDCode);
void LCD_WriteByte(uint8_t LCDByte);
void LCD_PutChar(uint8_t ch);
void LCD_GotoXY(uint8_t x, uint8_t y);
void LCD_printf(uint8_t *s);
void LCD_Init(void);
void LCD_clear(void);
void LCD_NoCursor(void);