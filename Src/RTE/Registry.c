#include "Registry.h"
#include "Util.h"
#include "Interfaces.h"
#include "Structures.h"
#include "BasicTypeImp.h"
#include "Type.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>


int _registerObject(char*name, void*value, castable castMethod){

  Object * obj = malloc(sizeof(Object));
  obj->hash = _FNV_1A(name);
  obj->value = value;
  obj->cast = castMethod;

  for(int i = 0; i < Config->maxObjCount; ++i){
    if (!TypeReg->objectMap[i]){
      obj->typeId = i;
      TypeReg->objectMap[i] = obj;

      printf("%s registered with id: %d :: %llx\r\n", name, i, obj->hash);

      return i;
    }
  }

  return -1;
}

void registerBasicTypes(){

  int failCheck = 0;

  failCheck |= registerObject("void", malloc(sizeof(void)), NULL);
  failCheck |= registerObject("int", malloc(sizeof(int)), _int2cast);
  failCheck |= registerObject("uint", malloc(sizeof(unsigned)), NULL);
  failCheck |= registerObject("long", malloc(sizeof(long)), NULL);
  failCheck |= registerObject("ulong", malloc(sizeof(unsigned long)), NULL);
  failCheck |= registerObject("real", malloc(sizeof(double)), NULL);
  failCheck |= registerObject("char", malloc(sizeof(char)), NULL);
  failCheck |= registerObject("uchar", malloc(sizeof(unsigned char)), NULL);
  failCheck |= registerObject("wchar", malloc(sizeof(short)), NULL);
  failCheck |= registerObject("string", malloc(sizeof(char *)), NULL);
  failCheck |= registerObject("wstring", malloc(sizeof(short *)), NULL);
  failCheck |= registerObject("bit", malloc(sizeof(char *)), NULL);
  failCheck |= registerObject("class", malloc(sizeof(Object)), NULL);
  failCheck |= registerObject("dynamic", malloc(sizeof(Object)), NULL);
  failCheck |= registerObject("function", malloc(sizeof(void *)), NULL);
  failCheck |= registerObject("array", malloc(sizeof(void *)), NULL);
  failCheck |= registerObject("col", malloc(sizeof(void *)), NULL);
  failCheck |= registerObject("keypair", malloc(sizeof(KeyPair)), NULL);
  failCheck |= registerObject("file", malloc(sizeof(void)), NULL);
  failCheck |= registerObject("stream", malloc(sizeof(FILE)), NULL);
  failCheck |= registerObject("node", malloc(sizeof(NodeHandle)), NULL);

}
