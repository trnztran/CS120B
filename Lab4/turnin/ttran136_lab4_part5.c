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

enum States {Start, pound, x1, y, x2, unlock, lock} State;
unsigned char X = 0x00;
unsigned char Y = 0x00;
unsigned char pound = 0x00;			
unsigned char button = 0x00;
unsigned char tmpB = 0x00;
unsigned char tmpC = 0x00;

void deadbolt(){
	switch(State){
		case Start:
			State = pound;
			break;
		case pound:	//press pound
			if(!X && !Y && pound && !button){State = x1;}
			else{State = pound;}
			break;
		case x1:
			if{X && !Y && !pound && !button){State = y;}
			else{State = pound;}
			break;
		case y:
			if{!X && Y && !pound && !button){State = x2;}
			else{State = pound;}
			break;	
		case x2:
			if{X && !Y && !pound && !button){State = unlock;}
			else{State = pound;}
			break;	
		case unlock:	//press button to lock
			if{!X && !Y && !pound && button){State = lock;}
			else{State = unlock;}
			break;
		case lock:
			State = Init;
			break;
		default:break;
	}
	switch(State){
		case pound:break;
		case pound: break;
		case x1: break;
		case y: break;
		case x2: break;
		case unlock:
			tmpB = 0x01;
			break;
		case lock:
			tmpB = 0x00;
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
	X = PINA & 0x01;
	Y = PINA & 0x02;
	pound = PINA & 0x04;
	button = PINA & 0x80;
	temp = 0x00;
	while (1) {
    		deadbolt();
	}
    return 1;
}
