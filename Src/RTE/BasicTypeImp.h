#ifndef KNX_BASIC_IMP
#define KNX_BASIC_IMP

#include "Interfaces.h"

/*
Provides basic type procedures
*/

typedef enum{
  _eVoid,
  _eInt,
  _eUInt
}BasicTypeId;

Object * _int2cast(Object *, Object *);


#endif
