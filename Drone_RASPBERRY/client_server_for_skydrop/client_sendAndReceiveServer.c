/*
** sendAndReceiveServer.c for  in /home/crusem_m//Projet/Irc/myirc-2015-2014s-crusem_m
** 
** Made by michael crusem
** Login   <crusem_m@epitech.net>
** 
** Started on  Fri Apr 20 16:30:47 2012 michael crusem
** Last update Sun Apr 22 22:16:09 2012 michael crusem
*/

#include "client.h"

void		send_serveur(int fd, char *buffer, int len)
{
  if (send(fd, buffer, len, 0) == -1)
    write(1, "ERROR: Bad send to server\n", 26);
}

int		acceptFile(s_data *data)
{
  char	*buff = malloc(SIZE_BUFFER);
  int	nbread;

  write(1, "Accept file? [Y/N]\n", 19);
  if ((nbread = read(0, buff, SIZE_BUFFER)) == -1)
    return (EXIT_FAILURE);
  if (strncmp("Y", buff, nbread - 1) == 0)
    write(data->fd, "Y", 1);
  else
    write(data->fd, "N", 1);
  return (EXIT_SUCCESS);
}

void		rcv_serveur(s_data *data, int *connecte)
{
  char	buffer[SIZE_BUFFER];
  int	size;

  memset(buffer, 0, sizeof(buffer));
  size = recv(data->fd, buffer, SIZE_BUFFER, 0);
  if (size == 0)
    {
      write(1, "Server deconneted\n", 18);
      *connecte = 0;
    }
  if (strncmp("FILE?", buffer, 7) == 0)
    acceptFile(data);
  else if (strncmp("receiveFile", buffer, 11) == 0)
    receiveFile(buffer, data, size);
  else
    {
      write(1, buffer, size);
      write(1, "\n", 1);
    }
}

int		client_connect(struct sockaddr_in * sin, int fd)
{
  if ((connect(fd, (struct sockaddr *)sin, sizeof(*sin))) == -1)
    {
      close (fd);
      write(2, ERROR_02, strlen(ERROR_02));
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int		recover_command(s_data *data, char *buffer, int *connecte)
{
  struct sockaddr_in	sin;
  char			*tmp;

  if (*connecte == 1)
    {
      write(1, "You are already connect\n", 24);
      return (EXIT_SUCCESS);
    }
  strtok(buffer, " ");
  if ((data->host = strtok(NULL, " ")) == NULL)
    return (EXIT_FAILURE);
  if (data->host[strlen(data->host) - 1] == '\n')
    data->host[strlen(data->host) - 1] = '\0';
  if ((tmp = strtok(NULL, " ")) != NULL && atoi(tmp) != 0)
    data->port = atoi(tmp);
  printf("Try to connect : host:%s, port:%i\n", data->host, data->port);
  if ((data->fd = client_socket()) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if ((client_socket_ini(&sin, data->port, data->host)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if ((client_connect(&sin, data->fd)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  *connecte = 1;
  return (EXIT_SUCCESS);
}
