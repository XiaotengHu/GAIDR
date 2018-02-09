/*
 * 
 * Created on: Dec 26, 2017
 * Author: Xiaoteng Hu
 * Description:mydb.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */


#include "mydb.h"

MYSQL *connection = NULL;
MYSQL mysql;

void init_db(){
	mysql_init(&mysql);
}

int conn_db(const char *hostname,const char *username, const char *password, const char *dbname){
	if(connection){
		mysql_close(connection);
	}
	connection = mysql_real_connect(&mysql, hostname, username, password, dbname, 0, 0, 0);
	cout<<"connection!!!!!"<<connection<<endl;
	if(connection == NULL){
	   printf("%s\n", mysql_error(&mysql));
	   return -1;
	}
	printf("success connect to mysql \n");
	return 0;
}

//close mysql
void disconn_db(){
	if(connection){
		mysql_close(connection);
		connection = NULL;
	}
}
//run sql
int open_db(const char *SQL){
	int state = mysql_query(connection,SQL);
	if(state !=0){
		printf("%s\n", mysql_error(connection));
		return -1;
	}
	MYSQL_RES *result = mysql_store_result(connection);

	if(result == (MYSQL_RES *) NULL){
		printf("%s\n", mysql_error(connection));
		return -1;
	}else{
		MYSQL_FIELD *sqlField;
		int iFieldCount = 0;

		while(1){
			sqlField = mysql_fetch_field(result);
			if(sqlField == NULL){
				break;
			}
			printf("%s\t", sqlField->name);
			iFieldCount++;
		}
		printf("\n");

		MYSQL_ROW sqlRow;
		while(1){
			sqlRow = mysql_fetch_row(result);
			if(sqlRow == NULL){
				break;
			}

			for(int i = 0; i< iFieldCount; i++){
				if(sqlRow[i] == NULL){
					printf("NULL\t");
				}else{
					printf("%s\t", (const char *)sqlRow[i]);
				}
			}
			printf("\n");
		}
		printf("query is ok, %u rows affected\n", (unsigned int)mysql_affected_rows(connection));
		mysql_free_result(result);
	}
	return 0;
}

int exec_db(const char *SQL){
	int state = mysql_query(connection,SQL);
	if(state !=0){
		printf("%s\n", mysql_error(connection));
		return -1;
	}
	printf("query is ok, %u rows affected\n", (unsigned int)mysql_affected_rows(connection));
	return 0;
}

int getCount(const char *SQL){
	cout<<"SQL!!!!!"<<SQL<<endl;
	cout<<"connection!!!!!"<<connection<<endl;
	int state = mysql_query(connection, SQL);
	cout << "state" << state <<endl;
	if(state !=0){
		printf("%s\n", mysql_error(connection));
		return -1;
	}

	MYSQL_RES *result = mysql_store_result(connection);

	if(result == (MYSQL_RES *) NULL) {
		printf("%s\n", mysql_error(connection));
		return -1;
	}else{
		MYSQL_FIELD *sqlField;
		int iFieldCount = 0;

		while(1){
			sqlField = mysql_fetch_field(result);
			if(sqlField == NULL){
				break;
			}
			iFieldCount++;
		}
		MYSQL_ROW sqlRow;
		while(1){
			sqlRow = mysql_fetch_row(result);
			if(sqlRow == NULL){
				break;
			}
			for(int i =0;i<iFieldCount;i++){
				if(sqlRow[i] == NULL){
					return -1;
				}else{
					return atoi(sqlRow[i]);
				}
			}
		}
		mysql_free_result(result);
	}
	return -1;
}

string getValue(const char *SQL){
	int state = mysql_query(connection,SQL);
	if(state !=0){
		printf("%s\n", mysql_error(connection));
		return "";
	}
	MYSQL_RES *result = mysql_store_result(connection);

	if(result == (MYSQL_RES *) NULL){
		printf("%s\n",mysql_error(connection));
		return "";
	}else{
		MYSQL_FIELD *sqlField;
		int iFieldCount = 0;

		while(1){
			sqlField = mysql_fetch_field(result);
		    if(sqlField == NULL){
		    	break;
		    }
		    iFieldCount++;
		}
		cout<<"sqlRow[i]"<<iFieldCount<<endl;
		MYSQL_ROW sqlRow;
		while(1){
			sqlRow = mysql_fetch_row(result);
			if(sqlRow == NULL){
				break;
			}
			for(int i=0;i <iFieldCount;i++){
				if(sqlRow[i] == NULL){
		    		return "";
				}else{
					return sqlRow[i];
					cout<<"sqlRow[i]"<<sqlRow[i]<<endl;
				}
			}
		}
		mysql_free_result(result);
	}
	return "";
}

int updateInfo(const char *SQL){
	int state = mysql_query(connection,SQL);
	if(state!=0){
		printf("%s\n",mysql_error(connection));
		return -1;
	}
	return 0;
}





