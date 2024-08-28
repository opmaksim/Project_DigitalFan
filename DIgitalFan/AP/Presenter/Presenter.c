#include "Presenter.h"

char *state[5] = {"OFF", "LOW", "MID", "HIGH", "AUTO"};

extern uint8_t fanRandom;

void Presenter_init(){
	FND_init();
	LCD_init();
	LCD_I2C_init();
	Fan_init();
}

void Presenter_dispTimeData(uint8_t hour, uint8_t min, uint8_t sec, uint16_t milisec){
	static uint16_t prevMilisec = 0xff;
	if(milisec/10 == prevMilisec){
		prevMilisec = milisec/10;
		return;
	}
	uint16_t stopWatchData;
	stopWatchData = min*100+sec;
	FND_setFndData(stopWatchData);
	if(milisec < 500) FND_colonOn();
	else FND_colonOff();
	
	static uint8_t prevstate;
	uint8_t FanState;
	FanState = Model_getFanStateData();
	char Fan_buff[30];
	switch(FanState){
		case OFF:
		sprintf(Fan_buff, "S:%s ", state[0]);
		
		break;
		case LOW:
		sprintf(Fan_buff, "S:%s ", state[1]);
		
		break;
		case MIDDLE:
		sprintf(Fan_buff, "S:%s ", state[2]);
		
		break;
		case HIGH:
		sprintf(Fan_buff, "S:%s", state[3]);
		
		break;
		case AUTO:
		sprintf(Fan_buff, "S:%s", state[4]);
		
		break;
	}
	char buff[30];
	sprintf(buff,"Timer Set");
	LCD_writeStringXY(0,3,buff);
	sprintf(buff,"%02d:%02d:%02d", min, sec, milisec/10);
	LCD_writeStringXY(1,1,strcat(Fan_buff, buff));
	if(FanState != prevstate)
	{
		LCD_I2C_clearDisplay();
		prevstate = FanState;
	}
	LCD_Gauge();
}



void Presenter_FanData(){
	uint8_t fanState;
	fanState = Model_getFanStateData();
	switch(fanState){
		case AUTO:
		Fan_speedMode(fanRandom);
		break;
		default:
		Fan_speedMode(fanState);
		break;
	}
}

void LCD_Gauge()
{
	uint8_t fanState;
	fanState = Model_getFanStateData();
	static uint8_t laststate;
	if(fanRandom != laststate)
	{
		LCD_I2C_clearDisplay();
		laststate = fanRandom;
	}
	if(fanState == OFF || (fanState == AUTO && fanRandom == OFF))
	{
		LCD_I2C_clearDisplay();
	}
	else if(fanState == LOW || (fanState == AUTO && fanRandom == LOW))
	{
		LCD_Gauge_Low();
	}
	else if(fanState == MIDDLE || (fanState == AUTO && fanRandom == MIDDLE))
	{
		LCD_Gauge_middle();
	}
	else if(fanState == HIGH || (fanState == AUTO && fanRandom == HIGH))
	{
		LCD_Gauge_high();
	}
}

