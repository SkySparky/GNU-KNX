#compiles KNX runtime engine, modules, and utility programs

SUBDIRS = Src/SDK/ Src/RTE/

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done
