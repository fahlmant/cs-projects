#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <signal.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "ipdb.h"

struct table{

	int count;
	sem_t table_lock;
	ip_row_t data_table[MAX_ROWS];
};

void sig_catch(int sig);
void cmd_handle(char *cmd, struct table* data);
void fetch(char *cmd, struct table* data, int flag);
void show(struct table* data);
void clear_table(struct table * data);
void check_table(char *cmd, struct table* data);
void help(char *cmd);
void lock_row(char* cmd, struct table* data);
void unlock_row(struct table* data);
void lock_table(struct table* data);
void unlock_table(struct table* data);
void save(char* cmd, struct table* data);
void load(char* cmd, struct table* data);

void load(char* cmd, struct table* data)
{
	int fd;
	char buffer[NAME_SIZE];
	int i = 0;
	cmd += 5;
	cmd[strlen(cmd)] = '\0';
	
	fd = open(cmd, O_RDONLY);
	while((read(fd, buffer, 1) > 0))
		{
			lseek(fd, -1, SEEK_CUR);
			memset(buffer, ' ', NAME_SIZE);
			read(fd, buffer, NAME_SIZE);
			for(; i < NAME_SIZE; i++)
				{
					if(buffer[i] == ' ')
						{
							buffer[i] = '\0';
						}
						
				}
			fetch(buffer, data, 1);
			lseek(fd, 1, SEEK_CUR);
		}
}

void save(char* cmd, struct table* data)
{
	int fd;
	int i = 0;
	int j = 0;
	char buffer[NAME_SIZE];
	
	cmd += 5;
	cmd[strlen(cmd)] = '\0';

	fd = open(cmd, O_CREAT | O_WRONLY, 0666);
	sem_wait(&(data->table_lock));
	for(; i < data-> count; i++)
		{
			sem_wait(&(data->data_table[i].row_lock));
			memset(buffer, ' ', NAME_SIZE);
			strcpy(buffer, data->data_table[i].row_name);
			for(; j < NAME_SIZE; j++)
				{
					if(buffer[j] == '\0')
						{
							buffer[j] = ' ';
						}
				}
			write(fd, buffer, NAME_SIZE);
			write(fd, "\n", 1);
			sem_post(&(data->data_table[i].row_lock));
		}
}

void unlock_table(struct table* data)
{
	sem_post(&(data->table_lock));
}

void lock_table(struct table* data)
{
	sem_wait(&(data->table_lock));
}

void unlock_row(struct table* data)
{
	int i = 0;
	sem_wait(&(data->table_lock));
	for(; i < data->count; i ++)
		{
			sem_post(&(data->data_table[i].row_lock));
		}
	sem_post(&(data->table_lock));
			
}


void lock_row(char* cmd, struct table* data)
{
	int i = 0;
	ip_row_t local_row;

	cmd += 9;
	cmd[strlen(cmd)] = '\0';
	strcpy(local_row.row_name, cmd);

	sem_wait(&(data->table_lock));
	for(; i < data->count; i++)
	{
		if(strcmp(local_row.row_name, data->data_table[i].row_name) == 0)
			{
				sem_wait(&(data->data_table[i].row_lock));
				i = data->count + 1;
			}
	}
	sem_post(&(data->table_lock));
}

void help(char *cmd)
{
	printf("Help:                  Prints this text\n");
	printf("Exit:                  Closes the program and removes shared memory in /dev/shm\n");
	printf("Fetch <hostname>:      Gets the IPv4 (and IPv6 if applicable) of the hostname and stores it in the database\n");
	printf("Check <hostname>:      Check if the given hostname is in the database\n");
	printf("Show:                  shows the contents of the database\n");
	printf("Save <filename>:       Saves contents of the database to a file specified by filename\n");
	printf("Load <filename>:       Loads contents of the file at filename into the database\n");
	printf("Clear:                 Removes all contents of the table\n");
	printf("lock_table:            locks the table until an unlock command is given\n");
	printf("unlock_table:          unlocks the table if locked\n");
	printf("lock_row <hostname>:   locks a given row until unlock command is given\n");
	printf("unlock_row <hostname>: unlocks given row if locked\n"); 
}

void clear_table(struct table* data)
{
	//delete all information in table
	int i = 0;
	sem_wait(&(data->table_lock));
	for(; i < data->count; i++)
		{
			memset(data->data_table[i].row_name, 0, NAME_SIZE);
			memset(data->data_table[i].row_address4, 0, NAME_SIZE);
			memset(data->data_table[i].row_address6, 0, NAME_SIZE);
			sem_destroy(&(data->data_table[i].row_lock));
		}
	data->count = 0;
	sem_post(&(data->table_lock));
}

void check_table(char *cmd, struct table* data)
{
	//check for the give hostname
	int i = 0;
	int test = 0;
	ip_row_t local_row;

	cmd += 6;
	cmd[strlen(cmd)] = '\0';
	strcpy(local_row.row_name, cmd);
	
	sem_wait(&(data->table_lock));
	for(; i < data->count; i++)
		{
			if(strncmp(local_row.row_name, data->data_table[i].row_name, strlen(local_row.row_name)) == 0)
				{ 
					sem_wait(&(data->data_table[i].row_lock));
					printf("Name: %s    IPv4: %s    IPv6: %s\n", data->data_table[i].row_name, data->data_table[i].row_address4, data->data_table[i].row_address6);
					sem_post(&(data->data_table[i].row_lock));
					test = 1;
				}
		}
	sem_post(&(data->table_lock));
	if(test != 1)
		{
			printf("This host was not found in the database\n");
		}

}

 void fetch(char *cmd, struct table* data, int flag)
{
   
	struct ip_row row; 
	struct ip_row test_row;
	struct addrinfo hints, *res, *p;
	int status, ip4 = 0, ip6 = 0;
	char ipstr[INET6_ADDRSTRLEN];
	int i = 0;
	int test = 0;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if(flag == 0)
		{
			cmd += 6;
			cmd[strlen(cmd)] = '\0';
		}
	strcpy(test_row.row_name, cmd);
	sem_wait(&(data->table_lock));
	for(; i < data->count; i++)
		{
			if(strcmp(test_row.row_name, data->data_table[i].row_name) == 0)
				{
					test = 1;
				}
		}

	status = getaddrinfo(cmd, NULL, &hints, &res);
	if(test != 1)
		{
			for(p = res; p != NULL; p = p->ai_next)
				{
					void *addr;
					if(p->ai_family == AF_INET && ip4 == 0)
						{
							struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
							addr = &(ipv4->sin_addr);
							inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
							ip4 = 1;
							memcpy(data->data_table[data->count].row_address4, ipstr, NAME_SIZE);
						}
					else if(p->ai_family != AF_INET && ip6 == 0)
						{
							struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
							addr = &(ipv6->sin6_addr);
							inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
							ip6 = 1;
							memcpy(data->data_table[data->count].row_address6, ipstr, NAME_SIZE);
						}
					
					
				}
		   
			strcpy(row.row_name, cmd);
			memcpy(data->data_table[data->count].row_name, row.row_name, NAME_SIZE);
			sem_init(&(data->data_table[data->count].row_lock), 1, 1);
			data->count += 1;
		}
	sem_post(&(data->table_lock));
	freeaddrinfo(res);
		                          
}

void show(struct table* data)
{
	int i = 0;
	int test;
	sem_wait(&(data->table_lock));
	for(; i < data->count; i++)
		{
			test = sem_wait(&(data->data_table[i].row_lock));
			printf("Name: %s     IPv4: %s      IPv6: %s\n", data->data_table[i].row_name, data->data_table[i].row_address4, data->data_table[i].row_address6);
			test = sem_post(&(data->data_table[i].row_lock));
		}
	sem_post(&(data->table_lock));
}

void cmd_handle(char *cmd, struct table* data)
{
	char shm_name[NAME_SIZE];
  if(strcmp(CMD_HELP, cmd) == 0)
    {
      help(cmd);
    }
  else if(strcmp(CMD_EXIT, cmd) == 0)
    {
	    SHARED_MEM_NAME(shm_name);
	    shm_unlink(shm_name);
	    exit(0);
    }
  else if(strncmp(CMD_FETCH, cmd, 5) == 0)
	  {
		  fetch(cmd, data, 0);
		  
	  }
  else if(strncmp(CMD_CHECK, cmd, 5) == 0)
	  {
		  check_table(cmd, data);
	  }
  else if(strcmp(CMD_SHOW, cmd) == 0)
	  {
		  show(data);
	  }
  else if(strncmp(CMD_SAVE, cmd, 4) == 0)
	  {
		  save(cmd, data);
	  }
  else if(strncmp(CMD_LOAD, cmd, 4) == 0)
	  {
		  load(cmd, data);
	  }
  else if(strcmp(CMD_CLEAR, cmd) == 0)
	  {
		  clear_table(data);
	  }
  else if(strcmp(CMD_LOCK_TABLE, cmd) == 0)
	  {
		  lock_table(data);
	  }
  else if(strcmp(CMD_UNLOCK_TABLE, cmd) == 0)
	  {
		  unlock_table(data);
	  }
  else if(strncmp(CMD_LOCK_ROW, cmd, 8) == 0)
	  {
		  lock_row(cmd, data);
	  }
  else if(strcmp(CMD_UNLOCK_ROW, cmd) == 0)
	  {
		  unlock_row(data);
	  }
  else
	  {
		  printf("This is not a recogonized command\n");
	  }

}

void sig_catch(int sig)
{
  char shm_name[NAME_SIZE];
  SHARED_MEM_NAME(shm_name);
  shm_unlink(shm_name);
  kill(0,sig);
  exit(0);
}

int main(int argc, char **argv)
{
  int shm_fd;
  char shm_name[NAME_SIZE];
  char cmd_buffer[1000];
  struct sigaction sig;
  struct table* data;
  

  sigemptyset(&sig.sa_mask);
  sig.sa_flags = 0;
  sig.sa_handler = sig_catch;

  sigaction(SIGINT, &sig, NULL);

  SHARED_MEM_NAME(shm_name);
  


  shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP);
  ftruncate(shm_fd, MAX_ROWS*sizeof(struct table));
  data = (struct table*)mmap(NULL, sizeof(struct table), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0
);
  if(access(shm_name, F_OK) != 0)
	  {
		  sem_init(&(data->table_lock), 1, 1);
	  }
 
 for(;;)
    {
      fputs(PROMPT, stdout);
      fgets(cmd_buffer, sizeof(cmd_buffer), stdin);
      cmd_buffer[strlen(cmd_buffer) - 1] = 0;
      cmd_handle(cmd_buffer, data);
    }

}
