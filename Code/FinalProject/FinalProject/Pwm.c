/*
 * Pwm.c
 *
 * Created: 6/2/2021 11:58:42 PM
 *  Author: Lenovo
 */ 
#include "Pwm.h"
#include "avr/io.h"
#include "DIO.h"

void Pwm_Init(void)
	DIO_ChannelDirection((unsigned char)11, (unsigned char) 0xff);  /*set OC0 pin as output*/