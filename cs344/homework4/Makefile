CC=gcc
CFLAGS=-Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -g

all: ipdb socket_client socket_server

ipdb: ipdb.o
	$(CC) myipdb.o -o myipdb -lrt

ipdb.o:
	$(CC) -c myipdb.c $(CFLAGS)

socket: socket_client socket_server

socket_client: socket_client.o
	$(CC) socket_client.o -o socket_client -lpthread

socket_client.o:
	$(CC) -c socket_client.c $(CFLAGS)

socket_server: socket_server.o
	$(CC) socket_server.o -o socket_server -lpthread

socket_server.o:
	$(CC) -c socket_server.c $(CFLAGS)



clean:
	rm -rf *.o myipdb *~ *#