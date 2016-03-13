#ifndef KNX_SDK_EXCHANGE
#define KNX_SDK_EXCHANGE

/*
Defines structures and methods for module communication

The dInfo structure contains raw and meta data for a data piece.
Tokenization utilizes this, in addition with a tree wrapper
*/

struct tInfo;

typedef enum{
//General Terms
  dNA,
//Meta type
  RawData, ManData, Command,
//Operators
//Encapsulators
  OParanth, CParanth, OBrack, CBrack, OBrace, CBrace,
//Math
  Add, Sub, Mult, Div, Pow, Root, Mod,
//Referencing
  RefMember, Index,
//Logic
//Comparison
  Lss, Gtr, LssEqu, GtrEqu, Equ, NEqu,
//Boolean
  And, Or, Not, Nand, Nor, Xor, XNor,
//Assignment
  Set, SetAdd, SetSub, SetMult, SetDiv,
//Logic
  If, Else, Tern,
//Attribution
  Flag

}dType;

typedef struct tInfo
{
  dType type;
  void * data;
}dInfo;

//ensure dInfo cleared
dInfo * makeInfo(dType, void*data);

int infoDelete(dInfo*);

#endif

/*
Note about data preservation:

Usable info such as numerical or textual data is preserved. Token strings are
are only stored as a meta value, and are not preserved.

Managed types are stored only by pointer, and are not deleted during deconstruction
*/
