/*
** client_connect.c for my_irc in /home/croux_g//local/system_unix/IRC
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Mon Apr 16 16:36:44 2012 geoffrey croux
** Last update Sun Apr 22 15:44:27 2012 michael crusem
*/

#include "client.h"

void		createEndString(char **end, char *nickName, char *fileName, struct stat sb, char *tmp)
{
  *end = strcat(*end, "receiveFile");
  *end = strcat(*end, ":");
  *end = strcat(*end, nickName);
  *end = strcat(*end, ":");
  *end = strcat(*end, fileName);
  *end = strcat(*end, ":");
  sprintf(tmp, "%d", (int)sb.st_size);
  *end = strcat(*end, tmp);
  *end = strcat(*end, ":");
}

int		send_file(s_data *data, char *nN, char *fN)
{
  struct stat	sb;
  char		*end = malloc(SIZE_BUFFER);
  char		*tmp = malloc(SIZE_BUFFER);
  char		*buff = malloc(SIZE_BUFFER);
  int		fd, size;

  end = memset(end, 0, sizeof(end));
  tmp = memset(tmp, 0, sizeof(tmp));
  buff = memset(buff, 0, sizeof(buff));
  if ((fd = open(fN, O_RDONLY)) == -1 || fstat(fd, &sb) == -1)
    {
      printf("Cannot transfert file : %s\n", fN);
      return (EXIT_FAILURE);
    }
  createEndString(&end, nN, fN, sb, tmp);

  write(data->fd, end, strlen(end));
  if ((size = read(data->fd, buff, SIZE_BUFFER) == -1))
    return (EXIT_FAILURE);
  else
    if (strncmp("Y", buff, size) == 0)
      {
	if ((size=read(fd,buff,SIZE_BUFFER-15-strlen(nN)-strlen(fN)-strlen(tmp)))==-1)
	  return (EXIT_FAILURE);
	end = strcat(end, buff);
	write(data->fd, end, size+15+strlen(nN)+strlen(fN)+strlen(tmp));
	while ((size = read(fd, buff, SIZE_BUFFER)))
	  write(data->fd, buff, size);
	free(end);
	free(tmp);
	free(buff);
	return (EXIT_SUCCESS);
      }
  free(end);
  free(tmp);
  free(buff);
  return (EXIT_FAILURE);
}

int		initDataForTransfert(char **nickName, char **fileName, char **tmp, int *sizeFile, char **writeOnFd)
{
  if ((*nickName = strtok(NULL, ":")) == NULL)
    return (EXIT_FAILURE);
  if ((*fileName = strtok(NULL, ":")) == NULL)
    return (EXIT_FAILURE);
  if ((*tmp = strtok(NULL, ":")) == NULL)
    return (EXIT_FAILURE);
  *sizeFile = atoi(*tmp);
  *writeOnFd = strtok(NULL, "");
  return (EXIT_SUCCESS);
}

int		receiveFile(char *buffer, s_data *data, int sizeRead)
{
  char	*tmp = malloc(SIZE_BUFFER);
  char	*nN = malloc(SIZE_BUFFER);
  char	*fN = malloc(SIZE_BUFFER);
  char	*writeOnFd = malloc(SIZE_BUFFER);
  int	sizeFile = 0, sizeAlreadyPrint = 0, fd, size;

  tmp = memset(tmp, 0, sizeof(tmp));
  nN = memset(nN, 0, sizeof(nN));
  fN = memset(fN, 0, sizeof(fN));
  writeOnFd = memset(writeOnFd, 0, sizeof(writeOnFd));
  strtok(buffer, ":");
  if (initDataForTransfert(&nN, &fN, &tmp, &sizeFile, &writeOnFd)==EXIT_FAILURE)
    return (EXIT_FAILURE);
  sizeAlreadyPrint = sizeRead-15-strlen(nN)-strlen(fN)-strlen(tmp);
  if ((fd = open(fN, O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
    return (EXIT_FAILURE);
  write(fd, writeOnFd, sizeAlreadyPrint);
  while (sizeAlreadyPrint < sizeFile)
    {
      size = recv(data->fd, writeOnFd, SIZE_BUFFER, 0);
      write(fd, writeOnFd, size);
      sizeAlreadyPrint+= size;
      writeOnFd = memset(writeOnFd, 0, sizeof(writeOnFd));
    }
  return (EXIT_SUCCESS);
}

void		checkCommand(char *buffer, s_data *data, int *connecte)
{
  if (strncmp("/server", buffer, 7) == 0)
    {
      if (recover_command(data, buffer, connecte) == EXIT_FAILURE)
	write(1, "ERROR: Connect server fail\n", 27);
      else
	write(1, "You are connected\n", 18);
    }
  else if (strncmp("/nick", buffer, 5) == 0)
    oneParam(buffer, data);
  else if (strncmp("/list", buffer, 5) == 0)
    oneOrZeroParam(buffer, data);
  else if (strncmp("/join", buffer, 5) == 0)
    oneParam(buffer, data);
  else if (strncmp("/part", buffer, 5) == 0)
    oneParam(buffer, data);
  else if (strncmp("/users", buffer, 6) == 0)
    zeroParam(buffer, data);
  else if (strncmp("/msg", buffer, 4) == 0)
    twoParam(buffer, data);
  else if (strncmp("/send_file", buffer, 10) == 0)
    twoParam(buffer, data);
  else if (strncmp("/accept_file", buffer, 7) == 0)
    oneParam(buffer, data);
  else if (strncmp("\n", buffer, 1) != 0)
    write(data->fd, buffer, data->len - 1);
}
