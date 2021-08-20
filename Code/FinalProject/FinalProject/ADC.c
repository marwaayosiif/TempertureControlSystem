#include "ADC.h"
#include "avr/io.h"
#include "DIO.h"

void adc_init(void)
{
	
	DIO_ChannelDirection((unsigned char)0, (unsigned char) 0x00);
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));   /* 16Mhz/128 = 125Khz the ADC reference clock*/
	ADMUX |= (1<<REFS0);                            /* Voltage reference from Avcc (5v)*/
	ADCSRA |= (1<<ADEN);                            /* Turn on ADC*/
	ADCSRA |= (1<<ADSC);                            /* Do an initial conversion because this one is the slowest and to ensure that everything is up and running*/
}

S32 read_adc(U8 channel)
{
	S32 Ain,AinLow;
	ADMUX &= 0xF0;										/* Clear the older channel that was read*/
	ADMUX |= channel;									/* Defines the new ADC channel to be read*/
	ADCSRA |= (1<<ADSC);
	while((ADCSRA&(1<<ADIF))==0);                       /* Starts a new conversion*/
	AinLow = (S32)ADCL;									/* Read lower byte*/
	Ain = (S32)ADCH*256;								/* Read higher 2 bits and Multiply with weight */
	Ain = Ain + AinLow;
	return Ain;											/* Returns the ADC value of the chosen channel*/
}