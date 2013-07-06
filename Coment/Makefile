BINARY=coment

SRCDIR=src
OBJDIR=obj
BINDIR=bin
INCDIR=include

CFLAGS=-c -std=c++11 -Wall -g -O0
INCLUDES=-I$(INCDIR)

SOURCES=$(shell find src -name *.cpp)
OBJECTS=$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
OUTPUT_OBJ=$(OBJDIR)/$(BINARY).o
OUTPUT=$(BINDIR)/$(BINARY).a

CC=g++-4.7

all: $(SOURCES) $(OUTPUT_OBJ)

$(OUTPUT_OBJ): $(OBJECTS)
	@mkdir -p bin
	$(AR) rcs $(OUTPUT) $(OBJECTS)
	@cp -R bin/* ../bin/

%.o:
	@mkdir -p obj
	@mkdir -p $(dir $@)
	$(CC) $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

.PHONY: all clean

