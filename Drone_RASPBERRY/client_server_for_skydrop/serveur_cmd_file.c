/*
** serveur_cmd_file.c for my_irc in /home/croux_g//local/system_unix/IRC/myirc-2015-2014s-crusem_m
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Sun Apr 22 19:48:59 2012 geoffrey croux
** Last update Sun Apr 22 22:17:41 2012 geoffrey croux
*/

#include "serveur.h"

int	serveur_cmd_file(char * cmd, list * begin, fd_set * writefds, list ** p)
{
  int	i = 0;

  if ((cmd = strtok(cmd, ":")) != 0)
    if ((cmd = strtok(NULL, ":")) != 0)
      {
	for (; begin ; begin = begin->next)
	  {
	    if (begin->client_nickname != 0 && strcmp(begin->client_nickname, cmd) == 0)
	      {
		if (FD_ISSET(begin->client_fd, writefds))
		  send_client(begin, 0, begin->client_fd, "FILE?");
		rcv_client(begin, begin->client_fd, 0);				      
		if (strncmp("Y", begin->message, 1) == 0)
		  (*p) = send_client((*p), 0, (*p)->client_fd, "Y");
		else
		  (*p) = send_client((*p), 0, (*p)->client_fd, "N");  
		if ((cmd = strtok(NULL, ":")) != 0)
		  if ((cmd = strtok(NULL, ":")) != 0)
		    {
		      while (i < atoi(cmd))
			{
			  rcv_client((*p), (*p)->client_fd, 0);
			  write(1, (*p)->message, (*p)->message_len);
			  (*p)->message[(*p)->message_len] = '\0';
			  send_client(begin, 0, begin->client_fd, (*p)->message);
			  i = i + (*p)->message_len;
			}
		    }
	      }
	  }
      }
  return (EXIT_SUCCESS);
}
