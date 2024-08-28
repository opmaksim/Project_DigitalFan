#include "Model_TimerState.h"

uint8_t TimerState;
uint8_t* TimerUartState;

uint8_t Model_getTimerStateData(){
	return TimerState;
}

void Model_setTimerStateData(uint8_t state){
	TimerState = state;
}

uint8_t* Model_getTimerUartStateData(){
	return TimerUartState;
}

void Model_setTimerUartStateData(uint8_t* state){
	TimerUartState = state;
}