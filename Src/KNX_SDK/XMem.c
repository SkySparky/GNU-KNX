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
      return ret;
    break;
    }
    case _mStr:
    {
      _string_ * ret = malloc(sizeof(_string_));
      ret->obj.type=type;
      ret->obj.hash=FNV_1a(name);
      ret->value=malloc(1);
      ret->value[0]='\0';
      return ret;
    }
    case _mStruct:
    {
      _string_ * ret = malloc(sizeof(_string_));
      ret->obj.type=type;
      ret->obj.hash=FNV_1a(name);
      ret->members=malloc(0);
      ret->numMembers=0;
      return ret;
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
