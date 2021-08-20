/*
 * Keypad.h
 *
 * Created: 6/1/2021 11:06:51 PM
 *  Author: zeinab walid
 */ 
#ifndef KEYPAD_H_INCLUDED
#define KEYPAD_H_INCLUDED

#include <avr/io.h>
#include <util/delay.h>


#ifndef F_CPU
#define F_CPU 16000000ul            /* Define CPU Frequency e.g. here 16MHz */
#endif


#define KEYPAD_PORT PORTD
#define KEYPAD_DDR   DDRD
#define KEYPAD_PIN   PIND

#define DELAY_COUNT ((unsigned char)100)
#include "states_control.h"
#include "Basic_Types.h"

/*#include <string.h>*/
#include <stdio.h>
#include <stdlib.h>

#include "DIO.h"
#include "DSP_M.h"
#include "scheduler.h"



void DIO_Keypad( unsigned char Value , unsigned char index);
S32 concat(unsigned char x, unsigned char y);
unsigned char GetKeyPressed(void);
void keypad_Interface(void);
void testPress(void);
/*Defined towice*/
/*extern S32 SetTemp;*/
// 
// void Delay_2000ms(void);void sendDataToModeManager(void);
extern unsigned char array[2];
extern unsigned char F1_100ms;
extern unsigned char F2_100ms;


#endif


