#ifndef APMAIN_H_
#define APMAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Listener/Listener.h"
#include "Service/Service_DigitalFan.h"
#include "Presenter/Presenter.h"
#include "../Model/Model_FanState/Model_FanState.h"
#include "../Model/Model_TimerState/Model_TimerState.h"
#include "../periph/TIM/TIM.h"
#include "../Periph/UART0/UART0.h"

void apMain_init();
void apMain_execute();

#endif