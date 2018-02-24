/*
** serveur.c for my_irc in /home/croux_g//local/system_unix/IRC/serveur
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Mon Apr 16 16:28:30 2012 geoffrey croux
** Last update Sun Apr 22 21:20:42 2012 geoffrey croux
*/

#include "serveur.h"

int		socket_fd;

void            function_signal_segv()
{
  printf("\nEt il est pour qui le 1.5/20 !?\nMoques toi,");
  printf(" mais moi je tombe pour mieu me relever. Et un jour viendra ou ");
  printf("je serai plus fort que toi.\n");
  
  close(socket_fd);

  exit (-1);
}

void            function_signal_ctrlc()
{
  printf("\nClick Clack Ctrl+C, CLOSE SERVEUR.\n");

  close(socket_fd);

  exit (0);
}

int		main(int ac, char ** av)
{
  struct sockaddr_in	sin;
  int		fd;

  if (ac != 2)
    {
      write(1, ERROR_00, strlen(ERROR_00));			return EXIT_FAILURE;
    }

  signal(SIGINT, function_signal_ctrlc);
  signal(SIGFPE, function_signal_segv);
  signal(SIGSEGV, function_signal_segv);

  if ((fd = serveur_socket()) == EXIT_FAILURE)			return (EXIT_FAILURE);

  socket_fd = fd;

  if ((serveur_socket_ini(&sin, atoi(av[1]))) == EXIT_FAILURE)	return (EXIT_FAILURE);
  if ((serveur_bind(&sin, fd)) == EXIT_FAILURE)			return (EXIT_FAILURE);
  if ((serveur_listen(fd)) == EXIT_FAILURE)			return (EXIT_FAILURE);
  if ((serveur_accept(fd)) == EXIT_FAILURE)			return (EXIT_FAILURE);

  return (EXIT_SUCCESS);
}
