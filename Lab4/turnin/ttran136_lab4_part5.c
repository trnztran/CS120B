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

enum States {Start, Init, unlock, lock} State;
unsigned char X = 0x00;
unsigned char Y = 0x00;
unsigned char pound = 0x00;			
unsigned char button = 0x00;
unsigned char tmpB = 0x00;
unsigned char tmpC = 0x00;
unsigned char sequence[] = {0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01};
unsigned char temp = 0x00;

void test_sequence(){
	while(1){
		if(PINA == sequence[temp]){
			temp = 0x01;
			break;
		}
		else{
			temp = 0;
		}
		break;
	}
}

void deadbolt(){
	switch(State){
		case Start:
			State = Init;
			break;
		case Init:	//press pound
			if(temp == 0x01){State = unlock;}
			else{State = Init;}
			break;
		case unlock:	//press button to lock
			if(button){State = lock;}
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
		case unlock:
			tmpB = 0x01;
			PORTC = 0x03;
			break;
		case lock:
			tmpB = 0x00;
			temp = 0x00;
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
	temp = 0x00;
	while (1) {
    		deadbolt();
	}
    return 1;
}
