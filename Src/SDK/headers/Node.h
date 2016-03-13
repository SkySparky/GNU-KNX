#ifndef KNX_SDK_NODE
#define KNX_SDK_NODE

/*
Structures and methods for lexical analysis
*/

typedef enum {vPublic, vPrivate, vProtected, vLegacy} visibility;

struct tNodeBase;

typedef struct tNodeBase
{

  long long unsigned id;//reference id. Prime number. Root ID = 1
  long long unsigned policySet;//semi-prime product
  visibility privacyPolicy;//general policy set for local memory scope

  struct nodeBase*children;
  struct nodeBase*parent;

} nodeBase;

#endif
