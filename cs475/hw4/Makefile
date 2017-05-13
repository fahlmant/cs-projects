all: one

one: project4.c
	g++ -o proj4 -lm -fopenmp project4.c  

one-tests: one
	./proj4

clean:
	rm -rf proj4
