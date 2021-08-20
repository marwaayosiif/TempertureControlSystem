/*
 * schedular.h
 *
 * Created: 6/3/2021 3:31:13 PM
 *  Author: FADY
 */ 


#ifndef SCHEDULAR_H_
#define SCHEDULAR_H_

#include<avr/interrupt.h>
#include "Notifier.h"
#include "LCD.h"
/* callbacks testing*/
typedef void (*Pftype)(void);

void enable_timer_interrupt();

void timer_init();


void Delay_100(Pftype nextFunction, S32 id);


#endif /* SCHEDULAR_H_ */