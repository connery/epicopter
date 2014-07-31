#ifndef __PGSQL_MANAGER__
#define __PGSQL_MANAGER__

#ifdef __cplusplus
extern "C" {
#endif

#include <libpq-fe.h>
#include "server.h"

typedef struct PGManager
{
  const char *conninfo;
  PGconn *conn;
  PGresult *res;
  Flightplan fp;
  char *request;

  void(*connectPManager)(struct PGManager *this);
  void(*execPSQL)(struct PGManager *this);
  void(*printPResults)(struct PGManager *this);
  Flightplan(*generatePFlightPlan)(struct PGManager *this);

  const char*(*getConnInfo)(struct PGManager *this);
  PGconn*(*getConn)(struct PGManager *this);
  PGresult*(*getResult)(struct PGManager *this);
  Flightplan(*getPFP)(struct PGManager *this);
  char*(*getPRequest)(struct PGManager *this);

  void(*setConnInfo)(struct PGManager *this, const char *new);
  void(*setConn)(struct PGManager *this, PGconn *new);
  void(*setResult)(struct PGManager *this, PGresult *new);
  void(*setPFP)(struct PGManager *this, Flightplan new);
  void(*setPRequest)(struct PGManager *this, char* new);

  void(*free)(struct PGManager *this);
}
  PGManager;
  
  PGManager createPManager(void);
  void connectPManager(PGManager *this);
  void execPSQL(PGManager *this);
  void printPResults(PGManager *this);
  void freePManager(struct PGManager *this);
  void closePManager(PGManager *this);
  Flightplan generatePFlightPlan(PGManager *this);

  const char *getConnInfo(PGManager *this);
  PGconn *getConn(PGManager *this);
  PGresult *getResult(PGManager *this);
  Flightplan getPFP(PGManager *this);
  char* getPRequest(PGManager *this);

  void setConnInfo(PGManager *this, const char* new);
  void setConn(PGManager *this, PGconn *new);
  void setResult(PGManager *this, PGresult *new);
  void setPFP(PGManager *this, Flightplan new);
  void setPRequest(PGManager *this, char *new);
#ifdef __cplusplus
}
#endif

#endif
