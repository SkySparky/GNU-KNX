#include "BasicTypeImp.h"
#include "Structures.h"

#include <stdlib.h>

Object * copyTransferable(Object * obj){
  Object * ret = malloc(sizeof(obj));

  ret->typeId = obj->typeId;
  ret->hash = 0;
  ret->value = malloc(sizeof(*obj->value));

  return ret;
}


//integer
Object * _int2uint(Object* left, Object* right){
  Object * ret = copyTransferable(right);

  *((unsigned *)ret->value) = *(int *)right->value;
  ret->castMethods = right->castMethods;

  return ret;
}

Object * _int2long(Object * left, Object * right){
  Object * ret = copyTransferable(right);

  *((long *)ret->value) = *(int *)right->value;
  ret->castMethods = right->castMethods;

  return ret;
}

castable * getIntCastMethods(){
  castable * castMethods = malloc((sizeof(castable *) * 2) + sizeof(castable *));

  castMethods[0] = &_int2uint;
  castMethods[1] = &_int2long;
  castMethods[2] = NULL;

  return castMethods;
}
