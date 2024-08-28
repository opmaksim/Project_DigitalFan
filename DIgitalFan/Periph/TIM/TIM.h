#ifndef TIM_H_
#define TIM_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void TIM0_init();
void TIM1_init();
void TIM2_init();
void TIM3_init();

#endif /* TIM0_H_ */