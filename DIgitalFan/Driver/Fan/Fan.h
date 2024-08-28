#ifndef FAN_H_
#define FAN_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../Periph/GPIO/GPIO.h"
#define FAN_ICR		ICR3
#define FAN_OCR		OCR3A

void Fan_init();
void Fan_speedMode(uint16_t data);
#endif