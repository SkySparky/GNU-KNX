#ifndef KNX_SDK_MEM
#define KNX_SDK_MEM

#include "wchar.h"

typedef long long unsigned HASH;

//Defines memory structures

typedef enum {mNA,
  mtInt, mtUInt, mtLint, mtULint, mtFloat, mtDouble, mtBool,
  mtChar, mtUChar, mtWChar, mtString,
  mtArray, mtStruct, mtVoid, mMethod,
  mFile, mScript,
  mModular=100//used as loadtime starting reference
} mType;



//tag declarations
struct tBase;//inherited base structure

struct tInt;
struct tUInt;
struct tLInt;
struct tULInt;
struct tFloat;
struct tDouble;
struct tBool;
struct tChar;
struct tUChar;
struct tWChar;
struct tString;
struct tArray;
struct tStruct;
struct tVoid;
//TODO Consider runtime loaded modular memory

struct mBranch;
struct tMemory;

typedef struct tBase
{
  HASH hash;
  unsigned char type;
  char lock:1;//one bit switch
}mBase;

//for storing data structures within a tree
typedef struct mBranch
{
  mBase*target;
  struct mBranch * left;
  struct mBranch * right;
  struct mBranch * parent;
}mBranch;

typedef struct tInt
{
  mBase*base;
  int value;
}mInt;

typedef struct tUInt
{
  mBase*base;
  unsigned value;
}mUInt;

typedef struct tLInt
{
  mBase*base;
  long long int value;
} mLInt;

typedef struct tULInt
{
  mBase*base;
  unsigned long long int value;
}mULInt;

typedef struct tFloat
{
  mBase*base;
  unsigned long long int value;
}mFloat;

typedef struct tDouble
{
  mBase*base;
  unsigned long long int value;
}mDouble;

typedef struct tBool
{
  mBase*base;
  char value;
}mBool;

typedef struct tChar
{
  mBase*base;
  char value;
}mChar;

typedef struct tUChar
{
  mBase*base;
  unsigned char value;
}mUChar;

typedef struct tWChar
{
  mBase*base;
  wchar_t value;
} mWChar;

typedef struct tString
{
  mBase*base;
  char*string;
  unsigned length;
}mString;

typedef struct tArray
{
  mBase*base;
  mBase*items;
  unsigned length;
  unsigned char type;//item type
} mArray;

typedef struct tStruct
{
  mBase*base;
  void * data;
}mStruct;

typedef struct tVoid
{
  mBase*base;
}mVoid;

typedef struct tMemory
{
  mBranch * root;
}mMemory;

//factories
mBase * makeBase();
mBranch * makeBranch();

mInt * makeInt();
mUInt * makeUInt();
mLInt * makeLInt();
mULInt * makeULInt();
mFloat * makeFloat();
mDouble * makeDouble();
mBool * makeBool();
mChar * makeChar();
mUChar * makeUChar();
mWChar * makeWChar();
mString * makeString();
mArray * makeArray();
mStruct * makeStruct();
mVoid * makeVoid();

mMemory * makeMemory();


//Utility functions
//search BST by hash
mBase*memSearch(mBranch*, HASH);
//determine type, and free memory accordingly
int memDelete(mBase*);

//locate correct factory
//name, type, initial value (ignored if inapplicable, assumed to be literal of selected type)
mBase*makeVar(char*, mType, void*);

#endif
