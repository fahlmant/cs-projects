all: one two four eight

one: project1.c
	gcc -DNUMT=1 -DNUMNODES=100 -o proj1-onet-onehund -fopenmp project1.c -std=c99
	gcc -DNUMT=1 -DNUMNODES=250 -o proj1-onet-twofifty -fopenmp project1.c -std=c99
	gcc -DNUMT=1 -DNUMNODES=500 -o proj1-onet-fivehund -fopenmp project1.c -std=c99
	gcc -DNUMT=1 -DNUMNODES=1000 -o proj1-onet-onethou -fopenmp project1.c -std=c99
	gcc -DNUMT=1 -DNUMNODES=2000 -o proj1-onet-twothou -fopenmp project1.c -std=c99
	gcc -DNUMT=1 -DNUMNODES=3000 -o proj1-onet-threethou -fopenmp project1.c -std=c99
	gcc -DNUMT=1 -DNUMNODES=5000 -o proj1-onet-fivethou -fopenmp project1.c -std=c99
	gcc -DNUMT=1 -DNUMNODES=6000 -o proj1-onet-sixthou -fopenmp project1.c -std=c99

two: project1.c
	gcc -DNUMT=2  -DNUMNODES=100 -o proj1-twot-onehund -fopenmp project1.c -std=c99
	gcc -DNUMT=2  -DNUMNODES=250 -o proj1-twot-twofifty -fopenmp project1.c -std=c99
	gcc -DNUMT=2  -DNUMNODES=500 -o proj1-twot-fivehund -fopenmp project1.c -std=c99
	gcc -DNUMT=2  -DNUMNODES=1000 -o proj1-twot-onethou -fopenmp project1.c -std=c99
	gcc -DNUMT=2  -DNUMNODES=2000 -o proj1-twot-twothou -fopenmp project1.c -std=c99
	gcc -DNUMT=2  -DNUMNODES=3000 -o proj1-twot-threethou -fopenmp project1.c -std=c99
	gcc -DNUMT=2  -DNUMNODES=5000 -o proj1-twot-fivethou -fopenmp project1.c -std=c99
	gcc -DNUMT=2  -DNUMNODES=6000 -o proj1-twot-sixthou -fopenmp project1.c -std=c99

four: project1.c
	gcc -DNUMT=4 -DNUMNODES=100 -o proj1-fourt-onehund -fopenmp project1.c -std=c99
	gcc -DNUMT=4 -DNUMNODES=250 -o proj1-fourt-twofifty -fopenmp project1.c -std=c99
	gcc -DNUMT=4 -DNUMNODES=500 -o proj1-fourt-fivehund -fopenmp project1.c -std=c99
	gcc -DNUMT=4 -DNUMNODES=1000 -o proj1-fourt-onethou -fopenmp project1.c -std=c99
	gcc -DNUMT=4 -DNUMNODES=2000 -o proj1-fourt-twothou -fopenmp project1.c -std=c99
	gcc -DNUMT=4 -DNUMNODES=3000 -o proj1-fourt-threethou -fopenmp project1.c -std=c99
	gcc -DNUMT=4 -DNUMNODES=5000 -o proj1-fourt-fivethou -fopenmp project1.c -std=c99
	gcc -DNUMT=4 -DNUMNODES=6000 -o proj1-fourt-sixthou -fopenmp project1.c -std=c99

eight: project1.c
	gcc -DNUMT=8 -DNUMNODES=100 -o proj1-eightt-onehund -fopenmp project1.c -std=c99
	gcc -DNUMT=8 -DNUMNODES=250 -o proj1-eightt-twofifty -fopenmp project1.c -std=c99
	gcc -DNUMT=8 -DNUMNODES=500 -o proj1-eightt-threehund -fopenmp project1.c -std=c99
	gcc -DNUMT=8 -DNUMNODES=1000 -o proj1-eightt-onethou -fopenmp project1.c -std=c99
	gcc -DNUMT=8 -DNUMNODES=2000 -o proj1-eightt-twothou -fopenmp project1.c -std=c99
	gcc -DNUMT=8 -DNUMNODES=3000 -o proj1-eightt-threethou -fopenmp project1.c -std=c99
	gcc -DNUMT=8 -DNUMNODES=5000 -o proj1-eightt-fivethou -fopenmp project1.c -std=c99
	gcc -DNUMT=8 -DNUMNODES=6000 -o proj1-eightt-sixthou -fopenmp project1.c -std=c99

tests: one two four eight
	./proj1-onet-onehund
	./proj1-onet-twofifty
	./proj1-onet-fivehund
	./proj1-onet-onethou
	./proj1-onet-twothou
	./proj1-onet-threethou
	./proj1-onet-fivethou
	./proj1-onet-sixthou
	./proj1-twot-onehund
	./proj1-twot-twofifty
	./proj1-twot-fivehund
	./proj1-twot-onethou
	./proj1-twot-twothou
	./proj1-twot-threethou
	./proj1-twot-fivethou
	./proj1-twot-sixthou
	./proj1-fourt-onehund
	./proj1-fourt-twofifty
	./proj1-fourt-fivehund
	./proj1-fourt-onethou
	./proj1-fourt-twothou
	./proj1-fourt-threethou
	./proj1-fourt-fivethou
	./proj1-fourt-sixthou
	./proj1-eightt-onehund
	./proj1-eightt-twofifty
	./proj1-eightt-threehund
	./proj1-eightt-onethou
	./proj1-eightt-twothou
	./proj1-eightt-threethou
	./proj1-eightt-fivethou
	./proj1-eightt-sixthou

clean:
	rm -rf proj1-*
