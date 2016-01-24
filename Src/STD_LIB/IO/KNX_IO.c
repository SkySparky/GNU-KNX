#include "KNX_IO.h"

#include <stdio.h>

void (*callback)()=NULL;

void register_function(void(*fnc)())
{
  callback=fnc;
}

extern void _test_(token*param, baseNode*bn,settings opts)
{
  printf("SUCCESS ()\n");
}

KNX_API_RETURN _display(token*data, baseNode*intr, settings opts)
{
  //callback();
  //data->flg=20;
  //printf("Shared Library Test : %d : %s \n", data->flg,data->data);
  printf("XXXXX\n");
  return NULL;
}
