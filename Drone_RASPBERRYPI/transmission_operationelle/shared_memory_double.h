
#ifndef __SHARED_MEMORY_DOUBLE_H__
#define __SHARED_MEMORY_DOUBLE_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct shared_double
{
  int                   sign;
  int                   whole_part;
  char                  decimal_part[10];
};

int     decimal_number_decomposition(double nb, struct shared_double * container);
double  decimal_number_recomposition(double nb, struct shared_double * container);

#endif
