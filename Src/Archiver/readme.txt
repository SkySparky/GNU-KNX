ARCHIVER

Part of the KNX toolset

In an effort to make loading external libraries a bit easier,
i've decided to make a simple archiver for combining .so files
with a simple header to define symbols found in the dynamic
shared library (as a workaround for symbol tables)

Working with it is simple: after building a dynamically linked
shared object, run:
  ark -t [table] -l [.so file]
to create a .ark file
this .ark file can be used to import libraries with the KNX engine

other option flags:

-v version
-h help
-c checks .so to ensure that symbols in the object file are defined
-d debug
-t [table] specifies table file
-l [.so] specifies object file
-n [name] specifies archive name
-p [path] specify output directory

Table file

Simply put, the table file is just one function title
per line

example:

function1
function2

no return values or argument parameters
no characters besides this
no spaces before the function name
you CAN use comments via the '#' character at the very start
of each new line

#this is a comment
 #this will cause problems
