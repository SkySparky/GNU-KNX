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
_mInt=1, _mShort, _mLong,//int, short, long long
_mBool,//unsigned char
_mDbl,//double
_mChar, _mStr,//char, char*
_mFile, _mScript, _mFunction,//...managed
_mStruct,//...managed
_mVoid,//void
//Lexile
_sOpParanth=20, _sClParanth,//( )
_sOpBrack, _sClBrack,//[ ]
_sOpBrace, _sClBrace,//{ }
_sList, _sMember,//, .
//Logic
_lAnd=40, _lOr, _lNot,//& | !
_lNand, _lNor, _Xnor, _lXor,//!& !| |! ||
//Comparison
_cEqu=50, _cNequ, _cQst,//== != ?
//Assignment
_aSet=60, _aAdd, _aSub, _aMult, _aDiv, _aPow, _aRoot, _aMod,//= _aOp=general mathematics operator
//Math
_eAdd=70, _eSub, _eMult, _eDiv, _eMod//+= -= *= /= %=
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

token*getHead(token*);
token*getTail(token*);
token*genToken(token*);

void freeToken(token*);//add specific memory deletions for raw values


//tokenized line
typedef struct
{
token*sequence;
}byteSequence;

byteSequence*genByteSequence();
bool freeByteSequence(byteSequence*);

typedef struct
{
  //defaults
  bool prntWrn : 1;
  bool prntErr : 1;
  bool prntSys : 1;
  bool prntEcho: 1;
  bool prntDbg : 1;
}settings;

#endif
