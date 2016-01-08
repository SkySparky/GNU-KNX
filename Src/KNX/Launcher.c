#include <stdio.h>

#include "Node.h"
#include "State.h"

#include "KNX.h"

#define TEST false

//determine initial/default settings
//return command to node if found
//exits with code -1 if multiple -c options specified
char*parseCMD(int argc, char**argv,state*sts)
{

return NULL;
}

int main(int argc, char**argv)
{
if (TEST)
{
char * buff;
buff=malloc(10);
strncpy(buff,"123456789",10);
buff[9]='\0';
printf("%s\n", buff);
printf("%d\n",buff[10]);
return 0;
}

if (PLATFORM==PLATFORM_WINDOWS)
	printf("%d bit windows\n", BITMODE);
if (PLATFORM==PLATFORM_LINUX)
	printf("%d bit linux\n", BITMODE);

state*sys=genState();
printf("%d\n",sys->registered);
//jump into node0 without creating new thread
nodeProc(sys,NULL, parseCMD(argc,argv, sys));

freeState(sys);

return 0;
}
