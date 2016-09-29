CC=gcc
CFLAGS=-Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -g
LATEX=pdflatex

all: assignment2

assignment2: assignment2.o
	$(CC) assignment2.o -o a2 -pthread

assignment2.o:
	$(CC) -c assignment2.c $(CFLAGS)

commit:
	./gitlog.sh > gitlog.tex

latex: commit
	$(LATEX) writeup.tex

clean:
	rm -rf *.o a2 *~ *.aux *.log *.out
