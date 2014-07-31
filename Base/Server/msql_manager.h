#ifndef __MSQL_MANAGER_H__
#define __MSQL_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

  //#include <my_global.h>
#include <mysql/mysql.h>
#include "server.h"

typedef struct SQLManager
{
  MYSQL *db;
  Flightplan fp;
  char *request;

  MYSQL*(*getDB)(struct SQLManager *this);
  void(*setDB)(struct SQLManager *this, MYSQL *new);
  
  Flightplan(*getFP)(struct SQLManager *this);
  void(*setFP)(struct SQLManager *this, Flightplan new);
  
  char*(*getRequest)(struct SQLManager *this);
  void(*setRequest)(struct SQLManager *this, char *new);

  void(*free)(struct SQLManager *this);
  void(*connectManager)(struct SQLManager *this, char *db_name,
			char *db_user, char *db_pwd);
  void(*execSQL)(struct SQLManager *this);
  void(*printMResults)(struct SQLManager *this);
  Flightplan(*generateFlightPlan)(struct SQLManager *this);
} 
  SQLManager;

  SQLManager createManager(void);
  void closeManager(SQLManager *this);
  void freeManager(struct SQLManager *this);
  void connectManager(SQLManager *this, char *db_name, char *db_user, char *db_pwd);

  MYSQL *getDB(SQLManager *this);
  void setDB(SQLManager *this, MYSQL *new);
  
  Flightplan getFP(SQLManager *this);
  void setFP(SQLManager *this, Flightplan new);
  
  char *getRequest(SQLManager *this);
  void setRequest(SQLManager *this, char *new);

  void execSQL(SQLManager *this);
  void printMResults(SQLManager *this);
  Flightplan generateFlightPlan(SQLManager *this);
#ifdef __cplusplus
}
#endif

#endif
