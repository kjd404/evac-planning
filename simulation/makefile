# Copyright 2017 <University of Idaho>
# Compiler
CC = g++

SRCDIR = src
BUILDDIR = generated
INCDIR = include
TARGET = evac
SRCEXT = cpp

SRCS = $(SRCDIR)/*.cpp

# Regular build
CFLAGS = -std=c++11 -pthread -g -O3
# Profiler Build
PCCFLAGS = -std=c++11 -pthread -pg -O3

INC = -I include -I $(BUILDDIR)

$(TARGET): $(SRCDIR)/* $(INCDIR)/*.h $(BUILDDIR)/lex.yy.c $(BUILDDIR)/parser.tab.c
	$(CC) $(CFLAGS) $(INC) -o $(TARGET) $(BUILDDIR)/*.c $(SRCS) -lm

$(BUILDDIR)/lex.yy.c: $(BUILDDIR)/parser.tab.c $(BUILDDIR)/parser.tab.h $(SRCDIR)/grammar/lexer.l
	@mkdir -p $(BUILDDIR)
	flex -o $(BUILDDIR)/lex.yy.c $(SRCDIR)/grammar/lexer.l

$(BUILDDIR)/parser.tab.c: $(SRCDIR)/grammar/parser.y
	@mkdir -p $(BUILDDIR)
	bison -b '$(BUILDDIR)/parser' -d $(SRCDIR)/grammar/parser.y

clean:
	rm -f $(BUILDDIR)/* $(TARGET)
