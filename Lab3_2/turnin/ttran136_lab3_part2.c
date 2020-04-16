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
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char FuelLevel = 0x00;
	unsigned char sensor = 0x00;
    /* Insert your solution below */
    while (1) {
	FuelLevel = PINA;
	if( FuelLevel == 1||FuelLevel == 2){
		sensor = 0x60; 
	}
	if( FuelLevel == 3||FuelLevel == 4){
		sensor = 0x70; 
	}
	if( FuelLevel == 5||FuelLevel == 6){
		sensor = 0x38;
	}
	if( FuelLevel >= 7 && FuelLevel <= 9){
		sensor =0x3C; 
	}
	if( FuelLevel >= 10 && FuelLevel <= 12){
		sensor = 0x3E;
	}
	if( FuelLevel >= 13 && FuelLevel <= 15){
		sensor = 0x3F;
	}
	PORTC = sensor;
    }

    return 1;
}
