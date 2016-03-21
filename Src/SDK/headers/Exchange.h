#ifndef KNX_SDK_EXCHANGE
#define KNX_SDK_EXCHANGE

/*
Defines structures and methods for module communication

The dInfo structure contains raw and meta data for a data piece.
Tokenization utilizes this, in addition with a tree wrapper
*/

#include "Memory.h"

#include "wchar.h"
#include <stdlib.h>

//API definitions
#define KNX_API_RETURN mBase*
#define KNX_API_PARAM mBase**params, nodeBase*node

#endif

/*
Note about data preservation:

Usable info such as numerical or textual data is preserved. Token strings are
are only stored as a meta value, and are not preserved.

Managed types are stored only by pointer, and are not deleted during deconstruction
*/
