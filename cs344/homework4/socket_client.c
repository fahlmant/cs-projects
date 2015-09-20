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

int cmd_handler(char* cmd);

int cmd_handler(char* cmd)
{
	if(strcmp(cmd, CMD_HELP) == 0)
		{
			printf("help stuff here\n");
			return 0;
		}
	else if(strcmp(cmd, CMD_EXIT) == 0)
		{
			printf("Do exit\n");
			return 1;
		}
	else if(strncmp(cmd, CMD_LOCAL_CHDIR, 3) == 0)
		{
			cmd += 4;
			chdir(cmd);
			return 0;
		}
	else if(strcmp(cmd, CMD_LOCAL_DIR) == 0)
		{
			pclose(popen(CMD_LS_POPEN, "w"));
			return 0;
		}
	else if(strcmp(cmd, CMD_LOCAL_PWD) == 0)
		{
			pclose(popen(CMD_PWD, "w"));
			return 0;
		}
	else if(strcmp(cmd, CMD_CHDIR) == 0)
		{
			return 1;
		}
	else if(strcmp(cmd, CMD_CHDIR) == 0)
		{
			return 1;
		}
	else if(strcmp(cmd, CMD_DIR) == 0)
		{
			return 1;
		}
	else if(strcmp(cmd, CMD_PWD) == 0)
		{
			return 1;
		}
	else if(strcmp(cmd, CMD_PUT) == 0)
		{
			return 1;
		}
	else if(strcmp(cmd, CMD_GET) == 0)
		{
			return 1;
		}
	return 2;
}


int main(int argc, char **argv)
{
	int test;
	int check;
	int option;
	int port;
	char *ip;
	int socket_fd;
	struct sockaddr_in server_addr;
	char cmd_buffer[MAXLINE];

	while((option = getopt(argc, argv, "pi")) != -1)
		{
			switch(option)
				{
				case('p'):
					port = atoi(argv[optind]);
					printf("Port: %d\n", port);
					break;
				case('i'):
					ip = argv[optind];
					printf("server ip: %s\n", ip);
					break;
				default:
					break;
				}
		}

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	//connect
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &server_addr.sin_addr);
	test = connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	printf("Test: %d\n", test);
	//talk to server

	for(;;)
		{
			fputs(PROMPT, stdout);
			fgets(cmd_buffer, MAXLINE, stdin);
			
			cmd_buffer[strlen(cmd_buffer) - 1] = 0;
			check = cmd_handler(cmd_buffer);
			if(check == 1)
				{
					write(socket_fd, cmd_buffer, strlen(cmd_buffer));
				}
			else if(check == 2)
				{
					printf("That is not a recogonized command\n");
				}

				memset(cmd_buffer, 0, MAXLINE);
		}
}
