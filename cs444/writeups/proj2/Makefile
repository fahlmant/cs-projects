CC=gcc
CFLAGS=-Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -g
LATEX=pdflatex

all: latex

commit:
	./gitlog.sh > gitlog.tex

latex: commit
	$(LATEX) writeup.tex

clean:
	rm -rf *.o *~ *.aux *.log *.out
