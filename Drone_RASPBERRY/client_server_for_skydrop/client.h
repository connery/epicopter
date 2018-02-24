/*
** client.h for my_irc in /home/croux_g//local/system_unix/IRC
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Mon Apr 16 16:39:36 2012 geoffrey croux
** Last update Sat Apr 21 20:11:48 2012 michael crusem
*/

#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <netdb.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define	ERROR_00 "USAGE: ./client\n"
#define	ERROR_01 "ERROR: socket failure.\n"
#define	ERROR_02 "ERROR: socket connect failure.\n"

#define	SIZE_BUFFER	1024
#define DEF_PORT	1515

typedef struct	t_data
{
  char	*host;
  int	port;
  int	len;
  int	fd;
}		s_data;


/* client.c */
int		main(int ac, char ** av);

/* client_socket.c */
int		client_socket();
int		client_socket_ini(struct sockaddr_in * s, int port, char * addr);

/* client_connect.c */
void		createEndString(char **end, char *nickName, char *fileName, struct stat sb, char *tmp);
int		send_file(s_data *data, char *nickName, char *fileName);
int		initDataForTransfert(char **nickName, char **fileName, char **tmp, int *sizeFile, char **writeOnFd);
int		receiveFile(char *buffer, s_data *data, int sizeRead);
void		checkCommand(char *buffer, s_data *data, int *connecte);

/* ParsCommand.c */
int		zeroParam(char *buffer, s_data *data);
int		oneOrZeroParam(char *buffer, s_data *data);
int		oneParam(char *buffer, s_data *data);
int		twoParam(char *buffer, s_data *data);
int		my_freeFail(char *buff);

/* sendAndReceiveServer.c */
void		send_serveur(int fd, char *buffer, int len);
void		rcv_serveur(s_data *data, int *connecte);
int		client_connect(struct sockaddr_in * sin, int fd);
int		recover_command(s_data *data, char *buffer, int *connecte);

/* loop.c */
void		initData(s_data *data);
void		manageEntrerStandard(s_data *data, char *buffer, int *connecte);
void		manageServeur(s_data *data, char *buffer, int *connecte, fd_set *writefds);
int		loop();


#endif /* __CLIENT_H__ */
