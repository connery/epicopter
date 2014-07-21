#include <errno.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "server.h"
#include "pgsql_manager.h"

static void initPG(PGManager *this);

PGManager createPManager() {
  PGManager this;
  this.conninfo = "dbname = epicopter";
  initPG(&this);
  this.free = freePManager;
  puts("PG db created.");
  return this;
}

static void initPG(PGManager *this) {
  this->conn = PQconnectdb(this->conninfo);
  this->res = NULL;
  this->conninfo = NULL;

  this->getConnInfo = getConnInfo;
  this->getConn = getConn;
  this->getResult = getResult;

  this->setConnInfo = setConnInfo;
  this->setConn = setConn;
  this->setResult = setResult;

  this->connectPManager = connectPManager;
  this->execPSQL = execPSQL;
  this->printPResults = printPResults;
  this->generatePFlightPlan = generatePFlightPlan;
}

void connectPManager(PGManager *this) {
  if (PQstatus(this->conn) != CONNECTION_OK)
    {
      fprintf(stderr, "Connection to PGSQL database failed: %s",
	      PQerrorMessage(this->conn));
      PQfinish(this->conn);
    }
  else
    puts("Connected to PGSQL databse.");
}

void closePManager(PGManager *this) {
  if (this->res != NULL)
    PQclear(this->res);
  
  if (this->conn != NULL)
    PQfinish(this->conn);

  this->conninfo = NULL;
  this->conn = NULL;
  this->res = NULL;
}

void execPSQL(PGManager *this, char *request) {

  if (PQstatus(this->getConn(this)) == CONNECTION_OK) {
    
    this->setResult(this, PQexec(this->getConn(this), request));
    if (PQresultStatus(this->getResult(this)) != PGRES_TUPLES_OK)
      fprintf(stderr, "Request failed: %s", PQerrorMessage(this->getConn(this)));
    else
      puts("Exec PGSQL succeed");
  }
}

void printPResults(PGManager *this) {
  int i, j;

  int nFields = PQnfields(this->getResult(this));
  
  for (i = 0; i < PQntuples(this->getResult(this)); i++)
    {      
      for (j = 0; j < nFields; j++)
	printf("%s =>", PQgetvalue(this->getResult(this), i, j));
      
      printf("\n");
    }

}

Flightplan generatePFlightPlan(PGManager *this) {
  Flightplan f;
  int i;

  f.id = 1;
  f.route = malloc(sizeof(Checkpoint) * PQntuples(this->getResult(this)));
  
  for (i = 0; i < PQntuples(this->getResult(this)); i++)
    {
    Checkpoint cp = {"", "", "", ""};
    
    strcat(cp.id, PQgetvalue(this->getResult(this), i, 0));
    strcat(cp.latitude, PQgetvalue(this->getResult(this), i, 1));
    strcat(cp.longitude, PQgetvalue(this->getResult(this), i, 2));
    strcat(cp.height, PQgetvalue(this->getResult(this), i, 3));
    f.route[i] = cp;
    printf("Checkpoint no %s\nLatitude %s Longitude %s Hauteur %s\n",
	   f.route[i].id, f.route[i].latitude, f.route[i].longitude, f.route[i].height);
    }
  return f;
}

void freePManager(PGManager *this) {
  closePManager(this);
  puts("PGSQL Manager destroyed.");
}

const char* getConnInfo(PGManager *this) {
  return this->conninfo;
}

PGconn *getConn(PGManager *this) {
  return this->conn;
}

PGresult *getResult(PGManager *this) {
  return this->res;
}

void setConnInfo(PGManager *this, const char* new) {
  this->conninfo = new;
}

void setConn(PGManager *this, PGconn *new) {
  this->conn = new;
}

void setResult(PGManager *this, PGresult *new) {
  this->res = new;
}