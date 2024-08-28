#include "Listener.h"

button_t btnAuto, btnOff, btnMode, btnTimer;

void Listener_init(){
	Buzzer_init();
	UART0_init();
	Button_init(&btnAuto, &DDRA, &PINA, 0);
	Button_init(&btnOff, &DDRA, &PINA, 1);
	Button_init(&btnMode, &DDRA, &PINA, 2);
	Button_init(&btnTimer, &DDRA, &PINA, 3);
}

void Listener_eventCheck(){
	Listener_TimerEvent();
	Listener_FanEvent();
	Listener_FanUARTEvent();
}

void Listener_TimerEvent(){
	uint8_t TimerState;
	TimerState = Model_getTimerStateData();
	switch(TimerState){
		case NONE:
		if(Button_GetState(&btnTimer) == ACT_RELEASED){
			TimerState = THREE;
			Model_setTimerStateData(TimerState);
			Buzzer_buttonOn(200);
		}
		break;
		case THREE:
		if(Button_GetState(&btnTimer) == ACT_RELEASED){
			TimerState = FIVE;
			Model_setTimerStateData(TimerState);
			Buzzer_buttonOn(400);
		}
		break;
		case FIVE:
		if(Button_GetState(&btnTimer) == ACT_RELEASED){
			TimerState = SEVEN;
			Model_setTimerStateData(TimerState);
			Buzzer_buttonOn(600);
		}
		break;
		case SEVEN:
		if(Button_GetState(&btnTimer) == ACT_RELEASED){
			TimerState = NONE;
			Model_setTimerStateData(TimerState);
			Buzzer_buttonOn(100);
		}
		break;
	}
}

void Listener_FanEvent(){
	uint8_t FanState;
	FanState = Model_getFanStateData();
	switch(FanState){
		case OFF:
		if((Button_GetState(&btnOff) == ACT_RELEASED)){
			FanState = LOW;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(300);
		}
		else if((Button_GetState(&btnMode) == ACT_RELEASED)){
			FanState = LOW;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(300);
		}
		else if((Button_GetState(&btnAuto) == ACT_RELEASED)){
			FanState = AUTO;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(1000);
		}
		break;
		case LOW:
		if((Button_GetState(&btnMode) == ACT_RELEASED)){
			FanState = MIDDLE;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(500);
		}
		else if((Button_GetState(&btnAuto) == ACT_RELEASED)){
			FanState = AUTO;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(1000);
		}
		else if((Button_GetState(&btnOff) == ACT_RELEASED)){
			FanState = OFF;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(100);
		}
		break;
		case MIDDLE:
		if((Button_GetState(&btnMode) == ACT_RELEASED)){
			FanState = HIGH;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(800);
		}
		else if((Button_GetState(&btnAuto) == ACT_RELEASED)){
			FanState = AUTO;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(1000);
		}
		else if((Button_GetState(&btnOff) == ACT_RELEASED)){
			FanState = OFF;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(100);
		}
		break;
		case HIGH:
		if((Button_GetState(&btnMode) == ACT_RELEASED)){
			FanState = LOW;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(300);
		}
		else if((Button_GetState(&btnAuto) == ACT_RELEASED)){
			FanState = AUTO;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(1000);
		}
		else if((Button_GetState(&btnOff) == ACT_RELEASED)){
			FanState = OFF;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(100);
		}
		case AUTO:
		if((Button_GetState(&btnMode) == ACT_RELEASED)){
			FanState = LOW;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(300);
		}
		else if((Button_GetState(&btnOff) == ACT_RELEASED)){
			FanState = OFF;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(100);
		}
		else if((Button_GetState(&btnMode) == ACT_RELEASED)){
			FanState = LOW;
			Model_setFanStateData(FanState);
			Buzzer_buttonOn(300);
			break;
		}
	}
}

void Listener_FanUARTEvent()
{
	uint8_t* rxString;
	if(UART0_getRxFlag())
	{
		UART0_clearRxFlag();
		rxString = UART0_readRxBuff();
		
		if(!strcmp((char *)rxString,"OFF\n"))
		{
			Buzzer_buttonOn(100);
			Model_setFanStateData(OFF);
			
		}
		else if(!strcmp((char *)rxString,"LOW\n"))
		{
			Buzzer_buttonOn(300);
			Model_setFanStateData(LOW);
		}
		else if(!strcmp((char *)rxString,"MIDDLE\n"))
		{
			Buzzer_buttonOn(500);
			Model_setFanStateData(MIDDLE);
		}
		else if(!strcmp((char *)rxString,"HIGH\n"))
		{
			Buzzer_buttonOn(800);
			Model_setFanStateData(HIGH);
		}
		else if(!strcmp((char *)rxString,"AUTO\n"))
		{
			Buzzer_buttonOn(1000);
			Model_setFanStateData(AUTO);
		}
		else if(!strcmp((char *)rxString,"NONE\n"))
		{
			Buzzer_buttonOn(100);
			Model_setTimerStateData(NONE);
		}
		else if(!strcmp((char *)rxString,"TIME_3min\n"))
		{
			Buzzer_buttonOn(200);
			Model_setTimerStateData(THREE);
			Model_setTimerUartStateData(rxString);
		}
		else if(!strcmp((char *)rxString,"TIME_5min\n"))
		{
			Buzzer_buttonOn(400);
			Model_setTimerStateData(FIVE);
			Model_setTimerUartStateData(rxString);
		}
		else if(!strcmp((char *)rxString,"TIME_7min\n"))
		{
			Buzzer_buttonOn(600);
			Model_setTimerStateData(SEVEN);
			Model_setTimerUartStateData(rxString);
		}
	}
}