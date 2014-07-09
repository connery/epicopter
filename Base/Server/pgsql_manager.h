#ifndef __PGSQL_MANAGER__
#define __PGSQL_MANAGER__

#ifdef __cplusplus
extern "C" {
#endif

#include <libpq-fe.h>

typedef struct PGManager
{
  const char *conninfo;
  PGconn *conn;
  PGresult *res;
  
  void(*connectPManager)(struct PGManager *this);
  void(*execPSQL)(struct PGManager *this, char *request);
  void(*printPResults)(struct PGManager *this);

  const char*(*getConnInfo)(struct PGManager *this);
  PGconn*(*getConn)(struct PGManager *this);
  PGresult*(*getResult)(struct PGManager *this);

  void(*setConnInfo)(struct PGManager *this, const char *new);
  void(*setConn)(struct PGManager *this, PGconn *new);
  void(*setResult)(struct PGManager *this, PGresult *new);

  void(*free)(struct PGManager *this);
}
  PGManager;
  
  PGManager createPManager(void);
  void connectPManager(PGManager *this);
  void execPSQL(PGManager *this, char *request);
  void printPResults(PGManager *this);
  void freePManager(struct PGManager *this);
  void closePManager(PGManager *this);

  const char *getConnInfo(PGManager *this);
  PGconn *getConn(PGManager *this);
  PGresult *getResult(PGManager *this);

  void setConnInfo(PGManager *this, const char* new);
  void setConn(PGManager *this, PGconn *new);
  void setResult(PGManager *this, PGresult *new);

#ifdef __cplusplus
}
#endif

#endif
