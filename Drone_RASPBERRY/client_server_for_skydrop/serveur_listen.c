/*
** serveur_listen.c for my_irc in /home/croux_g//local/system_unix/IRC/serveur
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Mon Apr 16 16:29:02 2012 geoffrey croux
** Last update Wed Apr 18 13:38:01 2012 geoffrey croux
*/

#include "serveur.h"

int		serveur_listen(int fd)
{
  if ((listen(fd, LISTEN_LIST_SIZE)) == -1)
    {
      close (fd);
      write(2, ERROR_03, strlen(ERROR_03));	return (EXIT_FAILURE);
    }

  return (EXIT_SUCCESS);
}
