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
#include "timer.h"

/* SM state declarations --- fill in as needed */
typedef enum ping_states { PInit,pingLow,pingHigh                           } ping_states;
typedef enum detect_eq_states { DEQInit,  eq_detected                       } detect_eq_states;
typedef enum detect_max_amp_states { DMAInit, DMA2                              } detect_max_amp_states;
typedef enum detect_zc_states { DZCInit,                                    } detect_zc_states;
typedef enum transmit_states {TInit,combSM                                        } transmit_states;

/* shared variables --- fill in as needed */

unsigned char amplitude;
unsigned char direction;
unsigned char eq;
unsigned char pingB;
unsigned char DMA;


/* state variables --- do not alter */
ping_states ping_state;
detect_eq_states detect_eq_state;
detect_max_amp_states detect_max_amp_state;
detect_zc_states detect_zc_state;
transmit_states transmit_state;

/* SM definitions --- complete each task as a SM in the appropriate file.
 * Alternatively, you can remove the #include statement and insert your
 *   SM implementation directly. 
 */
#include "ping.h"
#include "detect_eq.h"
#include "detect_max_amp.h"
#include "detect_zc.h"
#include "transmit.h"


/* main function --- do not alter */
int main(void) {
    /* DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    amplitude = ~PINA & 0x07;
    direction = ~PINA & 0xF8;
    // Common period for all tasks set to 100ms
    TimerSet(100);
    TimerOn();

    // init state vars
    ping_state = PInit;
    detect_eq_state = DEQInit;
    detect_max_amp_state = DMAInit;
    detect_zc_state = DZCInit;
    transmit_state = TInit;

    while (1) {
        Ping();
        Detect_EQ();
        Detect_Max_Amp();
        Detect_ZC();
        Transmit();
        while (!TimerFlag) { }
        TimerFlag = 0;
    }
    return 1;
}
