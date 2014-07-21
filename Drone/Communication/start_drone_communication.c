#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <string>

int main(int argc, char *argv[])
{
  int file_descriptor_tab[4];
  pid_t pid;
  char buf;

  if (pipe(file_descriptor_tab) == -1)
    {
      exit(EXIT_FAILURE);
    }

  if (pipe(&(file_descriptor_tab[2])) == -1)
    {
      exit(EXIT_FAILURE);
    }

  pid = fork();

  if (pid == -1)
  {
    exit(EXIT_FAILURE);
  }

  if (pid == 0)
  {
    dup2(file_descriptor_tab[0], STDIN_FILENO);
    dup2(file_descriptor_tab[3], STDOUT_FILENO);

    //close(file_descriptor_tab[1]);
    //close(file_descriptor_tab[2]);
 
    execl("/bin/sh", "sh", "-c", "python communication.py", NULL);

    close(file_descriptor_tab[0]);
    close(file_descriptor_tab[3]);
    
    exit(EXIT_SUCCESS);
    
  }
  else
  {
      pid = fork();

      if (pid == -1)
	{
	  exit(EXIT_FAILURE);
	}

        if (pid == 0)
	  {

	    while(1)
	      {
		write(file_descriptor_tab[1], "X#", 2); // Envoie des instructions
	      }
	  }
	else
	  {
	    
	    while (read(file_descriptor_tab[2], &buf, 1) > 0)
	      {
		write(STDOUT_FILENO, "_", 1);
		write(STDOUT_FILENO, &buf, 1);
		write(STDOUT_FILENO, "_", 1);
	      }

	    wait(NULL);
	  }

    wait(NULL);
    
    close(file_descriptor_tab[0]);
    close(file_descriptor_tab[1]);
    close(file_descriptor_tab[2]);
    close(file_descriptor_tab[3]);

    exit(EXIT_SUCCESS);
  }
}
