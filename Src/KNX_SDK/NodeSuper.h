#ifndef KNX_SDK_NODE
#define KNX_SDK_NODE

typedef struct baseNode
{
//connections
struct baseNode*parent;
struct baseNode**children;
//counters
unsigned numChildren;

//state
unsigned long long hash;//acting id

//bitfield switches
bool prntErr : 1;
bool prntWrn : 1;
} baseNode;

#endif