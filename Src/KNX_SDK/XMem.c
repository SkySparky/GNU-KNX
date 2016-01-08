#include "XMem.h"
#include "Util.h"

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
  return db;
}

void freeDatabase(database*db)
{
for (unsigned x=0; x<db->numObjects; ++x)
  freeObject(db->memory[x]);
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
