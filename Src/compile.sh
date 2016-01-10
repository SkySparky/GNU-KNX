echo off
clear

# Compilation settings

COMP_LEVEL=-std=c11
COMP_IGNORE=-Wno-unused-variable
COMP_MODE=-m64

# static library first

cd KNX_SDK
gcc -Wall -c Util.c -c Error.c -c NodeSuper.c -c Data.c -c XMem.c -c Debug.c -c Functional.c $COMP_LEVEL $COMP_IGNORE -lm
ar rcs libKNX_SDK.a Util.o Error.o NodeSuper.o Data.o Debug.o XMem.o Functional.o
cd ../
cd KNX
gcc -Wall -static Launcher.c Node.c State.c Interpreter.c Execute.c Keywords.c ../KNX_SDK/libKNX_SDK.a -o KNX $COMP_LEVEL $COMP_IGNORE -lm
cd ../
echo Done.
