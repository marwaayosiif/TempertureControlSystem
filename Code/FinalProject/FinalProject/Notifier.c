/*
 * Notifier.c
 */ 

/*For getting notified Add your function here*/

#include "Notifier.h"
#include "potentiometer.h"
#include "states_control.h"

void notify_50ms(){
	
}

void notify_100ms(){
	//PORTD ^= (1<<PD7);
	
	
}

void notify_200ms(){
	options();
	
	
}

void notify_500ms(){
	pwm_to_voltage();
}
