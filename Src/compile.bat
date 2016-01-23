echo off
cls

rem Compilation settings
setlocal
set COMP_LEVEL=-std=c11
set COMP_IGNORE=-Wno-unused-variable
set COMP_MODE=-m64
set STDLIB_PATH=STD_LIB\

rem Engine files
set SRCF=Launcher.c Node.c State.c Interpreter.c Execute.c Keywords.c
set OBJF=-o Launcher.o -o Node.o -o State.o -o Interpreter.o -o Execute.o -o Keywords.o
rem Library files
set SRCL=-c Util.c -c Error.c -c NodeSuper.c -c Data.c -c Debug.c -c Functional.c -c KMath.c -c XMem.c
set OBJL=-o Util.o -o Error.o -o NodeSuper.o -o Data.o -o Debug.o -o Functional.o -o KMath.o -o XMem.o

if /I %COMP_MODE% == -m64 set ENVO_DECL=-D_WIN32 -D_WIN64
if /I %COMP_MODE% == -m32 set ENVO_DECL=-D_WIN32

rem static library first
cd KNX_SDK
gcc -Wall %SRCL% %COMP_LEVEL% %COMP_IGNORE%
ar rcs libKNX_SDK.a %OBJL%
cd ..
if errorLevel 1 goto houston
cd KNX
gcc -Wall -static %SRCF% ../KNX_SDK/libKNX_SDK.a -o ../../bin/KNX %COMP_LEVEL% %COMP_IGNORE% %ENVO_DECL% -ldl

cd..
if errorLevel 1 goto houston
goto success
:houston
echo Compilation failed
goto jmpend
:success
echo Done.
:jmpend
endlocal
