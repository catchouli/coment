EXECUTABLE=sample

SRCDIR=src
OBJDIR=obj
BINDIR=bin
INCDIR=include

CFLAGS=-c -std=c++11 -Wall -g -O0
LDFLAGS=-lsfml-system -lsfml-window -lsfml-graphics
INCLUDES=-I$(INCDIR) -I../Coment/include
LIBRARIES=../bin/coment.a

SOURCES=$(shell find src -name *.cpp)
OBJECTS=$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
OUTPUT=$(BINDIR)/$(EXECUTABLE)

CC=g++-4.7

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	@mkdir -p bin
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@	
	@cp -R bin/* ../bin/

%.o:
	@mkdir -p obj
	$(CC) $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

.PHONY: all clean

