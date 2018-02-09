/*
 * 
 * Created on: Dec 26, 2017
 * Author: Xiaoteng Hu
 * Description:mydb.h
 *
 *
 */

#ifndef SRC_MYDB_MYDB_H_
#define SRC_MYDB_MYDB_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <mysql/mysql.h>
#include "../struct/structs.h"

using namespace std;

void init_db();
int conn_db(const char *hostname, const char *username, const char *password, const char *dbname);
void disconn_db();
int open_db(const char *SQL);
int exec_db(const char *SQL);

int getCount(const char *SQL);
string getValue(const char *SQL);
int updateInfo(const char *SQL);
list<IndexInfo> getIndexList(const char *SQL);


#endif /* SRC_MYDB_MYDB_H_ */
