#include "Interpreter.h"
#include "../KNX_SDK/Debug.h"
#include <string.h>
#include "Node.h"
#include "KNX.h"


#define isOp(c)(\
((c<'0' || c>'9') && (c<'a' || c>'z') && (c<'A' || c>'Z'))\
&& (c!='_' && c!='.'))

interpreter*genInterpreter(_state_ * st,_node_ * nd)
{
interpreter*ret = (interpreter*) malloc(sizeof(interpreter));
if (ret==NULL)
	return NULL;

ret->st=st;
ret->nd=nd;
ret->pending=false;
ret->litOp=0;
ret->listOp=0;
ret->blockOp=0;

ret->global=st->global;
ret->local=malloc(sizeof(database));
ret->local->memory=(object**)malloc(0);
ret->local->numObjects=0;

ret->buffSize=0;
ret->buffer=malloc(0);
ret->streamLength=0;
ret->stream=malloc(sizeof(token)*10);

return ret;
}

void reset(interpreter*intr)
{
intr->pending=false;
intr->waitExprss=false;
intr->waitLn=false;
intr->litOp=false;
intr->listOp=0;
intr->blockOp=0;

for (unsigned x=0; x<intr->streamLength; ++x)
	freeToken(intr->stream[x]);
if (intr->streamLength>10)
	intr->stream=realloc(intr->stream,10);
intr->streamLength=0;
}

char getEscape(char input)
{
switch (input)
{
case '0':
	return '\0';
case 'n':
	return '\n';
case 't':
	return '\t';
}

return input;
}

bool addToken(interpreter*intr, void*data, tCode type, bool raw)
{
//resize if necessary
if (intr->streamLength%10==0 && intr->streamLength>0)
	{
		token**tmpBuf=realloc(intr->stream, sizeof(token)*(intr->streamLength+10));
		if (tmpBuf==NULL)
			return false;
		intr->stream=tmpBuf;
		intr->streamLength+=10;
	}

token*tk=malloc(sizeof(token));
tk->data=data;
tk->type=type;
tk->raw=raw;
tk->order=intr->listOp+intr->blockOp+intr->brackOp;

if (tk==NULL)
	{
		if (intr->st->options.prntDbg)
			printf("Malloc fail\n");
		return false;
	}

intr->stream[intr->streamLength++]=tk;

return true;
}

//identify symbolic identifiers
void identify(char*input, unsigned length, interpreter*intr)
{
char*string=malloc(length+1);
strncpy(string,input,length);
string[length]='\0';
void*data=NULL;
tCode type=0;
bool raw=true;

switch (isNumeric(string, length))
{
	case 1://double
	type=_mDbl;
	data=malloc(sizeof(double));
	*(double*)(data)=atof(string);
	goto build;
	case 2://short
	type=_mShort;
	data=malloc(sizeof(short));
	*(short*)(data)=(short)atoi(string);
	goto build;
	case 3://int
	type=_mInt;
	data=malloc(sizeof(int));
	*(int*)(data)=atoi(string);
	goto build;
	case 4://long long
	type=_mLong;
	data=malloc(sizeof(long long));
	*(long long*)(data)=atoll(string);
	goto build;
	default:
	break;
}

//begin symbol checks
long long unsigned hash = FNV_1a(string);

//check for keyword
if ((type=keycode(hash))!=0)
	goto build;
printf("No Keyword\n");
build:;

free(string);
addToken(intr, data, type, raw);
}

void tokenize(char* string,unsigned length,interpreter*intr)
{

unsigned lIndex=0;

//0=normal, 1=string, 2=comment, 3=character, 4=flag
unsigned readMode=0;

//check pending states
if (intr->waitLn)
	{
	intr->waitLn=false;
	}

for (unsigned x=0; x<=length; ++x)
{
//ending value
	if (x==length)
	{
		if (readMode==4)
		{
			flag*flg = malloc (sizeof(flag));
			*flg = setFlag(0,string+lIndex);
			addToken(intr, (void*)flg, _oFlag, true);
		}
		if (readMode==3)
			{
				prntError(string, WRN_UNBOUND_STR, intr->st->options);
				if (x-lIndex>1)
					prntError(string, ERR_EXS_CHR, intr->st->options);
				else if (x-lIndex==0)
					prntError(string, ERR_BLNK_CHR, intr->st->options);
				else
				{
					char*chr = malloc(1);
					*chr=string[x-1];
					addToken(intr,(void*) chr, _mChar, true);
				}

				break;
			}
		if (lIndex==length)
			break;
		if (readMode==2)
			break;
		if (readMode==1)
		{
			prntError(string, WRN_UNBOUND_STR, intr->st->options);
			char*buff = malloc((x-lIndex)+1);
			strncpy(buff, string+lIndex, x-lIndex);
			buff[x-lIndex]='\0';
			addToken(intr,(void*) buff, _mStr, true);
			break;
		}
		else
		{
			identify(string+lIndex, x-lIndex, intr);
			break;
		}
	}

	//mode switches
	if (readMode==1)
		{
			if (string[x]=='\\')//escape
				{
					if (x+1<length)
					{
					//replace esacape character and shrink array
					for (unsigned loop=x; loop<length; ++loop)
						string[x]=string[x+1];
					string [x]=getEscape(string[x]);
					char*tmpStr = realloc(string, length-1);
					if (tmpStr==NULL)
							prntError(string, ERR_REALLOC, intr->st->options);
					else
						string=tmpStr;
					--length;
					}else
					{
					//pend next line
					}
				}
				else if (string[x]=='\"')
				{
					char*nVar = malloc(x-lIndex+1);
					strncpy(nVar, string+lIndex, x-lIndex);
					nVar[x-lIndex]='\0';
					readMode=0;
					lIndex=x+1;
					addToken(intr,(void*) nVar, _mStr, true);
				}

		}
	else if (readMode==2)
		{
				if (string[x]=='#')
					readMode=0;
				lIndex=x+1;
		}
	else if (readMode==3)
		{
			if (string[x]=='\''){
				if (x-lIndex>1)
					prntError(string, ERR_EXS_CHR, intr->st->options);
				else if (x-lIndex==0)
					prntError(string, ERR_BLNK_CHR, intr->st->options);
				else
				{
					char*chr = malloc(1);
					*chr=string[x-1];
					addToken(intr,(void*) chr, _mChar, true);
				}
			readMode=0;
			lIndex=x+1;
			}
		}else if (readMode==4)
		{
			if ((string[x+1]<'a' && string[x+1]>'z') || (string[x+1]<'A' && string[x+1]>'Z'))
				{
					char*tmp=malloc((x-lIndex)+1);
					strncpy(tmp,string+lIndex, x-lIndex);
					tmp[x-lIndex]='\0';
					flag*flg=malloc(sizeof(flag));
					*flg=setFlag(0,tmp);
					addToken(intr,(void*)flg,_oFlag, true);
					free(tmp);
					readMode=0;
				}
			lIndex=x+1;
		}
	else if (isOp(string[x])){
		if (x!=lIndex)
			identify(string+lIndex, x-lIndex, intr);

		switch (string[x])
		{
		//mode switches
		case '\'':readMode=3;break;
		case '\"':readMode=1;break;
		//encapsulations
		case '(':addToken(intr,NULL, _sOpParanth, true); intr->listOp++; break;
		case ')':
		if (intr->listOp>0)
		{
			intr->listOp--;
			addToken(intr,NULL, _sClParanth, true);
		}
		else
		 	prntError(string, ERR_NEG_PARANTH, intr->st->options);
		break;
		case '[':addToken(intr,NULL, _sOpBrack, true); intr->brackOp++; break;
		case ']':
		if (intr->brackOp>0)
		{
			intr->brackOp--;
			addToken(intr,NULL, _sClBrack, true);
		}

		else
			prntError(string, ERR_NEG_BRACK, intr->st->options);
		break;
		case '{':addToken(intr,NULL, _sOpBrace, true); intr->blockOp++; break;
		case '}':
		if (intr->blockOp>0)
		{
			intr->blockOp--;
			addToken(intr,NULL, _sClBrace, true);
		}
		else
			prntError(string, ERR_NEG_BRACE, intr->st->options);
		break;
		//logical
		case '&': addToken(intr,NULL, _lAnd, true); break;
		case '|'://OR, XNOR, XOR
		if (string[x+1]=='!')//XNOR
		{
			addToken(intr,NULL, _lXnor, true);//OR
			++x;
		}else if (string[x+1]=='|')//XOR
		{
			addToken(intr,NULL, _lXor, true);//OR
			++x;
		}else
			addToken(intr,NULL, _lOr, true);//OR
		break;
		case '!':
		if (string[x+1]=='|')
			{
				addToken(intr,NULL,_lNor,true);//NOR
				++x;
			}
		else if (string[x+1]=='&')
			{
				addToken(intr,NULL,_lNand,true);//NOR
				++x;
			}
		else if (string[x+1]=='=')
			{
				addToken(intr,NULL,_cNequ,true);//NOR
				++x;
			}
		else
			addToken(intr,NULL,_lNot,true);//NOT
		break;
		//comparitive
		case '<':
			if (string[x+1]=='=')
				{
					addToken(intr,NULL,_cLssEqu,true);
					++x;
				}
			else
				addToken(intr,NULL,_cLss,true);
		break;
		case '>':
				if (string[x+1]=='=')
				{
					addToken(intr,NULL,_cGtrEqu,true);
					++x;
				}
			else
				addToken(intr,NULL,_cGtr,true);
		break;
		//assignment
		case '=':
		if (string[x+1]=='=')
			{
				addToken(intr,NULL,_cEqu,true);//_cEqu
				++x;
			}
		else
			addToken(intr,NULL,_eSet,true);
		break;
		case '?':
			addToken(intr,NULL,_cQst,true);
		break;
		//arithmetic
		case '+':
			if (string[x+1]=='=')
			{
				addToken(intr,NULL,_eAdd,true);
				++x;
			}else
				addToken(intr,NULL,_aAdd,true);
			break;
		case '-':
			if (string[x+1]=='=')
			{
				addToken(intr,NULL,_eSub,true);//SET
				++x;
			}else
				addToken(intr,NULL,_aSub,true);
			break;
		case '*':
			if (string[x+1]=='=')
			{
				addToken(intr,NULL,_eMult,true);
				++x;
			}else
				addToken(intr,NULL,_aMult,true);
			break;
		case '/':
			if (string[x+1]=='=')
			{
				addToken(intr,NULL,_eDiv,true);
				++x;
			}else
				addToken(intr,NULL,_aDiv,true);
			break;
		case '%':
			if (string[x+1]=='=')
			{
				addToken(intr,NULL,_eMod,true);
				++x;
			}else
				addToken(intr,NULL,_aMod,true);
			break;
		case '^':
			addToken(intr,NULL,_aPow,true);
		case -5://root
			addToken(intr,NULL,_aRoot,true);
		break;
		//other
		case '\\':
		if (x+1==length)
			intr->waitLn=true;
		else
				prntError(string, WRN_NO_EFFECT,intr->st->options);
		break;
		case '~':readMode=4;
		if ((string[x+1]<'a' && string[x+1]>'z') || (string[x+1]<'A' && string[x+1]>'Z'))
			prntError(string, WRN_INV_FLAG, intr->st->options);
		else
			readMode=4;
		break;
		}
		lIndex=x+1;
	}
}
}

void interpret(char* string,unsigned length,interpreter*intr)
{
//ensure string size
if (length==0)
	length=strlen(string);
if (length==0)
	return;

//reset some states
intr->waitExprss=false;

tokenize(string, length, intr);

//determine whether or not to continue waiting
intr->pending=intr->waitExprss | intr->waitLn | intr->litOp |\
!(intr->listOp==0 && intr->blockOp==0 && intr->brackOp==0);

//if (intr->st->options.prntDbg)
/*	printf("%d%d%d%d %d %d %d\n",intr->pending, intr->waitExprss, intr->waitLn,\
intr->litOp, intr->listOp, intr->blockOp, intr->brackOp);
*/
if (intr->pending)
	return;

//begin execution phase
execute(intr);
//cleanup
reset(intr);
}
