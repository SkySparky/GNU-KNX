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

REFACTOR THE SHNOZZ OUT OF THIS!!!!!!!!!!!!!
*/

#include "KNX.h"
#include "Interpreter.h"

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
#include "Interpreter.h"
struct _interpreter;
typedef struct _interpreter interpreter;

#define DEF_KEYWORDS      12

#if BITMODE==64
static unsigned long long keyList[DEF_KEYWORDS] = {
18094488662358668885ULL,//short
12898489496898901054ULL,//int
2986610728418162995ULL,//long
18094485093136321893ULL,//float
2986610726070705085ULL,//bool
2986610724327605949ULL,//char
10733259895173323864ULL,//string
10733259895058722336ULL,//struct
10732784859024281776ULL,//method

18094490007562572359ULL,//xnode
10732928266430976756ULL,//import

2986610718626400101ULL//exit

};
#elif BITEMODE == 32
static unsigned long long keyList[DEF_KEYWORDS] = {
1112857194740724949,//short
6880781574236766,//int
1011474890373329235,//long
1112855885144361349,//float
1011474888870370365,//bool
1011474888615136029,//char
16016055873698317624,//string
16016055873634850080,//struct
16015900429428855856,//method

1112857672448079367,//xnode
16015945215496767700,//import

1011474885660797061//exit
};
#endif
//Index locations
#define KW_NA     -1
#define KW_SHORT   0
#define KW_INT     1
#define KW_LONG    2
#define KW_FLOAT   3
#define KW_BOOL    4
#define KW_CHAR    5
#define KW_STRING  6
#define KW_STRUCT  7
#define KW_METHOD  8

#define KW_XNODE   9
#define KW_IMPORT  10

#define KW_EXIT    11

tCode keycode(long long unsigned hash);

token * invokeKeyword(token*, interpreter*);

#endif
