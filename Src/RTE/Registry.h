#ifndef KNX_REG
#define KNX_REG

#include "Interfaces.h"
#include "Core.h"
#include "Var.h"
#include "Structures.h"

/*
Defines common registration methods stored in Core.h
*/

//register new object
int _registerObject(char*, void*, castable);

//core object types
void registerBasicTypes();

#endif
