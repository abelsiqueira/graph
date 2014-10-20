include make.inc

all: lib tests

SUBMAKES = $(dir $(shell ls */Makefile))

.PHONY: lib tests
lib tests:
	$(MAKE) -C $@ all

clean purge:
	@for dir in $(SUBMAKES); do $(MAKE) -C $$dir; done
