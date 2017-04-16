all: one four

one: project1.c
	gcc -DNUMT=1 -o proj1-onet -fopenmp project1.c -std=c99

four: project1.c
	gcc -DNUMT=4 -o proj1-fourt -fopenmp project1.c -std=c99

tests: one four
	./proj1-onet
	./proj1-fourt

clean:
	rm -rf proj1-*
