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
#include <avr/interrupt.h>

void set_PWM(double frequency) {
	static double current_frequency; 
	if (frequency != current_frequency) {
		if (!frequency) { TCCR0B &= 0x08; } 
		else { TCCR0B |= 0x03; } 
		if (frequency < 0.954) { OCR0A = 0xFFFF; }
		else if (frequency > 31250) { OCR0A = 0x0000; }
		else { OCR0A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT0 = 0; 
		current_frequency = frequency; 
	}
}

void PWM_on() {
	TCCR0A = (1 << COM0A0 | 1 << WGM00);
	TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);
	set_PWM(0);
}

void PWM_off() {
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}

enum States{off, turnOff, on, compOn, up, waitUp, down, waitDown}state;


unsigned char button = 0x00;

const double array[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char i = 0x00;

void tick(){
	button = ~PINA & 0x07;
	switch(state){ // Transitions
		case off:
			if(button == 1)
				state = on;
			else
				state = off;
			break;
		case turnOff:
			if(!(button == 1))
				state = off;
			else
				state = turnOff;
			break;
		case on:
			if(button == 1)
				state = on;
			else
				state = compOn;
			break;
		case compOn:
			if(button == 2){
				if(i < 7)
					i++;
				state = up;
			}
			else if(button == 4){
				if(i > 0)
					i--;
				state = down;
			}
			else if(button == 1)
				state = turnOff;
			else
				state = compOn;
			break;
		case up:
			state = waitUp;
			break;
		case waitUp:
			if(button == 2)
				state = waitUp;
			else
				state = compOn;
			break;
		case down:
			state = waitDown;
			break;
		case waitDown:
			if(button == 4)
				state = waitDown;
			else
				state = compOn;
			break;
	}
	switch(state){ // State actions
		case off:
			PWM_off();
			break;
		case turnOff:
			break;
		case on:
			PWM_on();
			break;
		case compOn:
			break;
		case up:
			set_PWM(array[i]);
			break;
		case waitUp:
			break;
		case down:
			set_PWM(array[i]);
			break;
		case waitDown:
			break;

	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; 
	DDRB = 0xFF; PORTB = 0x00; 
	PWM_on();
	state = off;
	while(1){
		tick();
	}
