#Name: Taylor Fahlman
#Email: fahlmant@onid.oregonstate.edu
#Class: CS344-001
#Assignment 3
#Resource: man pages, piazza, worked wiht kenoteb

CC=gcc
CFLAGS=-Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -g

all: fifo_server fifo_client myword_freq

myword_freq: myword_freq.o
	$(CC) myword_freq.o -o myword_freq

myword_freq.o:
	$(CC) -c myword_freq.c $(CFLAGS)

fifo_server: fifo_server.o
	$(CC) fifo_server.o -o fifo_server

fifo_server.o:
	$(CC) -c fifo_server.c $(CFLAGS)

fifo_client: fifo_client.o
	$(CC) fifo_client.o -o fifo_client

fifo_client.o:
	$(CC) -c fifo_client.c $(CFLAGS)

tests:
	rm -rf my_word_test.txt
	rm -rf his_word_test.txt
	./myword_freq jargon.txt > my_word_test.txt
	word_freq.bash jargon.txt > his_word_test.txt
	diff my_word_test.txt his_word_test.txt	
clean:
	rm -rf *.o myword_freq my_word_test.txt his_word_test.txt fifo_client fifo_server ~/Client* ~/Server*

