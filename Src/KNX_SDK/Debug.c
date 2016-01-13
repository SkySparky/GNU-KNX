#include "Debug.h"

void prntMemory(database*db)
{

}

void _prntTree(baseNode*target, unsigned short level)
{

for (unsigned x=0; x<level; ++x)
	printf("\t");
printf("%u %p\n", target->handle, target);
for (unsigned x=0; x<target->numChildren; ++x)
	if (target->children[x]!=NULL)
		_prntTree(target->children[x], level+1);
}

void prntTree(baseNode*target)
{
	printf("DEBUG::TREE VIEW\n");
if (target==NULL)
	return;

_prntTree(target,0);
}

void prntTokens(token*target)
{
while (target!=NULL)
{
	printf("[");
	if (target->raw)
		printf("r");
	switch (target->type)
	{
		case _mShort:printf("SHORT");break;
		case _mInt:printf("INT");break;
		case _mLong:printf("LONG");break;
		case _mBool:printf("BOOL");break;
		case _mDbl:printf("DBL");break;
		case _mChar:printf("CHAR");break;
		case _mStr:printf("STR");break;
		case _mFile:printf("FILE");break;
		case _mScript:printf("SCRIPT");break;
		case _mFunction:printf("FNC");break;
		case _mVoid:printf("VOID");break;

		case _sOpParanth:printf("OP");break;
		case _sClParanth:printf("CP");break;
		case _sOpBrack:printf("OBK");break;
		case _sClBrack:printf("CBK");break;
		case _sOpBrace:printf("OBR");break;
		case _sClBrace:printf("CBR");break;
		case _sList:printf("LST");break;
		case _sMember:printf("MMBR");break;

		case _lAnd:printf("AND");break;
		case _lOr:printf("OR");break;
		case _lNot:printf("NOT");break;
		case _lNand:printf("NAND");break;
		case _lNor:printf("NOR");break;
		case _lXnor:printf("XNOR");break;
		case _lXor:printf("XOR");break;

		case _cEqu:printf("EQU");break;
		case _cNequ:printf("NEQU");break;
		case _cQst:printf("QST");break;
		case _cGtr:printf("GTR");break;
		case _cGtrEqu:printf("GTREQU");break;
		case _cLss:printf("LSS");break;
		case _cLssEqu:printf("LSSEQU");break;

		case _aAdd:printf("ADD");break;
		case _aSub:printf("SUB");break;
		case _aMult:printf("MULT");break;
		case _aDiv:printf("DIV");break;
		case _aPow:printf("POW");break;
		case _aRoot:printf("ROOT");break;
		case _aMod:printf("MOD");break;

		case _eSet:printf("SET");break;
		case _eAdd:printf("EADD");break;
		case _eSub:printf("ESUB");break;
		case _eMult:printf("EMULT");break;
		case _eDiv:printf("EDIV");break;
		case _eMod:printf("EMOD");break;

		case _kExit:printf("EXIT");break;
		case _kXNode:printf("XNODE");break;
		case _kTerm:printf("TERM");break;
		case _kDel:printf("DEL");break;
		case _kBreak:printf("BREAK");break;
		case _kSwtch:printf("SWTCH");break;
		case _kImport:printf("IMPORT");break;
		case _kReturn:printf("RET");break;
		case _kMsg:printf("MSG");break;
		case _kIf:printf("IF");break;
		case _kWhile:printf("WHLE");break;
		case _kFrEach:printf("FEACH");break;
		case _kTry:printf("TRY");break;
		case _kCatch:printf("CATCH");break;
		case _kCast:printf("CST");break;

		case _oFlag:printf("FLAG");break;
		default:
		printf("NA");
		break;
	}
	printf(" %hu]", target->order);
	target=target->next;
}
printf("\n");
}
