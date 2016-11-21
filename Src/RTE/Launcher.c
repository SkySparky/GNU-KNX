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
  initializeConfig();
  initializeInterfaces();
  initializeCore();
  initializeNodeRegistry();
  intitializeTypeRegistry();

  return responseCode;
}

int main(int argc, char **argv)
{
  if (!systemInit()){
    printf("Failed to start\r\n");
    return -1;
  }

  parseCMD(argc, argv);

  //initialize root node
  Node * root = buildNode("root", NULL);
  registerNode(root);

  return 0;
}
