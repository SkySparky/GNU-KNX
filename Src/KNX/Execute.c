#include "Interpreter.h"

typedef struct
{
  token**data;
  unsigned cnt;
}list;

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

list**recExecute(interpreter*intr, token**stream, unsigned offset)
{
  unsigned currLevel=stream[offset]->order;
  token**retStreak=malloc(0);
  for (unsigned x=offset; x<intr->streamLength; ++x)
  {
    switch (stream[x]->type)
    {
      case _kExit:
      if (x+1<intr->streamLength){
        if (_isData(stream[x+1]->type))
          _int_exit(stream[x+1]);
        }
        else
          _int_exit(NULL);
        break;

      case _sOpBrace://{

        break;
      case _sClBrace://}

        break;
      case _sOpBrack://[

        break;
      case _sClBrack://]

        break;
      case _sOpParanth://(

        break;
      case _sClParanth://)

        break;
      default:

      break;
    }
  }

  return NULL;
}

void execute(interpreter* intr)
{
if (intr->st->options.prntDbg)
	prntTokens(intr->stream, intr->streamLength);
//free tokens

recExecute(intr,intr->stream, 0);

}
