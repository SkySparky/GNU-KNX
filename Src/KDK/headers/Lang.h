#ifndef KDK_LANG
#define KDK_LANG

typedef enum {
  _lNA,
  _lNumeric,
  _lText,
  _lChar,
  _lVariable,

  //OPERATORS

  //Math
  _lAdd,
  _lSub,
  _lDiv,
  _lMult,
  _lModu,
  _lPow,
  _lRoot,

  //Assignment
  _lSet,//A=B
  _lSetAnd,//A&=B
  _lSetOr,//A|=B
  _lSetAdd,//A+=B
  _lSetSub,//A-=B
  _lSetMult,//A*=B
  _lSetDiv,//A/=B
  _lSetModu,//A%=B
  _lPreInc,//++A
  _lPostInc,//A++
  _lPreDec,//--A
  _lPostDec,//A--

  //comparison logic
  _lGtr,//>
  _lLss,//<
  _lEqu,//==
  _lNEqu,//!=
  _lGtrEqu,//>=
  _lLssEqu,//<=
  _lWithinInc,//>=<A
  _lWithinEx,//><A
  _lOutsideInc,//<=>A
  _lOutsideEx,//<>A
  _lTernary,//(CONDITION)?1_RESULT,2_RESULT

  //indexing
  _lIndex,//:
  _lList,//,

  //Encapsulation
  _lOBrace,//{
  _lCBrace,//}
  _lOBrack,//[
  _lCBrack,//]
  _lOParan,//(
  _lCParan,//)

  //logic operators
  _lAnd,//&&    AB
  _lOr,//||     A+B
  _lNot,//!     !A
  _lNAnd,//!&   !(AB)
  _lNOr,//!|    !(A+B)
  _lXOr,//|!    !AB + !BA
  _lXNor,//~|   !A!B + AB

  //bitwise operations
  _lLShift,//bit shift left <<
  _lRShift,//bit shift right >>
  _lBAnd,//bitwise AND &
  _lBOr,//bitwise OR |
  _lBNot,//bitwise invert ~

  //Lambda
  _lLambda//$ Lambda notation (A, B) $ {EXPRESSION}

} Lexeme;

typedef enum {
  _pNormal, //Regular parsing mode
  _pSString,//Single quote
  _pDString,//Double quote
  _pSComment,//Single line comment
  _pMComment//Multi line comment
} ParseMode;

#define ExpectsToken(pm) (pm == _pSString || pm == _pDString || pm == _pMComment)

//basic input identifier
typedef struct Token{

  struct Token * next;
  struct Token * previous;

  char * raw;
  Lexeme lexeme;

} Token;

//statement cache for intermediate parsing
typedef struct TCache{
  Token * current;
  Token * head;//NOTE: Head is beginning

  unsigned nestLevel;//current () nest level open. Don't execute until 0
  char * nestType;

  ParseMode pMode;
} TCache;

Token * BuildToken(char * raw_start, char * raw_end, Lexeme lx);
void DeleteToken(Token *);

#endif
