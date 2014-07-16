#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
//#include <my_global.h>
#include <mysql/mysql.h>

#include "server.h"

static void run(void)
{  
  Network network = createNetwork();
  SQLManager manager = createManager();
  PGManager managere = createPManager();
  
  int max = network.getSocket(&network);
  int singleton = 0;
  fd_set rdfs;
  int ckp = 1;

  manager.connectManager(&manager, "localhost", "root", "root");
  managere.connectPManager(&managere);
  
  if (manager.getDB(&manager) != NULL) {
    manager.execSQL(&manager, "USE epicopter");
    manager.execSQL(&manager, "SELECT * FROM epicopter;");
    manager.printMResults(&manager);
  }
  else
    puts("error");

  if (managere.getConn(&managere) != NULL)
    {
      managere.execPSQL(&managere, "SELECT * FROM flight;");
      managere.printPResults(&managere);
    }
  
  
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
			ckp = 0;
			break;
		      }
		      else if (ckp < 5 &&
			       (ckp >= 0 || strcmp(network.getBuffer(&network), "VAL;y") == 0)) {
			/*
			char rqt = "SELECT * FROM test WHERE ";
			char *tmp = malloc(strlen(rqt) + 8);
			strcat(rqt, 
			

			ckp++;
			network.setBuffer(&network, "VAL;43;35;50;EOF;");
			network.writeClient(&network, network.getClients(&network)[i].sock); 
			break;
		      }
		    
		    if (strcmp(network.getBuffer(&network), "VAL;n") == 0) {
		      network.setBuffer(&network, "VAL;latitude;longtitude;hauteur;EOF;");
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
  
  managere.free(&managere);
  manager.free(&manager);
  network.free(&network);
}

int main(int argc, char **argv)
{
  run();

  return EXIT_SUCCESS;
}
