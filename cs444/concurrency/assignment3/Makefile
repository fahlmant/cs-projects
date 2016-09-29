CC=gcc
CFLAGS=-Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -g
LATEX=pdflatex

all: assignment3

assignment3: assignment3.o
	$(CC) assignment3.o -o a3 -pthread

assignment3.o:
	$(CC) -c assignment3.c $(CFLAGS)

commit:
	./gitlog.sh > gitlog.tex

latex: commit
	$(LATEX) writeup.tex

clean:
	rm -rf *.o a3 *~ *.aux *.log *.out
