#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

char * recupImage()
{
  FILE *fp = NULL;
  int c;
  char *str = NULL, *temp = NULL; 
  int i = 0;
  int size = 0;

  fp = fopen("image.c", "rb");

  str = malloc(sizeof(char));
  temp = malloc(sizeof(char));
  if (fp != NULL)
    {
      do
	{
	  c = fgetc(fp);

	  printf("%c",c);
	  temp= realloc(str, sizeof(char)*(strlen(str)+1));
	  while(str[i])
	    {
	      temp[i] = str[i];
	      i++;
	    }
	  str = realloc(str, sizeof(char)*(strlen(str)+2));
	  
	  
	  while(str[i])
	    {
	      str[i] =  temp[i];
	      i++;
	    }
	    str[i] = c;
	}while(c != EOF);

      fclose(fp);
    }
  /*
  while((c = fgetc(fp)) != feof(fp))
    {
      size++;
      printf("%c",c);
      temp= realloc(str, sizeof(char)*(strlen(str)+1));
      while(str[i])
	{
	  temp[i] = str[i];
	  i++;
	}
      str = realloc(str, sizeof(char)*(strlen(str)+2));
      

      while(str[i])
	{
	  str[i] =  temp[i];
	  i++;
	}
      str[i] = c;
      }*/
  printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
  return str;
}
