# Linux Makefile

BINDIR = bin

all: shared static

shared:
	@mkdir -p $(BINDIR)
	$(MAKE) -C balls shared OPTFLAG=$(OPTFLAG) DBGFLAG=$(DBGFLAG)
	@#$(MAKE) -C breakout shared OPTFLAG=$(OPTFLAG) DBGFLAG=$(DBGFLAG)
	@(test -d ../bin && (cp -R $(BINDIR)/* ../bin/)) || true

static:
	@mkdir -p $(BINDIR)
	$(MAKE) -C balls static OPTFLAG=$(OPTFLAG) DBGFLAG=$(DBGFLAG)
	@#$(MAKE) -C breakout static OPTFLAG=$(OPTFLAG) DBGFLAG=$(DBGFLAG)
	@(test -d ../bin && (cp -R $(BINDIR)/* ../bin/)) || true

clean:
	rm -rf $(BINDIR)
	$(MAKE) -C balls clean
	@#$(MAKE) -C breakout clean
	$(MAKE) -C common clean

.PHONY: all shared static clean
