# Build/install library

BINARY = coment
MAJOR_VERSION = 1
MINOR_VERSION = 0

STATICNAME = $(BINARY).a
LINKNAME = lib$(BINARY).so
SONAME = $(LINKNAME).$(MAJOR_VERSION)
REALNAME = $(LINKNAME).$(MAJOR_VERSION).$(MINOR_VERSION)

INSTALL_DIR = /usr/lib

INCLUDES = -I$(INCDIR)

SRCDIR = src
OBJDIR = obj
BINDIR = bin
INCDIR = include

CXXFLAGS = -c -fPIC -std=c++11 -Wall -O2
LDFLAGS = -shared -Wl,-soname,$(SONAME) -o bin/$(REALNAME)

SOURCES = $(shell find src -name *.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: shared static

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

%.o: $(SOURCES)
	@mkdir -p obj
	@mkdir -p $(dir $@)
	$(CXX) $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) $(INCLUDES) $(CXXFLAGS) -o $@

install:
	cp bin/$(REALNAME) $(INSTALL_DIR)
	ldconfig -n $(INSTALL_DIR)
	ln -sfn $(INSTALL_DIR)/$(REALNAME) $(INSTALL_DIR)/$(LINKNAME)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

.PHONY: all shared static install clean

