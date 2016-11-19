#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

#include "KDK.h"

#include "Core.h"
#include "CMD.h"

//initializes data tables and loads standard libraries
//return false on fatal error
bool systemInit(){
  bool responseCode = true;

  //from Core.h
  initializeCore();
  initializeNodeRegistry();

  return responseCode;
}

int main(int argc, char **argv)
{

  parseCMD(argc, argv);

  if (!systemInit()){
    printf("Failed to start\r\n");
    return -1;
  }

  return 0;
}
