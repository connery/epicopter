/*
** ParsCommand.c for  in /home/crusem_m//Projet/Irc/myirc-2015-2014s-crusem_m
** 
** Made by michael crusem
** Login   <crusem_m@epitech.net>
** 
** Started on  Fri Apr 20 16:34:37 2012 michael crusem
** Last update Sat Apr 21 20:11:25 2012 michael crusem
*/

#include "client.h"

int		zeroParam(char *buffer, s_data *data)
{
  char	*buff = strdup(buffer);
  char	*tmp;

  strtok(buff, " ");
  tmp = strtok(NULL, " ");
  if (tmp != NULL)
    if (tmp[0] != '\n')
      {
	free(buff);
	return (EXIT_FAILURE);
      }

  buffer[data->len - 1] = '\0';
  write(data->fd, buffer, data->len - 1);
  printf("message |%s| envoyer au serveur:%i, de taille:%i\n", buffer, data->fd, data->len - 1);
  free(buff);
  return (EXIT_SUCCESS);
}

int		oneOrZeroParam(char *buffer, s_data *data)
{
  char	*buff = strdup(buffer);
  char	*tmp;

  strtok(buff, " ");
  tmp = strtok(NULL, " ");
  /* if (tmp == NULL || (tmp[0] && tmp[0] == '\n')) */
  /*   { */
  /*     free(buff); */
  /*     return (EXIT_FAILURE); */
  /*   } */
  tmp = strtok(NULL, " ");
  if (tmp != NULL)
    if (tmp[0] != '\n')
      {
	free(buff);
	return (EXIT_FAILURE);
      }
  buffer[data->len - 1] = '\0';
  write(data->fd, buffer, data->len - 1);
  printf("message |%s| envoyer au serveur:%i, de taille:%i\n", buffer, data->fd, data->len - 1);
  free(buff);
  return (EXIT_SUCCESS);
}

int		oneParam(char *buffer, s_data *data)
{
  char	*buff = strdup(buffer);
  char	*tmp;

  strtok(buff, " ");
  tmp = strtok(NULL, " ");
  if (tmp == NULL || (tmp[0] && tmp[0] == '\n'))
    {
      free(buff);
      return (EXIT_FAILURE);
    }
  tmp = strtok(NULL, " ");
  if (tmp != NULL)
    if (tmp[0] != '\n')
      {
	free(buff);
	return (EXIT_FAILURE);
      }
  buffer[data->len - 1] = '\0';
  write(data->fd, buffer, data->len - 1);
  printf("message |%s| envoyer au serveur:%i, de taille:%i\n", buffer, data->fd, data->len - 1);
  free(buff);
  return (EXIT_SUCCESS);
}

int		twoParam(char *buffer, s_data *data)
{
  char	*nN, *fN, *tmp, *buff = strdup(buffer);

  tmp = strtok(buff, " ");
  if ((nN = strtok(NULL, " ")) == NULL || (nN[0] && nN[0] == '\n'))
    return (my_freeFail(buff));
  if ((fN = strtok(NULL, " ")) == NULL || (fN[0] && fN[0] == '\n'))
    return (my_freeFail(buff));
  fN[strlen(fN) - 1] = '\0';
  if ((tmp = strtok(NULL, " ")) != NULL)
    if (tmp[0] != '\n')
      return (my_freeFail(buff));
  buffer[data->len - 1] = '\0';
  if (strncmp(buffer, "/send_file", 10) == 0 &&
      send_file(data, nN, fN) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  else
    {
      write(data->fd, buffer, data->len - 1);
      printf("message |%s| envoyer au serveur:%i, de taille:%i\n", buffer, data->fd, data->len - 1);
    }
  free(buff);
  return (EXIT_SUCCESS);
}

int		my_freeFail(char *buff)
{
  free(buff);
  return (EXIT_FAILURE);
}
