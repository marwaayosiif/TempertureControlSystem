/*
 * potentiometer.c
 *
 * Created: 6/7/2021 4:00:49 PM
 *  Author: Lenovo
 */ 
#include "potentiometer.h" 
void pwm_to_voltage (void)
{
	S32 value;
	
	value=read_adc(0);
	lF64 vt;
	vt = Voltage_PWM();
	lF64 vr = (5 * value) / (lF64)1023;
	lF64 neumerator = (lF64)(vr*2 /10) * vt ;
	
	
	U32 duty  = (U32)( ( neumerator /10)  *  254  );
	Pwm_SetDutyCycle(duty);
}