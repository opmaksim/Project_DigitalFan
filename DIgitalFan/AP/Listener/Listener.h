#ifndef LISTENER_H_
#define LISTENER_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "../../Model/Model_TimerState/Model_TimerState.h"
#include "../../Model/Model_FanState/Model_FanState.h"
#include "../../Periph/GPIO/GPIO.h"
#include "../../Periph/UART0/UART0.h"
#include "../../Driver/Buzzer/Buzzer.h"
#include "../../Driver/Button/button.h"

void Listener_init();
void Listener_eventCheck();
void Listener_TimerEvent();
void Listener_FanEvent();
void Listener_AutoEvent();
void Listener_FanUARTEvent();
#endif