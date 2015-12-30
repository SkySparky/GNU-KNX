#include <stdio.h>

#include "Node.h"
#include "State.h"

#define TEST true

//determine initial/default settings
//return command to node if found
//exits with code -1 if multiple -c options specified
char*parseCMD(int argc, char**argv)
{

return NULL;
}

int main(int argc, char**argv)
{
if (TEST)
{
printf("hash >> %llu\n",FNV_1a("hello"));
return 0;
}

state*sys=genState();
printf("%d\n",sys->registered);
//jump into node0 without creating new thread
nodeProc(sys,NULL, parseCMD(argc,argv));

return 0;
}