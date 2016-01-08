#include "BuiltIn.h"

bool isFunction(char*input,unsigned length)
{
char*buffer = malloc(length+1);
strncpy(buffer,input,length);
buffer[length]='\0';
long long unsigned hash = FNV_1a(buffer);
free(buffer);

for (unsigned x=0; x<FNC_LENGTH; ++x)
  if (fncList[x]==hash)
    return true;

};

token * _fnc_exit(token*root, unsigned terms, __state*st)
{
if (terms!=0)
  prntError("exit() takes no arguments\n",FNC_MSG,st->options);
exit();
}
