#ifndef __DB_MANAGER_H__
#define __DB_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <my_global.h>
#include <mysql.h>

typedef struct SQLManager
{
  MYSQL *db;

  MYSQL*(*getDB)(struct SQLManager *this);
  void(*setDB)(struct SQLManager *this);
  void(*free)(struct SQLManager *this);
} 
  SQLManager;

  SQLManager createManager(void);
  void closeManager(SQLManager *this);
  void freeManager(struct SQLManager *this);

  MYSQL *getDB(SQLManager *this);
  void setDB(SQLManager *this, MYSQL *new);

#ifdef __cplusplus
}
#endif

#endif
