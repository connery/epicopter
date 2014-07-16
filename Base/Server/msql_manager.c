#include <errno.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "server.h"
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


Checkpoint createRow(MYSQL_ROW row, int nbField) {
  Checkpoint cp = {0, 12, 34, 56};

  return cp;
}


void generateRes(MYSQL_RES *res, SQLManager *this) {
  int i, j;
  int nbRow, nbField;

  printf("printres \n");

  nbRow = mysql_num_rows(res);
  nbField =  mysql_num_fields(res);

  Flightplan f;
  f.id = 1;
  f.route = malloc(sizeof(Checkpoint) * nbRow);

  MYSQL_ROW row;
  i = 0;
  
  printf("Before while\n");
  
  while (row = mysql_fetch_row(res)) {
    printf("Entering while\n");
    Checkpoint cp = {i, i, i, i};
    f.route[i] = cp;
    printf("Checkpoint no %i\nLatitude %i Longitude %i Hauteur %i\n", f.route[i].id, f.route[i].latitude, f.route[i].longitude, f.route[i].height);
    i++;
  }
}

void printMResults(SQLManager *this) {
 
  MYSQL_RES *result = mysql_store_result(this->db);
  
  if (result == NULL) 
    closeManager(&this);

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  
  int i;

  printf("numbers of fields %i\n", num_fields);
  printf("numbers of row %i\n", mysql_num_rows(result));

  printf("Test double tab\n");
  
  generateRes(result, this);
}


/*
void getRows(MYSQL_RES res) {
  char *ret = malloc(sizeof(char) * 55);

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  
  int i;

  while ((row = mysql_fetch_row(result))) 
    for(i = 0; i < num_fields; i++) 
      {

	printf("%s ", row[i] ? row[i] : "NULL");
      }

  printf("\n"); 

  return ret;
}
*/
