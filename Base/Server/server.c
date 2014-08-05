#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
//#include <my_global.h>
#include <mysql/mysql.h>

#include "server.h"

void *myPSQLThread(PGManager *manager) {
  puts("PGSQL thread started");
  manager->execPSQL(manager);
  manager->setPFP(manager, manager->generatePFlightPlan(manager));
  puts("PGSQL thread ended");
}

void *mySQLThread(SQLManager *manager) {
  puts("SQL thread started");
  manager->execSQL(manager);
  manager->setFP(manager, manager->generateFlightPlan(manager));
  puts("SQL thread ended");
}


static void run(void)
{  
  Network network = createNetwork();
  SQLManager manager = createManager();
  PGManager managere = createPManager();

  int max = network.getSocket(&network);
  int singleton = 0;
  fd_set rdfs;
  int ckp = 0;

  Flightplan k;
  pthread_t tid;
  void *status;

  manager.connectManager(&manager, "localhost", "root", "root");
  managere.connectPManager(&managere);

  if (manager.getDB(&manager) != NULL) {
    manager.setRequest(&manager, "USE epicopter");
    manager.execSQL(&manager);
    
    manager.setRequest(&manager, "SELECT * FROM flights");
    pthread_create(&tid, NULL, mySQLThread, &manager);
    pthread_join(tid, &status);
    
    k = manager.getFP(&manager);
    
    int u ;
    for (u = 0; u < k.nbCkp; u++)
      puts(generateReturn(&k, u));
    
  }
  else
    puts("error");

  /*
  if (managere.getConn(&managere) != NULL)
    {
      managere.setPRequest(&managere, "SELECT * FROM flight");
      pthread_create(&tid, NULL, myPSQLThread, &managere);
      pthread_join(tid, &status);
      
      k = managere.getPFP(&managere);

      int u ;
      for (u = 0; u < k.nbCkp; u++)
	puts(generateReturn(&k, u));
    }
  */
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
		      launch(&network, i);
		      break;
		    }
		  
		    if (strcmp(network.getBuffer(&network), "END;") == 0) {
		      network.removeClient(&network, i);
		      break;
		    }

		    if (strncmp(network.getBuffer(&network), "ENV;", 4) == 0) {
		      puts("Sent buffer");
		      puts(network.getBuffer(&network));
		      if (strcmp(network.getBuffer(&network), "ENV;FIN;") != 0) {
			network.setBuffer(&network, "ENV;OK;EOF;");
			network.writeClient(&network, network.getClients(&network)[i].sock); 
			break;
		      }
		      else {
			puts("End sending");
			break;
		      }
		    }
		    
		    if (strncmp(network.getBuffer(&network), "VAL;", 4) == 0) {
		      validation(&network, &manager, i, &ckp);
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
  

  managere.free(&managere);
  manager.free(&manager);
  network.free(&network);
}

int main(int argc, char **argv)
{
  run();

  return EXIT_SUCCESS;
}
