#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <string>

#include "linked_lists_lib/my_list.h"

int * pipe_tab_initialisation();

int * pipe_tab_initialisation()
{
  int file_descriptor_tab[8];

   // PIPES VERS ARDUINO :

  if (pipe(file_descriptor_tab) == -1)
    {
      exit(EXIT_FAILURE);
    }

  if (pipe(&(file_descriptor_tab[2])) == -1)
    {
      exit(EXIT_FAILURE);
    }

  // PIPES VERS CLIENT :

  if (pipe(&(file_descriptor_tab[4])) == -1)
    {
      exit(EXIT_FAILURE);
    }

  if (pipe(&(file_descriptor_tab[6])) == -1)
    {
      exit(EXIT_FAILURE);
    }

  return (file_descriptor_tab);
}

int main(int argc, char *argv[])
{
  int *file_descriptor_tab = malloc(sizeof(int) * 8); // UNE SERIE DE 2 PIPES VERS ARDUINO, UNE SERIE DE 2 PIPES VERS LE CLIENT

  pid_t pid;
  char buf;

  file_descriptor_tab = pipe_tab_initialisation();

  // DIVISION DES PROCESSUS :

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
	    // On lance le client

	    execl("/bin/sh", "client_drone", "127.0.0.1", "client_drone#01", file_descriptor_tab[4]); // parametre : file_descriptor_tab[4] 

	  }
	else
	  {
	    // Gestion des informations de vol

	    // creation de la boucle de lecture

	    t_mylist        * pointer;
	    int i;

	    for (pointer = my_put_in_list(0, ' '), i = 0; i < 20; i++)
	      {
		pointer = my_put_in_list(pointer, ' ');
	      }
	    
	    t_mylist        * begin;
	    for (begin = pointer; begin->next; begin = begin->next);

	    begin->next = pointer;
	    pointer->prev = begin;
	    
	    //

	    fd_set rdfs;

	    int max_fd;
	    
	    if (file_descriptor_tab[2] < file_descriptor_tab[5])
	      max_fd = file_descriptor_tab[5] + 1;
	    else
	      max_fd = file_descriptor_tab[2] + 1;

	    while (1)
	      {
		FD_ZERO(&rdfs);

		/* add exit pipe arduino file_descriptor_tab[2] */
		FD_SET(file_descriptor_tab[2], &rdfs);

		/* add exit pipe client file_descriptor_tab[5] */
		FD_SET(file_descriptor_tab[5], &rdfs);


		if (select(max_fd, &rdfs, NULL, NULL, NULL) == -1)
		  {
		    exit();
		  }


		if (FD_ISSET(file_descriptor_tab[2], &rdfs))
		  {
		    /* read on exit pipe arduino file_descriptor_tab[2] */
		    
		     while (read(file_descriptor_tab[2], &buf, 1) > 0)
		       {

			 pointer->c = buf;
			 pointer = pointer->next;

			 // (1) lecture des instructions recues depuis la carte arduino (parseur de donnees)
			 // (2) interpretation / enregistrement des donnees
			 // (3) reponse si necessaire : write(file_descriptor_tab[1], '', 1);

		
			 write(STDOUT_FILENO, "<-", 2);
			 write(STDOUT_FILENO, &buf, 1);
			 write(STDOUT_FILENO, "<-", 2);
		       }

		  }
		else if (FD_ISSET(file_descriptor_tab[5], &rdfs))
		  {
		    /* read on exit pipe client file_descriptor_tab[5] */

		    while (read(file_descriptor_tab[5], &buf, 1) > 0)
		      {

			write(file_descriptor_tab[1], &buf, 1); // transmission des donnees recues depuis le client vers la carte arduino
			
			write(STDOUT_FILENO, "->", 2);
			write(STDOUT_FILENO, &buf, 1);
			write(STDOUT_FILENO, "->", 2);
		      }

		  }

		// Envoie des instructions en fonction des donnees recues :

		// Exemple :  write(file_descriptor_tab[1], "X#", 2);

	      }

	    wait(NULL);
	  }

    wait(NULL);
    
    close(file_descriptor_tab[0]);
    close(file_descriptor_tab[1]);
    close(file_descriptor_tab[2]);
    close(file_descriptor_tab[3]);
    close(file_descriptor_tab[4]);
    close(file_descriptor_tab[5]);
    close(file_descriptor_tab[6]);
    close(file_descriptor_tab[7]);

    exit(EXIT_SUCCESS);
  }
}
