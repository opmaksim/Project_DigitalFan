#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../Periph/I2C/I2C.h"

#define LCD_I2C_RS						0
#define LCD_I2C_RW						1
#define LCD_I2C_ENABLE					2
#define	LCD_I2C_BACKLIGHT				3
#define LCD_I2C_SLA						0x27
#define LCD_I2C_SLA_W					LCD_I2C_SLA<<1

#define LCD_I2C_4bit_Function_set		0x28
#define Display_I2C_Off					0x08
#define Display_I2C_Clear				0x01
#define Entry_Mode_I2C_Set				0x06
#define Display_I2C_On					0x0C

void LCD_I2C_init();
void LCD_I2C_backLightOn();
void LCD_I2C_backLightOff();
void LCD_I2C_sendToI2C(uint8_t sla_w, uint8_t data);
void LCD_I2C_cmdMode();
void LCD_I2C_charMode();
void LCD_I2C_writeMode();
void LCD_I2C_enableHigh();
void LCD_I2C_enableLow();
void LCD_I2C_writeNibble(uint8_t data);
void LCD_I2C_writeByte(uint8_t data);
void LCD_I2C_writeCmdData(uint8_t data);
void LCD_I2C_writeCharData(uint8_t data);
void LCD_I2C_writeString(char *str);
void LCD_I2C_gotoXY(uint8_t row, uint8_t col);
void LCD_I2C_writeStringXY(uint8_t row, uint8_t col, char* str);
void LCD_I2C_clearDisplay();
void LCD_Gauge_Low();
void LCD_Gauge_middle();
void LCD_Gauge_high();
#endif