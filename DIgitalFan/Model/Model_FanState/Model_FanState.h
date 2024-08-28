
#ifndef MODEL_FANSTATE_H_
#define MODEL_FANSTATE_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

enum {OFF, LOW = 5, MIDDLE = 2, HIGH = 1, AUTO = 6};


uint8_t Model_getFanStateData();
void Model_setFanStateData(uint8_t state);
#endif