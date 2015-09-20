# *Name: Taylor Fahlman
# *Email: fahlmant@onid.oregonstate.edu
# *Class: CS344-001
# *Assignment #2
# *EXTRA CREDIT IS ATTEMPTED

all: myoscar

myoscar: oscar.o
	gcc oscar.o -o myoscar

oscar.o: oscar.c
	gcc -c oscar.c -g

tests: testa testT

testa12345:
	rm -rf oscar12345.oscar
	rm -rf myoscar12345.oscar
	./oscar -a oscar12345.oscar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	./myoscar -a myoscar12345.oscar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	diff oscar12345.oscar myoscar12345.oscar

testa135:
	rm -rf oscar135.oscar
	rm -rf myoscar135.oscar
	./oscar -a oscar135.oscar 1-s.txt 3-s.txt 5-s.txt
	./myoscar -a myoscar135.oscar 1-s.txt 3-s.txt 5-s.txt
	diff oscar135.oscar myoscar135.oscar

testa24:
	rm -rf oscar24.oscar
	rm -rf myoscar24.oscar
	./oscar -a oscar24.oscar 2-s.txt 4-s.txt
	./myoscar -a myoscar24.oscar 2-s.txt 4-s.txt
	diff oscar24.oscar myoscar24.oscar

testa: testa12345 testa135 testa24 

testT12345:
	rm -rf oscar12345.oscar
	./oscar -a oscar12345.oscar 1-s.txt 2-s.txt 3-s.txt 4-s.txt 5-s.txt
	./oscar -T oscar12345.oscar > oscar-ltoc.txt
	./myoscar -T oscar12345.oscar > myoscar-ltoc.txt
	diff oscar-ltoc.txt myoscar-ltoc.txt

testT135:
	rm -rf oscar135.oscar
	./oscar -a oscar135.oscar 1-s.txt 3-s.txt 5-s.txt
	./oscar -T oscar135.oscar > oscar-ltoc.txt
	./myoscar -T oscar135.oscar > myoscar-ltoc.txt
	diff oscar-ltoc.txt myoscar-ltoc.txt

testT24:
	rm -rf oscar24.oscar
	./oscar -a oscar24.oscar 2-s.txt 4-s.txt
	./oscar -T oscar24.oscar > oscar-ltoc.txt
	./myoscar -T oscar24.oscar > myoscar-ltoc.txt
	diff oscar-ltoc.txt myoscar-ltoc.txt

testT: testT12345 testT135 testT24



rmoscar:
	rm -rf *.oscar
clean:
	rm -rf myoscar *.o *# '~*' 
