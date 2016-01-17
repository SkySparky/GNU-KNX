#include <stdio.h>

#include "Node.h"
#include "State.h"

#include "KNX.h"

#define TEST false

#ifdef _WIN32
	#include <windows.h>
#endif

void printHelp()
{
printf("-w : Suppress warnings\n");
printf("-e : Suppress errors\n");
printf("-s : Suppress system printouts\n");
printf("-r : Suppress echo\n");
printf("-d : Enable debug printouts\n");
printf("-t : Disable tab assist\n");
printf("-v : Display Engine and SDK version\n");
printf("-l : Record debug log\n");
printf("-x : Prevent interpreter from executing\n");
printf("--maxnodes=[num] : Set maximum allowed nodes\n");
printf("--tabsize=[num] : Set spacing size of tab for tab assist\n");
printf("\n");
}

//determine initial/default settings
//return command to node if found
//exits with code -1 if multiple -c options specified
char*parseCMD(int argc, char**argv,state*sts)
{
char*ret=NULL;
bool cnt=true;

for (unsigned x=1; x<argc; ++x)
	if (argv[x][0]=='-')
	{
		toLower(argv[x]);
		if (argv[x][1]==0)
			prntError(argv[x], WRN_BLNK_OPT, sts->options);
		else if (argv[x][1]=='-')//multi character
			{
				 char lP[40];
				 char rP[40];
				 char op=0;//0=no op, 1 = SET
				 unsigned len=strlen(argv[x]);

				 for (unsigned y=0; y<len && op==0; ++y)
				 {
					 switch (argv[x][y])
					 {
						 case '=': op='='; break;
						 default:
						 break;
					 }
					 if (op!=0)
					 {
						 strncpy(lP,argv[x],y);
						 strncpy(rP,argv[x]+y+1, (y-x)-1);
						 lP[y]='\0';
						 rP[y-x]='\0';

						 if (strncmp(lP, "--maxnodes", len)==0)
						 	{
								int num = atoi(rP);
								if (num<1 || num>SYSTEM_MAX_NODES)
									prntError(argv[x], WRN_INV_OPT, sts->options);
								else
									sts->maxNodes=num;
								//printf("Maxnodes %u\n", sts->maxNodes);
							}
							else if (strncmp(lP, "--tabsize", len)==0)
 						 {
 							 int num = atoi(rP);
 							 if (num<0)
 								 prntError(argv[x], WRN_INV_OPT, sts->options);
 							 else
 								 sts->tabSize=num;

							 //printf("Mod tab %u\n", sts->tabSize);
 						 }
					 }
				 }

			}
		else//next character
			{
				switch (argv[x][1])
				{
					case 'w': sts->options.prntWrn=0;break;
					case 'e': sts->options.prntErr=0;break;
					case 's': sts->options.prntSys=0;break;
					case 'r': sts->options.prntEcho=0;break;
					case 'd': sts->options.prntDbg=1;break;
					case 't': sts->options.tabAssist=0;break;
					case 'v': printf("%s : %s \n", INTERPRETER_VERSON, SDK_VERSION);break;
					case 'l': sts->options.dbgLog=0;break;
					case 'x': cnt=false; break;
					case 'h': printHelp(); break;
					default:
					prntError(argv[x], WRN_UNDEF_OPT, sts->options);
					break;
				}
			}
	}
else
{
	if (ret!=NULL)
		{
			prntError(ret, ERR_REDEF_CMD, sts->options);
		}
	else
		{
			unsigned len = strlen(argv[x]);
			ret=malloc(len+1);
			strncpy(ret,argv[x], len);
			ret[len]='\0';
		}
}
if (!cnt)
	exit(0);
return ret;
}

int main(int argc, char**argv)
{
if (TEST)
{
printf("%u\n",setFlag(0,"aABC\0"));
return 0;
}

state*sys=genState();

if (sys->options.prntDbg)
{
	if (PLATFORM==PLATFORM_WINDOWS)
		printf("%d bit windows\n", BITMODE);
	if (PLATFORM==PLATFORM_LINUX)
		printf("%d bit linux\n", BITMODE);
	printf("%d\n",sys->registered);
}

//jump into node0 without creating new thread
nodeProc(sys,NULL, parseCMD(argc,argv, sys));

freeState(sys);

return 0;
}

#ifdef _WIN32
int CALLBACK WinMain(
  _In_ HINSTANCE hInstance,
  _In_ HINSTANCE hPrevInstance,
  _In_ LPSTR     lpCmdLine,
  _In_ int       nCmdShow
)
{
	
	return 0;
}
#endif