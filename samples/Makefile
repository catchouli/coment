# Linux Makefile

all: shared static

shared:
	@mkdir -p bin
	@mkdir -p ../bin
	$(MAKE) -C balls shared
	@cp -R bin/* ../bin/

static:
	@mkdir -p bin
	@mkdir -p ../bin
	$(MAKE) -C balls static
	@cp -R bin/* ../bin/

clean:
	rm -rf bin
	$(MAKE) -C balls clean

.PHONY: all shared static clean
