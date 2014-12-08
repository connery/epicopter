
#include "node.h"


#define BUFLEN 10240
#define PORT 9930
#define DATALEN 8192
#define BASEOP "192.168.1.17"
#define NAME_SIZE 10




void err(char *s)
{
  perror(s);
  exit(1);
}

int main(int argc, char** argv)
{
  struct sockaddr_in serv_addr;
  int sockfd, i, slen=sizeof(serv_addr), singleton = 1;
  char buf[BUFLEN];
  int state = 4;

  if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    err("socket");
 
  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  if (inet_aton(BASEOP, &serv_addr.sin_addr)==0)
    {
      fprintf(stderr, "inet_aton() failed\n");
      exit(1);
    }

  node * liste = NULL;
  node * liste2 = NULL;
  liste2 = malloc(sizeof(node));
  liste2->next = NULL;
  Packet ini;
  int j = 1, taille = 0;
  


  while(1)
    {     
      if(singleton == 0)
	{
	  if (state == 1)
	    {

	      ini.code = WAIT;
	    }
	  else
	    {
	      printf("MED\n");
	      ini.code = MED;
	      ini.ID = 0;
	      liste = (node *) generateListFromImage("image.jpg"); //rendre dynamique
	      ini.datalen = liste->p.datalen;
	      printf("MED END, datalen :%i\n", ini.datalen);
	      state = 4;
	      taille = count_item(liste);
       	    }
	  singleton = 1;
	}
      if(state == 4)
	{
	  if (singleton != 1)
	    {
	      if (j < taille)
		{
		  
		  liste = liste->next;
		  ini = liste->p;
	
		  printf("ID: %i\n",ini.ID);
		  j++;
		}
	      else
		{
		  
		  exit(1);

		}
	    }
	  else
	    singleton++;
	}
      if (sendto(sockfd,&ini, BUFLEN, 0,(struct sockaddr*)&serv_addr, slen)==-1)
	err("sendto()");
      printf("avant recv\n");
      getInfo(liste2);
      if (recvfrom(sockfd,&ini, BUFLEN, 0, (struct sockaddr*)&serv_addr, &slen)==-1)
	{
	  err("revc()");
	}
      else
	{
	  /*	  if (ini.nbckp > 0 )
		  {
		  printf("nombre: %i\n",ini.nbckp);
		  }
		  else
		  printf("ID: %i\n",ini.ID);*/
	  add_end(liste2, ini);
	  show(liste2);	
	}
    }
  show(liste2);
  close(sockfd);
  return 0;
}
 
