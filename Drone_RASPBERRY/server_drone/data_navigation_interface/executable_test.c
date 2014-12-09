#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

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
  struct data_navigation_container *test = malloc(sizeof(test));
  
  test->drone_latitude = 1.123456789;
  test->drone_longitude = 2.987654321;
  test->drone_height = 3.123;
  test->drone_time = 4.321;
  
  test->drone_n_sats = 5;

  return test;
}

int	main (int argc, char * argv[])
{
  int		fd[2];
  pid_t		pid;

  struct data_navigation_container *data = init();

  pipe(fd);

  if ((pid = fork()) < 0)
    { 
      fprintf (stderr,"Il y a une erreur \n"); 

      exit(EXIT_FAILURE); 
    } 

  else if (pid == 0)
    {
      close(fd[0]);

      while (1)
	{
	  data->drone_latitude = data->drone_latitude + 1.0;
	  data->drone_time = data->drone_time + 1.0;

	  

	  write(fd[1], data, sizeof(*data));
	  sleep(1);
	}

      exit(EXIT_SUCCESS);
    } 
  else
    {
      close(fd[1]);

      char str[1024];
      sprintf(str, "./data_navigation_interface %i", fd[0]);
      system(str);

      int fin = wait(0);

      exit (EXIT_SUCCESS);
    }
}
