#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../Periph/GPIO/GPIO.h"

#define LCD_CONTROL_PORT		PORTB
#define LCD_CONTROL_DDR			DDRB
#define LCD_RS					4
#define LCD_RW					6
#define LCD_ENABLE				7
#define LCD_DATA_PORT			PORTC
#define LCD_DATA_DDR			DDRC

#define Function_set			0x38
#define Display_Off				0x08
#define Display_Clear			0x01
#define Entry_Mode_Set			0x06
#define Display_On				0x0C

void LCD_init();
void LCD_Off();
void Gpio_init();
void LCD_cmdMode();
void LCD_charMode();
void LCD_writeMode();
void LCD_enableHigh();
void LCD_enableLow();
void LCD_writeByte(uint8_t data);
void LCD_writeCmdData(uint8_t data);
void LCD_writeCharData(uint8_t data);
void LCD_writeString(char *str);
void LCD_gotoXY(uint8_t row, uint8_t col);
void LCD_writeStringXY(uint8_t row, uint8_t col, char* str);
void LCD_clearDisplay();
#endif