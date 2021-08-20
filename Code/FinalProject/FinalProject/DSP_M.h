#ifndef DSP_M_H
#define DSP_M_H

#include "Basic_Types.h"

#include "states_control.h"
#include "LCD.h"

void Idle_Screen(void);

void DSP_state_Temp(void);

void Keypad_Temp(S8 Set_Temp , S8 index);

U8 *  itoa ( S32 value, U8 * str, S32 base );

void LCD_String_xy (S8 row,S8 column,U8 *str);

S32 concat(unsigned char x, unsigned char y);

void SendData(void);

extern S32 SetTemp;

void Welcome_Screen(void);void shift_lcd_right(void);void shift_lcd_left(void);

#endif

