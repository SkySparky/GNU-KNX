#include <stdio.h>
#include <dlfcn.h>

#include <stdlib.h>

#include "../KDK/KDK.h"

int main(int argc, char **argv)
{
  /* on Linux, use "./myclass.so" */
  void* handle = dlopen("./_bin_/myclass.so", RTLD_LAZY);

  void* (*DoSomething)();

  DoSomething = (void* (*)())dlsym(handle, "DoSomething");

  DoSomething();

  return 0;
}
