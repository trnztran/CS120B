/*	Author: ttran136
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"


volatile unsigned char TimerFlag=0;
unsigned long _avr_timer_M=1;
unsigned long _avr_timer_cntcurr=0;
 
void TimerISR()
{
	TimerFlag=1;
}

void TimerSet(unsigned long M)
{
	_avr_timer_M=M;
	_avr_timer_cntcurr=_avr_timer_M;
}

void TimerOn()
{
	TCCR1B=0x0B;
	OCR1A=125;
	TIMSK1=0x02;
	TCNT1=0;
	_avr_timer_cntcurr=_avr_timer_M;
	SREG |= 0x80;
}

void TimerOff()
{
	TCCR1B=0x00;
}

ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr==0)
	{
		TimerISR();
		_avr_timer_cntcurr=_avr_timer_M;
	}
}

enum states{Start,led1, led2,led3,led4,wait,restart}state;
	
void tick()
{
	switch(state) //Transition
	{
		case Start:
		state=led1;
		break;
		
		case led1:
		if((~PINA & 0x01) == 0x01){
			state = wait;
		}
		else{
			state=led2;
		}
		break;
		
		case led2:
		if((~PINA & 0x01) == 0x01){
			state = wait;
		}
		else{
			state = led3;	
		}
		break;
		
		case led3:
		if((~PINA & 0x01) == 0x01){
			state = wait;
		}
		else{
			state = led4;	
		}
		break;
		
		case led4:
		if((~PINA & 0x01) == 0x01){
			state = wait;
		}
		else{
			state = led1;
		}
		break;
		case wait:
		if((~PINA & 0x01) == 0x01){
			state = wait;
		}
		else{
			state = restart;
		}
		break;
		case restart:
		if((~PINA & 0x01) == 0x01){
			state = led1;
		}
		else{
			state = restart;
		}
		break;
		default:
		state=Start;
		break;
	}
	
	switch(state) //Actions
	{
		case led1:
		PORTB=0x01;
		break;
		
		case led2:
		PORTB=0x02;
		break;
		
		case led3:
		PORTB=0x04;
		break;
		
		case led4:
		PORTB = 0x02;
		break;
		
		default:
		break;
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB=0xFF; PORTB=0x00;
	TimerSet(300);
	TimerOn();
	
    while (1) 
    {
		tick();
		while(!TimerFlag);
		TimerFlag=0;
    }
}
