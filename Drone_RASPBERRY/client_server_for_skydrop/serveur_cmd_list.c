/*
** serveur_cmd_list.c for my_irc in /home/croux_g//local/system_unix/IRC/myirc-2015-2014s-crusem_m
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Sun Apr 22 19:00:03 2012 geoffrey croux
** Last update Sun Apr 22 19:22:53 2012 geoffrey croux
*/

#include "serveur.h"

int	serveur_cmd_list(channel_list ** c, list ** p, fd_set * writefds)
{
  channel_list * c_begin;

  for (c_begin = (*c); c_begin; c_begin = c_begin->next)
    {
      if (FD_ISSET((*p)->client_fd, writefds) && c_begin->channel)
	{
	  (*p) = send_client((*p), 0, (*p)->client_fd, c_begin->channel);
	}
    }

  return (EXIT_SUCCESS);
}
