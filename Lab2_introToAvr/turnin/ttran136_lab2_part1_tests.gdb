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
	DDRB = 0xFF; PORTB = 0x00;

	unsigned char Input1 = 0x00; 	//light sensor
	unsigned char Input0 = 0x00;	//grage door sensor
    /* Insert your solution below */
    while (1) {
	Input0 = PINA & 0x01;
	Input1 = PINA & 0x02;
	if((Input1 == 0x00) && (Input0 == 0x01)){
		PORTB = 0x01;
    }
	else{
		PORTB = 0x00;
		}	
	}
    return 1;
}
