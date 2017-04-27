all: one two four eight

one: project2.c
	gcc -DNUMT=1 -DCHUNKTYPE=static -DCHUNKSIZE=1 -o proj2-onet-s1 -fopenmp project2.c -std=c99
	gcc -DNUMT=1 -DCHUNKTYPE=static -DCHUNKSIZE=4096 -o proj2-onet-s4096 -fopenmp project2.c -std=c99
	gcc -DNUMT=1 -DCHUNKTYPE=dynamic -DCHUNKSIZE=1 -o proj2-onet-d1 -fopenmp project2.c -std=c99
	gcc -DNUMT=1 -DCHUNKTYPE=dynamic -DCHUNKSIZE=4096 -o proj2-onet-d4096 -fopenmp project2.c -std=c99

two: project2.c
	gcc -DNUMT=2 -DCHUNKTYPE=static -DCHUNKSIZE=1 -o proj2-twot-s1 -fopenmp project2.c -std=c99
	gcc -DNUMT=2 -DCHUNKTYPE=static -DCHUNKSIZE=4096 -o proj2-twot-s4096 -fopenmp project2.c -std=c99
	gcc -DNUMT=2 -DCHUNKTYPE=dynamic -DCHUNKSIZE=1 -o proj2-twot-d1 -fopenmp project2.c -std=c99
	gcc -DNUMT=2 -DCHUNKTYPE=dynamic -DCHUNKSIZE=4096 -o proj2-twot-d4096 -fopenmp project2.c -std=c99

four: project2.c
	gcc -DNUMT=4 -DCHUNKTYPE=static -DCHUNKSIZE=1 -o proj2-fourt-s1 -fopenmp project2.c -std=c99
	gcc -DNUMT=4 -DCHUNKTYPE=static -DCHUNKSIZE=4096 -o proj2-fourt-s4096 -fopenmp project2.c -std=c99
	gcc -DNUMT=4 -DCHUNKTYPE=dynamic -DCHUNKSIZE=1 -o proj2-fourt-d1 -fopenmp project2.c -std=c99
	gcc -DNUMT=4 -DCHUNKTYPE=dynamic -DCHUNKSIZE=4096 -o proj2-fourt-d4096 -fopenmp project2.c -std=c99

eight: project2.c
	gcc -DNUMT=8 -DCHUNKTYPE=static -DCHUNKSIZE=1 -o proj2-eightt-s1 -fopenmp project2.c -std=c99
	gcc -DNUMT=8 -DCHUNKTYPE=static -DCHUNKSIZE=4096 -o proj2-eightt-s4096 -fopenmp project2.c -std=c99
	gcc -DNUMT=8 -DCHUNKTYPE=dynamic -DCHUNKSIZE=1 -o proj2-eightt-d1 -fopenmp project2.c -std=c99
	gcc -DNUMT=8 -DCHUNKTYPE=dynamic -DCHUNKSIZE=4096 -o proj2-eightt-d4096 -fopenmp project2.c -std=c99

tests: one two four eight
	./proj2-onet
	./proj2-twot
	./proj2-fourt
	./proj2-eightt

clean:
	rm -rf proj2-*
