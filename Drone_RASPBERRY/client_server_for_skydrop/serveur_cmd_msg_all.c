/*
** serveur_cmd_msg_all.c for my_irc in /home/croux_g//local/system_unix/IRC/myirc-2015-2014s-crusem_m
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Sun Apr 22 19:38:43 2012 geoffrey croux
** Last update Sun Apr 22 19:48:03 2012 geoffrey croux
*/

#include "serveur.h"

int	serveur_cmd_msg_all(char * cmd_save, list * begin, list ** p, fd_set * writefds)
{
  for (; begin ; begin = begin->next)
    {
      if (begin != (*p) && begin->channel != 0 && (*p)->channel != 0 && strcmp(begin->channel, (*p)->channel) == 0)
	{
	  if (FD_ISSET(begin->client_fd, writefds))
	    {
	      (*p) = send_client((*p), 0, begin->client_fd, cmd_save);
	    }
	}
    }

  return (EXIT_SUCCESS);
}
