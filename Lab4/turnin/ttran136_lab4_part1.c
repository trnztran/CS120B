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

enum States {Start, Init, pressed1, released1, pressed2, released2} State;
unsigned char button = 0x00;

void Led(){
	switch(State){
		case Start:
			State = Init;
			break;
		
		case Init:
			if(button== 0x01){
				State = pressed1;
			}
			break;
		case pressed1:
			if(button == 0x00){
				State = released1;
			}
			break;
		case released1:
			if(button == 0x01){
				State = pressed2;
			}
			break;
		case pressed2:
			if(button == 0x00){
				State = released2;
			}
			break;
		case released2:
			if(button == 0x01){
				State = pressed1;
			}
			break;
		default: State = Start; 
			break;
	}
	switch(State){
		case Init:
			PORTB = 0x01;
			break;
		case pressed1:
			PORTB = 0x02;
			break;
		case released1:
			break;
		case pressed 2:
			PORTB = 0x01;
			break;
		case released2:
			break;
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
