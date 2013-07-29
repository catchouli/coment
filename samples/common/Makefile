# Build this sample

EXECUTABLE=samples/common/common.a

SRCDIR=src
OBJDIR=obj
BINDIR=bin
INCDIR=include

CXXFLAGS=-c -Wall $(OPTFLAGS) $(DBGFLAG)
LDFLAGS=
INCLUDES=-I$(INCDIR) -I../../coment/include

SOURCES=$(shell find src -name "*.cpp")
OBJECTS=$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: static

static: $(BINDIR)/$(EXECUTABLE)

$(BINDIR)/$(EXECUTABLE): $(OBJECTS)
	@# Create executable directory
	@mkdir -p $(BINDIR)/$(dir $(EXECUTABLE))

	@# Build executable
	@#$(CC) $(LDFLAGS) $(OBJECTS) ../../bin/coment.a -o $@
	$(AR) rcs $@ $(OBJECTS)

	@# Copy to ../bin if existent
	@(test -d ../bin && (cp -R $(BINDIR)/* ../bin/)) || true

obj/%.o: $(SOURCES)
	@# Create directory of object
	@mkdir -p $(dir $@)

	@# Compile
	$(CXX) $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) $(INCLUDES) $(CXXFLAGS) -o $@

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

.PHONY: all static clean
