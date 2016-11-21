#ifndef KNX_BASIC_IMP
#define KNX_BASIC_IMP

#include "Interfaces.h"

/*
Provides basic type procedures
*/

typedef enum{
  eVoid,
  eInt,
  eUInt
}BasicTypeId;

castable * getIntCastMethods();


#endif
