all: one two four eight

one: project2.c
	gcc -DNUMT=1 -o proj2-onet -fopenmp project2.c -std=c99

two: project2.c
	gcc -DNUMT=2 -o proj2-twot -fopenmp project2.c -std=c99


four: project2.c
	gcc -DNUMT=4 -o proj2-fourt -fopenmp project2.c -std=c99

eight: project2.c
	gcc -DNUMT=8 -o proj2-eightt -fopenmp project2.c -std=c99

tests: one four
	./proj2-onet
	./proj2-fourt

clean:
	rm -rf proj2-*
