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

int main (int argc, char * argv[])
{
  int     fd[2];
  pid_t pid;
  struct data_navigation_container *data = init();
 
  pipe(fd);

  if ( (pid = fork()) < 0 )
    { 
      fprintf (stderr,"Il y a une erreur \n"); 
      exit(EXIT_FAILURE); 
    } 
  else if (pid == 0)
    {
      close(fd[0]);

      printf("FILS: mon pid est: %d, celui de mon père: %d \n", getpid(), getppid());
      write(fd[1], data, sizeof(*data));
      exit(EXIT_SUCCESS);
    } 
  else
    {
      close(fd[1]);

      char str[1024];
      sprintf(str, "./test %i", fd[0]);
      /* strcpy(str, "./test 3"); */
      system(str);

      printf("PÈRE: Je suis le père, mon pid est: %d, celui de mon fils: %d \n", getpid(), pid);
      printf("fd[0], fd du fils %i\n", fd[0]);
      printf("fd[1], fd du papa %i\n", fd[1]);
      int fin = wait(0);
      printf ("PÈRE: Mon fils se termine: son pid %d \n", fin);
      exit (EXIT_SUCCESS);
    }
}
