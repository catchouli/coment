# Build this sample

EXECUTABLE=samples/balls/balls

SHARED_OUTPUT=$(EXECUTABLE)-shared
STATIC_OUTPUT=$(EXECUTABLE)-static

SRCDIR=src
OBJDIR=obj
BINDIR=bin
INCDIR=include

CXXFLAGS=-c -Wall $(OPTFLAGS) $(DBGFLAG)
LDFLAGS=-lSDL2
INCLUDES=-I$(INCDIR) -I../../coment/include

SOURCES=$(shell find src -name "*.cpp")
OBJECTS=$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: shared static

shared: $(BINDIR)/$(SHARED_OUTPUT)

static: $(BINDIR)/$(STATIC_OUTPUT)

$(BINDIR)/$(SHARED_OUTPUT): $(OBJECTS)
	@# Create executable directory
	@mkdir -p $(BINDIR)/$(dir $(EXECUTABLE))

	@# Build executable
	$(CXX) $(LDFLAGS) -L../../bin -lcoment $(OBJECTS) -o $@

	@# Copy to ../bin if existent
	test -d ../bin && cp -R $(BINDIR)/* ../bin/

$(BINDIR)/$(STATIC_OUTPUT): $(OBJECTS)
	@# Create executable directory
	@mkdir -p $(BINDIR)/$(dir $(EXECUTABLE))

	@# Build executable
	$(CXX) $(LDFLAGS) $(OBJECTS) ../../bin/coment.a -o $@

	@# Copy to ../bin if existent
	@test -d ../bin && cp -R $(BINDIR)/* ../bin/

obj/%.o: $(SOURCES)
	@# Create directory of object
	@mkdir -p $(dir $@)

	@# Compile
	$(CXX) $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) $(INCLUDES) $(CXXFLAGS) -o $@

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

.PHONY: all shared static clean
