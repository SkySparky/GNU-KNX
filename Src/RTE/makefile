#Compiles runtime language

export LD_LIBRARY_PATH=/../../_bin_

CC = gcc
CFLAGS = -std=c11 -Wall -DNULL=0 -Dtrue=1 -Dfalse=0
LFLAGS = -lm -L -l../../_bin_/KDK
OUT = KNX
CLEANEXT = o a
BITVRS=64
DBGFLAG=
SRC=Launcher.c Error.c

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
	$(CC) $(SRC) $(OSMODE) $(CFLAGS) $(PLATFORM) $(LFLAGS) -o $(RUNPATH)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
