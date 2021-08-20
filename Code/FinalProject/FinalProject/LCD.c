/*
 * testLcd.c
 *
 * Created: 6/1/2021 8:48:09 PM
 * Author : FADY
 */ 


#include <avr/io.h>
#include "LCD.h"
#include "DIO.h"
#include "scheduler.h"

void LCD_Init (void)			         /* LCD Initialize function */
{	
	DIO_ChannelDirection(10,0xFF);      /* Make port B pin 2 direction as o/p */
	
	DIO_ChannelDirection(12,0xFF);      /* Make port B pin 4 direction as o/p */
	
	DIO_ChannelDirection(20,0xFF);      /* Make C port pin 4 direction as o/p */
	
	DIO_ChannelDirection(21,0xFF);      /* Make C port pin 5 direction as o/p */
	
	DIO_ChannelDirection(22,0xFF);      /* Make C port pin 6 direction as o/p */
	
	DIO_ChannelDirection(23,0xFF);      /* Make C port pin 7 direction as o/p */
	
	DIO_ChannelWrite(12,0x00);          /* clear EN pin */
				
	LCD_Command(0x02);		           /* Initializes LCD in 4-bit mode  */
	
	LCD_Command(0x28);                 /* Configures LCD in 2-line 4-bit mode and 5x7 matrix */
	
	LCD_Command(0x0c);                 /* Display on cursor OFF*/
	
	LCD_Command(0x06);                 /* Increment cursor (shift cursor to right)*/
	
	LCD_Command(0x01);                /* Clear display screen*/
	
	LCD_Command (0x80);               /* force cursor to begin with first line*/
}

void LCD_Command( unsigned char cmnd )
{   
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0);     /* sending upper nibble */

	DIO_ChannelWrite(10,0x00);                       /* RS=0 , cmnd reg. */

	DIO_ChannelWrite(12,0xff);                       /*  set EN bit */
	
	_delay_us(2);
	

	DIO_ChannelWrite(12,0x00);                       /*  clear EN bit */
	
	_delay_us(100);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);     /* sending lower nibble */
	
	DIO_ChannelWrite(12,0xff);
	
	_delay_us(1);
	
	DIO_ChannelWrite(12,0x00);
	
	_delay_ms(2);             /* delay da lma bshelo bt5raf  ??? */
	
}

void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0);          /* sending upper nibble */
	
	DIO_ChannelWrite(10,0xff);                             /* RS=1, data reg. */

	DIO_ChannelWrite(12,0xff);
	
	_delay_us(1);

	DIO_ChannelWrite(12,0x00);

	_delay_us(200);                    /* delay da lma 5leto 100us bt5raf  ??? */

	LCD_Port = (LCD_Port & 0x0F) | (data << 4);          /* sending lower nibble */

	DIO_ChannelWrite(12,0xff);
	
	_delay_us(1);

	DIO_ChannelWrite(12,0x00);
	
	_delay_ms(2); /* delay da lma bshelo bt5raf  ??? */
}

void LCD_String (U8 *str)		/* Send string to LCD function */
{
	unsigned char i=0;
	
	while(str[i]!=0)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
		i++;
	}
}

void LCD_String_xy (S8 row,S8 column,U8 *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && column < 16)
	{
		
	LCD_Command((column & 0x0F)|0x80);	     /* Command of first row and required position<16 */	
	
	}
	
	else if (row == 1 && column<16)
	{
		
	LCD_Command((column & 0x0F)|0xC0);	    /* Command of first row and required position<16 */	
	
	}
	
	LCD_String(str);		
}

void LCD_Clear(void)
{
	LCD_Command (0x01);		        /* Clear display command */
	
	_delay_us(100);
	
}
