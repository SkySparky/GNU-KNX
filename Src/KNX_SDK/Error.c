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
case PRNT_ERR: clr=ANSI_RED; printf("%sError (%#08x): %s\n\t>> %s\n", clr, code, err, line); break;
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

if ((code<1000 && !opts.prntErr) || ((code>=1000 && code<2000) && !opts.prntWrn))
  return;

switch (code)
{
//Errors
case ERR_NODE_XSPAWN: printc("Node failed to spawn",line,PRNT_ERR, code); break;
case ERR_NODE_XDESTROY: printc("Node failed to deregister",line,PRNT_ERR, code); break;
case ERR_NODE_EXIST: printc("Node does not exist",line,PRNT_ERR, code); break;
case ERR_REDEF_CMD: printc("Command line argument already defined",line,PRNT_ERR, code); break;
case ERR_EXT_IMP_FAIL: printc("External function failed to import ",line,PRNT_ERR, code); break;
case ERR_EXT_LIB_FAIL: printc("External library failed to import ",line,PRNT_ERR, code); break;

case ERR_REALLOC: printc("Memory failed to reallocate",line,PRNT_ERR, code); break;
case ERR_MALLOC: printc("Memory failed to allocate",line,PRNT_ERR, code); break;
case ERR_STDIO_REALLOC: printc("Std IO buffer failed to reallocate",line,PRNT_ERR, code); break;

case ERR_FILE_404: printc("File not found",line,PRNT_ERR, code); break;
case ERR_FILE_DEL: printc("Could not delete file",line,PRNT_ERR, code); break;
case ERR_FILE_CREATE: printc("Could not create file",line,PRNT_ERR, code); break;
case ERR_FILE_WRITE: printc("Could not write to file",line,PRNT_ERR, code); break;
case ERR_FILE_OPEN: printc("Could not open file",line,PRNT_ERR, code); break;

case ERR_BLNK_CHR: printc("Cannot declare blank character",line,PRNT_ERR, code); break;
case ERR_EXS_CHR: printc("Cannot use multiple characters in string",line,PRNT_ERR, code); break;
case ERR_ILL_SYN: printc("Illegal syntax",line,PRNT_ERR, code); break;
case ERR_ILL_ARG: printc("Illegal argument",line,PRNT_ERR, code); break;
case ERR_SHRT_ARG: printc("Too few arguments",line,PRNT_ERR, code); break;
case ERR_LNG_ARG: printc("Too many arguments",line,PRNT_ERR, code); break;
case ERR_NEG_BRACK: printc("Unexpected bracket",line,PRNT_ERR, code); break;
case ERR_NEG_BRACE: printc("Unexpected brace",line,PRNT_ERR, code); break;
case ERR_NEG_PARANTH: printc("Unexpected paranthesis",line,PRNT_ERR, code); break;
case ERR_MSMTCH_PAR: printc("Mismatch encapsulation with Paranthesis",line,PRNT_ERR, code); break;
case ERR_MSMTCH_BRK: printc("Mismatch encapsulation with Bracket",line,PRNT_ERR, code); break;
case ERR_MSMTCH_BRC: printc("Mismatch encapsulation with Brace",line,PRNT_ERR, code); break;
case ERR_MSS_FLG_TARG: printc("Missing flag target",line,PRNT_ERR, code); break;
case ERR_INV_FLG_TARG: printc("Invalid flag target",line,PRNT_ERR, code); break;

case ERR_XMEMBER: printc("Member object does not exist",line,PRNT_ERR, code); break;
case ERR_XOBJ: printc("Object does not exist",line,PRNT_ERR, code); break;
case ERR_REDEF: printc("Object redefinition",line,PRNT_ERR, code); break;
case ERR_ACC_DENIED: printc("Memory access denied",line,PRNT_ERR, code); break;

case ERR_LIB_404: printc("Library not found",line,PRNT_ERR, code); break;
case ERR_LIB_OPEN: printc("Could not open library",line,PRNT_ERR, code); break;

//Warnings
case WRN_BLNK_OPT:printc("No option value following identifier",line,PRNT_WRN, code); break;
case WRN_UNDEF_OPT:printc("Unrecognized option value following identifier",line,PRNT_WRN, code); break;
case WRN_INV_OPT:printc("Invalid option value following identifier",line,PRNT_WRN, code); break;

case WRN_UNBOUND_STR: printc("Unbound string",line,PRNT_WRN, code); break;
case WRN_UNBOUND_CHR: printc("Unbound character",line,PRNT_WRN, code); break;
case WRN_NO_EFFECT: printc("Character has no effect",line,PRNT_WRN, code); break;

case WRN_IMPLICIT_CAST: printc("Implicit cast",line,PRNT_WRN, code); break;
case WRN_INV_FLAG: printc("Invlalid flag format",line,PRNT_WRN, code); break;

//Other
case FNC_MSG: printc("",line,PRNT_MISC, code); break;

default:
printc("",line,PRNT_MISC, code); break;
}
}
