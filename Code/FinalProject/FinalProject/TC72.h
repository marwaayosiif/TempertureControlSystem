/*
 * TC72.h
 *
 * Created: 6/2/2021 11:06:51 AM
 *  Author: Marwa Adel
 */ 


#ifndef TC72_H
#define TC72_H


#include "Basic_Types.h"
#include "SPI.h"
#include "DIO.h"


#define HIGH ((U8)0xff)
#define LOW ((U8)0X00)
#define TC72_CONTROL_WRITE ((S32)0x80)
#define CONTINOUS_TEMP ((S32)0x04)
#define MSB ((S32)0x02)
#define TC72_CONTROL_READ ((S32)0x00)


/* Functions prototype*/
void TC72_Intit(void);
S32 Read_Temperature(void);

#endif /* TC72_H */

