/*
** serveur_cmd_join.c for my_irc in /home/croux_g//local/system_unix/IRC/myirc-2015-2014s-crusem_m
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Sun Apr 22 19:00:45 2012 geoffrey croux
** Last update Sun Apr 22 19:20:05 2012 geoffrey croux
*/

#include "serveur.h"

int	serveur_cmd_join(char * cmd, channel_list ** c, list ** p)
{
  if ((cmd = strtok(NULL, " ")) != 0)
    {
      (*c) = serveur_add_channel(*c);

      (*p)->channel = strdup(cmd);
      (*c)->channel = strdup(cmd);
    }

  return (EXIT_SUCCESS);
}
