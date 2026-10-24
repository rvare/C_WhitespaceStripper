SRCDIR=./src
OBJDIR=./build
TSTDIR=./tests

# Change to your specific compiler
CC=gcc -Wall
CDEBUG=gcc -g -Wall

default: $(SRCDIR)/main.c
	$(CC) $(SRCDIR)/main.c -o $(OBJDIR)/whtstrp

debug: ./src/main.c
	$(CDEBUG) $(SRCDIR)/main.c -o $(OBJDIR)/whtstrp

