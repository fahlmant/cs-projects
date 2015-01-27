all: prog prog2

prog: bst.o compare.o
	gcc -g -Wall -std=c99 -o prog bst.o compare.o
	
prog2: bst.o compare2.o
	gcc -g -Wall -std=c99 -o prog2 bst.o compare2.o

compare.o: compare.c
	gcc -g -Wall -std=c99 -c compare.c
	
compare2.o: compare2.c
	gcc -g -Wall -std=c99 -c compare2.c
		
bst.o: bst.c bst.h
	gcc -g -Wall -std=c99 -c bst.c

clean:	
	rm bst.o
	rm compare.o
	rm compare2.o
	rm prog
