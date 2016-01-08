#ifndef KNX_SDK_KEYWORD
#define KNX_SDK_KEYWORD

#include "Data.h"
#include "Defs.h"

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

#define DEF_KEYWORDS      1

#if BITMODE==64
static unsigned long long keyList[5] = {
0x3593de2f826fd4cd,//short
0x2b9fff192bd4c83e,//int
0xcde8c9ad70d16733,//long

0xe79e4d608e807965//exit

};
#else
static unsigned long long keyList[5] = {
0xba226bd5,//short
0x95e97e5e,//int
0xc2ecdf53,//long

0xcded1a85//exit
};
#endif
//Index locations
#define KW_NA     -1
#define KW_EXIT   0

tCode keycode(long long unsigned hash);

#endif
