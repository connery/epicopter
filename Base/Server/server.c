#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <my_global.h>
#include <mysql.h>

#include "server.h"


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


static void run(void)
{  
  Network network = createNetwork();
  SQLManager manager = createManager();
  
  int max = network.getSocket(&network);
  int singleton = 0;
  fd_set rdfs;
  int ckp = 0;


  manager.connectManager(&manager, "localhost", "root", "caca");
  manager.execSQL(&manager, "CREATE DATABASE poil");
  /*
  while(1)
    {
      int i = 0;
      char **tab;

      FD_ZERO(&rdfs);
      FD_SET(STDIN_FILENO, &rdfs);
      FD_SET(network.getSocket(&network), &rdfs);

      for (i = 0; i < network.getActual(&network); i++)
	FD_SET(network.getClients(&network)[i].sock, &rdfs);
	      
      if (select(max + 1, &rdfs, NULL, NULL, NULL) == -1) {
	  perror("select()");
	  exit(errno);
	}

      if (FD_ISSET(STDIN_FILENO, &rdfs))
	  break;
            
      else if (FD_ISSET(network.getSocket(&network), &rdfs))
	{
	  puts("NEW CLIENT");
	  
	  SOCKADDR_IN csin = { 0 };
	  socklen_t sinsize = sizeof csin;

	  int csock = accept(network.getSocket(&network), (SOCKADDR *)&csin, &sinsize);

	  if (csock == SOCKET_ERROR) {
	    perror("accept()");
	    continue;
	  }
	  
	  Client c = { csock };

	  FD_SET(csock, &rdfs);

	  network.getClients(&network)[network.getActual(&network)] = c;	  
	  network.incActual(&network);	  

	  if (network.readClient(&network, csock) < 0)
	    {
	      continue;
	    }
	  else {
	    max = csock > max ? csock : max;
	    
	    if (strcmp(network.getBuffer(&network), "END;") == 0) {
	      network.removeClient(&network, network.getActual(&network) - 1);	  
	      singleton = 0;
	    } else {
	      network.setBuffer(&network, "CON;y;EOF;");
	      network.writeClient(&network, csock); 
	    }
	  }
	}
      
      else
	{
	  int i = 0;
	  
	  for (i = 0; i < network.getActual(&network); i++)
	    {
	      if (FD_ISSET(network.getClients(&network)[i].sock, &rdfs))
		{
		  int n = network.readClient(&network, network.getClients(&network)[i].sock);
		  if (n < 0) { 
		    network.removeClient(&network, i);
		    break;
		  }
		  else if (n > 0) {
		    
		    if (strcmp(network.getBuffer(&network), "LAN;map;") == 0) {
		      network.setBuffer(&network, "LAN;0005;EOF;");
		      network.writeClient(&network, network.getClients(&network)[i].sock); 
		      break;
		    }
		  
		    if (strcmp(network.getBuffer(&network), "END;") == 0) {
		      network.removeClient(&network, i);
		      break;
		    }
		    
		    if (strncmp(network.getBuffer(&network), "VAL;", 4) == 0) {
		      if (ckp == 5) {
			network.setBuffer(&network, "VAL;fin;EOF;");
			network.writeClient(&network, network.getClients(&network)[i].sock); 
			ckp++;
			break;
		      }
		      else if (ckp >= 0 || strcmp(network.getBuffer(&network), "VAL;y") == 0) {
			  ckp++;
			  network.setBuffer(&network, "VAL;longitude;latitude;hauteur;EOF;");
			  network.writeClient(&network, network.getClients(&network)[i].sock); 
			  break;
			}
		    
		    if (strcmp(network.getBuffer(&network), "VAL;n") == 0) {
		      network.setBuffer(&network, "VAL;longitude;latitude;hauteur;EOF;");
		      network.writeClient(&network, network.getClients(&network)[i].sock); 
		      break;
		    } 
		  }			  
		  
		  if (strncmp(network.getBuffer(&network), "CON;", 4) == 0) {
		    network.setBuffer(&network, "CON;y;EOF;");
		    network.writeClient(&network, network.getClients(&network)[i].sock); 
		    break;
		  }
		}
	    }
	}
    }
    }
  */
  
  
  printf("actual : %i\n", network.getActual(&network));

  manager.free(&manager);
  network.free(&network);
}

int main(int argc, char **argv)
{
  run();

  return EXIT_SUCCESS;
}
