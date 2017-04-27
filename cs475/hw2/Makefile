all: one two four six eight ten

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

six: project2.c
	gcc -DNUMT=6 -DCHUNKTYPE=static -DCHUNKSIZE=1 -o proj2-sixt-s1 -fopenmp project2.c -std=c99
	gcc -DNUMT=6 -DCHUNKTYPE=static -DCHUNKSIZE=4096 -o proj2-sixt-s4096 -fopenmp project2.c -std=c99
	gcc -DNUMT=6 -DCHUNKTYPE=dynamic -DCHUNKSIZE=1 -o proj2-sixt-d1 -fopenmp project2.c -std=c99
	gcc -DNUMT=6 -DCHUNKTYPE=dynamic -DCHUNKSIZE=4096 -o proj2-sixt-d4096 -fopenmp project2.c -std=c99

eight: project2.c
	gcc -DNUMT=8 -DCHUNKTYPE=static -DCHUNKSIZE=1 -o proj2-eightt-s1 -fopenmp project2.c -std=c99
	gcc -DNUMT=8 -DCHUNKTYPE=static -DCHUNKSIZE=4096 -o proj2-eightt-s4096 -fopenmp project2.c -std=c99
	gcc -DNUMT=8 -DCHUNKTYPE=dynamic -DCHUNKSIZE=1 -o proj2-eightt-d1 -fopenmp project2.c -std=c99
	gcc -DNUMT=8 -DCHUNKTYPE=dynamic -DCHUNKSIZE=4096 -o proj2-eightt-d4096 -fopenmp project2.c -std=c99

ten: project2.c
	gcc -DNUMT=10 -DCHUNKTYPE=static -DCHUNKSIZE=1 -o proj2-tent-s1 -fopenmp project2.c -std=c99
	gcc -DNUMT=10 -DCHUNKTYPE=static -DCHUNKSIZE=4096 -o proj2-tent-s4096 -fopenmp project2.c -std=c99
	gcc -DNUMT=10 -DCHUNKTYPE=dynamic -DCHUNKSIZE=1 -o proj2-tent-d1 -fopenmp project2.c -std=c99
	gcc -DNUMT=10 -DCHUNKTYPE=dynamic -DCHUNKSIZE=4096 -o proj2-tent-d4096 -fopenmp project2.c -std=c99


one-tests: one
	./proj2-onet-s1
	./proj2-onet-s4096
	./proj2-onet-d1
	./proj2-onet-d4096

two-tests: two
	./proj2-twot-s1
	./proj2-twot-s4096
	./proj2-twot-d1
	./proj2-twot-d4096

four-tests: four
	./proj2-fourt-s1
	./proj2-fourt-s4096
	./proj2-fourt-d1
	./proj2-fourt-d4096

six-tests: six
	./proj2-sixt-s1
	./proj2-sixt-s4096
	./proj2-sixt-d1
	./proj2-sixt-d4096

eight-tests: eight
	./proj2-eightt-s1
	./proj2-eightt-s4096
	./proj2-eightt-d1
	./proj2-eightt-d4096

ten-tests: ten
	./proj2-tent-s1
	./proj2-tent-s4096
	./proj2-tent-d1
	./proj2-tent-d4096

tests: one-tests two-tests four-tests six-tests eight-tests ten-tests


clean:
	rm -rf proj2-*
