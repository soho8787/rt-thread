#include <stdio.h>
#include <sqlite3.h>
#include "finsh.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    rt_kprintf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  rt_kprintf("\n");
  return 0;
}

int test10_main(int argc, char **argv){
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  if( argc!=3 ){
    rt_kprintf("Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
    return(1);
  }
  rc = sqlite3_open(argv[1], &db);
  if( rc ){
    rt_kprintf("Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }
  rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
  if( rc!=SQLITE_OK ){
    rt_kprintf("SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
  return 0;
}
FINSH_FUNCTION_EXPORT(test10_main, sqlite test)