#ifndef KNX_SDK_KEYWORD
#define KNX_SDK_KEYWORD

/*
Keywords are related to functions in that they
carry out a particular task.
However, these functions do not require argument lists
and will only accept a single right-hand input.
Not all keywords will require an input.

For instance, "int i" accepts 'i' to be the title of the
declared object
exit can be written as "exit" or "exit 0" to exit the
program with a return code of 0

*/

#include "KNX.h"

/*
short
int
long
double
bool
char
string
struct
method

exit
xnode
terminate
delete
switch
break
import
return
message
if
else
while
foreach
try
catch
cast

19*/

#define DEF_KEYWORDS      4

#if BITMODE==64
static unsigned long long keyList[DEF_KEYWORDS] = {
0x3593de2f826fd4cd,//short
0x2b9fff192bd4c83e,//int
0xcde8c9ad70d16733,//long

0xe79e4d608e807965//exit

};
#else
static unsigned long long keyList[DEF_KEYWORDS] = {
0xba226bd5,//short
0x95e97e5e,//int
0xc2ecdf53,//long

0xcded1a85//exit
};
#endif
//Index locations
#define KW_NA     -1
#define KW_SHORT   0
#define KW_INT     1
#define KW_LONG    2
#define KW_EXIT    3

tCode keycode(long long unsigned hash);

void _int_exit(token*retCode);

#endif
