#include <unistd.h>
#include <stdlib.h>
#include "socket_hdr.h"
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>

void server(void *in);

void server(void *in)
{
	printf("connected\n");
}

int main(int argc, char **argv)
{
	int option;
	int port;
	int socket_fd;
	int listen_fd; 
	socklen_t client_size;
	char cmd_buffer[MAXLINE];
	struct sockaddr_in client_addr;
	struct sockaddr_in server_addr;
	pthread_t *thread = NULL; 
	void *func = server;

	while((option = getopt(argc, argv, "p")) != -1)
		{
			switch(option)
				{
				case('p'):
					port = atoi(argv[optind]);
				}
		}

	printf("Port %d\n", port);


	listen_fd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);

	bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
	listen(listen_fd, LISTENQ);
	
	client_size = sizeof(client_addr);
	socket_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_size);

	//	pthread_create(thread, NULL, func, NULL);

	for(;;)
		{
			memset(cmd_buffer, 0, MAXLINE);
			//		pthread_create(thread, NULL, func, NULL);
			
			read(socket_fd, cmd_buffer, MAXLINE);
			cmd_buffer[strlen(cmd_buffer)] = 0;
			printf("%s\n", cmd_buffer);
			//talk to client
			//for(;;)
				//{
					
					//				}
		}
}
