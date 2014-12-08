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
  struct data_navigation_container *test = malloc(sizeof(*test));
  
  test->drone_latitude = 1.111111111;
  test->drone_longitude = 2.222222222;
  test->drone_height = 3.333;
  test->drone_time = 4.444444444;
  
  test->drone_n_sats = 5;

  return test;
}

int main(int ac, char **av)
{
  struct data_navigation_container *data = init();
  WINDOW	*mainwin;
  int		fd;
  char		cmd[1024] = "";
  void		*buf = malloc(1024);
  int		i = 0;
  
  /* Récupération du fd */
  if (av[1] == NULL)
    {
      printf("Il manque le fd en paramètre\n");
      exit(EXIT_FAILURE);
    }
  else
    fd = atoi(av[1]);
  
  /* Initialisation ncurses */
  if ( (mainwin = initscr()) == NULL )
    {
      fprintf(stderr, "Erreur d'initialisation des ncurses\n");
      exit(EXIT_FAILURE);
    }
  
  /* while (strcmp(cmd, "") != 0) */
  while (read(fd, buf, 1024))
    {
      data = (struct data_navigation_container*) buf;
      
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
      getch(); // replace sleep
    }
  
  /* Clean */
  delwin(mainwin);
  endwin();
  refresh();

  return EXIT_SUCCESS;
}

/* int main() */
/* { */
/*   initscr();/\* Start curses mode   *\/ */
/*   printw("Hello World !!!");/\* Print Hello World  *\/ */
/*   refresh();/\* Print it on to the real screen *\/ */
/*   getch();/\* Wait for user input *\/ */
/*   endwin();/\* End curses mode  *\/ */
/*   return 0; */
/* } */

