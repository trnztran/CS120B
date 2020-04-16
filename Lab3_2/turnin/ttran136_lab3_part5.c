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
	DDRB = 0xFE; PORTB = 0x01;
	DDRD = 0x00; PORTD = 0xFF;
	
	unsigned char airbag = 0x00;
	unsigned char weight = 0x00;
	while(1){
	weight = PIND;
	weight = (PIND <<1)|(PINB & 0x01);
	if(weight >= 70){
		airbag = 0x02;
	}
	else if((weight>5) && (weight<70)){	
		airbag = 0x04;
	}
	else if(weight<=5){
		airbag = 0x00; 
	}
	PORTB = airbag;
}
return 1;
}
