/*
** serveur_cmd_msg.c for my_irc in /home/croux_g//local/system_unix/IRC/myirc-2015-2014s-crusem_m
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Sun Apr 22 19:02:13 2012 geoffrey croux
** Last update Sun Apr 22 19:33:51 2012 geoffrey croux
*/

#include "serveur.h"

int	serveur_cmd_msg(char * cmd, list * begin, list ** p, fd_set * writefds)
{
   list * client_receiver;

      if ((cmd = strtok(NULL, " ")) != 0)
	{
	  if ((client_receiver = serveur_nickname_exist(cmd, begin)) == (list*)(0))
	    {
	      strcpy((*p)->message, "ERROR : invalid receiver nickname.\n");
	      (*p)->message_len = strlen("ERROR : invalid receiver nickname.\n");

	      if (FD_ISSET((*p)->client_fd, writefds))
		{
		  (*p) = send_client((*p), 0, (*p)->client_fd, 0);
		}
	    }
	  else
	    {
	      if ((cmd = strtok(NULL, " ")) != 0)
		{
		  if (FD_ISSET(client_receiver->client_fd, writefds) && begin->channel != 0 && (*p)->channel != 0 && strcmp(begin->channel, (*p)->channel) == 0)
		    {
		      (*p) = send_client((*p), 0, client_receiver->client_fd, cmd);
		    }
		  return (0);
		}
	    }
	}

  return (EXIT_SUCCESS);
}
