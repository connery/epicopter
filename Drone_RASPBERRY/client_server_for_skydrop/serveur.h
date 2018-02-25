/*
** serveur.h for my_irc in /home/croux_g//local/system_unix/IRC
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Mon Apr 16 16:40:03 2012 geoffrey croux
** Last update Sun Apr 22 21:18:39 2012 geoffrey croux
*/

#ifndef __SERVEUR_H__
#define __SERVEUR_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <signal.h>

#define		BUFFER_SIZE 1024
#define		LISTEN_LIST_SIZE 10

#define		ERROR_00 "USAGE: ./serveur `port number`\n"
#define		ERROR_01 "ERROR: socket failure.\n"
#define		ERROR_02 "ERROR: socket bind failure.\n"
#define		ERROR_03 "ERROR: socket listen failure.\n"
#define		ERROR_04 "ERROR: socket accept failure.\n"

int		dest;

//		structures
struct		s_list
{
  struct	s_list	* next;

  char		* client_nickname;
  char		* client_receiver;
  char		* channel;

  char	message[BUFFER_SIZE];
  int	message_len;

  int	client_fd;
};

typedef struct s_list list;

struct		s_channel
{
  struct	s_channel * next;

  char		* channel;
};

typedef struct	s_channel channel_list;


//		serveur.c
int		main(int , char ** );

void            function_signal_segv();
void            function_signal_ctrlc();

//		serveur_socket.c
int		serveur_socket();
int		serveur_socket_ini(struct sockaddr_in * , int );


//		serveur_bind.c
int		serveur_bind(struct sockaddr_in * , int );


//		serveur_listen.c
int		serveur_listen(int );


//		serveur_accept.c
int		serveur_accept(int);
int		serveur_old(int ,list * );
int		serveur_control(list * , fd_set * );

list		* serveur_do_client(list ** , channel_list ** , fd_set * , fd_set * );
list		* rcv_client(list * , int , int );
list		* send_client(list * , int , int , char *);
list		* serveur_add_client(list * , int );
list		* serveur_nickname_exist(char * , list * );
list		* serveur_del_client(list * , int );

channel_list	* serveur_add_channel(channel_list * c);

//		serveur_interpreter.c
int		serveur_interpreter(list * , list ** , channel_list ** , fd_set * );

//		serveur_cmd_nick.c
int		serveur_cmd_nick(char * , list ** );

//		serveur_cmd_list.c
int		serveur_cmd_list(channel_list ** , list ** , fd_set * );

//		serveur_cmd_join.c
int		serveur_cmd_join(char * , channel_list ** , list ** );

//		serveur_cmd_users.c
int		serveur_cmd_users(list * , list ** , fd_set * );

//		serveur_cmd_msg.c
int		serveur_cmd_msg(char * , list * , list ** , fd_set * );

//		serveur_cmd_msg_all.c
int		serveur_cmd_msg_all(char * , list * , list ** , fd_set * );

//		serveur_cmd_file.c
int		serveur_cmd_file(char * , list * , fd_set * , list ** );

#endif
