# Linux Makefile

all: shared static

shared:
	@mkdir -p bin
	$(MAKE) -C coment shared
	$(MAKE) -C samples shared
	$(MAKE) -C tests shared

sharedlib:
	@mkdir -p bin
	$(MAKE) -C coment shared

static:
	@mkdir -p bin
	$(MAKE) -C coment static
	$(MAKE) -C samples static
	$(MAKE) -C tests static

staticlib:
	@mkdir -p bin
	$(MAKE) -C coment static

install:
	$(MAKE) -C coment install

uninstall:
	$(MAKE) -C coment uninstall

clean:
	@rm -rf bin
	$(MAKE) -C coment clean
	$(MAKE) -C samples clean
	$(MAKE) -C tests clean

.PHONY: all shared sharedlib static staticlib install clean
