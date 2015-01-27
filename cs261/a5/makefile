all: prog prog2

prog: dynamicArray.o main.o toDoList.o
	gcc -g -Wall -std=c99 -o prog dynamicArray.o toDoList.o main.o
	
main.o: main.c dynamicArray.h toDoList.h
	gcc -g -Wall -std=c99 -c main.c
	
dynamicArray.o: dynamicArray.c dynamicArray.h
	gcc -g -Wall -std=c99 -c dynamicArray.c
	
toDoList.o: toDoList.c toDoList.h
	gcc -g -Wall -std=c99 -c toDoList.c

prog2: dynamicArray.o main2.o toDoList.o
	gcc -g -Wall -std=c99 -o prog2 dynamicArray.o toDoList.o main2.o
	
main2.o: main2.c dynamicArray.h toDoList.h
	gcc -g -Wall -std=c99 -c main2.c
	

	


clean:	
	rm dynamicArray.o
	rm toDoList.o
	rm main.o
	rm main2.o
	rm prog
