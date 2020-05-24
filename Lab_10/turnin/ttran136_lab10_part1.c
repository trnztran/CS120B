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
#include "io.h"
#include "timer.h"

enum states1{start1,led1,led2,led3}state1;
enum states2{start2, blinkOn, blinkOff}state2;
enum states3{start3, combSM}state3;
static unsigned char threeLEDs;
static unsigned char blinkingLED;

void tick1(){
    switch(state1){
        case start1:
            state1 = led1;
            break;
        case led1:
            state1 = led2;
            break;
        case led2:
            state1 = led3;
            break;
        case led3:
            state1 = led1;
            break;
        default:
            break;
    }
    switch(state1){
        case start1:
            break;
        case led1:
            threeLEDs = 0x01;
            break;
        case led2:
            threeLEDs = 0x02;
            break;
        case led3:
            threeLEDs = 0x04;
            break;
        default:
            break;
    }
}

void tick2(){
    switch(state2){
        case start2:
            state2 = blinkOn;
            break;
        case blinkOn:
            state2 = blinkOff;
            break;
        case blinkOff:
            state2 = blinkOn;
            break;
        default:
            break;
    }
    switch(state2){
        case start2:
            break;
        case blinkOn:
            blinkingLED = 0x08;
            break;
        case blinkOff:
            blinkigLED = 0x00;
            break;
        default:
            break;
    }
}

void tick3(){
    switch(state3){
        case start3:
            state3 = combSM;
            break;
        case combSM:
            break;
        default:
            break;
    }
    switch(state3){
        case start3:
            break;
        case combSM:
            PORTB = (threeLEDs|blinkingLED);
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; PORTB = 0x00;
    PORTB = threeLEDs;
    TimerSet(1000);
    TimerOn();
    state1 = start1;
    state2 = start2;
    /* Insert your solution below */
    while (1) {
        tick1();
        tick2();
        tick3();
        while(!TimerFlag){
        }
        TimerFlag = 0;
    }
    return 1;
}
