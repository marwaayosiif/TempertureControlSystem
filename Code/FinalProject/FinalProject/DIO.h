#ifndef DIO_H_INCLUDED
#define DIO_H_INCLUDED



#define DIO_OK  ((unsigned char)0)
#define DIO_NOK ((unsigned char)1)
#include "Basic_Types.h"
typedef unsigned char DIO_CheckType;

DIO_CheckType DIO_Init(void);
DIO_CheckType DIO_ChannelDirection(unsigned char ChannelId, unsigned char Direction);
DIO_CheckType DIO_ChannelWrite(unsigned char ChannelId, unsigned char Data);
DIO_CheckType DIO_ChannelRead(unsigned char ChannelId, unsigned char *DataPtr);



#endif  /*DIO_H_INCLUDED*/
