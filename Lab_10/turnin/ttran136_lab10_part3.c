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
#define A2 (~PINA & 0x04)

enum states1{start1,led1,led2,led3}state1;
enum states2{start2, blinkOn, blinkOff}state2;
enum states3{start3, combSM}state3;
enum states4{start4, on, off, reset} state4;
static unsigned char threeLEDs;
static unsigned char blinkingLED;
static unsigned char speaker;

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
            blinkingLED = 0x00;
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
            PORTB = (speaker|threeLEDs|blinkingLED);
            break;
        default:
            break;
    }
}

void tick4(){
    switch(state4){
        case start4:
            state4 = off;
            break;
        case off:
            if(A2){
                state4= on;
            }
            else{
                state4 = off;
            }
            break;
        case on:
            state4 = reset;
            break;
        case reset:
            state4 = off;
            break;
        default:
            break;
    }
    switch(state4){
        case start4:
            break;
        case off:
            speaker = 0x00;
            break;
        case on:
            speaker = 0x10;
            break;
        case reset:
            speaker = 0x00;
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    unsigned long threePeriod = 300;
    unsigned long blinkPeriod = 1000;
    unsigned long PERIOD = 1;
    unsigned long speakerPeriod = 2;
    TimerSet(PERIOD);
    TimerOn();
    state1 = start1;
    state2 = start2;
    state3 = start3;
    state4 = start4;
    /* Insert your solution below */
    while (1) {
        if(threePeriod >= 300){
            tick1();
            threePeriod = 0;
        }
        if(blinkPeriod >= 1000){
            tick2();
            blinkPeriod = 0;
        }
        if(speakerPeriod >=2){
            tick4();
            blinkPeriod = 0;
        }
        tick3();
        while(!TimerFlag){
        }
        TimerFlag = 0;
        threePeriod += PERIOD;
        blinkPeriod += PERIOD;
        speakerPeriod += PERIOD;
    }
    return 1;
}
