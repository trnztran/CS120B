/*	Author: ttran136
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 * demo link for part 2: https://drive.google.com/file/d/1O8xQPZ5fmuqCDIKgpTOqEnsyr9VEl2ZK/view?usp=sharing
 *
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, init, wait, increment, decrement, reset, wait1, wait2, wait3}state;
unsigned char buttonA0 = 0x00;
unsigned char buttonA1 = 0x00;
unsigned char tmpC = 0x00;

void tick(){
    switch(state){
        case Start:
            state = init;
            break;
        case init:
            state = wait;
            break;
        case wait:
            if(!buttonA0 && !buttonA1){
                state = wait;
            }
            else if(buttonA0 && buttonA1){
                state = reset;
            }
            else if((tmpC < 9) && (buttonA0 && !buttonA1)){
                state = increment;
            }
            else if((tmpC > 0) && (!buttonA0 && buttonA1)){
                state = decrement;
            }
            else{
                state = wait;
            }
            break;
        case increment:
            state = wait1;
            break;
        case decrement:
            state = wait2;
            break;
        case reset:
            state = wait3;
            break;
        case wait3:
            if(!buttonA0 && !buttonA1){
                state = wait;
            }
            else if(buttonA0 && buttonA1){
                state = wait3;
            }
            break;
        case wait2:
            if(buttonA0 && buttonA1){
                state = reset;
            }
            else if (!buttonA1){
                state = wait2;
            }
            break;
        case wait1:
            if(buttonA0 && buttonA1){
                state = reset;
            }
            else if (buttonA0){
                state = wait1;
            }
            break;
        default:
            break;
    }
    switch(state){
        case Start:
            break;
        case init:
            tmpC = 0x00;
            break;
        case wait:
            break;
        case increment:
            tmpC++;
            break;
        case decrement:
            tmpC--;
            break;
        case reset:
            tmpC = 0x00;
            break;
        case wait3:
        case wait2:
        case wait1:
            break;
        default:
            break;
    }
}
            

int main(void) {
    /* Insert DDR and PORT initializations */
 	DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */

    while (1) {
            PORTC = tmpC;
            buttonA0 = ~PINA & 0x01;
            buttonA1 = ~PINA & 0x02;
            tick();
    }
    return 1;
}
