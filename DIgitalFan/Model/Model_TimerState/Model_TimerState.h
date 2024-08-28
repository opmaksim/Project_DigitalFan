#ifndef MODEL_TIMERSTATE_H_
#define MODEL_TIMERSTATE_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
enum {NONE, THREE, FIVE, SEVEN};

uint8_t Model_getTimerStateData();
void Model_setTimerStateData(uint8_t state);
uint8_t* Model_getTimerUartStateData();
void Model_setTimerUartStateData(uint8_t* state);
#endif