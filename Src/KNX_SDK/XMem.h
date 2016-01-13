#ifndef KNX_SDK_MEM
#define KNX_SDK_MEM

#include "Data.h"

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

typedef struct
{
object**memory;
unsigned numObjects;
}database;


//System Data
typedef struct
{

}module;

database*genDatabase();
void freeDatabase(database*);
object*_getObject(database*, unsigned long long);
object*getObject(database*, char*);
bool addObject(database*, object*);
bool delObject(database*, object*);

#endif
