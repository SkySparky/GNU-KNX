#ifndef KNX_SDK_DATA
#define KNX_SDK_DATA

#include "Defs.h"

/*
Defines bytecode format and protocol
for DLL linkage

These are the structures used in importable
modules
*/

//tokenized data
typedef struct
{
//TODO
}token;

token*genToken();
bool freeToken(token*);

//tokenized line
typedef struct
{
token*sequence;
}byteSequence;

byteSequence*genByteSequence();
bool freeByteSequence(byteSequence*);


#endif