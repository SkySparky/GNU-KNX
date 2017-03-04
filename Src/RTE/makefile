#Compiles runtime language

#BINPATH="../../_bin_/"
CC = gcc
CFLAGS = -std=c11 -Wall -I../KDK/headers -Iheaders -I../../../KNX_Libraries/headers -DNULL=0 -Dtrue=1 -Dfalse=0
LFLAGS = -lm -ldl -lpthread -L$(BINPATH) -l:libKDK.so -Wl,-rpath=$(BINPATH)
VERSION=-DRTEVERSION=\"0.0.1\"
OUT = KNX
CLEANEXT = o a
BITVRS=64
DBGFLAG=
SRC=Launcher.c CMD.c InitInterfaces.c Node.c Tokenizer.c

ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../_bin_/
	EXT=
	RUNPATH=./$(EXPORT_PTH)$(OUT)$(EXT)
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
	EXPORT_PTH=../../_bin_/
	EXT=.exe
	RUNPATH=$(EXPORT_PTH)$(OUT)$(EXT)
endif

all:
	$(CC) $(SRC) $(OSMODE) $(CFLAGS) $(KLIB) $(VERSION) $(PLATFORM) $(LFLAGS) -o $(RUNPATH)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
