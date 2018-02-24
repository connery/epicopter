/*
** loop.c for  in /home/crusem_m//Projet/Irc/myirc-2015-2014s-crusem_m
** 
** Made by michael crusem
** Login   <crusem_m@epitech.net>
** 
** Started on  Fri Apr 20 16:28:34 2012 michael crusem
** Last update Fri Apr 20 16:29:58 2012 michael crusem
*/

#include "client.h"

void		initData(s_data *data)
{
  data->host = malloc(SIZE_BUFFER + 1);
  memset(data->host, 0, sizeof(data->host));
  data->port = DEF_PORT;
  data->len = 0;
  data->fd = -1;
}

void		manageEntrerStandard(s_data *data, char *buffer, int *connecte)
{
  data->len = read(0, buffer, SIZE_BUFFER);
  if (!data->len)
    {
      write(1, "Ciao\n", 5);
      exit(0);
    }
  checkCommand(buffer, data, connecte);
}

void		manageServeur(s_data *data, char *buffer, int *connecte, fd_set *writefds)
{
  rcv_serveur(data, connecte);
  if (FD_ISSET(data->fd, writefds))
    send_serveur(data->fd, buffer, data->len);
}

int		loop()
{
  char			buffer[SIZE_BUFFER];
  int			connecte = 0, result = 0;
  fd_set		readfds;
  fd_set		writefds;
  s_data		*data = malloc(sizeof(s_data));

  initData(data);
  while (result != -1)
    {
      write(1, "prompt -> ", 10);
      memset(buffer, 0, sizeof(buffer));
      FD_ZERO(&readfds);
      if (connecte == 1)
	FD_SET(data->fd, &readfds);
      FD_SET(0, &readfds);
      if ((result = select(5, &readfds, NULL, NULL, NULL)) == (-1))
	return EXIT_FAILURE;
      if (FD_ISSET(data->fd, &readfds))
	manageServeur(data, buffer, &connecte, &writefds);
      if (FD_ISSET(0, &readfds))
	manageEntrerStandard(data, buffer, &connecte);
    }
  close(data->fd);
  return (EXIT_SUCCESS);
}
