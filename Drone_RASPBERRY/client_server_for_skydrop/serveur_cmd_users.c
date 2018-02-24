/*
** serveur_cmd_users.c for my_irc in /home/croux_g//local/system_unix/IRC/myirc-2015-2014s-crusem_m
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Sun Apr 22 19:01:44 2012 geoffrey croux
** Last update Sun Apr 22 19:26:26 2012 geoffrey croux
*/

#include "serveur.h"

int	serveur_cmd_users(list * begin, list ** p, fd_set * writefds)
{
  for (; begin ; begin = begin->next)
    {
      if (begin->client_nickname != 0 && begin->channel != 0 && (*p)->channel != 0 && strcmp(begin->channel, (*p)->channel) == 0)
	{      
	  if (FD_ISSET((*p)->client_fd, writefds))
	    {
	      (*p) = send_client((*p), 0, (*p)->client_fd, begin->client_nickname);
	    }	      
	}
      else if ((*p)->channel == 0)
	{
	  if (FD_ISSET((*p)->client_fd, writefds))
	    {
	      (*p) = send_client((*p), 0, (*p)->client_fd, "ERROR: You have not join channel.\n");
	    }
	  return (0);
	}
    }

  return (EXIT_SUCCESS);
}
