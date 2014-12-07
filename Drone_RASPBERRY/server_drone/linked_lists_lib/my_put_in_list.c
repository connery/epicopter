/*
** my_put_in_list.c for my_put_in_list.c in /home/croux_g//afs/rendu/piscine_rattrapage/Jour_05
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Fri Dec 17 21:45:53 2010 geoffrey croux
** Last update Fri Dec 17 23:06:01 2010 geoffrey croux
*/

#include "my_list.h"
#include "stdlib.h"

t_mylist		*my_put_in_list(t_mylist *list, char c)
{
  t_mylist		*new;

  if (list != 0)
    {
      while (list->prev)
	list = list->prev;
    }
  new = malloc(sizeof(*new));
  new->c = c;
  new->next = list;
  new->prev = 0;
  if (list != 0)
    list->prev = new;
  list = new;
  return (list);
}
