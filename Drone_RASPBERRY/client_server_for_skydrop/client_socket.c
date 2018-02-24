/*
** client_socket.c for my_irc in /home/croux_g//local/system_unix/IRC
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Mon Apr 16 16:37:53 2012 geoffrey croux
** Last update Sat Dec  1 17:34:47 2012 geoffrey croux
*/

#include "client.h"

int		client_socket()
{
  int	fd;
  struct protoent	* pe;

  pe = getprotobyname("TCP");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    {
      write(2, ERROR_01, strlen(ERROR_01));
      return (EXIT_FAILURE);
    }
  return (fd);
}

int		client_socket_ini(struct sockaddr_in * s, int port, char * addr)
{
  s->sin_family = AF_INET;
  s->sin_port = htons(port);
  s->sin_addr.s_addr = inet_addr(addr);
  return (EXIT_SUCCESS);
}
