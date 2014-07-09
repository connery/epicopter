#include <stdlib.h>

char* itoa(int i, char b[]){
  char const digit[] = "0123456789";
  char* p = b;
  if(i<0){
    *p++ = '-';
    i *= -1;
  }
  int shifter = i;
  do{ //Move to where representation ends
    ++p;
    shifter = shifter/10;
  }while(shifter);
  *p = '\0';
  do{ //Move back, inserting digits as u go
    *--p = digit[i%10];
    i = i/10;
  }while(i);
  return b;
}

int getSeparator(char *input) {
  int i;
  int c = 0;

  for (i = 0; input[i]; i++)
    if (input[i] == ';')
      c++;
  return c;
}

char **parser(char *input, int a,char **tab) {
  int i, j, k;
  int c = getSeparator(input);

  if (a == 0)
    {
      tab = malloc(sizeof(char) * c);
            
      for (i = 0; i < c; i++) {
	tab[i] = malloc(sizeof(char) * 60);
      }    
    }
  else
    {
      for (i = 0; i < c; i++)
	free(tab[i]);
      
      free(tab);
      
      tab = malloc( sizeof(char) * c);
      
      for (i = 0; i < c; i++) 
	tab[i] = malloc(sizeof(char) * 60);
    }

  k = 0;
  for (i = 0; i < c; i++) 
    for (j = 0; input[k] != ';'; j++, k++) {
      tab[i][j] = input[k];
      
      if (input[k] == ';')
	k++;
      
    }
  return tab;
}
