#include <errno.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "msql_manager.h"

static void initDB(SQLManager *this);
static void putError(SQLManager *this);

SQLManager createManager()
{
  SQLManager this;
  initDB(&this);
  this.free = freeManager;
  puts("MYSQL manager created.");
  return this;
}

static void putError(SQLManager *this) {
  fprintf(stderr, "%s\n", mysql_error(this->db));
}

static void initDB(SQLManager *this)
{
  this->db = mysql_init(NULL);
  if (this->db == NULL)
    putError(this);
  
  this->getDB = getDB;
  this->setDB = setDB;
  
  this->connectManager = connectManager;
  this->execSQL = execSQL;
  this->printMResults = printMResults;
}

MYSQL *getDB(SQLManager *this) {
  return this->db;
}

void setDB(SQLManager *this, MYSQL *new) {
  this->db = new;
}

void connectManager(SQLManager *this, char *db_name, char *db_user, char *db_pwd) {
  if (mysql_real_connect(this->db, db_name, db_user, db_pwd,
			 NULL, 0, NULL, 0) == NULL) {
    putError(this);
    closeManager(this);
  } else
    puts("Connected to MYSQL databse.");
}

void execSQL(SQLManager *this, char *request) {
  if (mysql_query(this->db, request) == 1) {
    putError(this);
    closeManager(this);
  } else
    puts("Request done.");
}

void closeManager(SQLManager *this) {
  mysql_close(this->db);
  this->db = NULL;
}

void freeManager(SQLManager *this) {
  closeManager(this);
  puts("MYSQL Manager destroyed.");
}

void printMResults(SQLManager *this) {
 
  MYSQL_RES *result = mysql_store_result(this->db);
  
  if (result == NULL) 
    closeManager(&this);

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  
  int i;
  while ((row = mysql_fetch_row(result))) 
    for(i = 0; i < num_fields; i++) 
      printf("%s ", row[i] ? row[i] : "NULL"); 
  printf("\n"); 
}
