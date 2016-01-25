#ifndef KNX_SDK_MEM
#define KNX_SDK_MEM

#include "Data.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef KNX_API_RETURN (*exLibPtr)(KNX_API_PARAM);

typedef struct
{
tCode type;
long long unsigned hash;
}object;

typedef struct
{
  object obj;
  int value;
}_integer_;

typedef struct
{
  object obj;
  char*value;
}_string_;

typedef struct
{
  object obj;
  object**members;
  unsigned numMembers;
}_struct_;

object*genObject(tCode, char*name);
bool freeObject(object*);

//DLL/so function library handle
typedef struct
{
char*moduleName;
exLibPtr * function;
unsigned long long * fHash;
unsigned numFunction;
void*handle;//close on exit or unloading all references, NOT at end of loading
}module;

//store modules
typedef struct
{
module*modList;
unsigned numModules;
}exModule;

typedef struct database
{
exModule mLib;
object**memory;
unsigned numObjects;
}database;

database*genDatabase();
void freeDatabase(database*);
object*_getObject(database*, unsigned long long);
object*getObject(database*, char*);
bool addObject(database*, object*);
bool delObject(database*, object*);
int loadLibrary(char*, database*, settings);
void freeLibrary(exModule*);
void freeModule(module*);
char**getSymTable(char*, unsigned*);

KNX_API_RETURN invokeEx(KNX_API_PARAM, long long unsigned, database*);

#endif
