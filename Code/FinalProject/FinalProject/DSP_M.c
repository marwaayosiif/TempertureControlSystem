#include "DSP_M.h"


S8 array[2] = {2,5};

U8 states[15];

extern volatile unsigned char lcd_100ms;

int leftStepper = 0;

int rightStepper = 8;

unsigned char goingleft = 1;

unsigned char repeat = 0;

extern unsigned char flagForSendData;
void Idle_Screen(void)
{
	LCD_String_xy ((S8)0, (S8) 0, "SET:25");
	LCD_String_xy((S8)0,(S8)10,"CRT:");
	LCD_String_xy((S8)1,(S8)0, "STATE:");

}

void Keypad_Temp(S8 Set_Temp , S8 index)
{
	U8 Temp [5] = {0};
	
	if ((Set_Temp != (S8) 0XFF) && (Set_Temp != (S8)35))
	{
		
		itoa((S32)Set_Temp, Temp, (S8)10);
		
		LCD_String_xy((S8)0, index, Temp);
		
		array[index - 4] = Set_Temp;
		
	}
	else{}
	return;
}

void DSP_state_Temp(void)
{
	S32 CurrentTemp = (S32) Temp_LCD();

	U8 CopyTemp [5] = {0};

	if (strcmp(states,get_states_name()) != 0)
	{
		strcpy(states,get_states_name());
		LCD_String_xy((S8)1,(S8)7, "         ");
	}

	if (CurrentTemp != (S32) 0XFF)
	{

		if (CurrentTemp <= 9)
		{
			itoa(CurrentTemp, CopyTemp, 10);
			LCD_String_xy ((S8)0,(S8) 14, "0");
			LCD_String_xy ((S8)0,(S8)15, CopyTemp);
		}
		else
		{
			itoa(CurrentTemp, CopyTemp, 10);
			LCD_String_xy ((S8)0,(S8)14, CopyTemp);

		}

		LCD_String_xy ((S8)1,(S8)7, states);

	}
	else
	{

	}
	return;
}

void Welcome_Screen(void){
	char text[] = {"WELCOME"};

	while (repeat < 3)
	{
		if (leftStepper == 9)
		{
			goingleft = 0;
		}
		if(leftStepper <= 9 && goingleft){

			LCD_String_xy (0, leftStepper, text);

			if (lcd_100ms == 1)
			{
				
				shift_lcd_right();
				_delay_us(100);
				LCD_Clear();

				leftStepper++;
				
			}
		}
		else if (rightStepper > 1 && !goingleft)
		{
			LCD_String_xy (0, rightStepper, text);
			//100msflag from timer
			if (lcd_100ms == 1)
			{
				shift_lcd_left();
				_delay_us(100);
				LCD_Clear();
				rightStepper--;
			}
		}
		else
		{
			leftStepper = 0;
			rightStepper = 9;
			goingleft = 1;
			repeat = repeat +1;
		}
	}
	
}

void shift_lcd_right(void)
{
	
	LCD_Command(0x1c);          /*shift display to right*/

}

void shift_lcd_left(void)
{
	LCD_Command(0x18);         /*shift display to left*/
	
}

