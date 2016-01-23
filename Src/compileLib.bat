rem compiles the standard shared libraries
echo off
cls
setlocal

set SETTINGS=-m64 -std=c11

cd STD_LIB

gcc -c -fpic IO/KNX_IO.c -o IO/KNX_IO.o
gcc -g -pipe -O2 -pipe -fPIC IO/KNX_IO.o ../KNX_SDK/libKNX_SDK.a -shared -o ../../bin/std/KNX_IO.so
rem gcc -Wl,-E -g -pipe -O2 -pipe -fPIC  myobjectfile.o mystaticlibrary.a -shared -o mylib.so
cd ..

endlocal

echo Done.
