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

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}


unsigned short max = 0x0C7=8;
unsigned short test = 0x00;
	
int main(void){	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	ADC_init();
	
    while(1){
					test = ADC;
					if(test >= (max / 2))
					{
						PORTB = 0x01;
					}
					else
					{
						PORTB = 0x00;
					}
    }
}
