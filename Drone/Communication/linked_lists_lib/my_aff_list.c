/*
** my_aff_list.c for my_aff_list.c in /home/croux_g//afs/rendu/piscine_rattrapage/Jour_05
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Fri Dec 17 21:50:40 2010 geoffrey croux
** Last update Fri Dec 17 23:07:00 2010 geoffrey croux
*/

#include "my_list.h"
#include "unistd.h"

void		my_aff_list(t_mylist *list)
{
  while (list)
    {
      my_putchar(list->c);
      list = list->next;
    }
}
