rem compiles the standard shared libraries
echo off
cls
setlocal

set SETTINGS=-m64 -std=c11
set LIBSETT=-g -pipe -O2 -pipe -fPIC
set STTPATH=../KNX_SDK/libKNX_SDK.a
set OUTPTH=../../_bin/std/

cd STD_LIB

gcc -c -fpic IO/KNX_IO.c -o IO/KNX_IO.o
gcc %LIBSETT% IO/KNX_IO.o %STTPATH% -shared -o %OUTPTH%KNX_IO.so
rem gcc -Wl,-E -g -pipe -O2 -pipe -fPIC  myobjectfile.o mystaticlibrary.a -shared -o mylib.so
cd ..

endlocal

echo Done.
