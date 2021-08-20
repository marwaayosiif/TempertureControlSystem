/*
 * FinalProject.c
 *
 * Created: 6/1/2021 2:15:11 PM
 * Author : EG
 */ 



#define F_CPU 16000000ul			/* Define CPU Frequency e.g. here 16MHz */
#include "DIO.h"
#include "LCD.h"
#include "TC72.h"
#include "SPI.h"
#include "states_control.h" 
#include "scheduler.h"
#include "Notifier.h"
#include "DSP_M.h"
#include "Pwm.h"
#include "ADC.h"
#include "Keypad.h"
#define MAX_COUNT ((unsigned char)100)
#define DECIMAL_BASE ((unsigned char)10)
#define DELAY_COUNT ((unsigned char)100)
#include <util/delay.h>			/* Include Delay header file */
#include <avr/io.h>


int main(void)
{   
	SPI_Init();
	TC72_Intit();
	adc_init();
	Pwm_Init();
	States_Control_Init();
	
 	LCD_Init();			/* Initialization of LCD*/		
	timer_init();
	Welcome_Screen();
	Idle_Screen();
		

	while(1){
		/* LCD interface with TC72*/
		keypad_Interface();	

		
	}
		return 0;
       
   
}

