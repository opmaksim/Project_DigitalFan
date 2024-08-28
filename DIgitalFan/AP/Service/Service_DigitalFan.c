#include "Service_DigitalFan.h"

static uint16_t milisec;
static uint8_t sec, min, hour;
static uint8_t lastTimerState;
uint8_t fanRandom;
static uint16_t counter;

void DigitalFan_init(){
	lastTimerState = NONE;
	milisec = 0;
	sec = 0;
	min = 0;
	hour = 1;
}

void DigitalFan_Timecalc(){
	if((hour != 0 || min != 0 || sec != 0 || milisec != 0)) DigitalFan_dicmilisec();
	else{
		lastTimerState = NONE;
		Model_setTimerStateData(NONE);
		Model_setFanStateData(OFF);
	}
}

void DigitalFan_dicmilisec()
{
	uint8_t TimerState;
	TimerState = Model_getTimerStateData();
	if(TimerState != NONE) {
		milisec = (milisec - 1 + 1000) % 1000;
		} else {
		DigitalFan_init();
		return;
	}
	if(milisec != 999) return;
	sec = (sec - 1 + 60) % 60;

	if(sec != 59) return;
	min = (min - 1 + 60) % 60;

	if(min != 59) return;
	hour = (hour - 1 + 24) % 24;
}

void DigitalFan_execute(){
	DigitalFan_Timer();
}

void DigitalFan_Timer(){
	uint8_t TimerState;
	uint8_t FanState;
	uint8_t* TimeUartState;
	
	TimerState = Model_getTimerStateData();
	FanState = Model_getFanStateData();
	TimeUartState = Model_getTimerUartStateData();
	if(FanState != OFF){
		if(TimerState != lastTimerState) {
			if(TimerState == THREE || (!strcmp((char *)TimeUartState, "TIME_3min\n"))) set_Time(0,0,3,0);
			else if(TimerState == FIVE || (!strcmp((char *)TimeUartState, "TIME_5min\n"))) set_Time(0,0,5,0);
			else if(TimerState == SEVEN || (!strcmp((char *)TimeUartState, "TIME_7min\n"))) set_Time(0,0,7,0);
			lastTimerState = TimerState;
		}
		else if(!(hour != 0 || min != 0 || sec != 0 || milisec != 0))
		{
			Model_setFanStateData(OFF);
		}
	}
	else{
		set_Time(1,0,0,0);
		lastTimerState = NONE;
		Model_setTimerStateData(NONE);
		Model_setFanStateData(OFF);
		
	}
	Presenter_FanData();
	Presenter_dispTimeData(hour, min, sec, milisec);
}

void set_Time(uint8_t hour1, uint8_t min1, uint8_t sec1, uint16_t milisec1){
	hour = hour1;
	min = min1;
	sec = sec1;
	milisec = milisec1;
}

void DigitalFan_Autocalc()
{
	uint8_t fanState;
	fanState = Model_getFanStateData();
	if(fanState == AUTO)
	{
		counter++;
		if(counter >= 2000)
		{
			DigitalFan_AutoData();
			counter = 0;
		}
	}
}

void DigitalFan_AutoData()
{
	fanRandom = rand() % 4;
	switch(fanRandom){
		case 0:
		fanRandom = OFF;
		break;
		case 1:
		fanRandom = LOW;
		break;
		case 2:
		fanRandom = MIDDLE;
		break;
		case 3:
		fanRandom = HIGH;
		break;
	}
}
