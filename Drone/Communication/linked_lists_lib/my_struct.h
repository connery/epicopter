/*
** my_struct.h for my_struct.h in /home/croux_g//afs/rendu/piscine_rattrapage/Jour_05
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Fri Dec 17 21:39:08 2010 geoffrey croux
** Last update Fri Dec 17 23:10:41 2010 geoffrey croux
*/

#ifndef __MY_STRUCT_H__
#define __MY_STRUCT_H__

struct				s_mystruct
{
  char				str[512];
  char				entier_8;
  unsigned short int		entier_16;
  int				entier_32;
};

typedef struct	s_mystruct	t_mystruct;

#endif __MY_STRUCT_H__
