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

enum States {Start, Init,s1,s2,unlock, lock} State;
unsigned char X = 0x00;
unsigned char Y = 0x00;
unsigned char pound = 0x00;			
unsigned char button = 0x00;
unsigned char tmpB = 0x00;
unsigned char tmpC = 0x00;
void deadbolt(){
	switch(State){
		case Start:
			State = Init;
			break;
		case Init:	//press pound
			if(pound && !X && !Y && !button){State = s1;}
			else{State = Init;}
			break;
		case s1:	//release pound
			if(!pound && !X &&!Y && !button){State = s2;}
			else{State = Init;}
			break;
		case s2:	//press y
			if(Y &&!pound && !X && !Y && !button){State = unlock;}
			else{State = Init;}
			break;
		case unlock:	//press button to lock
			if(button &&!Y &&!X && !pound){State = lock;}
			else{State = unlock;}
			break;
		case lock:
			State = Init;
			break;
		default:break;
	}
	switch(State){
		case Init:
			PORTC = 0x00;
			break;
		case s1:
			PORTC = 0x01;
			break;
		case s2:
			PORTC = 0x02;
			break;
		case unlock:
			tmpB = 0x01;
			PORTC = 0x03;
			break;
		case lock:
			tmpB = 0x00;
			PORTC = 0x04;
			break;
		default: break;
	}
}				
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    State = Start;
	X = PINA & 0x01;
	Y = PINA & 0x02;
	pound = PINA & 0x04;
	button = PINA & 0x80;
	while (1) {
    		deadbolt();
	}
    return 1;
}
