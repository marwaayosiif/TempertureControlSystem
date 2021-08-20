#ifndef STATES_CONTROL_H
#define STATES_CONTROL_H

#include "states_Cfg.h"
#include "Basic_Types.h"

#include <string.h>
#include <stdlib.h>

#define RepetationCounterMAX ((U32)370)

#define Max_Difference_To_Enter_NormalState ((S32)(5))

#define Min_Difference_To_Enter_ErrorState ((S32)(10))

void States_Control_Init(void);

void HashButtonClick(void);

const U8 * get_states_name(void);

void Operation_Control(void);


void Switch_State(S32 Current_Temp ,S32 Set_Temp,lF64 VPMW, U8 stateIndex);

S32 Temp_LCD(void);

lF64 Voltage_PWM(void);

void options(void);

/* S32 abs(S32 x); */

extern const Status_Operation_ModeType Status_Operation_Mode[States_Operations_Num];

extern U32 FlagForDashButton ;


#endif
