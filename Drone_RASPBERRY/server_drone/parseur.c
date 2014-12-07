#include <stdlib.h>
#include <stdio.h>

/* DATA */
static int dataNumber = 0;

typedef enum { false, true } boolean;

typedef struct {
  double	*points;
  boolean	takeVideo;
  boolean	takePicture;
}		t_data;
/* ***** */

void	parseur(t_data *myStruct, char *str)
{
  switch (dataNumber) {
  case 0: /* premier passage, demande de l'envoi des points */
    /*
      Vérification que les coordonnées du point sont bien recu
      Si oui :
	Sauvegarde du point dans la structure;
	demande du point suivant;
	Si dernier point :
	  dataNumber++;
      Si non :
	redemander le point au serveur;
     */
    printf("cas 0 :\n");
    dataNumber++;
    break;
  case 1: /* Est ce que le drone doit prendre des vidéos */
    printf("cas 1 :\n");
    dataNumber++;
    /*
     Vérification que la donnée est bien recu
       Si oui :
         Enregistrement de l'information dans la structure;
	 Demande de la donnée suivante;
	 dataNumber++;
       Si non :
         redemander la donnée au serveur;
     */
    break;

  case 2: /* Est ce que le drone doit prendre des photos */
    printf("cas 2 :\n");
    dataNumber++;
    /*
     Vérification que la donnée est bien recu
       Si oui :
         Enregistrement de l'information dans la structure;
	 Demande de la donnée suivante;
	 dataNumber++;
       Si non :
         redemander la donnée au serveur;
     */
    break;

  case 3: /* FIN */
    printf("cas 3 :\n");
    dataNumber = 0;
    /*
      Deconnexion du serveur;
      dataNumber = 0;
     */
    break;

  default:
    break;
  }  
}

t_data	*xmalloc(t_data *myStruct)
{
  myStruct = malloc(sizeof(t_data *));
  myStruct->points = malloc(sizeof(double *) * 100);
  return (myStruct);
}

void	xfree(t_data *myStruct)
{
  free(myStruct->points);
  free(myStruct);
}

int	main(int ac, char **av)
{
  t_data *myStruct;

  myStruct = 0;
  myStruct = xmalloc(myStruct);
  while (1) {
    parseur(myStruct, "p1:21.1264568756456489;156.15456786789797653213");
    sleep(1);
  }
  xfree(myStruct);
  return 0;
}
