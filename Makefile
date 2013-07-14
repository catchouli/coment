# Linux Makefile

all: shared static

shared:
	@mkdir -p bin
	$(MAKE) -C Coment shared
	$(MAKE) -C Sample shared

sharedlib:
	@mkdir -p bin
	$(MAKE) -C Coment shared

static:
	@mkdir -p bin
	$(MAKE) -C Coment static
	$(MAKE) -C Sample static

staticlib:
	@mkdir -p bin
	$(MAKE) -C Coment static

install:
	$(MAKE) -C Coment install

uninstall:
	$(MAKE) -C Coment uninstall

clean:
	@rm -rf bin
	$(MAKE) clean -C Coment
	$(MAKE) clean -C Sample

.PHONY: all shared sharedlib static staticlib install clean
