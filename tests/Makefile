# Build the unit tests

EXECUTABLE=tests/tests

SHARED_OUTPUT=$(EXECUTABLE)-shared
STATIC_OUTPUT=$(EXECUTABLE)-static

SRCDIR=src
OBJDIR=obj
BINDIR=bin
INCDIR=include

CXXFLAGS=-c -Wall $(OPTFLAGS) $(DBGFLAG)
LDFLAGS=
INCLUDES=-I$(INCDIR) -I../coment/include

SOURCES=$(shell find src -name "*.cpp")
OBJECTS=$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: shared static

shared: $(BINDIR)/$(SHARED_OUTPUT)

static: $(BINDIR)/$(STATIC_OUTPUT)

$(BINDIR)/$(SHARED_OUTPUT): $(OBJECTS)
	@# Make binary directory
	@mkdir -p $(BINDIR)/$(dir $(EXECUTABLE))

	@# Build tests against shared library
	$(CXX) $(LDFLAGS) -L../bin -lcoment $(OBJECTS) -o $@

	@# Copy binaries to ../bin/ if existent
	@(test -d ../bin && (cp -R $(BINDIR)/* ../bin/)) || true

$(BINDIR)/$(STATIC_OUTPUT): $(OBJECTS)
	@# Make binary directory
	@mkdir -p $(BINDIR)/$(dir $(EXECUTABLE))

	@# Build tests against static library
	$(CXX) $(LDFLAGS) $(OBJECTS) ../bin/coment.a -o $@

	@# Copy binaries to ../bin/ if existent
	@(test -d ../bin && (cp -R $(BINDIR)/* ../bin/)) || true

obj/%.o: $(SOURCES)
	@# Create obj directory
	@mkdir -p $(dir $@)

	@# Build object
	$(CXX) $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) $(INCLUDES) $(CXXFLAGS) -o $@

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

.PHONY: all shared static clean
