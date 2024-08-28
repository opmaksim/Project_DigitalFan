#ifndef PRESENTER_H_
#define PRESENTER_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "../../Driver/Fan/Fan.h"
#include "../../Driver/FND/FND.h"
#include "../../Driver/LCD/LCD.h"
#include "../../Driver/I2C_LCD/LCD_I2C.h"
#include "../Service/Service_DigitalFan.h"
#include "../../Model/Model_FanState/Model_FanState.h"

void Presenter_init();
void Presenter_dispTimeData(uint8_t hour, uint8_t min, uint8_t sec, uint16_t milisec);
void Presenter_FanData();
void Presenter_FanAutoData();
void LCD_Gauge();
#endif