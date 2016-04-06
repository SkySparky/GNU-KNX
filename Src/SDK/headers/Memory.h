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

#define isNumeric(x) (x>=mtInt && x<=mtDouble)//is integral/floating point
#define isTextual(x) (x>=mtChar && x<=mtString)//characters, strings
#define isNumComp(x) (x>=mtmtInt && x<=mtWChar)//numeric, or castable to numeric

//tag declarations
struct mBase;//inherited base structure

struct mInt;
struct mUInt;
struct mLInt;
struct mULInt;
struct mFloat;
struct mDouble;
struct mBool;
struct mChar;
struct mUChar;
struct mWChar;
struct mString;
struct mArray;
struct mStruct;
struct mVoid;
//TODO Consider runtime loaded modular memory

struct mBranch;
struct tMemory;

typedef struct mBase
{
  HASH hash;
  mType type;
  //settings
  unsigned char lock:1;//one bit switch
  unsigned char raw:1;//is literal (1) or managed (0)
}mBase;

typedef struct mInt
{
  mBase base;
  int value;
} mInt;

typedef struct mUInt
{
  mBase base;
  unsigned value;
} mUInt;

typedef struct mLInt
{
  mBase base;
  long value;
} mLInt;

typedef struct mULInt
{
  mBase base;
  unsigned long value;
} mULInt;

typedef struct mFloat
{
  mBase base;
  float value;
}mFloat;

typedef struct mDouble
{
  mBase base;
  double value;
}mDouble;

typedef struct mBool
{
  mBase base;
  unsigned char value;
}mBool;

typedef struct mChar
{
  mBase base;
  char value;
}mChar;

typedef struct mUChar
{
  mBase base;
  unsigned char value;
}mUChar;

typedef struct mWChar
{
  mBase base;
  short value;
}mWChar;

typedef struct mString
{
  mBase base;
  char*value;
}mString;

typedef struct mArray
{
  mBase base;
  void * value;
  unsigned length;
}mArray;

//TODO consider using splay tree after benchmark tests
typedef struct mStruct
{
  mBase base;

  mBase * value;
  unsigned length;
}mStruct;

typedef struct mVoid
{
  mBase base;
  void * value;
  mType type;
}mVoid;

//for storing data structures within a tree
typedef struct mBranch
{
  mBase * target;
  struct mBranch * left;
  struct mBranch * right;
  struct mBranch * parent;
}mBranch;

//splay tree memory container
typedef struct tMemory
{
  mBranch * root;
}mMemory;

//factories
mBranch * makeBranch();

mBase makeBase(char*, mType, unsigned char, unsigned char);

mMemory * makeMemory();
int freeMemory(mMemory*);//permenantly clear full memory structure


//Utility functions
//search BST by hash
mBase*memSearch(mMemory*, mBranch*, HASH);

mBase * getMember(mMemory*,HASH);

//0=invalid input -1=input already exists 1=success
//adds new branch to binary tree
int addBranch(mMemory*,mBase*);
//determine type, and free memory accordingly
int memDelete(mBase*);
//TODO implement splay method
int memSplay(mMemory*, mBranch*);

//locate correct factory
//name, type, initial value (ignored if inapplicable)
mBase*makeVar(char*, mType, void*, unsigned char);

//returns member, removes from input
char * getMemberString(char*, unsigned);

#endif
