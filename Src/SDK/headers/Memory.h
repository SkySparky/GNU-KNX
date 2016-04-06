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

//for storing data structures within a tree
typedef struct mBranch
{
  mBase target;
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
mBase*memSearch(mBranch*, HASH);

mBase * getMember(mMemory*,HASH);

int addBranch(mMemory*,mBase*);
//determine type, and free memory accordingly
int memDelete(mBase*);

//locate correct factory
//name, type, initial value (ignored if inapplicable)
mBase*makeVar(char*, mType, void*, unsigned char);

//returns member, removes from input
char * getMemberString(char*, unsigned);

#endif
