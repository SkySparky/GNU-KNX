#include "Contract.h"

char * getKDKVersion(){
  return KDKVersion;
}

//return a comma delimited string of function names in this library
char * RegisterModule(){
  printf("Called from shared library\r\n");
  return NULL;
}
