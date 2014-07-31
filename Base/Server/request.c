#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
//#include <my_global.h>
#include <mysql/mysql.h>

#include "server.h"

void launch(Network *network, int current) {
  network->setBuffer(network, "LAN;0005;EOF;");
  network->writeClient(network, network->getClients(network)[current].sock);
}

void validation(Network *network, SQLManager *manager, int current, int *nbCp) {
  Flightplan f;
  pthread_t tid;
  void *status;

  f = manager->getFP(manager);
  
  if (strncmp(network->getBuffer(network), "VAL;", 4) == 0) {
    if ((*nbCp) == 0) {
      manager->setRequest(manager, "SELECT * FROM flights");
      pthread_create(&tid, NULL, mySQLThread, manager);
      pthread_join(tid, &status);
      f = manager->getFP(manager);
    }
    network->setBuffer(network, generateReturn(&f, (*nbCp)));
    network->writeClient(network, network->getClients(network)[current].sock);
    (*nbCp)++;  
  }
  else if ((*nbCp) == f.nbCkp
	   && strncmp(network->getBuffer(network), "VAL;", 4) == 0) {
    network->setBuffer(network, "VAL;fin;EOF;");
    network->writeClient(network, network->getClients(network)[current].sock); 
    (*nbCp) = 0;  
  }

  else if (strcmp(network->getBuffer(network), "VAL;n") == 0 && nbCp < f.nbCkp) {
    network->setBuffer(network, generateReturn(&f, nbCp));
    network->writeClient(network, network->getClients(network)[current].sock); 
  }
}
