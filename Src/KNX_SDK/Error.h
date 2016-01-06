#ifndef KNX_SDK_ERROR
#define KNX_SDK_ERROR

#include "Defs.h"
#include "Data.h"

/*
Defines error codes and implements the error printout function
*/

#define OK		    0
#define MAX_ERR   999
#define MAX_WRN   1999

//Errors
//General
  //Node  1-15
#define ERR_NODE_XSPAWN   1//fail to create node
#define ERR_NODE_XDESTROY 2//fail to destroy node
#define ERR_NODE_EXIST    3//node doesnt exist
  //Memory 16-25
#define ERR_REALLOC       16//realloc fail
#define ERR_MALLOC        17//malloc fail
#define ERR_STDIO_REALLOC 18//terminal input failure
//File 26-35
#define ERR_FILE_404      26//file not found
#define ERR_FILE_DEL      27//failed to delete file
#define ERR_FILE_CREATE   28//failed to create file
#define ERR_FILE_WRITE    29//failed to write to file
#define ERR_FILE_OPEN     30//failed to open file
//Parser 36-100
#define ERR_BLNK_CHR      36//no input to char
#define ERR_EXS_CHR       37//excessive input to char
#define ERR_ILL_SYN       38//illegal syntax
#define ERR_ILL_ARG       39//illegal argument
#define ERR_SHRT_ARG      40//too few arguments
#define ERR_LNG_ARG       41//too many arguments

//Data  101-120
#define ERR_XMEMBER       101//has no member
#define ERR_XOBJ          102//no such object
#define ERR_REDEF         103//object already exists
#define ERR_ACC_DENIED    104//invalid permission

//Library 121-140
#define ERR_LIB_404       121//library not found
#define ERR_LIB_OPEN      122//failed to open library

//Warnings 1000-1999
//General 1001-1099

//File 1100-1199

//Parser 1200-1299
#define WRN_UNBOUND_STR   1200//string not closed by end of line
//Data 1300-1399
#define WRN_IMPLICIT_CAST 1300//implicitly casted types

#endif

//Error printout

//line, error code
void prntError(char*, int, settings);
