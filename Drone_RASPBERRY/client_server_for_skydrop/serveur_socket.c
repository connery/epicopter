/*
** serveur_socket.c for my_irc in /home/croux_g//local/system_unix/IRC/serveur
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Mon Apr 16 16:29:23 2012 geoffrey croux
** Last update Mon Apr 16 17:00:46 2012 geoffrey croux
*/

#include "serveur.h"

int		serveur_socket()
{
  int	fd;
  struct protoent	* pe;

  pe = getprotobyname("TCP"); 
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      write(2, ERROR_01, strlen(ERROR_01));	return (EXIT_FAILURE);
    }

  return (fd);
}

int		serveur_socket_ini(struct sockaddr_in * s, int port)
{
  s->sin_family = AF_INET;
  s->sin_port = htons(port);
  s->sin_addr.s_addr = INADDR_ANY;
  
  return (EXIT_SUCCESS);
}
