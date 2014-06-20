#include <errno.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "db_manager.h"

static void initDB(SQLManager *this);

SQLManager createManager()
{
  SQLManager this;
  initDB(&this);
  this.free = freeManager;
  puts("DB created");
  return this;
}

static void initDB(SQLManager *this)
{
  this->db = mysql_init(NULL);
  if (this->db == NULL)
    fprintf(stderr, "%s\n", mysql_error(this->db));
  
  this->getDB = getDB;
  this->setDB = setDB;
}

MYSQL *getDB(SQLManager *this) {
  return this->db;
}

void setDB(SQLManager *this, MYSQL *new) {
  this->db = new;
}

void closeManager(SQLManager *this) {
  mysql_close(this->db);
  this->db = NULL;
}

void freeManager(SQLManager *this) {
  closeManager(this);
  puts("Manager destroyed");
}
