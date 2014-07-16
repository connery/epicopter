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

  MYSQL*(*getDB)(struct SQLManager *this);
  void(*setDB)(struct SQLManager *this, MYSQL *new);
  void(*free)(struct SQLManager *this);
  void(*connectManager)(struct SQLManager *this, char *db_name,
			char *db_user, char *db_pwd);
  void(*execSQL)(struct SQLManager *this, char *request);
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
  void execSQL(SQLManager *this, char *request);
  void printMResults(SQLManager *this);
  Flightplan generateFlightPlan(SQLManager *this);
#ifdef __cplusplus
}
#endif

#endif
