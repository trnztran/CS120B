/*	Author: ttran136
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo link: https://drive.google.com/file/d/1RwEpCZEPsutEi35CTXPmGpJTU-0pJ9GL/view?usp=sharing
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "io.h"
#include "timer.h"



enum states{Start,init,wait,increment,reset, decrement,rep_inc,rep_dec,rep_inc_wait,rep_dec_wait}state;
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
			else if(button0 && !button1){
				state = increment;	
			}
			else if(button1 && !button0){
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
				state = rep_dec_wait;
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
			if(button0 && (timer<10)){
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
			if(button1 && (timer<10)){
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
			break;
		case increment:
			if(tmpC<9){
				tmpC++;
				timer++;
			}
			break;
		case decrement:
			if(tmpC>0){
				tmpC--;
				timer++;
			}
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
			if(tmpC<9){
				tmpC++;
				timer = 0;
			}
			break;
		case rep_dec:
			if(tmpC>0){
				tmpC--;
				timer = 0;
			}
			break;
		default:
			break;
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC=0x00;
	DDRD = 0xFF; PORTD = 0x00;
	TimerSet(100);
	TimerOn();
	LCD_init();
	LCD_Cursor(1);
	
    while (1) 
    {
		LCD_ClearScreen();
		PORTC = tmpC;
		LCD_WriteData(tmpC +'0');
		button0 = ~PINA & 0x01;
		button1 = ~PINA & 0x02;
		tick();
		while(!TimerFlag);
		TimerFlag=0;
    }
}
