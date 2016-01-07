#include "Interpreter.h"

#include "../KNX_SDK/Debug.h"

#include <string.h>


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

ret->buffSize=0;
ret->buffer=malloc(0);

return ret;
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

token * addToken(token*parent, void*data, tCode type, bool raw)
{

if (parent==NULL)
{
	parent=genToken(parent);
	parent->data=data;
	parent->type=type;
	parent->raw=raw;
	return parent;
}

token * curr = genToken(parent);
curr->data=data;
curr->type=type;
curr->raw=raw;
curr->previous=parent;
parent->next=curr;

return curr;
}

//identify symbolic identifiers
token* identify(char*string, unsigned length, interpreter*intr, token*tail)
{
void*data=NULL;
tCode type=0;
bool raw=true;
if (intr->st->options.prntDbg)
	printf("identifying: %s\n", string);

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

build:

return addToken(tail, data, type, raw);
}

token * tokenize(char* string,unsigned length,interpreter*intr)
{

unsigned lIndex=0;

//0=normal, 1=string, 2=comment, 3=character
unsigned readMode=0;
token*current=NULL;

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
		if (readMode==3)
			{
				printf("%d %d\n", x, lIndex);
				prntError(string, WRN_UNBOUND_STR, intr->st->options);
				if (x-lIndex>1)
					prntError(string, ERR_EXS_CHR, intr->st->options);
				else if (x-lIndex==0)
					prntError(string, ERR_BLNK_CHR, intr->st->options);
				else
				{
					char*chr = malloc(1);
					*chr=string[x-1];
					current=addToken(current,(void*) chr, _mChar, true);
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
			current=addToken(current,(void*) buff, _mStr, true);
			break;
		}
		else
		{
			current = identify(string+lIndex, x-lIndex-1, intr, current);
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
					current=addToken(current,(void*) nVar, _mStr, true);
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
				printf(">> %d %d\n", x, lIndex);
				if (x-lIndex>1)
					prntError(string, ERR_EXS_CHR, intr->st->options);
				else if (x-lIndex==0)
					prntError(string, ERR_BLNK_CHR, intr->st->options);
				else
				{
					char*chr = malloc(1);
					*chr=string[x-1];
					current=addToken(current,(void*) chr, _mChar, true);
				}
			readMode=0;
			lIndex=x+1;
			}
		}
	else if (isOp(string[x])){
		if (x!=lIndex)
			current = identify(string+lIndex, x-lIndex, intr, current);

		switch (string[x])
		{
		//mode switches
		case '\'':readMode=3;break;
		case '\"':readMode=1;break;
		//encapsulations
		case '(':current=addToken(current,NULL, _sOpParanth, true); break;
		case ')':current=addToken(current,NULL, _sClParanth, true); break;
		case '[':current=addToken(current,NULL, _sOpBrack, true); break;
		case ']':current=addToken(current,NULL, _sClBrack, true); break;
		case '{':current=addToken(current,NULL, _sOpBrace, true); break;
		case '}':current=addToken(current,NULL, _sClBrace, true); break;
		//logical
		case '&': current=addToken(current,NULL, _lAnd, true); break;
		case '|'://OR, XNOR, XOR
		if (x+1==length)
			{
				current=addToken(current,NULL, _lOr, true);//OR
				break;
			}
		if (string[x+1]=='!')//XNOR
		{
			current=addToken(current,NULL, _lOr, true);//OR
			++x;
		}else if (string[x+1]=='|')//XOR
		{
			current=addToken(current,NULL, _lXor, true);//OR
			++x;
		}else
			current=addToken(current,NULL, _lOr, true);//OR
		break;
		case '!':
		if (x+1==length)
			{
				current=addToken(current,NULL,_lNot,true);//NOT
				break;
			}
		if (string[x+1]=='|')
			{
				current=addToken(current,NULL,_lNor,true);//NOR
				++x;
			}
		else if (string[x+1]=='&')
			{
				current=addToken(current,NULL,_lNand,true);//NOR
				++x;
			}
		else if (string[x+1]=='=')
			{
				current=addToken(current,NULL,_cNequ,true);//NOR
				++x;
			}
		else
			current=addToken(current,NULL,_lNot,true);//NOT
		break;
		//comparitive
		case '<':
			if (x+1==length)
				current=addToken(current,NULL,_cLss,true);
			else if (string[x+1]=='=')
				{
					current=addToken(current,NULL,_cLssEqu,true);
					++x;
				}
			else
				current=addToken(current,NULL,_cLss,true);
		break;
		case '>':
			if (x+1==length)
				current=addToken(current,NULL,_cGtr,true);
			else if (string[x+1]=='=')
				{
					current=addToken(current,NULL,_cGtrEqu,true);
					++x;
				}
			else
				current=addToken(current,NULL,_cGtr,true);
		break;
		//assignment
		case '=':
		if (x+1==length)
			{
				current=addToken(current,NULL,_eSet,true);//SET
				break;
			}
		else if (string[x+1]=='=')
			{
				current=addToken(current,NULL,_cEqu,true);//_cEqu
				++x;
			}
		else
			current=addToken(current,NULL,_eSet,true);
		break;
		case '?':
			current=addToken(current,NULL,_cQst,true);
		break;
		//arithmetic
		case '+':
			if (x+1==length)
				current=addToken(current,NULL,_aAdd,true);
			else if (string[x+1]=='=')
			{
				current=addToken(current,NULL,_eAdd,true);
				++x;
			}else
				current=addToken(current,NULL,_aAdd,true);
			break;
		case '-':
		if (x+1==length)
				current=addToken(current,NULL,_aSub,true);
			else if (string[x+1]=='=')
			{
				current=addToken(current,NULL,_eSub,true);//SET
				++x;
			}else
				current=addToken(current,NULL,_aSub,true);
			break;
		case '*':
		if (x+1==length)
				current=addToken(current,NULL,_aMult,true);
			else if (string[x+1]=='=')
			{
				current=addToken(current,NULL,_eMult,true);
				++x;
			}else
				current=addToken(current,NULL,_aMult,true);
			break;
		case '/':
		if (x+1==length)
				current=addToken(current,NULL,_aDiv,true);
			else if (string[x+1]=='=')
			{
				current=addToken(current,NULL,_eDiv,true);
				++x;
			}else
				current=addToken(current,NULL,_aDiv,true);
			break;
		case '%':
		if (x+1==length)
				current=addToken(current,NULL,_aMod,true);
			else if (string[x+1]=='=')
			{
				current=addToken(current,NULL,_eMod,true);
				++x;
			}else
				current=addToken(current,NULL,_aMod,true);
			break;
		case '^':
			current=addToken(current,NULL,_aPow,true);
		case -5://root
			current=addToken(current,NULL,_aRoot,true);
		break;
		//other
		case '\\':
		if (x+1==length)
			intr->waitLn=true;
		else
				prntError(string, WRN_NO_EFFECT,intr->st->options);
		break;
		case '~':
		if (x+1==length)
			prntError(string, WRN_INV_FLAG, intr->st->options);
		else if ((string[x+1]<'a' || string[x+1]>'z') &&
						 (string[x+1]<'A' || string[x+1]>'Z'))
			prntError(string, WRN_INV_FLAG, intr->st->options);
		else
			{
				current=addToken(current,NULL,_oFlag,true);
				++x;
			}
		break;
		}
		lIndex=x+1;
	}
}
current=getHead(current);
if (intr->st->options.prntSys)
	prntTokens(current);
return current;
}

void interpret(char* string,unsigned length,interpreter*intr)
{
//ensure string size
if (length==0)
	length=strlen(string);
if (length==0)
	return;

if (intr->st->options.prntEcho)
	printf("\t\t>> %s\n", string);

token*tokenStream=tokenize(string, length, intr);

//determine whether or not to continue waiting
intr->pending=!intr->litOp && !intr->listOp && !intr->blockOp? false: true;

freeToken(tokenStream);
}
