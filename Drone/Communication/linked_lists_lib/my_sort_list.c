/*
** my_sort_list.c for ne my_sort_list.c in /home/croux_g//afs/rendu/piscine_rattrapage/Jour_05
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Fri Dec 17 22:29:20 2010 geoffrey croux
** Last update Fri Dec 17 22:31:22 2010 geoffrey croux
*/

#include "my_list.h"

t_mylist		*my_sort_list(t_mylist *list)
{
  int			temp;

  while (list->next)
    list = list->next;
  while (list->prev)
    {
      if (list->c < list->prev->c)
        {
          temp = list->c;
          list->c = list->prev->c;
          list->prev->c = temp;
          while (list->next)
            list = list->next;
        }
      list = list->prev;
    }
  return (list);
}
