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

enum States {Start, Init, check, increment, decrement, reset, wait1, wait2} State;
unsigned char A0 = 0x00;
unsigned char A1 = 0x00;
unsigned char tmpC = 0x00;
void tick(){
	switch(State){
		case Start:
			State = Init;
			break;
		case Init:
			State = check;
			break;
		case check:
			if(A0 && !A1){State = increment;}
			else if(!A0 && A1){State = decrement;}
			else if(A0 && A1){State = reset;}
			break;
		case increment:
			State = wait1;
			break;
		case decrement:
			State = wait2;
			break;
		case reset:
			State = check;
			break;
		case wait1:
			if(!A0){State = check;}
			else if(A0){State = wait1;}
			else if(A0 && A1){State = reset;}
			break;
		case wait2:
			if(!A1){State = check;}
			else if(A1){State = wait2;}
			else if(A0 && A1){State = reset;}
			break;
		default: break;
		}
	switch(State){
		case Start:break;
		case Init:
			tmpC = 0x07;
			break;
		case check: break;
		case increment:
			if(tmpC < 9){
				tmpC = tmpC +1;
			}
			break;
		case decrement:
			if(tmpC>0){
				tmpC = tmpC - 1;
			}
			break;
		case reset:
			tmpC = 0x00;
			break;		
		case wait1:break;
		case wait2: break;
		default: break;
		}
}
			
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    State = Start;
	while (1) {
		A0 = PINA & 0x01;
		A1 = PINA & 0x02;
		PORTC = tmpC;
		tick();
    }
    return 1;
}
