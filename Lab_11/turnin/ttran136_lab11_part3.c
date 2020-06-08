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
#include "io.h"
#include "keypad.h"
#include "scheduler.h"

enum States{output};
unsigned char tmpA = 0x00;

int tick(int state){
	unsigned char i;
	i = GetKeypadKey();
	switch(state){
		case output:
			switch (x) {
				case '\0': 
					break; 
				case '1': 
					tmpA = 0x01;
					LCD_Cursor(1); 
					LCD_WriteData(tmpA + '0'); 
					break; 
				case '2': 
					tmpA = 0x02;
					LCD_Cursor(1); 
					LCD_WriteData(tmpA + '0');
					break;
				case '3': 
					tmpA = 0x03;
					LCD_Cursor(1); 
					LCD_WriteData(tmpA + '0'); 
					break;
				case '4': 
					tmpA = 0x04; 
					LCD_Cursor(1); 
					LCD_WriteData(tmpA + '0'); 
					break;
				case '5': 
					tmpA = 0x05;
					LCD_Cursor(1); 
					LCD_WriteData(tmpA + '0'); 
					break;
				case '6':
					tmpA = 0x06;
					LCD_Cursor(1); 
					LCD_WriteData(tmpA + '0'); 
				        break;
				case '7': 
					tmpA = 0x07;
					LCD_Cursor(1); 
					LCD_WriteData(tmpA + '0'); 
					break;
				case '8': 
                    		    	tmpA = 0x08;
				    	LCD_Cursor(1); 
                   		    	LCD_WriteData(tmpA + '0'); 
                    		    	break;
				case '9': 
					tmpA = 0x09;
					LCD_Cursor(1); 
					LCD_WriteData(tmpA + '0'); 
					break;
				case 'A': 
                      		    	tmpA = 0x0A;
				    	LCD_Cursor(1); 
                   		    	LCD_WriteData(tmpA + 0x37); 
                   		    	break;
				case 'B': 
					tmpA = 0x0B;
				    	LCD_Cursor(1); 
					LCD_WriteData(tmpA + 0x37); 
				        break;
				case 'C': 
                    		    	tmpA = 0x0C;
				    	LCD_Cursor(1); 
                    		     	LCD_WriteData(tmpA + 0x37); 
                    			break;
				case 'D': 
                    			tmpA = 0x0D;
				    	LCD_Cursor(1); 
                    			LCD_WriteData(tmpA + 0x37); 
                    			break;
				case '*': 
                    			tmpA = 0x0E;
				    	LCD_Cursor(1); 
                    			LCD_WriteData(tmpA + 0x1C);
                    			break;
				case '0': 
                    			tmpA = 0x00;
				    	LCD_Cursor(1); 
                   			LCD_WriteData(tmpA + '0'); 
                    			break;
				case '#': 
                    			tmpA = 0x0F;
				    	LCD_Cursor(1);
                    			LCD_WriteData(tmpA + 0x14);
                    			break;
				default: 
                    			tmpA = 0x1B; 
                    			break; 
			}
			state = output;
			PORTA=tmpA;
			break;
		}
		return state;
}


int main()
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRC = 0xF0; PORTC = 0x0F; 
	DDRD = 0xFF; PORTD = 0x00;
	
	static task task1;
	task *tasks[] = { &task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	task1.state = 0;
	task1.period = 30;
	task1.elapsedTime = 10;
	task1.TickFct = &tick;

	TimerSet(10);
	TimerOn();
	LCD_init();

	unsigned short i; // Scheduler for-loop iterator
	while(1) {
		// Scheduler code
		for ( i = 0; i < numTasks; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime >= tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}
