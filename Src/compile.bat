echo off
cls

rem Compilation settings

set COMP_LEVEL=-std=c11
set COMP_IGNORE=-Wno-unused-variable
set COMP_MODE=-m64

rem static library first

cd KNX_SDK
rem gcc -Wall -static Util.c NodeSuper.c -l KNX_SDK -o SDK.o %COMP_LEVEL%
gcc -Wall -c Util.c -c Error.c -c NodeSuper.c -c Data.c %COMP_LEVEL% %COMP_IGNORE%
ar rcs libKNX_SDK.a Util.o Error.o NodeSuper.o Data.o
cd ..
if errorLevel 1 goto houston
cd KNX
gcc -Wall -static Launcher.c Node.c State.c Interpreter.c ../KNX_SDK/libKNX_SDK.a -o KNX %COMP_LEVEL% %COMP_IGNORE%
cd..
if errorLevel 1 goto houston
goto success
:houston
echo Compilation failed
goto jmpend
:success
echo Done.
:jmpend