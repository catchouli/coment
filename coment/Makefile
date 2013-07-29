# Build/install library

BINARY = coment
MAJOR_VERSION = 0
MINOR_VERSION = 1

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

CXXFLAGS = -c -fPIC -Wall $(OPTFLAGS) $(DBGFLAG)
LDFLAGS = -shared -Wl,-soname,$(SONAME) -o bin/$(REALNAME)

SOURCES = $(shell find src -name "*.cpp")
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: shared static

shared: $(BINDIR)/$(REALNAME)

static: $(BINDIR)/$(STATICNAME)

$(BINDIR)/$(REALNAME): $(OBJECTS)
	@# Make binary directory
	@mkdir -p $(BINDIR)

	@# Build shared library
	$(CC) $(LDFLAGS) $(OBJECTS)

	@# Make symlink so that other projects can build from this directory
	ln -sfn ./$(REALNAME) $(LINKNAME)
	mv $(LINKNAME) bin

	@# Copy binaries to ../bin if existent
	@(test -d ../bin && (cp -R $(BINDIR)/* ../bin/)) || true

bin/$(STATICNAME): $(OBJECTS)
	@# Make binary directory
	@mkdir -p $(BINDIR)

	@# Build static library
	$(AR) rcs $@ $(OBJECTS)

	@# Copy binaries to ../bin if existent
	@(test -d ../bin && (cp -R $(BINDIR)/* ../bin/)) || true

obj/%.o: $(SOURCES)
	@# Make directory of object
	@mkdir -p $(dir $@)

	@# Build object
	$(CXX) $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) $(INCLUDES) $(CXXFLAGS) -o $@

install:
	@# Check library is built and exit if not
	@test -s bin/$(REALNAME) || { echo "Error: Library not yet built. Try running "make shared" first."; exit 1; }

	#@ Make directories for library install
	@mkdir -p $(INSTALL_DIR_LIB)
	@mkdir -p $(INSTALL_DIR_INC)/coment

	@# Copy includes to install directory
	cp -R include/coment/* $(INSTALL_DIR_INC)/coment/

	#@ Copy libraries to install directory
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

