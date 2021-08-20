
#include "Keypad.h"

DIO_CheckType (* FunArr[2]) (unsigned char channel,unsigned char data) = {&DIO_ChannelWrite,&DIO_ChannelDirection};

unsigned char key_pad = 0;

unsigned char start_Write_Flag = 0;
unsigned char under_score_Flag = 0;
unsigned char flagForSendData = 0;

void DIO_Keypad( unsigned char Value , unsigned char index)
{
	unsigned char j = 24;
	unsigned char i;
	for (i  = (unsigned char)0 ; i <= (unsigned char)7 ;i++)
	{
		FunArr[index](j,Value);
		j+= (unsigned char)1;
	}
	
}

unsigned char GetKeyPressed(void)
{
    unsigned char return_new = (unsigned char)0XFF ;
    unsigned char keypad[12]={1,2,3,
                            4,5,6,
                            7,8,9,
                        '*',0,'#'};
    unsigned char C;
    /*KEYPAD_PORT|= 0X0F*/
    DIO_Keypad( (unsigned char)0x0F, (unsigned char)0);

    for(C= (unsigned char)0; C< (unsigned char)3 ;C++)
    {


        DIO_Keypad((~( (unsigned char)(0X7F)) ), (unsigned char)1);

        DIO_Keypad(( (unsigned char)(0X40) >> C ), (unsigned char)1);
        unsigned char r;
        for(r= (unsigned char)0;r< (unsigned char) 4;r++)
        {
            /*unsigned char *Data;*/
            /*DIO_ChannelRead(24,&Data);*/
            if(!(KEYPAD_PIN & ( (unsigned char)(0X08)>>r)))
            {
                return_new = keypad[( ( r* (unsigned char)3 ) +C)];
                /*return keypad[(r* (unsigned char)3 +c)];*/
            }
            else
            {
                /*pass*/
            }
        }
    }


    return return_new;
}


void keypad_Interface(void)
{
	 
	key_pad = GetKeyPressed();
	
	
	if(key_pad == (unsigned char)35 )
	{
		HashButtonClick();
	}
	
else if (key_pad != 0xff) /*IF KeyPad is pressed*/
{
		if (F1_100ms && start_Write_Flag == 0)
		{
			
			Keypad_Temp(key_pad, (unsigned char)4);
			
			F1_100ms = 0;
			
			F2_100ms = 0;
			
			LCD_String_xy((S8)0, (unsigned char)5, "_");
			under_score_Flag = 1;
			
			
			start_Write_Flag = 1;
			
			Delay_100(testPress,(S32)6);
			
		}
		
		if (F2_100ms)
		{
			
			if (start_Write_Flag == 1)
			{
				Keypad_Temp(key_pad,(unsigned char)5);
				under_score_Flag = 2;
				start_Write_Flag = 0;
			}
			
			F2_100ms = 0;
			
			F1_100ms = 0;
			
			Delay_100(testPress,(S32)6);
		}else{}

}
	DSP_state_Temp();

	sendDataToModeManager();

	}
	
void sendDataToModeManager(void)
{
	unsigned char num_1 = (unsigned char)array[0];
	unsigned char num_2 = (unsigned char)array[1];
	if (under_score_Flag == 2)
	{
		SetTemp = concat( num_1 , num_2);
	}else
	{
		//do nothing
	}

}
/* JUSTIFICATION: we used built in libraries for int to string conversion and for other string manipulations*/
S32 concat(unsigned char x, unsigned char y){
	char str1[50] = "";
	char str2[50] = "";

	sprintf(str1,"%d",x);
	sprintf(str2,"%d",y);

	strcat(str1,str2);

	return atoi(str1);
}

void testPress(void)
{
	key_pad = GetKeyPressed();
}
