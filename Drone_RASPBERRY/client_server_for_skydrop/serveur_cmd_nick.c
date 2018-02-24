/*
** serveur_cmd_nick.c for my_irc in /home/croux_g//local/system_unix/IRC/myirc-2015-2014s-crusem_m
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Sun Apr 22 18:59:03 2012 geoffrey croux
** Last update Sun Apr 22 19:07:23 2012 geoffrey croux
*/

#include "serveur.h"

int	serveur_cmd_nick(char * cmd, list ** p)
{
  if ((cmd = strtok(NULL, " ")) != 0)
    {
      (*p)->client_nickname = strdup(cmd);
    }

  return (EXIT_SUCCESS);
}
