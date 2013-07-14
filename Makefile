# Linux Makefile

all: shared static

shared:
	@mkdir -p bin
	$(MAKE) -C Coment shared
	$(MAKE) -C Sample shared
	$(MAKE) -C Tests shared

sharedlib:
	@mkdir -p bin
	$(MAKE) -C Coment shared

static:
	@mkdir -p bin
	$(MAKE) -C Coment static
	$(MAKE) -C Sample static
	$(MAKE) -C Tests static

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
	$(MAKE) clean -C Tests

.PHONY: all shared sharedlib static staticlib install clean
