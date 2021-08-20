#include "states_Cfg.h"

const Status_Operation_ModeType Status_Operation_Mode[States_Operations_Num] =
{
	{"StandBY" ,(U8) 0 ,(U8)0},
	{"Operation",(U8)1,(U8)1},
	{"Normal",(U8)1,(U8)0},
	{"Error",(U8)0,(U8)0}
};

U32 FlagForDashButton = (U32) 0;