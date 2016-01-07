#ifndef KNX_SDK_KEYWORD
#define KNX_SDK_KEYWORD

#include "Data.h"
#include "Defs.h"

/*
int
char
string
struct

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
0xe79e4d608e807965//exit

};
#else
static unsigned long long keyList[5] = {
0xcded1a85//exit
};
#endif
//Index locations
#define KW_NA     -1
#define KW_EXIT   0

#endif
