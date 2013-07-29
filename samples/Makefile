# Linux Makefile

BINDIR = bin

all: shared static

shared:
	@mkdir -p $(BINDIR)
	$(MAKE) -C balls shared OPTFLAG=$(OPTFLAG) DBGFLAG=$(DBGFLAG)
	@test -d ../bin && cp -R bin/* ../bin/

static:
	@mkdir -p $(BINDIR)
	$(MAKE) -C balls static OPTFLAG=$(OPTFLAG) DBGFLAG=$(DBGFLAG)
	@test -d ../bin && cp -R bin/* ../bin/

clean:
	rm -rf $(BINDIR)
	$(MAKE) -C balls clean

.PHONY: all shared static clean
