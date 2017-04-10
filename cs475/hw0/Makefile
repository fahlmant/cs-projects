all: one four

one: project0.c
	gcc -DNUMT=1 -o proj0-onet -fopenmp project0.c -std=c99

four: project0.c
	gcc -DNUMT=4 -o proj0-fourt -fopenmp project0.c -std=c99

tests: one four
	./proj0-onet
	./proj0-fourt

clean:
	rm -rf proj0-*
