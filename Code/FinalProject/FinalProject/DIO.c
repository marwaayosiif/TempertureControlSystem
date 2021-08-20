#include "DIO.h"
#include "DIO_Cfg.h"
/*start address of each port*/
#define PORTA_BASE_ADDRESS ((unsigned char)0x3B)
#define PORTB_BASE_ADDRESS ((unsigned char)0x38)
#define PORTC_BASE_ADDRESS ((unsigned char)0x35)
#define PORTD_BASE_ADDRESS ((unsigned char)0x32)

/*Port subsystem registers offset*/
#define PORT_REG_OFFSET ((unsigned char)0)
#define DDR_REG_OFFSET ((unsigned char)1)
#define PIN_REG_OFFSET ((unsigned char)2)

#define NUM_OF_PORTS ((unsigned char)4)

/*Registers definitions*/

/* JUSTIFICATION: Misra Rule 19.7 => memory consumption and it is a simple function do not need this memory for the three lines */

#define PORT_REG(PORT_ID) (*((volatile  unsigned char*)((PortBaseAddresses[(PORT_ID)]) - (PORT_REG_OFFSET))))
#define DDR_REG(PORT_ID) (*((volatile  unsigned char*)(PortBaseAddresses[(PORT_ID)] - DDR_REG_OFFSET)))
#define PIN_REG(PORT_ID) (*((volatile  unsigned char*)(PortBaseAddresses[(PORT_ID)] - PIN_REG_OFFSET)))

/*base address lookup table*/
const unsigned char PortBaseAddresses[NUM_OF_PORTS] =
{PORTA_BASE_ADDRESS,
	PORTB_BASE_ADDRESS,
	PORTC_BASE_ADDRESS,
PORTD_BASE_ADDRESS};



DIO_CheckType DIO_ChannelDirection(unsigned char ChannelId, unsigned char Direction)
{
	unsigned char portId ;
	DIO_CheckType Result;
	portId = DIO_ConfigParam[ChannelId].PortId;
	if((ChannelId <= DIO_NUM_OF_CHANNELS) && (portId <= NUM_OF_PORTS))
	{

	    /* JUSTIFICATION: Mirsa Rule 11.3 => SPCR is And Addres so to access it
	             * we should use pointers and on the other side there is data  2 Lines*/
		
		/* JUSTIFICATION: Mirsa Rule 10.3 => we tried casting to the same signedness but it doesn't go away.*/
		DDR_REG(portId) &= ((unsigned char)(~(DIO_ConfigParam[ChannelId].PortMask)));
		DDR_REG(portId) |=  (DIO_ConfigParam[ChannelId].PortMask & Direction);
		Result = DIO_OK;

	}

	else
	{
		/*invalid port*/
		Result = DIO_NOK;

	}
	return Result;
}

DIO_CheckType DIO_ChannelWrite(unsigned char ChannelId, unsigned char Data)
{
	unsigned char portNum ;
	DIO_CheckType result;
	portNum = DIO_ConfigParam[ChannelId].PortId;
	if((ChannelId <= DIO_NUM_OF_CHANNELS) && (portNum <= NUM_OF_PORTS))
	{
	    /* JUSTIFICATION: Mirsa Rule 11.3 => SPCR is And Addres so to access it
	             * we should use pointers and on the other side there is data 2 Lines */
		/* JUSTIFICATION: Mirsa Rule 10.3 => we tried casting to the same signedness but it doesn't go away.*/
		PORT_REG(portNum) &= ((unsigned char)(~(DIO_ConfigParam[ChannelId].PortMask)));
		PORT_REG(portNum) |=  (DIO_ConfigParam[ChannelId].PortMask & Data);
		result = DIO_OK;

	}

	else
	{
		/*invalid port*/
		result = DIO_NOK;

	}
	return result;
}

DIO_CheckType DIO_ChannelRead( unsigned char ChannelId, unsigned char *DataPtr)
{
	unsigned char port ;
	DIO_CheckType RESULT ;
	port = DIO_ConfigParam[ChannelId].PortId;

	if((ChannelId <= DIO_NUM_OF_CHANNELS )&& (port <= NUM_OF_PORTS)){

	    /* JUSTIFICATION: Mirsa Rule 11.3 => SPCR is And Addres so to access it
	             * we should use pointers and on the other side there is data  */
		
		/* JUSTIFICATION: Mirsa Rule 10.3 => we tried casting to the same signedness but it doesn't go away.*/
		*DataPtr = PIN_REG(port);
		RESULT = DIO_OK;
	}
	else
	{
		RESULT = DIO_NOK;

	}
	return RESULT;

}



