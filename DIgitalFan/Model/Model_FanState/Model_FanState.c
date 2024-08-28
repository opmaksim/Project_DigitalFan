#include "Model_FanState.h"

uint8_t FanState;

uint8_t Model_getFanStateData(){
	return FanState;
}

void Model_setFanStateData(uint8_t state){
	FanState = state;
}