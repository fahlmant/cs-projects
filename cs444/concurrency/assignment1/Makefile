CC=gcc
CFLAGS=-Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -g
LATEX=pdflatex

all: assignment1 latex

assignment1: assignment1.o
	$(CC) assignment1.o -o a1 -pthread

assignment1.o:
	$(CC) -c assignment1.c $(CFLAGS)

commit:
	./gitlog.sh > gitlog.tex

latex: commit
	$(LATEX) writeup.tex

clean:
	rm -rf *.o a1 *~ *.aux *.log *.out
