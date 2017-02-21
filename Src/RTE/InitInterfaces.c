#include "Init.h"

#include <stdio.h>

int NodeProc(Node*parent){
  printf("test\r\n");
  return 0;
}

void InitInterfaces()
{
  _nodeProc = &NodeProc;
}
