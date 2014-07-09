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

  const char*(*getConnInfo)(struct PGManager *this);
  PGconn*(*getConn)(struct PGManager *this);
  PGresult*(*getResult)(struct PGManager *this);

  void(*setConnInfo)(struct PGManager *this, const char *info);
  void(*setConn)(struct PGManager *this, PGconn *conn);
  void(*setResult)(struct PGManager *this, PGresult *res);

  void(*free)(struct PGManager *this);
}
  PGManager;
  
  PGManager createPManager(void);
  void connectPManager(PGManager *this);
  void freePManager(struct PGManager *this);
  void closePManager(PGManager *this);

  const char *getConnInfo(PGManager *this);
  PGconn *getConn(PGManager *this);
  PGresult *getResult(PGManager *this);

  void setConnInfo(PGManager *this, const char* info);
  void setConn(PGManager *this, PGconn *conn);
  void setResult(PGManager *this, PGresult *res);

#ifdef __cplusplus
}
#endif

#endif
