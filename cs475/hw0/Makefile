all: one four

one: project0.c
	gcc -DNUMT=1 -o proj0-onet -fopenmp project0.c

four: project0.c
	gcc -DNUMT=4 -o proj0-fourt -fopenmp project0.c

clean:
	rm -rf proj0-*
