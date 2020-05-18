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
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	// in Free Running Mode, a new conversion will trigger
	// whenever the previous conversion completes.
}

unsigned short max = 0x0C7;
unsigned short sample = 0x00;
unsigned short test = 0x00;
	
int main(void)
{	
	test = (max / 8);
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	ADC_init();
	
    while(1)
    {
		sample = ADC;
		if(sample <= test)
		{
			PORTB = 0x01;
		}
		else if(sample <= (2*test))
		{
			PORTB = 0x03;
		}
		else if(sample <= (3*test))
		{
			PORTB = 0x07;
		}
		else if(sample <= (4*test))
		{
			PORTB = 0x0F;
		}
		else if(sample <= (5*test))
		{
			PORTB = 0x1F;
		}
		else if(sample <= (6*test))
		{
			PORTB = 0x3F;
		}
		else if(sample <= (7*test))
		{
			PORTB = 0x7F;
		}
		else
		{
			PORTB = 0xFF; 
		}
    }
}
