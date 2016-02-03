echo off
clear

# Compilation settings

COMP_LEVEL=-std=c11
COMP_IGNORE=-Wno-unused-variable
COMP_MODE=-m64
SRC_C="Launcher.c Node.c State.c Interpreter.c Execute.c Keywords.c"
SRC_O="-o Launcher.o -o Node.o -o State.o -o Interpreter.o -o Execute.o -o Keywords.o"
LIB_C="-c Util.c -c Error.c -c NodeSuper.c -c Data.c -c Debug.c -c Functional.c -c KMath.c -c XMem.c"
LIB_O="-o Util.o -o Error.o -o NodeSuper.o -o Data.o -o Debug.o -o Functional.o -o KMath.o -o XMem.o"

# static library first

cd KNX_SDK
gcc -Wall $LIB_C $COMP_LEVEL $COMP_IGNORE -lm -ldl
ar rcs libKNX_SDK.a $LIB_O
cd ..
cd KNX
gcc -Wall -static $SRC_C ../KNX_SDK/libKNX_SDK.a -o KNX $COMP_LEVEL $COMP_IGNORE -lm -ldl
cd ..
echo Done.
