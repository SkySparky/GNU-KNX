#compiles KNX runtime engine, modules, and utility programs

SUBDIRS = Src/KDK/ Src/RTE/
BITVRS=64
BINPATH=$(shell pwd)/_bin_

export BITVRS
export BINPATH

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done

.PHONY: run
run:
	_bin_/KNX

.PHONY: dbg
dbg:
	_bin_/KNX -h -v

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
	 $(MAKE) clean -C $$dir; \
	done
	 rm -f $@ _bin_/KNX
	 rm -f $@ _bin_/*.so
