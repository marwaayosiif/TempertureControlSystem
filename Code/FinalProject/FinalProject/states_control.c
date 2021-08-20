#include "states_control.h"

U8 Current_States_Name [50] ={0};

lF64 Voltage_To_PWM = 0;

S32 Temp_To_LCD = 0;

S32 SetTemp = (S32) 25;

U32 count_Error_State_Rep = 0;

void States_Control_Init(void)
{
	/* JUSTIFICATION: we used built in libraries for int to string conversion and for other string manipulations*/
    strcpy(Current_States_Name, Status_Operation_Mode[0].stateName);
}

void HashButtonClick(void)
{
    FlagForDashButton = FlagForDashButton + (U32)1;

    /* Clicked for the First Time -> GO TO Operational */

    if (FlagForDashButton == (U32)1)
    {
        strcpy(Current_States_Name,Status_Operation_Mode[1].stateName);

    }
    /* Clicked for the Second Time  -> GO TO STANDBY */
    else if (FlagForDashButton == (U32)2)
    {
		/* JUSTIFICATION: we used built in libraries for int to string conversion and for other string manipulations*/
        strcpy(Current_States_Name,Status_Operation_Mode[0].stateName);

        FlagForDashButton = (U32)0;
    }
    else
    {
		FlagForDashButton = (U32)0; 
	}
}

const U8* get_states_name(void)
{
    return(Current_States_Name);
}

void Operation_Control(void)
{
    S32 CurrentTemp = Read_Temperature();
   
    S32 Difference_Temp = (S32) 0;

    /* Calculate Difference and Voltage To PMW */
    
    lF64 Vt = (lF64)0;           /*((Set Temp / Current Temp ) * 10) / 100) */

    lF64 Num = SetTemp - CurrentTemp ;

    Vt = (Num) / (lF64)10 ;

    Difference_Temp = abs(CurrentTemp - SetTemp);


    /*  Current State Operational State */
	/* JUSTIFICATION: we used built in libraries for int to string conversion and for other string manipulations*/
    if (strcmp(Current_States_Name, Status_Operation_Mode[1].stateName) == (S32) 0)
    {
       
            /* Trigger Current State to Normal State */

        if(Difference_Temp <= Max_Difference_To_Enter_NormalState)
            {
               

                Switch_State(CurrentTemp,SetTemp,Vt,(U8)2);

            }
       
            /* Trigger Current State to Error State */
        else if ((CurrentTemp > SetTemp) && (Difference_Temp > Min_Difference_To_Enter_ErrorState))

            {

                   Switch_State(CurrentTemp,SetTemp,Vt,(U8)3);

            }

        
        /* Trigger Current State to Operational State */
        else
            { 
                /* Check If This Condition Repeated  */

                if ((Difference_Temp > Min_Difference_To_Enter_ErrorState) && (SetTemp > CurrentTemp))

                {
                    count_Error_State_Rep =  count_Error_State_Rep + (U32)1 ;
                }   
                else /* If the System Interrupts the Repetition Of the last Condition */
                {
                    count_Error_State_Rep = (U32)0 ;
                }
                
                /* Still In Operational State if it counts less than [((3(Min)*60)(sec)*1000)]msec/[200]msec " Timer between calls " = 900 in ideal case ,but because of proteus delay
				the counter that achieve 3 Min is 370 "Justification".
				 */
				
                if (count_Error_State_Rep < RepetationCounterMAX)
                {
                
                    Switch_State(CurrentTemp,SetTemp,Vt,(U8)1);

                }
                /* If Not */
                else 
                {
                    Switch_State(CurrentTemp,SetTemp,Vt,(U8)3);

                }
            }

    }
    
    /* Normal State */
	/* JUSTIFICATION: we used built in libraries for int to string conversion and for other string manipulations*/
    else if (strcmp(Current_States_Name,Status_Operation_Mode[2].stateName) == (S32) 0)
    {
        if (Difference_Temp <= Max_Difference_To_Enter_NormalState)
        {
            Switch_State(CurrentTemp,SetTemp,Vt, (U8)2);  /* Still In Normal State */
        }
        else if ((Difference_Temp > Min_Difference_To_Enter_ErrorState) && (CurrentTemp > SetTemp))
        {
            Switch_State(CurrentTemp,SetTemp,Vt, (U8)3);  /* Go TO Error State */
        }
        else if ((Difference_Temp > Max_Difference_To_Enter_NormalState) && (CurrentTemp < SetTemp))

        {
             Switch_State(CurrentTemp,SetTemp,Vt, (U8)1);  /* Go TO Operational State */
        }
        else
        {
        }

    }
    
    /* Error State */
	/* JUSTIFICATION: we used built in libraries for int to string conversion and for other string manipulations*/
    else if (strcmp(Current_States_Name,Status_Operation_Mode[3].stateName) == (S32) 0)
    {

        Switch_State(CurrentTemp,SetTemp,Vt,(U8)3);
    }
    else
    {

    }
}

void Switch_State(S32 Current_Temp ,S32 Set_Temp,lF64 VPMW, U8 stateIndex)
{

    switch (stateIndex)
    {

    case (U8)1: /*OPERATIONAL STATE */
    {
		/* JUSTIFICATION: we used built in libraries for int to string conversion and for other string manipulations*/
        strcpy(Current_States_Name,Status_Operation_Mode[1].stateName);
        Temp_To_LCD = Current_Temp ;

        if (Set_Temp > Current_Temp)
        {
            Voltage_To_PWM = VPMW ;
        }

        else 
        {
            Voltage_To_PWM = (lF64) 0;
        }

    }break;
   case (U8)2: /* NOMRAL STATE */
    {
		/* JUSTIFICATION: we used built in libraries for int to string conversion and for other string manipulations*/
        strcpy(Current_States_Name,Status_Operation_Mode[2].stateName);
        Temp_To_LCD = Current_Temp ;
        Voltage_To_PWM = (lF64) 0;
        count_Error_State_Rep =(U32) 0;

    }break;
    
    case (U8)3: /* ERROR STATE */
    {
		/* JUSTIFICATION: we used built in libraries for int to string conversion and for other string manipulations*/
        strcpy(Current_States_Name,Status_Operation_Mode[3].stateName);
        Temp_To_LCD = (S32)0 ;
        Voltage_To_PWM = (lF64)0;
        count_Error_State_Rep = (U32) 0 ;
    }break;
    default:
        break;
    }
}

S32 Temp_LCD(void)
{
    return Temp_To_LCD;
}

lF64 Voltage_PWM(void)
{
    return Voltage_To_PWM;
}

void options(void){
	/* JUSTIFICATION: we used built in libraries for int to string conversion and for other string manipulations*/
	
    if (strcmp(Current_States_Name,Status_Operation_Mode[0].stateName) == (S8)0)
    {
        Temp_To_LCD = (S32) 0;
        Voltage_To_PWM =  (lF64) 0;
    }
    else
    {

        Operation_Control();
    }
}



