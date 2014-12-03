
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <errno.h>

int	main(int ac, char ** av)
{
  int	nb;

  if (ac < 2)
    {
      printf("Usage : %s [file descriptor]\n", av[0]);
      return (-1);
    }

  int	file_descriptor = atoi(av[1]);
  char	buffer[1024];

  while (1)
    {

      if ((nb = read(0, (void *)(buffer), 1024)) < 0) { write(2, "error", 5); exit(-1); }
      buffer[nb] = 0;
      printf("Interpretation de l'instruction suivante : %s\n", buffer);
      errno = 0;
      if (write(file_descriptor, (void *)(buffer), (size_t)(nb)) < 0)
	{
	  if (errno != 0) { (void)fprintf(stderr, "Impossible d'ecrire sur le file descriptor, %s\n", strerror(errno)); }
	  //write(2, "write error", 11);
	  exit(-1);
	}
    }
  return (0);
}
