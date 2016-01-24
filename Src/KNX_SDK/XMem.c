#include "XMem.h"
#include "Util.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Error.h"

#define MAX_STREL_SIZE  50

object*genObject(tCode type, char*name)
{
  if (name==NULL)
    return NULL;

  switch (type)
  {
    case _mInt:
    {
      _integer_ * ret = malloc(sizeof(_integer_));
      ret->obj.type=type;
      ret->obj.hash=FNV_1a(name);
      ret->value=0;
      return (object*)ret;
    break;
    }
    case _mStr:
    {
      _string_ * ret = malloc(sizeof(_string_));
      ret->obj.type=type;
      ret->obj.hash=FNV_1a(name);
      ret->value=malloc(1);
      ret->value[0]='\0';
      return (object*)ret;
    }
    case _mStruct:
    {
      _struct_ * ret = malloc(sizeof(_struct_));
      ret->obj.type=type;
      ret->obj.hash=FNV_1a(name);
      ret->members=malloc(0);
      ret->numMembers=0;
      return (object*)ret;
    }
    default:
    return NULL;
  }

  return NULL;
}

bool freeObject(object*target)
{

  return true;
}

database*genDatabase()
{
  database*db=malloc(sizeof(database));
  db->memory=malloc(0);
  db->numObjects=0;
  db->mLib.numModules=0;
  db->mLib.modList=malloc(0);
  return db;
}

void freeLibrary(exModule*exMod)
{
  for (unsigned x=0; x<exMod->numModules; ++x)
    freeModule(&exMod->modList[x]);
  free (exMod);
}

void freeModule(module*mod)
{
free(mod->moduleName);
free(mod->fHash);
dlclose(mod->handle);
}

void freeDatabase(database*db)
{
//free native memory object
for (unsigned x=0; x<db->numObjects; ++x)
  freeObject(db->memory[x]);
//free library dependencies
for (unsigned x=0; x<db->mLib.numModules; ++x)
{
  for (unsigned y=0; y<db->mLib.modList[x].numFunction; ++y)
    free(db->mLib.modList[x].function[y]);
  free(db->mLib.modList[x].function);
  free(db->mLib.modList[x].moduleName);
}
free(db->mLib.modList);



free(db);

}

object*_getObject(database*db, unsigned long long hash)
{
for (unsigned x=0; x<db->numObjects; ++x)
  if (hash==db->memory[x]->hash)
    return db->memory[x];
return NULL;
}

object*getObject(database*db, char*string)
{
  return _getObject(db, FNV_1a(string));
}

bool addObject(database*db, object*obj)
{
  if (_getObject(db, obj->hash))
    return false;

  object**tmp = realloc( db->memory,sizeof(object)*db->numObjects+1);
  if (!tmp)
    return false;
  db->memory=tmp;
  db->memory[db->numObjects++]=obj;
  return true;
}

bool delObject(database*db, object*obj)
{
  object*target=_getObject(db, obj->hash);
  if (target==NULL)
    return false;

  for (unsigned x=0; x<db->numObjects; ++x)
    if (target==db->memory[x])
      {
        free(target);
        for (unsigned y=0; y<db->numObjects-1; ++y)
          db->memory[y]=db->memory[y+1];
      }

  object**tmp = realloc( db->memory,sizeof(object)*db->numObjects-1);
  if (!tmp)
    return false;
  db->memory=tmp;
  return true;
}

char**getSymTable(char*filename, unsigned*tblSize)
{
  *tblSize=0;
  FILE *fp = fopen(filename,"r");
  if (!fp)
  {
    printf("%s\n", filename);
    return NULL;
  }

  //TODO - Truncate path

  char**table=malloc(0);

  char buffer[128];
  char tBuf[128];

  while(fgets(buffer, sizeof(buffer), fp))
  {
    unsigned len = strlen(buffer);
    for (unsigned x=0; x<len; ++x)
      if ((int)buffer[x]<48 || x+1==len)
        {
          if (x==0)//empty line
            break;
          if (x+1==len)
            tBuf[x]=buffer[x];
          tBuf[x+(x+1==len?1:0)]='\0';
          table=realloc(table,(*tblSize+1)*sizeof(char*));
          table[*tblSize]=malloc(MAX_STREL_SIZE*sizeof(char));
          strncpy(table[*tblSize],tBuf, strlen(tBuf)+2);
          ++*tblSize;
          break;
        }else
          tBuf[x]=buffer[x];
  }

  fclose(fp);
  return table;
}

//0=success 1=not found 2=symbol definition not found
int loadLibrary(char* filename, database*db, settings opts)
{
  if (filename==NULL)
    return 1;
  char*fileSO=malloc(strlen(filename)+4);
  strncpy(fileSO,filename,strlen(filename));
  strncpy(fileSO+strlen(filename),".so\0",3);

  void *handle;
  char *error;

  handle = dlopen (fileSO, RTLD_LAZY);
  if (!handle) {
      fprintf (stderr, "%s\n", dlerror());
      return 1;
  }
  dlerror();    /* Clear any existing error */
  //fnc=dlsym(handle, "_display");

  //load symbol table
  char*fileSYM=malloc(strlen(filename)+5);
  strncpy(fileSYM,filename,strlen(filename));
  strncpy(fileSYM+strlen(filename),".sym\0",5);
  unsigned tblSize=0;
  char**table=getSymTable(fileSYM,&tblSize);

  if (table==NULL)
    return 2;

  if ((error = dlerror()) != NULL)  {
    if (opts.prntSys)
      prntError(filename,ERR_EXT_LIB_FAIL,opts);
      return 1;
  }

  //add library
  int libIndex=++db->mLib.numModules;
  db->mLib.modList=realloc(db->mLib.modList,sizeof(module)*libIndex);
  db->mLib.modList[libIndex-1].moduleName=malloc(strlen(filename)+1);
  strncpy(db->mLib.modList[libIndex-1].moduleName,filename,strlen(filename)+1);
  db->mLib.modList[libIndex-1].function=malloc(tblSize*sizeof(exLibPtr));
  db->mLib.modList[libIndex-1].fHash=malloc(sizeof(unsigned long long)*tblSize);
  db->mLib.modList[libIndex-1].numFunction=tblSize;
  db->mLib.modList[libIndex-1].handle=handle;
  //load table to memory
  int counter=0;
  while(table[counter]!=NULL && counter<tblSize)
  {
    KNX_API_RETURN (*fnc)(token*,baseNode*,settings)=NULL;
    if(opts.prntDbg)
      printf("%s : Loading %s:\t\t",db->mLib.modList[libIndex-1].moduleName,table[counter]);
    fnc=dlsym(handle, table[counter]);

    if (!fnc)
    {
      if (opts.prntSys)
        prntError(table[counter],ERR_EXT_IMP_FAIL,opts);

      db->mLib.modList[libIndex-1].function[counter]=NULL;
      db->mLib.modList[libIndex-1].fHash[counter]=0;
      ++counter;
      continue;
    }
    if (opts.prntDbg)
      printf("SUCCESS (%d)\n", counter);
    //fnc(NULL,NULL,opts);
    //printf("~~%p <~> %p\n", fnc, &fnc);
    //append to library
    db->mLib.modList[libIndex-1].function[counter]=fnc;
    db->mLib.modList[libIndex-1].fHash[counter]=FNV_1a(table[counter]);

    //printf("From table: >> ");
    //db->mLib.modList[libIndex-1].function[counter](NULL,NULL,opts);
    ++counter;
  }
  for (unsigned x=0; x<tblSize; ++x)
    free(table[x]);
  free(table);

  //dlclose(handle);
  return true;
}

KNX_API_RETURN invokeEx(token*input, baseNode*bn, settings opts, long long unsigned sHash, database*db)
{
  token*ret=NULL;
  //search for intended function
  //search libraries
  for (unsigned i_lib=0; i_lib<db->mLib.numModules; ++i_lib)
  {
    for (unsigned i_fnc=0; i_fnc<db->mLib.modList[i_lib].numFunction; ++i_fnc)
    {
      if (opts.prntDbg)
        printf("ExLib cmp chk : %llu >> %llu\n", sHash, db->mLib.modList[i_lib].fHash[i_fnc]);
      if (db->mLib.modList[i_lib].fHash[i_fnc]==sHash)
        {
          //######################################################
          dlerror();    /* Clear any existing error */
          ret = db->mLib.modList[i_lib].function[i_fnc](NULL,NULL,opts);
          goto brk;
        }
    }

  }
  brk:;
  return ret;
}
