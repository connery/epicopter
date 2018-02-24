/*
** client.c for my_irc in /home/croux_g//local/system_unix/IRC
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Mon Apr 16 16:36:28 2012 geoffrey croux
** Last update Fri Apr 20 16:39:17 2012 michael crusem
*/

#include "client.h"

int		main(int ac, char **av)
{
  if (ac != 1)
    {
      (void)av;
      write(2, ERROR_00, strlen(ERROR_00));
      return (EXIT_FAILURE);
    }
  if (loop() == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
