# Linux Makefile

OPTFLAG = -O2
OPTIONS = OPTFLAG=$(OPTFLAG) DBGFLAG=$(DBGFLAG)

all: shared static

shared:
	@mkdir -p bin
	$(MAKE) -C coment shared $(OPTIONS)
	$(MAKE) -C samples shared $(OPTIONS)
	$(MAKE) -C tests shared $(OPTIONS)

sharedlib:
	@mkdir -p bin
	$(MAKE) -C coment shared $(OPTIONS)

static:
	@mkdir -p bin
	$(MAKE) -C coment static $(OPTIONS)
	$(MAKE) -C samples static $(OPTIONS)
	$(MAKE) -C tests static $(OPTIONS)

staticlib:
	@mkdir -p bin
	$(MAKE) -C coment static $(OPTIONS)

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
