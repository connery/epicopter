/*
** my_list.h for my_list.h in /home/croux_g//afs/rendu/piscine_rattrapage/Jour_05
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Fri Dec 17 21:41:56 2010 geoffrey croux
** Last update Fri Dec 17 23:03:28 2010 geoffrey croux
*/

#ifndef __MY_LIST_H__
#define __MY_LIST_H__

#include "my_lib.h"

struct			s_mylist
{
  char			c;

  struct s_mylist	*next;
  struct s_mylist	*prev;
};

typedef	struct	s_mylist	t_mylist;

void            my_aff_list(t_mylist *list);
t_mylist	* my_put_in_list(t_mylist *list, char c);

#endif
