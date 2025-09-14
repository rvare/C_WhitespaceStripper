SRCDIR=./src
OBJDIR=./build
TSTDIR=./tests

CDEBUG=-g -Wall

default: $(SRCDIR)/main.c
	gcc -Wall $(SRCDIR)/main.c -o $(OBJDIR)/a.exe

debug: ./src/main.c
	gcc $(CDEBUG) $(SRCDIR)/main.c -o $(OBJDIR)/a.exe

test: ./build/a.exe
	$(OBJDIR)/a.exe $(TSTDIR)/test1.txt
	$(OBJDIR)/a.exe $(TSTDIR)/test2.txt
	$(OBJDIR)/a.exe $(TSTDIR)/test3.txt
	$(OBJDIR)/a.exe $(TSTDIR)/test4.txt

clean:
	rm a.exe
