﻿#ifndef UART0_H_
#define UART0_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
void UART0_ISR_Process();
void UART0_init();
void UART0_Transmit(unsigned char data);
unsigned char UART0_Receive(void);
void UART0_sendString(char *str);
uint8_t UART0_Avail();

void UART0_clearRxFlag();
void UART0_setRxFlag();
uint8_t UART0_getRxFlag();
uint8_t* UART0_readRxBuff();
#endif