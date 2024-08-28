#include "TIM.h"

void TIM0_init() // 1ms overflow Interrupt, FND Display
{
	// 128 1ms interrupt
	TCCR0 |= ((1<<CS02) | (0<<CS01) | (1<<CS00));	// 128 PreScaler
	TIMSK |= (1<<TOIE0);							//TIMSK Timer/Counter0 overflow 설정
	TCNT0 = 130;
}

void TIM1_init(){
	TCCR1B |= ((0<<CS12) | (1<<CS11) | (1<<CS10));
	TCCR1B |= ((1<<WGM13) | (1<<WGM12));
	TCCR1A |= ((1<<WGM11) | (0<<WGM10));
	TCCR1A &= ~((1<<COM1A1) | (1<<COM1A0));
}

void TIM2_init(){
	//TCCR2, 1/64 1ms period interrupt, CTC mode
	//1/64 prescaler
	TCCR2 |= ((0<<CS22) | (1<<CS21) | (1<<CS20));
	TIMSK |= (1<<OCIE2);
	//CTC mode
	TCCR2 |= ((1<<WGM21) | (0<<WGM20));
	OCR2 = 250-1;
}

void TIM3_init(){
	TCCR3B |= ((0<<CS32) | (1<<CS31) | (1<<CS30));	// Prescaler -> 1/64
	TCCR3B |= ((1<<WGM33) | (1<<WGM32));
	TCCR3A |= ((1<<WGM31) | (0<<WGM30));			// Fast PWM Mode 14
	TCCR3A |= ((1<<COM3A1) | (0<<COM3A0));
}