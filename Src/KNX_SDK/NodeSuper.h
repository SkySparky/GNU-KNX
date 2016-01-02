#ifndef KNX_SDK_NODE
#define KNX_SDK_NODE

#include "Defs.h"

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


} baseNode;

bool setupBaseNode(baseNode*);
baseNode*genBaseNode();
bool freeBaseNode(baseNode*);

bool addChild(baseNode*);
bool removeChild(baseNode*);
bool setParent(baseNode*);

#endif