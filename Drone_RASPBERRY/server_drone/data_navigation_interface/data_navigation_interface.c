#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

struct		data_navigation_container
{ 
  double	drone_latitude;
  double	drone_longitude;
  double	drone_height;
  double	drone_time;

  int		drone_n_sats;
};

struct data_navigation_container *init()
{
  struct data_navigation_container * data = malloc(sizeof(struct data_navigation_container));
  
  data->drone_latitude = 0.0000000000;
  data->drone_longitude = 0.0000000000;
  data->drone_height = 0.0000000000;
  data->drone_time = 0.0000000000;
  
  data->drone_n_sats = 0;

  return (data);
}

int	data_navigation_interface_loop(struct data_navigation_container * data, int fd, void * buffer)
{
  if (read(fd, buffer, 1024))
    {
      data = (struct data_navigation_container*) buffer;
 
      char	cmd[1024] = "";
     
      strcpy(cmd, "");
      sprintf(cmd, "latittude = \t%.10f", data->drone_latitude);
      mvaddstr(0, 0, cmd);
      
      strcpy(cmd, "");
      sprintf(cmd, "longitude = \t%.10f", data->drone_longitude);
      mvaddstr(1, 0, cmd);
      
      strcpy(cmd, "");
      sprintf(cmd, "hauteur = \t%.10f", data->drone_height);
      mvaddstr(2, 0, cmd);
      
      refresh();
      //getch(); // replace sleep

    }

  data_navigation_interface_loop(data, fd, buffer);

  return (EXIT_SUCCESS);
}

int	data_navigation_interface(int fd)
{
  struct data_navigation_container * data = init();

  WINDOW	* mainwin;
  void		* buffer = malloc(1024 * sizeof(char));

  if ((mainwin = initscr()) == NULL)
    {
      fprintf(stderr, "Erreur d'initialisation des ncurses\n");
      exit(EXIT_FAILURE);
    }

  data_navigation_interface_loop(data, fd, buffer);

  // CLEAN

  delwin(mainwin);
  endwin();
  refresh();

  return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
  if (av[1] == NULL)
    {
      printf("Il manque le fd en paramètre\n");
      exit(EXIT_FAILURE);
    }
  else
    {
      data_navigation_interface(atoi(av[1]));
    }

  return (EXIT_SUCCESS);
}

