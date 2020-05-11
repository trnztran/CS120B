/*	Author: ttran136
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	demo video for part 1,2,3: https://drive.google.com/file/d/1QLQfFOvnke7PooO3WSacv7ycJOy8e4Xc/view?usp=sharing
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
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

enum states{Start,led1,led2,led3}STATES;
	
void tick()
{
	switch(STATES) //Transition
	{
		case Start:
		STATES=led1;
		break;
		
		case led1:
		STATES=led2;
		break;
		
		case led2:
		STATES=led3;
		break;
		
		case led3:
		STATES=led1;
		break;
		
		default:
		STATES=Start;
		break;
	}
	
	switch(STATES) //Actions
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
		
		default:
		break;
	}
}


int main(void)
{
	DDRB=0xFF; PORTB=0x00;
	TimerSet(1000);
	TimerOn();
	
    while (1) 
    {
		tick();
		while(!TimerFlag);
		TimerFlag=0;
    }
}
