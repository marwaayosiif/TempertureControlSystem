/*
 * Pwm.c
 *
 * Created: 6/2/2021 11:58:42 PM
 *  Author: Lenovo
 */ 
#include "Pwm.h"
#include "avr/io.h"
#include "DIO.h"

void Pwm_Init(void){	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01)  | (1<<CS00)| (1<<CS01) | (1<<CS02);
	DIO_ChannelDirection((unsigned char)11, (unsigned char) 0xff);  /*set OC0 pin as output*/}void Pwm_SetDutyCycle(U32 DutyCycle){	OCR0 = DutyCycle;}