#include "Fan.h"

uint16_t FanData;

void Fan_init(){
	Gpio_initPin(&DDRE, OUTPUT, 3);
}

void Fan_speedMode(uint16_t data){
	FAN_ICR = (250000 / 250) - 1;
	if(data == 0) FAN_OCR = 0;
	else FAN_OCR = FAN_ICR / data;
}