#compiles KNX SDK

CC=gcc
CFLAGS= -std=c11 -pedantic -Wall -c
#LDFLAGS= -g
LIBS= -lm
SRC=Memory.c Node.c Error.c Exchange.c
OBJ=$(SRC:.c=.o)
INCLUDES= -Iheaders
OUT=libKDK.a
CLEANEXT = o a
BITVRS=64
EXPORT_PTH=../../_bin_/
EPATH_FULL=$(EXPORT_PTH)$(OUT)

#configure for Linux and Windows
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


%.o : %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $< $(LIBS)

$(EPATH_FULL): $(OBJ)
	ar rcs $(EPATH_FULL) $(OBJ)


.PHONY: clean
clean:
	rm -f $@ *.o
