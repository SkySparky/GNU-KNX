#include "Error.h"

#define RED     0
#define GREEN   1
#define YELLOW  2
#define CYAN    3

#define PRNT_NORM 0
#define PRNT_ERR  1
#define PRNT_WRN  2
#define PRNT_MISC 3

//Define color change functions
#ifdef PLATFORM_LINUX
#define ANSI_RED      "\x1b[31m"
#define ANSI_GREEN    "\x1b[32m"
#define ANSI_YELLOW   "\x1b[33m"
#define ANSI_CYAN     "\x1b[36m"
#define ANSI_WHITE    "\x1b[37m"
void printc(char*err, char*line, short mode, int code)
{
char*clr=NULL;
switch(mode)
{
case PRNT_NORM: clr=ANSI_WHITE; printf("%sMessage: \n\t>> %s\n", clr, line); break;
case PRNT_ERR: clr=ANSI_RED; printf("%sError (%d): %s\n\t>> %s\n", clr, code, err, line); break;
//case GREEN: clr=ANSI_GREEN; break;
case PRNT_WRN: clr=ANSI_YELLOW; printf("%sWarning (%#08x): %s\n\t>>%s\n", clr, code, err, line); break;
case PRNT_MISC: clr=ANSI_CYAN; printf("%s (%#08x): %s \n", clr, code, line); break;
}
printf("\x1b[37m");
}
#else//WINDOWS
#include <windows.h>
HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO cinfo;
WORD svAttr;
GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
svAttr=consoleInfo.wAttributes;
void printc()
{

}
#endif

void prntError(char*line, int code, settings opts)
{
if (code<=0)
  return;

switch (code)
{
//Errors
case ERR_NODE_XSPAWN: printc("Node failed to spawn\n",line,PRNT_ERR, code); break;
case ERR_NODE_XDESTROY: printc("Node failed to deregister\n",line,PRNT_ERR, code); break;
case ERR_NODE_EXIST: printc("Node does not exist\n",line,PRNT_ERR, code); break;

case ERR_REALLOC: printc("Memory failed to reallocate\n",line,PRNT_ERR, code); break;
case ERR_MALLOC: printc("Memory failed to allocate\n",line,PRNT_ERR, code); break;
case ERR_STDIO_REALLOC: printc("Std IO buffer failed to reallocate\n",line,PRNT_ERR, code); break;

case ERR_FILE_404: printc("File not found\n",line,PRNT_ERR, code); break;
case ERR_FILE_DEL: printc("Could not delete file\n",line,PRNT_ERR, code); break;
case ERR_FILE_CREATE: printc("Could not create file\n",line,PRNT_ERR, code); break;
case ERR_FILE_WRITE: printc("Could not write to file\n",line,PRNT_ERR, code); break;
case ERR_FILE_OPEN: printc("Could not open file\n",line,PRNT_ERR, code); break;

case ERR_BLNK_CHR: printc("Cannot declare blank character\n",line,PRNT_ERR, code); break;
case ERR_EXS_CHR: printc("Cannot use multiple characters in string\n",line,PRNT_ERR, code); break;
case ERR_ILL_SYN: printc("Illegal syntax\n",line,PRNT_ERR, code); break;
case ERR_ILL_ARG: printc("Illegal argument\n",line,PRNT_ERR, code); break;
case ERR_SHRT_ARG: printc("Too few arguments\n",line,PRNT_ERR, code); break;
case ERR_LNG_ARG: printc("Too many arguments\n",line,PRNT_ERR, code); break;

case ERR_XMEMBER: printc("Member object does not exist\n",line,PRNT_ERR, code); break;
case ERR_XOBJ: printc("Object does not exist\n",line,PRNT_ERR, code); break;
case ERR_REDEF: printc("Object redefinition\n",line,PRNT_ERR, code); break;
case ERR_ACC_DENIED: printc("Memory access denied\n",line,PRNT_ERR, code); break;

case ERR_LIB_404: printc("Library not found\n",line,PRNT_ERR, code); break;
case ERR_LIB_OPEN: printc("Could not open library\n",line,PRNT_ERR, code); break;

//Warnings
case WRN_UNBOUND_STR: printc("Unbound string",line,PRNT_WRN, code); break;
case WRN_IMPLICIT_CAST: printc("Implicit cast",line,PRNT_WRN, code); break;

default:
printc("",line,PRNT_MISC, code); break;
}
}
