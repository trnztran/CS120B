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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char numA = 0x00;
	unsigned char numB = 0x00;
	unsigned char totalA = 0x00;
	unsigned char totalB = 0x00;
    /* Insert your solution below */
    while (1) {
	numA = PINA;
	numB = PINB;
	totalA = 0x00;
	totalB = 0x00;
	while(numA || numB){
		if(numA & 0x01){
			totalA++;
		}
		if(numB & 0x01){
			totalB++;
		}
		numA = numA>>1;
		numB = numB>>1;
	}
	PORTC = totalA +totalB;
}
	return 1;
}
