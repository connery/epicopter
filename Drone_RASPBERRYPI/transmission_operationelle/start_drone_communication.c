#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <string.h>

#include "linked_lists_lib/my_list.h"
#include "sbp_piksi/libswiftnav/include/libswiftnav/sbp_messages.h" // DEFINE STRUCTURE USED FOR SHARED MEMORY

#define		SHARED_MEMORY_KEY 00045

int * pipe_tab_initialisation(int * file_descriptor_tab);

int * pipe_tab_initialisation(int * file_descriptor_tab)
{

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

int	client_drone_process(int * file_descriptor_tab)
{

  // On lance le client

  // execl("/bin/sh", "client_drone", "127.0.0.1", "client_drone#01", file_descriptor_tab[4]); // parametre : file_descriptor_tab[4] 
  while (1);

  exit(EXIT_SUCCESS);

  return (0);
}

int	serveur_drone_process(int * file_descriptor_tab)
{
  // definition des variables specifiques a la gestion de memoire partagee

  int   shared_memory_segment_id;

  void          * shared_memory;
  sbp_pos_llh_t * data = malloc(sizeof(data));

  double	drone_latitude;
  double	drone_longitude;

  if ((shared_memory_segment_id = shmget(SHARED_MEMORY_KEY, sizeof(data), 0444)) < 0) { /* ERROR EXIT */ }
  if ((shared_memory = shmat(shared_memory_segment_id, NULL, 0)) == (void*)(-1)) { /* ERROR EXIT */ }

  // shmdt(shared_memory); // DESTRUCTION DE LA MEMOIRE PARTAGEE

  // Gestion des informations de vol


  // creation de la boucle de lecture

  t_mylist      * pointer;
  int		i;
  char		buf;

  for (pointer = my_put_in_list(0, ' '), i = 0; i < 20; i++)
    {
      pointer = my_put_in_list(pointer, ' ');
    }
  
  t_mylist        * begin;
  for (begin = pointer; begin->next; begin = begin->next);

  begin->next = pointer;
  pointer->prev = begin;

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
	  exit(1);
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


	      // DRONE GEODETIC POSITION
	      
	      drone_latitude = ((sbp_pos_llh_t *)shared_memory)->lat;
	      drone_longitude = ((sbp_pos_llh_t *)shared_memory)->lon;

	      // SEND DRONE GEODETIC POSITION TO ARDUINO

	      // write(file_descriptor_tab[1], drone_latitude, sizeof(drone_latitude));
	      // write(file_descriptor_tab[1], drone_longitude, sizeof(drone_longitude));

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

  return (0);
}

int	python_communication_serial_process(int * file_descriptor_tab)
{

  dup2(file_descriptor_tab[0], STDIN_FILENO);
  dup2(file_descriptor_tab[3], STDOUT_FILENO);

  //close(file_descriptor_tab[1]);
  //close(file_descriptor_tab[2]);
 
  execl("/bin/sh", "sh", "-c", "python communication.py", NULL);

  close(file_descriptor_tab[0]);
  close(file_descriptor_tab[3]);

  exit(EXIT_SUCCESS);

  return (0);
}

int	gps_receiver_process(int * file_descriptor_tab)
{

  execl("/bin/sh", "sbp_piksi/gps_communication"); 

  exit(EXIT_SUCCESS);

  return (0);
}

int main(int argc, char *argv[])
{
  int * file_descriptor_tab = malloc(sizeof(int) * 8); // UNE SERIE DE 2 PIPES VERS ARDUINO, UNE SERIE DE 2 PIPES VERS LE CLIENT
  int * processus_id_tab = malloc(sizeof(int) * 4); // TABLEAU DE PID
  
  processus_id_tab[0] = getpid();

  file_descriptor_tab = pipe_tab_initialisation(file_descriptor_tab); // Creation des pipes de communication inter-processus

  // DIVISION DES PROCESSUS :

  processus_id_tab[1] = fork();

  if (processus_id_tab[1] == -1)
  {
    exit(EXIT_FAILURE);
  }

  if (processus_id_tab[1] == 0) // processus fils (premier processus fils)
  {
    printf("Ouverture du processus fils : 1\n");

    python_communication_serial_process(file_descriptor_tab);
  }
  else // processus pere
  {

    // DIVISION DES PROCESSUS :

    processus_id_tab[2] = fork();

    if (processus_id_tab[2] == -1)
      {
	exit(EXIT_FAILURE);
      }

    if (processus_id_tab[2] == 0) // processus fils (second processus fils)
      {
	printf("Ouverture du processus fils : 2\n");

	client_drone_process(file_descriptor_tab);
      }
    else // processus pere
      {

	 // DIVISION DES PROCESSUS :

	processus_id_tab[3] = fork();

	if (processus_id_tab[3] == -1)
	  {
	    exit(EXIT_FAILURE);
	  }

	if (processus_id_tab[3] == 0) // processus fils (troisieme processus fils)
	  {
	    printf("Ouverture du processus fils : 3\n");

	    gps_receiver_process(file_descriptor_tab);
	   
	  }
	else // processus pere
	  {
	    serveur_drone_process(file_descriptor_tab); 
	  }

	
      }

    

    while (processus_id_tab[1] != 0 && processus_id_tab[2] != 0 && processus_id_tab[3] != 0) // ATTENTE DE STATUT DE FIN DES PROCESSUS FILS
      {
	int pid = wait(NULL);

	for (int incrementor = 1; incrementor < 4; increment++)
	  {
	    if (processus_id_tab[incrementor] == pid)
	      processus_id_tab[incrementor] = 0;
	  }
      }


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
