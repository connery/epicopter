#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* DATA */
#define	NUMBER_MAX_POINT		100
#define	NUMBER_DATA_INSIDE_POINT	100
#define	X				0
#define	Y				1

static	int	dataNumber = 0;
typedef enum	{ false, true } boolean;
typedef struct {
  int		idMap;
  double	**points;
  boolean	takeVideo;
  boolean	takePicture;
}		t_data;
/* ***** */

/* FONCTIONS */
void	showStruct(t_data *data);

/* ********* */

void	parseur(t_data *myStruct, char *str)
{
  char	*tmp = malloc(sizeof(char) * (strlen(str) + 1));
  char	*dataType;
  
  memcpy(tmp, str, strlen(str) + 1);

  dataType = strtok(tmp, ";"); /* LAN, VAL, VID ou PIC */
  /**
     Pour avoir les chaines de caractères suivantes :
     tmp = strtok(NULL, ";");
     -> NULL parce que strtok garde la chaine et la renvoi après chaque appelle
     -> Renvoi null quand c'est terminé
   */

  if (strcmp(dataType, "LAN") == 0) /* LAN;IDmap;EOF */
    {
      myStruct->idMap = atoi(strtok(NULL, ";"));
      /* ENVOYER VAL; */
    }
  else if (strcmp(dataType, "VAL") == 0) /* VAL;LATTITUDE;LONGITUDE;HAUTEUR;EOF */
    {
      char *data = strtok(NULL, ";");
      if (strcmp(data, "FIN") == 0) /* Dernier point à été envoyé, fin des points du parcours */
  	{
	  myStruct->points[dataNumber] = NULL;
  	  /* ENVOYER "VID; au serveur */
      	}
      else
  	{
  	  myStruct->points[dataNumber][0] = strtod(data, NULL);
  	  myStruct->points[dataNumber][1] = strtod(strtok(NULL, ";"), NULL);
  	  myStruct->points[dataNumber][2] = strtod(strtok(NULL, ";"), NULL);
	  dataNumber++;
  	  /* ENVOYER "VAL;y; au serveur */
  	}
    }
  else if (strcmp(dataType, "VID") == 0) /* VID;Y;EOF ou VID;N;EOF */
    {
      if (strcmp(strtok(NULL, ";"), "Y") == 0)
  	myStruct->takeVideo = true;
      else
  	myStruct->takeVideo = false;
      /* ENVOYER "PIC; au serveur */
    }
  else if (strcmp(dataType, "PIC") == 0) /* PIC;Y;EOF ou PIC;N;EOF */
    {
      if (strcmp(strtok(NULL, ";"), "Y") == 0)
  	myStruct->takePicture = true;
      else
  	myStruct->takePicture = false;
      /* ENVOYER "DEC; au serveur */
      dataNumber = 0;
    }
  free(tmp);
}

void	showStruct(t_data *data)
{
  int	i;
  
  printf("IdMap = %d\n", data->idMap);
  printf("Video = %d\n", data->takeVideo);
  printf("Image = %d\n", data->takePicture);
  for (i = 0; data->points[i]; i++)
    printf("lattitude = %f\nlongittude = %f\nhauteur = %f\n", data->points[i][0], data->points[i][1], data->points[i][2]);
  printf("\n");
}

t_data	*mallocAll(t_data *myStruct)
{
  int	size, tmp;

  myStruct = malloc(sizeof(* myStruct));
  myStruct->points = malloc(sizeof(** myStruct->points) * NUMBER_MAX_POINT);
  for (size = NUMBER_MAX_POINT, tmp = 0; tmp < NUMBER_MAX_POINT; tmp++)
    {
      myStruct->points[tmp] = malloc(sizeof(double *) * NUMBER_DATA_INSIDE_POINT);
      memset(myStruct->points[tmp], 0, NUMBER_DATA_INSIDE_POINT);
    }
  return (myStruct);
}

void	freeAll(t_data *myStruct)
{
  int	size, tmp;

  for (size = NUMBER_MAX_POINT, tmp = 0; tmp < NUMBER_MAX_POINT; tmp++)
    free(myStruct->points[tmp]);
  free(myStruct->points);
  free(myStruct);
}

int	main(int ac, char **av)
{
  t_data	*myStruct;

  myStruct = 0;
  myStruct = mallocAll(myStruct);

  /* ENVOYER LAN;map; au serveur */
  parseur(myStruct, "LAN;158;");
  parseur(myStruct, "VAL;1;2;3;");
  parseur(myStruct, "VAL;4;5;6;");
  parseur(myStruct, "VAL;7;8;9;");
  parseur(myStruct, "VAL;10;11;12;");
  parseur(myStruct, "VAL;13;14;15;");
  parseur(myStruct, "VAL;16;17;18;");
  parseur(myStruct, "VAL;19;20;21;");
  parseur(myStruct, "VAL;22;23;24;");
  parseur(myStruct, "VAL;25;26;27;");
  parseur(myStruct, "VAL;28;29;30;");
  parseur(myStruct, "VAL;FIN;");
  parseur(myStruct, "VID;Y;");
  parseur(myStruct, "PIC;N;");

  showStruct(myStruct);

  freeAll(myStruct);

  return 0;
}
