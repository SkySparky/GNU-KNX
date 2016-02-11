CC=gcc
CFLAGS=-c -Wall
LFLAGS=
EXLIBS=-lm -ldl -static ../KNX_SDK/libKNX_SDK.a
SOURCES=Launcher.c Node.c State.c Interpreter.c Execute.c Keywords.c
OBJECTS=$(SOURCES: .c=.o)
XOUT=KNX.exe

all: $(SOURCES) $(XOUT)

$(XOUT): $(OBJECTS)
	$(CC) $(EXLIBS) $(OBJECTS) $(LFLAGS) -o $@
	
.c.o:
	$(CC) $(CFLAGS) $(EXLIBS) $< -o $@