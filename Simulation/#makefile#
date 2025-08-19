# Copyright 2017 <University of Idaho>
# Compiler
CC = g++

SRCDIR = src
BUILDDIR = build
INCDIR = include
TARGET = evac
SRCEXT = cpp

SRCS = $(SRCDIR)/*.cpp

# Regular build
CFLAGS = -std=c++11 -pthread -g -O3
# Profiler Build
PCCFLAGS = -std=c++11 -pthread -pg -O3

INC = -I include -I build

$(TARGET): $(SRCDIR)/* $(INCDIR)/*.h $(BUILDDIR)/lex.yy.c $(BUILDDIR)/parser.tab.c
	$(CC) $(CFLAGS) $(INC) -o $(TARGET) $(BUILDDIR)/*.c $(SRCS) -lm

build/lex.yy.c: $(BUILDDIR)/parser.tab.c $(BUILDDIR)/parser.tab.h $(SRCDIR)/lexer.l
	flex -o $(BUILDDIR)/lex.yy.c $(SRCDIR)/lexer.l

build/parser.tab.c: $(SRCDIR)/parser.y
	bison -b '$(BUILDDIR)/parser' -d $(SRCDIR)/parser.y

clean:
	rm $(BUILDDIR)/* $(TARGET)

