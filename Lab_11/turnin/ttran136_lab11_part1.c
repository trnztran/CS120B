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
#include "timer.h"
#include "scheduler.h"
#include "keypad.h"
#endif

typedef struct task{
	signed char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int(*TickFct)(int);
}task;

enum States{output};
unsigned char tmpB= 0x00;

int tick(int state) {
  unsigned char input;
  input = GetKeypadKey();
  switch(state) {
    case output:
    	switch(input) {
      		case '\0':
      			tmpB= 0x1F;
      			break;
      		case '1':
      			tmpB = 0x01;
      			break;
      		case '2':
      			tmpB = 0x02;
      			break;
      		case '3':
      			tmpB = 0x03;
      			break;
     		case '4':
      			tmpB = 0x04;
      			break;
      		case '5':
      			tmpB = 0x05;
      			break;
      		case '6':
      			tmpB = 0x06;
      			break;
      		case '7':
      			tmpB = 0x07;
      			break;
      		case '8':
      			tmpB = 0x08;
      			break;
      		case '9':
      			tmpB = 0x09;
      			break;
      		case 'A':
      			tmpB = 0x0A;
      			break;
      		case 'B':
      			tmpB = 0x0B;
      			break;
      		case 'C':
      			tmpB = 0x0C;
      			break;
      		case 'D':
      			tmpB = 0x0D;
      			break;
      		case '*':
      			tmpB = 0x0E;
      			break;
      		case '0':
      			tmpB = 0x00;
      			break;
      		case '#':
      			tmpB = 0x0F;
      			break;
      		default:
      			tmpB = 0x1B;
      			break;
    }
    state = output;
    PORTB = tmpB;
    break;
  }
  return state;
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0xF0; PORTA = 0x0F;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    DDRD = 0xFF; PORTD = 0x00;

    // unsigned long int
    static task task1;
    task *tasks[] = { &task1};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	   // Task 1
	   task1.state = 0;//Task initial state.
	   task1.period = 2;//Task Period.
	   task1.elapsedTime = 2;//Task current elapsed time.
     task1.TickFct = &tick;//Function pointer for the tick.

	   TimerSet(10);
	   TimerOn();

     unsigned short i; // Scheduler for-loop iterator
   	while(1) {
   		for ( i = 0; i < numTasks; i++ ) {
   			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
   				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
   				tasks[i]->elapsedTime = 0;
   			}
   			tasks[i]->elapsedTime += 1;
   		}
   		while(!TimerFlag);
   		TimerFlag = 0;
   	}
    return 0;
}
