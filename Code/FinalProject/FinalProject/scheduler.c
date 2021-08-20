/*
 * schedular.c
 *
 * Created: 6/3/2021 3:30:46 PM
 *  Author: FADY
 */ 
#include "scheduler.h"

/*counter for each 50ms*/
volatile S32 counter_50ms = 0;

/* global variable to count the number of overflows*/
volatile S32 tot_overflow = 0;
volatile S32 count_250 = 0;

Pftype callBacks[8] = {&notify_50ms, &notify_100ms, &notify_200ms, &notify_500ms,0,0,0,0};

unsigned char one_time_flag = 0;

unsigned char F1_100ms = 1;

unsigned char F2_100ms = 0;

unsigned char flag_100ms = 1;

unsigned char indexOf = 0;

unsigned char lcd_100ms = 0;

volatile unsigned char delayActivated = 0;



void Delay_100(Pftype nextFunction, S32 id )
{
 /* change id,counter types for misra later*/
	TCNT2 = 0;
	tot_overflow = 0;
	counter_50ms = 0;
	callBacks[id] = nextFunction;
	delayActivated = 1;
}



void timer_init()
{	/*Timer 2 Init*/
	TCNT2 = 0;   /* init counter 0*/

	TCCR2 = (1<<CS20) | (1<<CS22) | (1<<CS21); /* Timer 2 mode with 1024 prescale*/
	enable_timer_interrupt();
}

void enable_timer_interrupt(void){
		TIMSK = (1 << TOIE2) ;   /* Enable timer2 overflow interrupt(TOIE2)*/
		sei();        /* Enable global interrupts by setting global interrupt enable bit in SREG*/
		tot_overflow = 0;
}

ISR (TIMER2_OVF_vect)    
{
/* Timer2 ISR  MISRA VIOLATION JUSTIFICATION : ISR are known by AVR and doesn't need function Prototype*/
	tot_overflow ++;
	
	if (tot_overflow >= 3)
	{
		
		callBacks[0]();
		TCNT2 = 0;            /* reset counter*/
		
		tot_overflow = 0;     /* reset overflow counter*/
		
		counter_50ms = counter_50ms + 1 ;
		
		if (( counter_50ms % 2 ) == 0)
		{
			/*100 ms*/
			callBacks[1]();
			
			if (lcd_100ms == (unsigned char)1)
			{
				lcd_100ms = 0;

			}
			else if (lcd_100ms == (unsigned char)0)
			{
				lcd_100ms = 1;

			}
			if (one_time_flag == 1)
			{
				callBacks[indexOf]();
				one_time_flag = 0;
			}
			else
			{
				
			}
		}
		
		
		if ((counter_50ms % 4) == 0)
		{
			/*200 ms*/
			callBacks[2]();
			
			if (delayActivated == 1)
			{
				
				callBacks[6]();
				
			}
			else{}
				
			if (flag_100ms == (unsigned char)1)
			{
				
				flag_100ms = (unsigned char)2;
				
				F2_100ms = (unsigned char)1;
				
				
			}
			
			else if (flag_100ms == (unsigned char)2)
			{
				flag_100ms = (unsigned char)1;
				
				F1_100ms = (unsigned char)1;
				
			}
			else{
				/*do nothing*/
			}
			
		}
		
		if ((counter_50ms % 5) == 0)
		{
			count_250 = count_250 + 1;
			
			if((count_250 % 2) == 0)
			{
				
				
				callBacks[3]();
				
				count_250 = 0;
				
				
			}
			else
			{}
			
			counter_50ms = 0;
		}
		else{}
		
				
	}
		
		
/*No return from this function since it's an interrupt service routine*/
		
}

