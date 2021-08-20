#ifndef SPI_H
#define SPI_H
#include <avr/io.h>
#include "Basic_Types.h"

#define MOSI 15
#define SCK 13
#define SS 9
#define OUT 0xFF
#define IN 0X00
/*
#define SPCR (*((volatile unsigned char*)0x2D))
#define SPSR (*((volatile unsigned char*)0x2E))
#define SPDR (*((volatile unsigned char*)0x2F))
#define SPIE ((unsigned char)7)
#define SPE ((unsigned char)6)
#define DORD ((unsigned char)5)
#define MSTR ((unsigned char)4)
#define CPOL ((unsigned char)3)
#define CPHA ((unsigned char)2)
#define SPR1 ((unsigned char)1)
#define SPR0 ((unsigned char)0)
#define SPIF ((unsigned char)7)*/


void SPI_Init(void);
void SPI_Transmit(S32 TEMP);
S32 SPI_Receive(void);



#endif  /*SPI_H*/
