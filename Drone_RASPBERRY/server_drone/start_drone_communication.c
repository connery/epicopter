#define _XOPEN_SOURCE

#define _GNU_SOURCE

#include <fcntl.h>
#include <termios.h>

#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/types.h>

#include <sys/select.h>
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "linked_lists_lib/my_list.h"
#include "sbp_piksi/libswiftnav/include/libswiftnav/sbp_messages.h" // DEFINE STRUCTURE USED FOR SHARED MEMORY

#include "shared_memory_double.h"
#include "sbp_piksi/raspberry_uart_communication.h"

#include "errno.h"

#define		SHARED_MEMORY_KEY 11114

int		GLOBAL_ITERATION = 0;

struct		data_navigation_container
{ 
  double	drone_latitude;
  double	drone_longitude;
  double	drone_height;
  double	drone_time;

  int		drone_n_sats;
};


int *	pipe_tab_initialisation(int * file_descriptor_tab);

  // file_descriptor_tab[0] : SORTIE DE PIPE (DISPONIBLE EN LECTURE)
  // file_descriptor_tab[1] : ENTREE DE PIPE (DISPONIBLE EN ECRITURE)

  
  // file_descriptor_tab[2] : SORTIE DE PIPE (DISPONIBLE EN LECTURE)
  // file_descriptor_tab[3] : ENTREE DE PIPE (DISPONIBLE EN ECRITURE)

  
  // file_descriptor_tab[4] : SORTIE DE PIPE (DISPONIBLE EN LECTURE)
  // file_descriptor_tab[5] : ENTREE DE PIPE (DISPONIBLE EN ECRITURE)

  
  // file_descriptor_tab[6] : SORTIE DE PIPE (DISPONIBLE EN LECTURE)
  // file_descriptor_tab[7] : ENTREE DE PIPE (DISPONIBLE EN ECRITURE)


int *	pipe_tab_initialisation(int * file_descriptor_tab)
{
  if (pipe(&(file_descriptor_tab[0])) == -1) { exit(EXIT_FAILURE); }
  if (pipe(&(file_descriptor_tab[2])) == -1) { exit(EXIT_FAILURE); }
  if (pipe(&(file_descriptor_tab[4])) == -1) { exit(EXIT_FAILURE); }
  if (pipe(&(file_descriptor_tab[6])) == -1) { exit(EXIT_FAILURE); }

  return (file_descriptor_tab);
}

int	close_file_descriptor(int * file_descriptor_tab, int file_descriptor)
{
  int	incrementor;

  if (file_descriptor == 0) // Fermeture de tout les fd encore ouvert dans le processus
    {
      for (incrementor = 0; incrementor < 8; incrementor++)
	{
	  if (file_descriptor_tab[incrementor] != 0) { close(file_descriptor_tab[incrementor]); file_descriptor_tab[incrementor] = 0; }
	}
    }
  else
    {
      for (incrementor = 0; incrementor < 8; incrementor++) // Fermeture du fd en argument
	{
	  if (file_descriptor_tab[incrementor] == file_descriptor && file_descriptor_tab[incrementor] != 0) { close(file_descriptor_tab[incrementor]); file_descriptor_tab[incrementor] = 0; }
	}
    }

  return (EXIT_SUCCESS);
}

int	client_drone_process(int * file_descriptor_tab)
{
  // execl("/bin/sh", "client_drone", "127.0.0.1", "client_drone#01", file_descriptor_tab[4]); // parametre : file_descriptor_tab[4] 

  return (EXIT_SUCCESS);
}

int	read_global_positioning_system_data(void * shared_memory, struct piksi_data_shared_memory * k, struct shared_double * p, struct data_navigation_container * data_navigation)
{
  k = ((struct piksi_data_shared_memory *)shared_memory);

  p->sign = k->lat_sign;
  p->whole_part = k->lat_whole_part;

  p->decimal_part[0] = k->lat_decimal_part[0];
  p->decimal_part[1] = k->lat_decimal_part[1];
  p->decimal_part[2] = k->lat_decimal_part[2];
  p->decimal_part[3] = k->lat_decimal_part[3];
  p->decimal_part[4] = k->lat_decimal_part[4];
  p->decimal_part[5] = k->lat_decimal_part[5];
  p->decimal_part[6] = k->lat_decimal_part[6];
  p->decimal_part[7] = k->lat_decimal_part[7];
  p->decimal_part[8] = k->lat_decimal_part[8];
  p->decimal_part[9] = k->lat_decimal_part[9];
      
  data_navigation->drone_latitude = decimal_number_recomposition(0, p);

  

  p->sign = k->lon_sign;
  p->whole_part = k->lon_whole_part;

  p->decimal_part[0] = k->lon_decimal_part[0];
  p->decimal_part[1] = k->lon_decimal_part[1];
  p->decimal_part[2] = k->lon_decimal_part[2];
  p->decimal_part[3] = k->lon_decimal_part[3];
  p->decimal_part[4] = k->lon_decimal_part[4];
  p->decimal_part[5] = k->lon_decimal_part[5];
  p->decimal_part[6] = k->lon_decimal_part[6];
  p->decimal_part[7] = k->lon_decimal_part[7];
  p->decimal_part[8] = k->lon_decimal_part[8];
  p->decimal_part[9] = k->lon_decimal_part[9];
      
  data_navigation->drone_longitude = decimal_number_recomposition(0, p);
  

  p->sign = k->height_sign;
  p->whole_part = k->height_whole_part;

  p->decimal_part[0] = k->height_decimal_part[0];
  p->decimal_part[1] = k->height_decimal_part[1];
  p->decimal_part[2] = k->height_decimal_part[2];
  p->decimal_part[3] = k->height_decimal_part[3];
  p->decimal_part[4] = k->height_decimal_part[4];
  p->decimal_part[5] = k->height_decimal_part[5];
  p->decimal_part[6] = k->height_decimal_part[6];
  p->decimal_part[7] = k->height_decimal_part[7];
  p->decimal_part[8] = k->height_decimal_part[8];
  p->decimal_part[9] = k->height_decimal_part[9];
      
  data_navigation->drone_height = decimal_number_recomposition(0, p);

  
  
  p->sign = k->time_sign;
  p->whole_part = k->time_whole_part;

  p->decimal_part[0] = k->time_decimal_part[0];
  p->decimal_part[1] = k->time_decimal_part[1];
  p->decimal_part[2] = k->time_decimal_part[2];
  p->decimal_part[3] = k->time_decimal_part[3];
  p->decimal_part[4] = k->time_decimal_part[4];
  p->decimal_part[5] = k->time_decimal_part[5];
  p->decimal_part[6] = k->time_decimal_part[6];
  p->decimal_part[7] = k->time_decimal_part[7];
  p->decimal_part[8] = k->time_decimal_part[8];
  p->decimal_part[9] = k->time_decimal_part[9];
      
  data_navigation->drone_time = decimal_number_recomposition(0, p);

  data_navigation->drone_n_sats = k->n_sats;



  printf("--- DONNEES DE REFERENCE ---\n");

  printf("Latitude : %.10f\nLongitude : %.10f\nHauteur : %.10f\nTime : %.10f\nSatellites : %d\n", data_navigation->drone_latitude, data_navigation->drone_longitude, data_navigation->drone_height, data_navigation->drone_time, data_navigation->drone_n_sats);
  
  printf("----------------------------\n\n");

  return (0);
}

int     arduino_output(int * file_descriptor_tab, t_mylist ** pointer, struct data_navigation_container * data_navigation, void * shared_memory, struct piksi_data_shared_memory * k, struct shared_double * p)
{
  // (1) lecture des instructions recues depuis la carte arduino (parseur de donnees)
  // (2) interpretation / enregistrement des donnees
  // (3) reponse si necessaire : write(file_descriptor_tab[1], '', 1);

  char          buf;

  //printf("LECTURE SUR LE FLUX DE COMMUNICATION ARDUINO\n");

  // RECEPTION

  //sleep(1); // Attente de fin d'ecriture sur le flux de toutes les donnees pour les paquet de taille importante : 1 seconde

  while (read(file_descriptor_tab[2], &buf, 1) > 0)
    {
      // Gestion de la boucle d'inscructions // NON UTILISE POUR L'INSTANT

      (*pointer)->c = buf;
      (*pointer) = (*pointer)->next;

      write(0, &buf, 1);
    }

  // AFFICHAGE DES DONNES DISPONIBLES

  
  

  // printf("Latitude : %.10f \nLongitude : %.10f\nHauteur : %.10f\n\n", data_navigation->drone_latitude, data_navigation->drone_longitude, data_navigation->drone_height);


  // REPONSE

  /* sleep(1); */

  /* fd_set writefds; */

  /* FD_ZERO(&writefds); */
  /* FD_SET(file_descriptor_tab[1], &writefds); // Add input pipe arduino file_descriptor_tab[1] : flux de communication arduino ouvert en ecriture */


  /* if (select(file_descriptor_tab[1] + 1, NULL, &writefds, NULL, NULL) == -1) { if (errno != 0) { (void)fprintf(stderr, "Select error, %s\n", strerror(errno)); } exit(1); } */

  /* if (FD_ISSET(file_descriptor_tab[1], &writefds)) */
  /*   { */
     
  /*   } */

  return (0);
}



int     client_output(int * file_descriptor_tab, t_mylist ** pointer)
{
  char          buf;

  printf("Read on exit pipe client\n");

  while (read(file_descriptor_tab[4], &buf, 1) > 0)
    {
      write(file_descriptor_tab[1], &buf, 1); // transmission des donnees recues depuis le client vers la carte arduino

      /* write(STDOUT_FILENO, &buf, 1); */
    }

  return (0);
}

t_mylist *      create_loop_instruction()
{
  t_mylist *    pointer;
  t_mylist *    begin;

  int           i;

  for (pointer = my_put_in_list(0, ' '), i = 0; i < 20; i++)
    {
      pointer = my_put_in_list(pointer, ' ');
    }

  for (begin = pointer; begin->next; begin = begin->next);

  begin->next = pointer;
  pointer->prev = begin;


  return (begin);
}

int     loop_process(void * shared_memory, struct data_navigation_container * data_navigation, t_mylist * arduino_instruction_list, t_mylist * client_instruction_list, fd_set readfds, fd_set writefds, int max_fd, struct piksi_data_shared_memory * k, struct shared_double * p, struct timeval time_out, int * file_descriptor_tab)
{
  errno = 0;

  FD_ZERO(&readfds);

  FD_SET(file_descriptor_tab[2], &readfds); // Add exit pipe arduino file_descriptor_tab[2]

  FD_SET(file_descriptor_tab[5], &readfds); // Add exit pipe client file_descriptor_tab[5]

  time_out.tv_usec = 2000000; // Passage select toutes les 1 seconde si pas d'activite sur les fd



  if (file_descriptor_tab[2] < file_descriptor_tab[5]) { max_fd = file_descriptor_tab[5] + 1; } else { max_fd = file_descriptor_tab[2] + 1; } // Preparation a l'utilisation de select()

  if (select(max_fd, &readfds, NULL, NULL, &time_out) == -1) { if (errno != 0) { (void)fprintf(stderr, "Select error, %s\n", strerror(errno)); } exit(1); }

 
  read_global_positioning_system_data(shared_memory, k, p, data_navigation); // Update GPS data


  if (FD_ISSET(file_descriptor_tab[2], &readfds)) // Condition de detection d'ecriture sur le flux de communication arduino
    {
      arduino_output(file_descriptor_tab, &arduino_instruction_list, data_navigation, shared_memory, k, p); // Execution des instructions d'interpretation dedies au flux de communication arduino
    }
  else if (FD_ISSET(file_descriptor_tab[5], &readfds))
    {
      client_output(file_descriptor_tab, &client_instruction_list);
    }


  

  //fd_set writefds;

  FD_ZERO(&writefds);
  FD_SET(file_descriptor_tab[1], &writefds); // Add input pipe arduino file_descriptor_tab[1] : flux de communication arduino ouvert en ecriture


  if (select(file_descriptor_tab[4] + 1, NULL, &writefds, NULL, NULL) == -1) { if (errno != 0) { (void)fprintf(stderr, "Select error, %s\n", strerror(errno)); } exit(1); }

  if (FD_ISSET(file_descriptor_tab[4], &writefds))
    {

      //char	cmd[1024] = "#XaXbXcXdXeXfXgXhXiXjXkXlXmXnXoXpXqXrXsXtXuX";
      //char	cmd[1024] = "mxjx";
      
      char	cmd[1024] = "";


      strcat(cmd, "/02"); // Balise d'emission de coordonnees GPS

      sprintf(cmd, "%.10f", data_navigation->drone_latitude);
      strcat(cmd, ";");

      sprintf(cmd, "%.10f", data_navigation->drone_longitude);
      strcat(cmd, ";");

      sprintf(cmd, "%.10f", data_navigation->drone_height);
      strcat(cmd, ";");

      sprintf(cmd, "%.10f", data_navigation->drone_time);
      strcat(cmd, ";");

      sprintf(cmd, "%d", data_navigation->drone_n_sats);
      strcat(cmd, ";");

      write(file_descriptor_tab[5], cmd, strlen(cmd));

      // EXEC le code à gaetan avec parametre file_descriptor_tab[5]
      system("../client_drone/magellanExec");

      //sleep(1); // FOR TEST STAGE
    }







  loop_process(shared_memory, data_navigation, arduino_instruction_list, client_instruction_list, readfds, writefds, max_fd, k, p, time_out, file_descriptor_tab);

  return (0);
}

int     serveur_drone_process(int * file_descriptor_tab)
  {
    int           shared_memory_segment_id;
    void *        shared_memory;

    struct piksi_data_shared_memory * data;

    if ((data = malloc(sizeof(data))) == NULL) { write(2, "malloc_error", 12); }

    double        drone_latitude;
    double        drone_longitude;
    double        drone_height;

    while ((shared_memory_segment_id = shmget(SHARED_MEMORY_KEY, sizeof(data), 0444)) < 0)
      {
	write(2, "SHMGET ERROR : LA CLEF MEMOIRE PARTAGEE NE CORRESPOND A AUCUNE ZONE MEMOIRE OUVERTE \n", strlen("SHMGET ERROR : LA CLEF MEMOIRE PARTAGEE NE CORRESPOND A AUCUNE ZONE MEMOIRE OUVERTE \n"));
      }

    if ((shared_memory = shmat(shared_memory_segment_id, NULL, 0)) == (void*)(-1)) { write(2, "shmat_error", 11); exit(EXIT_FAILURE); }

    // shmdt(shared_memory); // DESTRUCTION DE LA MEMOIRE PARTAGEE


    t_mylist *    arduino_instruction_list = create_loop_instruction(); // creation de la boucle de lecture                                   
    t_mylist *    client_instruction_list = create_loop_instruction(); // creation de la boucle de lecture                                                                              


    fd_set        readfds, writefds;
    int           max_fd;

    struct timeval                        time_out;

    time_out.tv_usec = 0;


    int   filestream = -1, processus_id;

    struct termios options;

    filestream = open("/dev/ttyACM0", O_RDWR | O_NOCTTY); // Ouverture du port de communication serie arduino

    if (filestream == -1) { write(2, "open_error\n", 11); return (-1); }

    tcgetattr(filestream, &options);

    options.c_cflag = B115200 | PARENB | CSTOPB | CSIZE | CS8;
    options.c_lflag = ICANON;

    tcsetattr(filestream, TCSANOW, &options);


    file_descriptor_tab[2] = filestream; // Add file descriptor serial communication arduino in file_descriptor_tab for reading

    sleep(3);

    


    
    struct piksi_data_shared_memory *     k; // Memoire partagee
    struct shared_double *                p; // Memoire paratgee                                                                                                                                                            

    if ((k = malloc(sizeof(k))) == NULL) { write(2, "malloc_error", 12); }
    if ((p = malloc(sizeof(p))) == NULL) { write(2, "malloc_error", 12); }





    struct data_navigation_container *	data_navigation = malloc(sizeof(struct data_navigation_container));

    data_navigation->drone_latitude = drone_latitude;
    data_navigation->drone_longitude = drone_longitude;
    data_navigation->drone_height = drone_height;

    loop_process(shared_memory, data_navigation, arduino_instruction_list, client_instruction_list, readfds, writefds, max_fd, k, p, time_out, file_descriptor_tab);

    return (0);
}

int	python_communication_serial_process(int * file_descriptor_tab)
{
  char	* communication_command_line = malloc(30 * sizeof(char));
  char	* string_nb = malloc(10 * sizeof(char));
  
  strcat(communication_command_line, "python communication.py");
  strcat(communication_command_line, " ");

  sprintf(string_nb, "%d", file_descriptor_tab[0]);

  strcat(communication_command_line, string_nb);
  strcat(communication_command_line, " ");

  sprintf(string_nb, "%d", file_descriptor_tab[3]);
  strcat(communication_command_line, string_nb);
 
  sleep(2); // Init all processus waiting : do not remove !

  execl("/bin/sh", "sh", "-c", communication_command_line);

  return (EXIT_SUCCESS);
}

int	gps_receiver_process(int * file_descriptor_tab)
{
  //execl("/bin/sh", "gps_communication"); 

  return (EXIT_SUCCESS);
}

int	create_new_process(int * file_descriptor_tab, int * processus_id_tab, int processus_id,int (** process_function_list)(int * file_descriptor_tab))
{
  int incrementor, pid;

  if ((processus_id_tab[processus_id] = fork()) == -1)
    {
      return (EXIT_FAILURE);
    }

  if (processus_id_tab[processus_id] == 0) // Creation d'un nouveau processus, processus fils
    {
      (* process_function_list[processus_id])(file_descriptor_tab);
    }

  else
    {
      if (processus_id < 2) 
	{
	  create_new_process(file_descriptor_tab, processus_id_tab, processus_id + 1, process_function_list);
	}

      else
	{	  
	  (* process_function_list[3])(file_descriptor_tab);
	  
	  while (processus_id_tab[1] != 0 && processus_id_tab[2] != 0 && processus_id_tab[3] != 0) // ATTENTE DE STATUT DE FIN DES PROCESSUS FILS
	    {
	      pid = wait(NULL);
	      for (incrementor = 1; incrementor < 4; incrementor++) { if (processus_id_tab[incrementor] == pid) { processus_id_tab[incrementor] = 0; } }
	    }

	  close_file_descriptor(file_descriptor_tab, 0); // Fermeture de tout les fd ouvert dans le processus pere
      
	  return (EXIT_SUCCESS);
	} 
    }
  
  return (EXIT_SUCCESS);
}

int	main(int argc, char * argv[])
{
  int * file_descriptor_tab = malloc(sizeof(int) * 8); // UNE SERIE DE 2 PIPES VERS ARDUINO, UNE SERIE DE 2 PIPES VERS LE CLIENT
  int * processus_id_tab = malloc(sizeof(int) * 4); // TABLEAU DE PID
  
  processus_id_tab[0] = getpid();

  file_descriptor_tab = pipe_tab_initialisation(file_descriptor_tab); // Creation des pipes de communication inter-processus

  int (* process_function_list[4])(int *) = {gps_receiver_process, client_drone_process, python_communication_serial_process, serveur_drone_process};

  create_new_process(file_descriptor_tab, processus_id_tab, 0, process_function_list); // Creation des processus et appel des fonctions respectivement executee dans chaque processus

  return (EXIT_SUCCESS);
}
