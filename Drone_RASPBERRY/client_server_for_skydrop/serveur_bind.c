/*
** serveur_bind.c for my_irc in /home/croux_g//local/system_unix/IRC/serveur
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Mon Apr 16 16:28:03 2012 geoffrey croux
** Last update Mon Apr 16 17:02:41 2012 geoffrey croux
*/

#include "serveur.h"

int		serveur_bind(struct sockaddr_in * s, int fd)
{
  if ((bind(fd, (const struct sockaddr *)s, sizeof(*s))) == -1)
    {
      close(fd);
      write(2, ERROR_02, strlen(ERROR_02));	return (EXIT_FAILURE);
    }

  return (EXIT_SUCCESS);
}
