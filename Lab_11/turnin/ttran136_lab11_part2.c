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
#include "io.c"
#endif

typedef struct task{
	signed char task;
	unsigned long int period;
	unsigned long int elapsedTime;
	int (*TickFct)(int);
}task;

enum states{output};

unsigned char tmpB= 0x00;
unsigned char cursor = 1;
unsigned char i;

const unsigned char phrase[66]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','C','S','1','2','0','B',' ','i','s',',','L','e','g','e','n','d','.','.','.','w','a','i','t',' ','f','o','r',' ','i','t',' ','D','A','R','Y','!',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

int tick(int state) {
  switch(state) {
    case output:
    for (i = 1; i <= 16; i++) {
      LCD_Cursor(i);
      LCD_WriteData(phrase[cursor+i-2]);
      if (cursor+i+1 == 66) {
        cursor = 1;
      }
    }
    cursor++;
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
