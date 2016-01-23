#include "KNX_IO.h"

#include <stdio.h>

void (*callback)()=NULL;

void register_function(void(*fnc)())
{
  callback=fnc;
}

void _display(void)
{
  //callback();
  printf("Shared Library Test\n");
}
