# Build this sample

EXECUTABLE=sample

SHARED_OUTPUT=$(EXECUTABLE)-shared
STATIC_OUTPUT=$(EXECUTABLE)-static

SRCDIR=src
OBJDIR=obj
BINDIR=bin
INCDIR=include

CFLAGS=-c -std=c++11 -Wall -O2
LDFLAGS=-lsfml-system -lsfml-window -lsfml-graphics
INCLUDES=-I$(INCDIR) -I../Coment/include

SOURCES=$(shell find src -name *.cpp)
OBJECTS=$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: static shared

shared: $(SOURCES) bin/$(SHARED_OUTPUT)

static: $(SOURCES) bin/$(STATIC_OUTPUT)

bin/$(SHARED_OUTPUT): $(OBJECTS)
	@mkdir -p bin
	@mkdir -p ../bin
	$(CXX) $(LDFLAGS) -L../bin -lcoment $(OBJECTS) -o $@
	@cp -R bin/* ../bin/

bin/$(STATIC_OUTPUT): $(OBJECTS)
	@mkdir -p bin
	@mkdir -p ../bin
	$(CXX) $(LDFLAGS) $(OBJECTS) ../bin/coment.a -o $@
	@cp -R bin/* ../bin/	

%.o: $(SOURCES)
	@mkdir -p obj
	$(CXX) $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) $(INCLUDES) $(CFLAGS) -o $@

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

.PHONY: all shared static clean
