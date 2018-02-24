/*
** serveur_interpreter.c for my_irc in /home/croux_g//local/system_unix/IRC
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Wed Apr 18 15:48:15 2012 geoffrey croux
** Last update Sun Apr 22 19:57:03 2012 geoffrey croux
*/

#include "serveur.h"

int	serveur_interpreter(list * begin, list ** p, channel_list ** c, fd_set * writefds)
{
  char	* cmd;
  char	* cmd_save;

  (*p)->message[(*p)->message_len] = '\0';
  cmd_save = strdup((*p)->message);
  cmd = strdup((*p)->message);
  if (strncmp("receiveFile", cmd, 11) == 0)
    {
      serveur_cmd_file(cmd, begin, writefds, p);
      return (EXIT_SUCCESS);
    }
  cmd = strtok((*p)->message, " ");
  if (cmd == 0)
    return (EXIT_FAILURE);
  else if ((strcmp(cmd, "/nick")) == 0)
    serveur_cmd_nick(cmd, p);
  else if ((strcmp(cmd, "/list")) == 0)
    serveur_cmd_list(c, p, writefds);
  else if ((strcmp(cmd, "/join")) == 0)
    serveur_cmd_join(cmd, c, p);
  else if ((strcmp(cmd, "/part")) == 0)
    (*p)->channel = 0;
  else if ((strcmp(cmd, "/users")) == 0)
    serveur_cmd_users(begin, p, writefds);
  else if ((strcmp(cmd, "/msg")) == 0)
    serveur_cmd_msg(cmd, begin, p, writefds);
  else
    serveur_cmd_msg_all(cmd_save, begin, p, writefds);
  return (0);
}
