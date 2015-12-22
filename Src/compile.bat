echo off
cls

rem Compilation settings

set COMP_LEVEL=-std=c99

rem static library first

cd KNX_SDK
rem gcc -Wall -static Util.c -l KNX_SDK -o SDK.o %COMP_LEVEL%
gcc -c Util.c -o KNX_SDK.o
ar rcs libKNX_SDK.a KNX_SDK.o
cd ..
if errorLevel 1 goto houston
cd KNX
gcc -Wall -static Launcher.c ../KNX_SDK/libKNX_SDK.a -o KNX %COMP_LEVEL%
cd..
if errorLevel 1 goto houston
goto success
:houston
echo Compilation failed
goto jmpend
:success
echo Successful compilation
:jmpend