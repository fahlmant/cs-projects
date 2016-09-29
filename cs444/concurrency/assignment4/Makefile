CC=gcc
CFLAGS=-Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -g
LATEX=pdflatex

all: assignment4part1 assignment4part2

assignment4part2: assignment4part2.o
	$(CC) assignment4part2.o -o a4part2 -lpthread

assignment4part2.o:
	$(CC) -c assignment4part2.c $(CFLAGS)

assignment4part1: assignment4part1.o
	$(CC) assignment4part1.o -o a4part1 -lpthread

assignment4part1.o:
	$(CC) -c assignment4part1.c $(CFLAGS)

commit:
	./gitlog.sh > gitlog.tex

latex: commit
	$(LATEX) writeup.tex

clean:
	rm -rf *.o a4* *~ *.aux *.log *.out
