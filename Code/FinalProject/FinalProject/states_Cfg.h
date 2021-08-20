#ifndef STATES_CFG_H_INCLUDED
#define STATES_CFG_H_INCLUDED
#include "Basic_Types.h"
#include "TC72.h"
#define States_Operations_Num 4
typedef struct
{
	U8 stateName[50];
	U8 TempFlag;
	U8 VoltageFlag;
}Status_Operation_ModeType;

#endif
