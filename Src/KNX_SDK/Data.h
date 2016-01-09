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
_lNand, _lNor, _lXnor, _lXor,//!& !| |! ||
//Comparison
_cEqu=50, _cNequ, _cQst, _cLss, _cGtr, _cLssEqu, _cGtrEqu,//== != ?
//Math
_aAdd=60, _aSub, _aMult, _aDiv, _aPow, _aRoot, _aMod,//= _aOp=general mathematics operator
//Assignment
_eSet=70, _eAdd, _eSub, _eMult, _eDiv, _eMod,//+= -= *= /= %=
//Keywords
_kExit=80, _kXNode, _kTerm, _kDel, _kSwtch, _kBreak,
_kImport, _kReturn, _kMsg, _kIf, _kElse, _kWhile, _kFrEach,
_kTry, _kCatch, _kCast,
//Other
_oFlag=100

}tCode;

//Flag definitions
typedef unsigned int flag;//26 bits used for a-z

flag setFlag(flag, char*);
//tokenized data
typedef struct token
{
//TODO
tCode type;
void*data;
bool raw;
flag flg;
}token;

token*genToken(token*);

void freeToken(token*);//add specific memory deletions for raw values

typedef struct
{
  //defaults
  bool prntWrn : 1;
  bool prntErr : 1;
  bool prntSys : 1;
  bool prntEcho: 1;
  bool prntDbg : 1;

  bool tabAssist:1;
}settings;

#endif
