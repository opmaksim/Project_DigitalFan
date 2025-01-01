#include "Buzzer.h"

void Buzzer_init(){
	DDRB |= (1<<5);
}

void Buzzer_soundOn(){
	TCCR1A |= ((1<<COM1A1) | (0<<COM1A0));	// non-inverting mode
}

void Buzzer_soundOff(){
	TCCR1A &= ~((1<<COM1A1) | (1<<COM1A0));	// disconnected
}

void Buzzer_makeHertz(uint16_t hertz){
	if(hertz < 100) hertz = 100;
	else if(hertz > 5000) hertz = 5000;
	BUZZER_ICR = (250000 / hertz) - 1;
	BUZZER_OCR = BUZZER_ICR / 4;
}

void Buzzer_buttonOn(uint16_t hertz){
	Buzzer_soundOn();
	Buzzer_makeHertz(hertz);
	_delay_ms(400);
	Buzzer_soundOff();
}