/*
** my_utilities.c for my_utilities.c in /home/croux_g//local/Semestre_01/Systeme_Unix/TP/Les_Varargs_printf
** 
** Made by geoffrey croux
** Login   <croux_g@epitech.net>
** 
** Started on  Wed Nov 17 11:07:06 2010 geoffrey croux
** Last update Thu Jan  5 12:59:30 2012 geoffrey croux
*/

#include "my_lib.h"

void	my_putchar(char x);
int	my_putstr(char *str);
int	my_strlen(char *str);
int	my_putnbr(int nb);
unsigned int	my_putnbr_base(unsigned int n, char *base);
unsigned int	my_putnbr_base_binary(unsigned int n, char *base);


void	my_putchar(char x)
{
  write (1, &x, 1);
}

int	my_putstr(char *str)
{
  int	position;

  position = 0;
  
  while (str[position] != '\0')
    {
      my_putchar(str[position]);
      position = position + 1;
    }
  return (position);
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      i++;
    }
  return (i);
}

int	my_putnbr(int nb)
{
  int div;
  int position;
  int r;
  int z;

  div = 1;
  r = 0;
  z = 0;
  position = 0;
  if (nb < 0)
    {
      nb = -nb;
      my_putchar(45);
    }
  while (nb >= div)
    {
      div = div * 10;
      position = position + 1;
    }
  div /= 10;
  while (div > 1)
    {
      r = nb / div;
      my_putchar(r + 48);
      nb = nb % div;
      div = div / 10;
    }
  my_putchar(nb + 48);
  return (position);
}

unsigned int	my_putnbr_base(unsigned int n, char *base)
{
  unsigned int	deb;
  unsigned int	fin;
  unsigned int	len;
  unsigned int	octet;

  octet = 0;
  len = my_strlen(base) - 1;
  fin = n % len;
  deb = (n - fin) / len;
  if (deb != 0)
    octet = octet + my_putnbr_base(deb, base);
  my_putchar(base[fin]);
  octet++;
  return (octet);
}

unsigned int	my_putnbr_base_binary(unsigned int n, char *base)
{
  unsigned int	deb;
  unsigned int	fin;
  unsigned int	octet;

  octet = 0;
  fin = n % 2;
  deb = (n - fin) / 2;
  if (deb != 0)
    octet = octet + my_putnbr_base(deb, base);
  my_putchar(base[fin]);
  octet++;
  return (octet);
}
