#ifndef SERVICE_DIGITALFAN_H_
#define SERVICE_DIGITALFAN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "../../Model/Model_FanState/Model_FanState.h"
#include "../../Model/Model_TimerState/Model_TimerState.h"
#include "../Presenter/Presenter.h"
void DigitalFan_init();
void DigitalFan_Timecalc();
void DigitalFan_execute();
void DigitalFan_Timer();
void DigitalFan_dicmilisec();
void DigitalFan_Autocalc();
void DigitalFan_AutoData();
void set_Time(uint8_t hour1, uint8_t min1, uint8_t sec1, uint16_t milisec1);
#endif