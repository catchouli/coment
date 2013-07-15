# Build/install library

BINARY = coment
MAJOR_VERSION = 1
MINOR_VERSION = 0

STATICNAME = $(BINARY).a
LINKNAME = lib$(BINARY).so
SONAME = $(LINKNAME).$(MAJOR_VERSION)
REALNAME = $(LINKNAME).$(MAJOR_VERSION).$(MINOR_VERSION)

PREFIX ?= /usr

INSTALL_DIR_LIB = $(DESTDIR)$(PREFIX)/lib
INSTALL_DIR_INC = $(DESTDIR)$(PREFIX)/include

INCLUDES = -I$(INCDIR)

SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCDIR = include

CXXFLAGS = -c -fPIC -Wall -O2
LDFLAGS = -shared -Wl,-soname,$(SONAME) -o bin/$(REALNAME)

SOURCES = $(shell find src -name *.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: shared static

test:
	echo $(PREFIX)

shared: bin/$(REALNAME)

static: bin/$(STATICNAME)

bin/$(REALNAME): $(OBJECTS)
	@mkdir -p bin
	@mkdir -p ../bin
	$(CC) $(LDFLAGS) $(OBJECTS)
	ln -sfn ./$(REALNAME) $(LINKNAME)
	mv $(LINKNAME) bin
	cp -R bin/* ../bin

bin/$(STATICNAME): $(OBJECTS)
	@mkdir -p bin
	@mkdir -p ../bin
	$(AR) rcs $@ $(OBJECTS)
	cp bin/* ../bin

obj/%.o: $(SOURCES)
	@mkdir -p obj
	@mkdir -p $(dir $@)
	$(CXX) $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) $(INCLUDES) $(CXXFLAGS) -o $@

install:
	@test -s bin/$(REALNAME) || { echo "Error: Library not yet built. Try running "make shared" first."; exit 1; }

	@mkdir -p $(INSTALL_DIR_LIB)
	@mkdir -p $(INSTALL_DIR_INC)/coment
	cp -R include/coment/* $(INSTALL_DIR_INC)/coment/
	cp bin/$(REALNAME) $(INSTALL_DIR_LIB)
	ldconfig -n $(INSTALL_DIR_LIB)
	ln -sfn $(INSTALL_DIR_LIB)/$(REALNAME) $(INSTALL_DIR_LIB)/$(LINKNAME)

uninstall:
	rm -rf $(INSTALL_DIR_LIB)/libcoment.*
	rm -rf $(INSTALL_DIR_INC)/coment

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

.PHONY: all shared static install clean

