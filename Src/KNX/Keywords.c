#include "Keywords.h"
#include "../KNX_SDK/Error.h"

//convert symbol to token code
tCode keycode(long long unsigned hash)
{
  for (unsigned x=0; x<DEF_KEYWORDS; ++x)
  {
    //printf("%llu >> %llu : %llu\n",hash, keyList[x], hash-keyList[x]);
    if (keyList[x]==hash)
      switch(x)
      {
        case KW_SHORT: return _kShort;
        case KW_INT: return _kInt;
        case KW_LONG: return _kLong;
        case KW_FLOAT: return _kDouble;
        case KW_BOOL: return _kBool;
        case KW_CHAR: return _kChar;
        case KW_STRING: return _kString;
        case KW_METHOD: return _kFunction;

        case KW_XNODE: return _kXNode;
        case KW_IMPORT: return _kImport;

        case KW_EXIT: return _kExit;
        default:
        return _dNa;
      }
    }
  return _dNa;
}

//Built in functions
//replace with safe-shutdown method
void _int_exit(token*retCode)
{
  if (retCode==NULL)
  {
    printf("Exiting with return code 0\n");
    exit(0);
  }

  if (_isNumeric(retCode->type))
  {
    if (_isIntegral(retCode->type))
    {
      printf("Exiting with return code %d\n", *(int*)retCode->data);
      exit(*(int*)retCode->data);
    }
  }
}

void _int_import(token*libs, interpreter*intr)
{
  token * curr = libs;
  while (curr!=NULL)
  {
    //../_bin/std/IO.ark
    char*path=malloc(strlen(intr->st->dirPath)+strlen((char*)libs->data)+1);
    strncpy(path,intr->st->dirPath,strlen(intr->st->dirPath));
    strncpy(path+strlen(intr->st->dirPath), (char*)curr->data, strlen(curr->data)+1);

    printf("Searching %s\n", path);
    if (libs->type==_mStr)
      loadLibrary(path,intr->global,intr->st->options);
    else
      prntError((char*)curr->data,ERR_ILL_ARG,intr->st->options);
    free(path);
    curr=curr->next;
  }
printf("***");
}

token * invokeKeyword(token*args, interpreter*intr)
{
  if (args==NULL)
    return NULL;
  //printf("Keyword detected\n");
  if (args==NULL)
    return NULL;

  switch(args->type)
  {
    case _kExit: _int_exit(args->next); break;
    case _kImport: _int_import(args->next, intr); break;
    default:
    return NULL;
  }

  return NULL;
}
