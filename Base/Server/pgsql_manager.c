#include <errno.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "pgsql_manager.h"

static void initPG(PGManager *this);

PGManager createPManager() {
  PGManager this;
  this.conninfo = "dbname = postgres";
  initPG(&this);
  this.free = freePManager;
  puts("PG db created");
  return this;
}

static void initPG(PGManager *this) {
  this->conn = PQconnectdb(this->conninfo);
  this->res = NULL;
  this->conninfo = NULL;

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

