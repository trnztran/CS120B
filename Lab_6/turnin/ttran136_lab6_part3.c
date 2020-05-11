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

enum states{Start,init,wait,increment,reset, decrement,wait3,rep_inc,rep_dec,rep_inc_wait,rep_dec_wait}state;
unsigned char button0 = 0x00;
unsigned char button1 = 0x00;
unsigned char tmpC = 0x00;
unsigned char timer = 0;

void tick()
{
	switch(state) //Transition
	{
		case Start:
		state = init;
		break;
		case init:
		state = wait;
		break;
		case wait:
		if(button0 && button1){
			state = reset;
		}
		else if(button0){
			state = increment;	
		}
		else if(button1){
			state = decrement;
		}
		else{
			state = wait;
		}
		break;
		case increment:
		if(button0){
			state = rep_inc_wait;
		}
		else{
			state = wait;
		}
		break;
		case decrement:
		if(button1){
			state = rep_inc_wait;
		}
		else{
			state = wait;
		}
		break;
		case reset:
		if(button0 && button1){
			state = reset;
		}
		else{
			state = wait;
		}
		break;
		case rep_inc:
		state = rep_inc_wait;
		break;
		case rep_dec:
		state = rep_dec_wait;
		break;
		case rep_inc_wait:
		if(button0&&(timer<10)){
			state = rep_inc_wait;
		}
		else if(button0 &&(timer>=10)){
			state = rep_inc;
		}
		else{
			state = wait;
		}
		break;
		case rep_dec_wait:
		if(button1&&(timer<10)){
			state = rep_dec_wait;
		}
		else if(button1 &&(timer>=10)){
			state = rep_dec;
		}
		else{
			state = wait;
		}
		break;
		default:break;
	}
	
	switch(state){
		case Start:
		break;
		case init:
		tmpC = 0x07;
		break;
		case wait:
		timer = 0;
		case increment:
		tmpC++;
		timer++;
		break;
		case decrement:
		tmpC--;
		timer++;
		break;
		case reset:
		tmpC = 0x00;
		break;
		case rep_inc_wait:
		timer++;
		break;
		case rep_dec_wait:
		timer++;
		break;
		case rep_inc:
		tmpC++;
		timer = 0;
		break;
		case rep_dec:
		tmpC--;
		timer = 0;
		break;
		default:
		break;
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB=0xFF; PORTB=0x00;
	TimerSet(100);
	TimerOn();
	
    while (1) 
    {
		PORTB = tmpC;
		button0 = ~PINA & 0x01;
		button1 = ~PINA & 0x02;
		tick();
		while(!TimerFlag);
		TimerFlag=0;
    }
}
