#include "apMain.h"

ISR(USART0_RX_vect)
{
	UART0_ISR_Process();
}

ISR(TIMER0_OVF_vect)
{
	FND_ISR_Process();
	TCNT0=130;
}

ISR(TIMER2_COMP_vect)
{
	DigitalFan_Timecalc();
	DigitalFan_Autocalc();
}

void apMain_init(){
	DigitalFan_init();
	Listener_init();
	Presenter_init();
	TIM0_init();
	TIM1_init();
	TIM2_init();
	TIM3_init();
	sei();
	Model_setTimerStateData(NONE);
	Model_setFanStateData(OFF);
}

void apMain_execute(){
	Listener_eventCheck();
	DigitalFan_execute();
}