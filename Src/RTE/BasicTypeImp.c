#include "BasicTypeImp.h"
#include "Structures.h"

#include <stdlib.h>

Object * copyTransferable(Object * obj){
  Object * ret = malloc(sizeof(obj));

  ret->typeId = obj->typeId;
  ret->hash = 0;
  ret->value = malloc(sizeof(*obj->value));
  ret->cast = obj->cast;

  return ret;
}


//integer conversion methods
Object * _int2uint(Object* left, Object* right){
  Object * ret = copyTransferable(right);

  *((unsigned *)ret->value) = *(int *)right->value;

  return ret;
}

Object * _int2long(Object * left, Object * right){
  Object * ret = copyTransferable(right);

  *((long *)ret->value) = *(int *)right->value;

  return ret;
}

Object * _int2cast(Object * left, Object * right){

  switch (right->typeId){
    case _eUInt: return _int2uint(left, right);

    default: return NULL;
  }

  return NULL;
}
