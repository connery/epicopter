/*
** my_del_elem_in_list.c for my_del_elem_in_list.c in /home/croux_g//afs/rendu/piscine_rattrapage/Jour_05
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Fri Dec 17 21:56:47 2010 geoffrey croux
** Last update Fri Dec 17 23:06:32 2010 geoffrey croux
*/

#include "my_list.h"
#include "stdlib.h"

t_mylist	*check(t_mylist *l, int e)
{
  if (!l->prev && !l->next && l->entier == e)
    {
      free(l);
      return (0);
    }
  else if (!l->prev && l->entier == e)
    {
      l->next->prev = 0;
      free(l);
    }
  else if (!l->next && l->entier == e)
    {
      l->prev->next = 0;
      free(l);
    }
  return (l);
}

t_mylist	*my_del_elem_in_list(t_mylist *l, int e)
{
  for (; l->prev; l = l->prev)
    ;
  for (; l->next; l = l->next)
    {
      l = check(l, e);
      if (l->entier == e)
        {
          l->next->prev = l->prev;
          l->prev->next = l->next;
          free(l);
        }
    }
  l = check(l, e);
  if (l == 0)
    return (l);
  for (; l->prev; l = l->prev)
    ;
  return (l);
}
