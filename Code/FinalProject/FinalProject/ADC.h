
#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include "Basic_Types.h"

#ifndef F_CPU
#define F_CPU 16000000ul			/* Define CPU Frequency e.g. here 16MHz */
#endif
#include <stdlib.h>
#include <util/delay.h>
S32 adc_value;


void adc_init(void);            /*Function to initialize/configure the ADC*/
S32 read_adc(U8 channel);    /*Function to read an arbitrary analog channel/pin*/
#endif