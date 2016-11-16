#compiles KNX runtime engine, modules, and utility programs

SUBDIRS = Src/KDK/ Src/RTE/
BITVRS=64

export BITVRS

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done

.PHONY: run
run:
	_bin_/KNX

.PHONY: dbg
dbg:
	_bin_/KNX -d
