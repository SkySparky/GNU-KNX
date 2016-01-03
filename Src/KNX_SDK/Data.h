#ifndef KNX_SDK_DATA
#define KNX_SDK_DATA

#include "Defs.h"

/*
Defines bytecode format and protocol
for DLL linkage

These are the structures used in importable
modules
*/

typedef enum {
//Memory
_mInt=1, _mShort, _mLong,
_mBool,
_mDbl,
_mChar, _mStr,
_mFile, _mScript, _mFunction,
_mStruct,
//Lexile
_sOpParanth=20, _sClParanth,
_sOpBrack, _sClBrack,
_sOpBrace, _sClBrace,
_sList,
//Logic
_lAnd=40, _lOr, _lNot,
_lNand, _lNor, _Xnor, _lXor,
//Comparison
_cEqu=50, _cNequ,
//Assignment
_aSet=60, _aOp,//_aOp=general mathematics operator
//Math
_eAdd=70, _eSub, _eMult, _eDiv, _eMod, _ePow, _eRoot
}tCode;

//typedef struct token _token;

//tokenized data
typedef struct token
{
//TODO
tCode type;
void*data;
bool raw;
struct token*next;
struct token*previous;
}token;

token*getTail(token*);
token*genToken(token*);
void freeToken(token*);


//tokenized line
typedef struct
{
token*sequence;
}byteSequence;

byteSequence*genByteSequence();
bool freeByteSequence(byteSequence*);


#endif