#ifndef KDK_VAR
#define KDK_VAR

#include <limits.h>

#include "Structures.h"
#include "Macro.h"

#define UNKNOWN_TYPE UINT_MAX

//template for adding to cast table

/*
Defines a means of searching or registering data types with or from the RTE
*/

//returns the session id of an object type by name, or UNKNOWN_TYPE if not found
unsigned  getTypeId(char *);
//register a new object. Returns assigned id, or UNKNOWN_TYPE on failure
//1) Object name
//2)_

/*
Indicates a type conversion method for a custom type
1) Associated module handle id
2) Left hand object type id
3) Right hand object type id
4) Castable type function pointer to custom conversion method
*/
//unsigned  registerCast(int, int, int, Castable);


#endif
