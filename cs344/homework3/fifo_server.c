/*Name: Taylor Fahlman
 *Email: fahlmant@onid.oregonstate.edu
 *Class: CS344-001 
 *Assignment: 3
 * Resources: Man pages, piazza worked with kenoteb
 */


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "fifo.h"

void test_input(char *input);
void sig_catch(int signal);
void remove_pipes(char *fifo_name);

void test_input(char *input)
{

  if(strncmp(CMD_CHDIR, input, 2) == 0)
    {
      input += 3;
      chdir(input);
    }
  return;
}

void remove_pipes(char *fifo_name)
{
  unlink(fifo_name);
  return;
}

void sig_catch(int sig)
{
  char server_fifo_name[256];
  CREATE_SERVER_FIFO_NAME(server_fifo_name);
  remove_pipes(server_fifo_name);
  kill(0,sig);
  exit(0);
}


int main(int argc, char **argv)
{
  
  char server_fifo_name[256];
  char client_read_name[256];
  char client_write_name[256];
  char in_buffer[10000];
  int server_fd;
  int client_read_fd;
  int client_write_fd;
  char client_pid[256];
  ssize_t bytes_read;
  pid_t pid;
  struct sigaction sig;
  FILE *f;


  sigemptyset(&sig.sa_mask);
  sig.sa_flags = 0;
  sig.sa_handler = sig_catch;

  sigaction(SIGINT, &sig, NULL);


  CREATE_SERVER_FIFO_NAME(server_fifo_name);
  mkfifo(server_fifo_name, FIFO_PERMISSIONS);

  for(;;)
    {

      server_fd = open(server_fifo_name, O_RDONLY);
      bytes_read = read(server_fd, client_pid, sizeof(client_pid)); 

      pid = fork();
      if(pid == 0)
	{

	  CREATE_CLIENT_READER_NAME(client_read_name, atoi(client_pid));
	  CREATE_CLIENT_WRITER_NAME(client_write_name, atoi(client_pid));

	  client_read_fd = open(client_read_name, O_WRONLY);
	  client_write_fd = open(client_write_name, O_RDONLY);
	  for(;;)
	    {
	      bytes_read = read(client_write_fd, in_buffer, sizeof(in_buffer));
	      if(bytes_read == 0)
		{
		  break;
		}
	      in_buffer[bytes_read] = 0;
	      if(strcmp(CMD_DIR, in_buffer) == 0)
		{
		  f = popen(CMD_LS_POPEN, "r");
		  fread(in_buffer, 1, 100000, f); 
		}
	      else if(strcmp(CMD_PWD, in_buffer) == 0)
		{
		  f = popen(CMD_PWD, "r");
		  fgets(in_buffer, 100000, f);
		}
	      else if(strcmp(CMD_EXIT, in_buffer) == 0)
		{
		  exit(0);
		}
	      else
		{
		  test_input(in_buffer);

		}
	      write(client_read_fd, in_buffer, 100000);
	    }
	}
    }
}
