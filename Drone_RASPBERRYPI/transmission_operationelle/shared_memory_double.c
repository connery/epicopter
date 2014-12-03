#include "shared_memory_double.h"

// MODIFICATION DU CODE INITIAL : ERREURE D'ARRONDI SUR LES DOUBLES

int	decimal_number_decomposition(double nb, struct shared_double * container)
{
  container->sign = 1;

  if (nb < 0.0000000000)
    {
      container->sign = -1;
      nb = nb * (-1);
    }

  container->whole_part = (int)(nb);

  nb = nb - (double)(container->whole_part);

  char * str_ret = malloc(21 * sizeof(char));

  sprintf(str_ret, "%.10f", nb);

  /* unsigned long long	l_decimal_part = (unsigned long long int)(nb * 10000000000); */


  int incrementor, position;

  for (incrementor = 0; incrementor < 10; incrementor++) {container->decimal_part[incrementor] = '0';}

  for (incrementor = 0; incrementor < 20 && str_ret[incrementor] != '.'; incrementor++) {}
  incrementor++;

  for (position = 0; str_ret && str_ret[incrementor] ; incrementor++, position++)
    {
      container->decimal_part[position] = str_ret[incrementor];      
    }


  unsigned long long div = 10;
  
  int	rest = 0;

  /* for (incrementor = 0; incrementor < 10; incrementor++) */
  /*   { */
  /*     rest = l_decimal_part % div; */

  /*     printf("l_decimal : %llu\n", l_decimal_part); */

  /*     l_decimal_part = l_decimal_part / div; */

  /*     container->decimal_part[position] = rest + 48; */
      
  /*     printf("unit : %d\n", container->decimal_part[position] - 48); */
  /*     position = position - 1; */
  /*   } */

  return (1);
}

double	decimal_number_recomposition(double nb, struct shared_double * container)
{
  int incrementor;
  unsigned long long div = 10;
  unsigned long long r_decimal_part = 0;

  for (incrementor = 0; incrementor < 10; incrementor++)
    {
      r_decimal_part = r_decimal_part + (container->decimal_part[incrementor] - 48);
      r_decimal_part = r_decimal_part * 10;
    }

  double return_value;

  return_value = (double)r_decimal_part / 100000000000;

  /* for (incrementor = 0; incrementor < 10 && container->decimal_part[incrementor] == '0' ; incrementor++) */
  /*   { */
  /*     return_value = return_value / 10; */
  /*   } */
  /* return_value = return_value / 10; */

 
  return_value = return_value + (double)(container->whole_part);
 
  return_value = return_value * container->sign;

  return (return_value);
}

/* int	main(int ac, char ** av) */
/* { */
/*   double	nb = -180.1234567894; */

/*   struct shared_double container; */

/*   decimal_number_decomposition(nb, &container); */

/*   double return_value = decimal_number_recomposition(nb, &container); */

/*   printf("return_value : %.10f\n", return_value); */
  
/*   return (0); */
/* } */
