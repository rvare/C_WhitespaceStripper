SRCDIR=./src
OBJDIR=./build
TSTDIR=./tests

CDEBUG=-g -Wall

default: $(SRCDIR)/main.c
	gcc -Wall $(SRCDIR)/main.c -o $(OBJDIR)/whtstrp

debug: ./src/main.c
	gcc $(CDEBUG) $(SRCDIR)/main.c -o $(OBJDIR)/whtstrp

test: ./build/a.exe
	$(OBJDIR)/whtstrp $(TSTDIR)/test1.txt
	$(OBJDIR)/whtstrp $(TSTDIR)/test2.txt
	$(OBJDIR)/whtstrp $(TSTDIR)/test3.txt
	$(OBJDIR)/whtstrp $(TSTDIR)/test4.txt

clean:
	rm whtstrp
