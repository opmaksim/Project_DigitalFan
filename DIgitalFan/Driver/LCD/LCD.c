#include "LCD.h"

void LCD_init(){
	Gpio_init();
	_delay_ms(15);
	LCD_writeCmdData(Function_set);	//Function set 0x38
	_delay_ms(5);
	LCD_writeCmdData(Function_set);	//Function set 0x38
	_delay_ms(1);
	LCD_writeCmdData(Function_set);	//Function set 0x38
	LCD_writeCmdData(Function_set);	//Function set 0x38
	LCD_writeCmdData(Display_Off);	//Display Off
	LCD_writeCmdData(Display_Clear);	//Display Clear
	LCD_writeCmdData(Entry_Mode_Set);	//Entry Mode Set
	LCD_writeCmdData(Display_On);	//Display On -> 위 과정까진 초기화, 마지막에 켜줘야됨
}

void Gpio_init(){
	Gpio_initPin(&LCD_CONTROL_DDR, OUTPUT, LCD_RS);
	Gpio_initPin(&LCD_CONTROL_DDR, OUTPUT, LCD_RW);
	Gpio_initPin(&LCD_CONTROL_DDR, OUTPUT, LCD_ENABLE);
	Gpio_initPort(&LCD_DATA_DDR, OUTPUT);
}

void LCD_Off(){
	Gpio_writePort(&LCD_CONTROL_PORT, 0x00);
}
void LCD_cmdMode(){
	//RS pin : bit 0
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_RS, GPIO_PIN_RESET);
}

void LCD_charMode(){
	//RS pin : bit 1
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_RS, GPIO_PIN_SET);
}

void LCD_writeMode(){
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_RW, GPIO_PIN_RESET);
}

void LCD_enableHigh(){
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_ENABLE, GPIO_PIN_SET);
	_delay_ms(1);
}

void LCD_enableLow(){
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_ENABLE, GPIO_PIN_RESET);
	_delay_ms(1);
}

void LCD_writeByte(uint8_t data){
	Gpio_writePort(&LCD_DATA_PORT, data);
}
// MCU -> LCD 명령어를 보낼 경우 (write mode)

void LCD_writeCmdData(uint8_t data){
	// LCD 명령어 전달
	LCD_cmdMode();
	LCD_writeMode();
	LCD_enableHigh();
	LCD_writeByte(data);
	LCD_enableLow();
}

// MCU -> LCD Data를 보낼 경우 (write mode)

void LCD_writeCharData(uint8_t data){
	// LCD char 쓰기 전달
	LCD_charMode();
	LCD_writeMode();
	LCD_enableHigh();
	LCD_writeByte(data);
	LCD_enableLow();
}

void LCD_writeString(char *str){
	for(int i = 0; str[i]; i++){
		LCD_writeCharData(str[i]);
	}
}

void LCD_gotoXY(uint8_t row, uint8_t col){
	col %= 16; row %= 2;
	uint8_t lcdregisterAddress = (0x40 * row) + col;
	uint8_t command = 0x80 + lcdregisterAddress;
	LCD_writeCmdData(command);
}

void LCD_writeStringXY(uint8_t row, uint8_t col, char* str){
	LCD_gotoXY(row, col);
	LCD_writeString(str);
}

void LCD_clearDisplay(){
	LCD_writeCmdData(Display_Clear);
}
