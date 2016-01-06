echo off
clear

# Compilation settings

COMP_LEVEL=-std=c11
COMP_IGNORE=-Wno-unused-variable
COMP_MODE=-m64

# static library first

cd KNX_SDK
# gcc -Wall -static Util.c NodeSuper.c -l KNX_SDK -o SDK.o $COMP_LEVEL
gcc -Wall -c Util.c -c Error.c -c NodeSuper.c -c Data.c -c Debug.c $COMP_LEVEL $COMP_IGNORE
ar rcs libKNX_SDK.a Util.o Error.o NodeSuper.o Data.o Debug.o
cd ../
cd KNX
gcc -Wall -static Launcher.c Node.c State.c Interpreter.c ../KNX_SDK/libKNX_SDK.a -o KNX $COMP_LEVEL $COMP_IGNORE
cd ../
echo Done.
