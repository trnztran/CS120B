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
	DDRB = 0XFF; PORTB = 0X00;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char upperBit;
	unsigned char lowerBit;
    while (1) {
	upperBit = PINA & 0xF0;
	lowerBit = PINA & 0x0F;
	upperBit = upperBit >> 4;
	lowerBit = lowerBit << 4;
	PORTB = upperBit;
	PORTC = lowerBit;
	}
	return 1;
}
