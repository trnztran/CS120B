/*	Author: ttran136
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  demo link for parts 1,2: https://drive.google.com/file/d/1TdJhEiOzRfccHwcVBxYnvmkFFYexuMNC/view?usp=sharing
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

enum States{start, silent, C_note, D_note, E_note}state;

unsigned char button = 0x00;

void button_Tick(){
	button = ~PINA & 0x07;
	switch(state){ // Transitions
        case start:
            state = silent;
            break;
        case silent:
			if(button == 1){
				state = C_note;
			}
			else if(button == 2){
				state = D_note;			
			}
			else if(button == 4){
				state = E_note;
			}
			else{
				state = silent;
			}
			break;
		case C_note:
			if(button == 1){
				state = C_note;
			}
			else{
				state = silent;
			}
			break;
		case D_note:
			if(button == 2){
				state = D_note;
			}
			else{
				state = silent;
			}
			break;
		case E_note:
			if(button == 4){
				state = E_note;
			}
			else{
				state = silent;
			}
			break;
	}
	switch(state){ // State actions
		case silent:
			set_PWM(0);
			break;
		case C_note:
			set_PWM(261.63);
			break;
		case D_note:
			set_PWM(293.66);
			break;
		case E_note:
			set_PWM(329.63);
			break;
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // A input initialized to 0xFF
	DDRB = 0xFF; PORTB = 0x00; // B output initialized to 0x00
	PWM_on();
	state = start;
	while(1){
		button_Tick();
	}
}
