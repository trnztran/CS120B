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
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, ButtonPress, wait} State;
unsigned char button = 0x00;

void Led(){
	switch(State){
		case Start:
			State = Init;
			break;
		
		case Init:
			if(button== 0x01){
				State = ButtonPress;
			}
			else if( button == 0x00){
				State = Init;
			}
			break;
		case ButtonPress:
			if(button == 0x01){
				State = ButtonPress;
			}
			else if(button == 0x00){
				State = wait;
			}
			break;
		case wait:
			if(button == 0x00){
				State = wait;
			}
			else if(button == 0x01){
				State = ButtonPress;
			}
			break;
		default: State = Start; 
			break;
	}
	switch(State){
		case Init:
			PORTB = 0x01;
			break;
		case ButtonPress:
			if(PORTB = 0x02){
				PORTB = 0x01;
			}
			else if (PORTB = 0x01){
				PORTB = 0x02;
			}
			break;
		case wait: break;
		default: break;
	} 
}	
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    State = Start;
	while (1) {
		button = PINA & 0x01;
		Led();
    }
    return 1;
}
