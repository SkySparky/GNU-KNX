#ifndef KNX_SDK_NODE
#define KNX_SDK_NODE

//#include "Xmem.h"
#include "Defs.h"

//forward declarations
struct database;

typedef struct exModule _nsEMod;
typedef struct object _nsObj;
typedef struct database _nsDb;

/*
Contains important information for
external libraries
*/
typedef struct baseNode
{
//connections
struct baseNode*parent;
struct baseNode**children;
//counters
unsigned numChildren;

//state
unsigned handle;//acting id
bool active;

//bitfield switches
bool prntErr : 1;
bool prntWrn : 1;

_nsDb*local;
_nsDb*global;


} baseNode;

bool setupBaseNode(baseNode*,_nsDb*);
baseNode*genBaseNode(_nsDb*);
bool freeBaseNode(baseNode*);

bool addChild(baseNode*);
bool removeChild(baseNode*);
bool setParent(baseNode*);

#endif
