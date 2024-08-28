#include "LCD_I2C.h"

uint8_t lcdControlData;

void LCD_I2C_init(){
	I2C_init();
	lcdControlData = 0;
	_delay_ms(15);
	LCD_I2C_cmdMode();
	LCD_I2C_writeMode();
	LCD_I2C_writeNibble(0x30);
	_delay_ms(5);
	LCD_I2C_writeNibble(0x30);
	_delay_ms(1);
	LCD_I2C_writeNibble(0x30);
	LCD_I2C_writeNibble(0x20);
	LCD_I2C_writeCmdData(LCD_I2C_4bit_Function_set);	//Display Off
	LCD_I2C_writeCmdData(Display_I2C_Clear);			//Display Clear
	LCD_I2C_writeCmdData(Entry_Mode_I2C_Set);			//Entry Mode Set
	LCD_I2C_writeCmdData(Display_I2C_On);				//Display On -> 위 과정까진 초기화, 마지막에 켜줘야됨
	LCD_I2C_backLightOn();
}

void LCD_I2C_backLightOn()
{
	lcdControlData |= (1<<LCD_I2C_BACKLIGHT);
	LCD_I2C_sendToI2C(LCD_I2C_SLA_W,lcdControlData);
}

void LCD_I2C_backLightOff()
{
	lcdControlData &= ~(1<<LCD_I2C_BACKLIGHT);
	LCD_I2C_sendToI2C(LCD_I2C_SLA_W,lcdControlData);
}

void LCD_I2C_sendToI2C(uint8_t sla_w, uint8_t data){
	I2C_txByte(sla_w, data);
}

void LCD_I2C_cmdMode(){
	//RS pin : bit 0
	lcdControlData &= ~(1<<LCD_I2C_RS);
	LCD_I2C_sendToI2C(LCD_I2C_SLA_W, lcdControlData);
}

void LCD_I2C_charMode(){
	//RS pin : bit 1
	lcdControlData |= (1<<LCD_I2C_RS);
	LCD_I2C_sendToI2C(LCD_I2C_SLA_W, lcdControlData);
}

void LCD_I2C_writeMode(){
	//RW pin : bit 0
	lcdControlData &= ~(1<<LCD_I2C_RW);
	LCD_I2C_sendToI2C(LCD_I2C_SLA_W, lcdControlData);
}

void LCD_I2C_enableHigh(){
	//E pin : bit 1
	lcdControlData |= (1<<LCD_I2C_ENABLE);
	LCD_I2C_sendToI2C(LCD_I2C_SLA_W, lcdControlData);
	_delay_ms(1);
}

void LCD_I2C_enableLow(){
	lcdControlData &= ~(1<<LCD_I2C_ENABLE);
	LCD_I2C_sendToI2C(LCD_I2C_SLA_W, lcdControlData);
	_delay_ms(1);
}

void LCD_I2C_writeNibble(uint8_t data){
	LCD_I2C_enableHigh();
	lcdControlData = (lcdControlData & 0x0f) | (data & 0xf0);
	LCD_I2C_sendToI2C(LCD_I2C_SLA_W, lcdControlData);
	LCD_I2C_enableLow();
}

void LCD_I2C_writeByte(uint8_t data){
	LCD_I2C_writeNibble(data);
	data<<=4;
	LCD_I2C_writeNibble(data);
}

// 8비트가 들어오면 상위 4비트를 먼저 보낸 후, 하위 4비트를 보내는 방식(I2C LCD는 4비트만 송수신 가능)

// MCU -> LCD 명령어를 보낼 경우 (write mode)

void LCD_I2C_writeCmdData(uint8_t data){
	// LCD 명령어 전달
	LCD_I2C_cmdMode();
	LCD_I2C_writeMode();
	LCD_I2C_enableHigh();
	LCD_I2C_writeByte(data);
	LCD_I2C_enableLow();
}

// MCU -> LCD Data를 보낼 경우 (write mode)

void LCD_I2C_writeCharData(uint8_t data){
	// LCD char 쓰기 전달
	LCD_I2C_charMode();
	LCD_I2C_writeMode();
	LCD_I2C_enableHigh();
	LCD_I2C_writeByte(data);
	LCD_I2C_enableLow();
}

void LCD_I2C_writeString(char *str){
	for(int i = 0; str[i]; i++){
		LCD_I2C_writeCharData(str[i]);
	}
}

void LCD_I2C_gotoXY(uint8_t row, uint8_t col){
	col %= 16; row %= 2;
	uint8_t lcdregisterAddress = (0x40 * row) + col;
	uint8_t command = 0x80 + lcdregisterAddress;
	LCD_I2C_writeCmdData(command);
}

void LCD_I2C_writeStringXY(uint8_t row, uint8_t col, char* str){
	LCD_I2C_gotoXY(row, col);
	LCD_I2C_writeString(str);
}

void LCD_I2C_clearDisplay(){
	LCD_I2C_writeCmdData(Display_I2C_Clear);
}

void LCD_Gauge_Low()
{
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,0);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,1);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,2);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,3);
}


void LCD_Gauge_middle()
{
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,0);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,1);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,2);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,3);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,4);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,5);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,6);
	LCD_I2C_writeCharData(0xff);
}
void LCD_Gauge_high()
{
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,0);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,1);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,2);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,3);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,4);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,5);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,6);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,7);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,8);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,9);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,10);
	LCD_I2C_writeCharData(0xff);
	LCD_I2C_gotoXY(0,11);
}
