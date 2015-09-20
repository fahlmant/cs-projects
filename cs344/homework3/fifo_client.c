/*
*Name: Taylor Fahlman
*Email: fahlmant@onid.oregonstate.edu
*Class: CS344-001
*Assignment 3
*Resource: man pages, pizza, worked wiht kenoteb
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fifo.h"

int check_input(char* input);

int check_input(char* input)
{
  if(strncmp(CMD_LOCAL_CHDIR, input, 3) == 0)
    {
      input += 4;
      chdir(input);
      return 1;
    }
  else if(strcmp(CMD_LOCAL_DIR, input) == 0)
    {
	  pclose(popen(CMD_LS_POPEN, "w"));
      return 1;
    }
  else if(strcmp(CMD_LOCAL_PWD, input) == 0)
    {
	  pclose(popen(CMD_PWD, "w"));
      return 1;
    }
  else if(strcmp(CMD_HELP, input) == 0)
    {
      printf("help: print this help text\n");
      printf("exit: exit the client, clinet server also exits\n");
      printf("cd <dir> : change the directory of the clinet-server\n");
      printf("lcd <dir> : change the directory of the client\n");
      printf("dir : shows a 'ls -lF' of the server side\n");
      printf("ldir : shows a 'ls -lF' of the client side\n");
      printf("pwd : shows the current directory for the server\n");
      printf("lpwd: shows the current directory for the client\n");
      return 1;
    }
  else if(strcmp(CMD_DIR, input) == 0)
    {
      return 0;
    }
  else if(strcmp(CMD_PWD, input) == 0)
    {
      return 0;
    }
  else if(strcmp(CMD_EXIT, input) == 0)
    {
      return 3;
    }
  // put first two chars in to a temp, compare with cmd_chddir
  else if(strncmp(CMD_CHDIR, input, 2) == 0)
    {
      return 0;
    }
  else
    {
      return 2;
    }
}



int main(int argc, char **argv)
{
  
  char server_fifo_name[256];
  char client_write[256];
  char client_read[256];
  char client_pid[256];
  char cmd_buffer[1000];
  char in_buffer[100000];
  char* cmd_check;
  int server_fd;
  int client_read_fd;
  int client_write_fd;
  int check_flag;
  pid_t pid;
  ssize_t bytes_written;
  ssize_t bytes_read;

  CREATE_SERVER_FIFO_NAME(server_fifo_name);
  server_fd = open(server_fifo_name, O_WRONLY);

  CREATE_CLIENT_WRITER_NAME(client_write, (int)getpid());
  mkfifo(client_write, FIFO_PERMISSIONS);

  CREATE_CLIENT_READER_NAME(client_read, (int)getpid());
  mkfifo(client_read, FIFO_PERMISSIONS);

  pid = getpid();

  sprintf(client_pid, "%d\n", pid);
  write(server_fd, client_pid, 5);

  client_read_fd =  open(client_read, O_RDONLY);
  client_write_fd = open(client_write, O_WRONLY);
 
  for(;;)
    {
      fputs(CLIENT_PROMPT, stdout);
      cmd_check = fgets(cmd_buffer, sizeof(cmd_buffer), stdin);
      if(cmd_check == NULL)
	{
	  break;
	}
      cmd_check[strlen(cmd_check) - 1] = 0;
      check_flag = check_input(cmd_check);
      if(check_flag == 0 || check_flag == 3)
	{
	  bytes_written = write(client_write_fd, cmd_check , strlen(cmd_buffer));
	  bytes_read = read(client_read_fd, in_buffer, sizeof(in_buffer)); 
	  in_buffer[bytes_read] = '\0';
	  printf("%s\n", in_buffer);
	  if(check_flag == 3)
	    {
	      close(client_read_fd);
	      close(client_write_fd);
	      unlink(client_read);
	      unlink(client_write);
	      exit(0);
	    }
	}
      
      else if(check_flag == 2)
	{
	  printf("That is not a recogonized command\n");
	}
      memset(cmd_buffer, 0, 1000);
      memset(in_buffer, 0, 100000);
      fputs("\n", stdout);
    }

  return 0;
}
