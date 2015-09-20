/*Name: Taylor Fahlman
 *Email: fahlmant@onid.oregonstate.edu
 *Class: CS344-001
 *Assignment: 3
 *References: http://stackoverflow.com/questions/2425167/use-of-exit-function
 *http://stackoverflow.com/questions/15883568/reading-from-stdin
 *http://stackoverflow.com/questions/26794310/piping-between-multiple-child-processes
 *http://stackoverflow.com/questions/21002558/redirect-to-execlp
 *http://stackoverflow.com/questions/23497555/using-pipes-to-connect-child-processes
 *http://stackoverflow.com/questions/2605130/redirecting-exec-output-to-a-buffer-or-file
 */





#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char** argv)
{
  pid_t pid;
  int  pipes_1[2];
  int pipes_2[2];
  int pipes_3[2];
  int pipes_4[2];
  pipe(pipes_1);
  pipe(pipes_2);
  pipe(pipes_3);
  pipe(pipes_4);


  switch(pid=fork())
    {
    case 0:
      dup2(pipes_1[1], 1);
      close(pipes_1[0]);
      close(pipes_1[1]);
      close(pipes_2[0]);
      close(pipes_2[1]);
      close(pipes_3[0]);
      close(pipes_3[0]);
      close(pipes_4[0]);
      close(pipes_4[0]);
      if(argc > 1)
	{
	  execlp("sed", "sed","s/[^a-zA-Z]/ /g", argv[1], (char*)NULL);
	}
      else
	{
	  execlp("sed", "sed", "s/[^a-zA-Z]/ /g", (char*)NULL);
	}
      break;

    default:
      break;
    }

  switch(pid = fork())
    {
    case 0:
      dup2(pipes_1[0],0); //copy std onto pipes 2 read
      dup2(pipes_2[1],1);
      close(pipes_3[0]);
      close(pipes_3[1]);
      close(pipes_2[0]);
      close(pipes_2[1]);
      close(pipes_4[0]);
      close(pipes_4[1]);
      close(pipes_1[0]);
      close(pipes_1[1]);
      execlp("tr", "tr", "[A-Z]", "[a-z]", (char*)NULL);

      break;
    default:

      break;
    }
  
  switch(pid=fork())
    {
    case 0:
      dup2(pipes_2[0], 0);
      dup2(pipes_3[1], 1);
      close(pipes_1[0]);
      close(pipes_1[1]);
      close(pipes_2[0]);
      close(pipes_2[1]);
      close(pipes_3[0]);
      close(pipes_3[1]);
      close(pipes_4[0]);
      close(pipes_4[1]);
      execlp("awk", "awk", "{for(i = 1; i <= NF; i++) {print $i;}}", (char*)NULL);
      break;
    default:

      break;
      }

  switch(pid=fork())
    {
    case 0:
      dup2(pipes_3[0], 0);
      dup2(pipes_4[1], 1);
      close(pipes_1[0]);
      close(pipes_1[1]);
      close(pipes_3[0]);
      close(pipes_3[1]);
      close(pipes_4[0]);
      close(pipes_4[1]);
      close(pipes_2[0]);
      close(pipes_2[1]);
      execlp("sort", "sort", (char*)NULL);
    default:
      break;
      }
 
  switch(pid=fork())
    {
    case 0:
      dup2(pipes_4[0], 0);
      close(pipes_1[0]);
      close(pipes_1[1]);
      close(pipes_2[0]);
      close(pipes_2[1]);
      close(pipes_3[0]);
      close(pipes_3[1]);
      close(pipes_4[0]);
      close(pipes_4[1]);
      execlp("uniq", "uniq", "-c", (char*)NULL);
    default:
      break;
    }

  wait(0);
 return 0;
}
