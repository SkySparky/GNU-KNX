#Compiles KNX Development Kit

CC = gcc
CFLAGS = -std=c11 -Wall -fPIC
LFLAGS = -lm
VERSION = -DKDKVersion=\"0.0.1\"
OUT = libKDK.so
CLEANEXT = o a
BITVRS=64
DBGFLAGS=
SRC=Util.c Contract.c 
EXPORT_PTH=../../_bin_/

ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
endif

all:
	$(CC) $(CFLAGS) $(VERSION) $(SRC) -shared -o $(EXPORT_PTH)$(OUT) $(OSMODE) $(LFLAGS) $(DBGFLAGS)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
