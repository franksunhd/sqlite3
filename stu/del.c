#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	
	char stuId[32] = "\0";
	int status = 0;


	status = cgiFormString("stuId",  stuId, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}

	char *errmsg;
	sqlite3 *db;
	char sql[128] = "\0";


	if (sqlite3_open("./stu.db", &db) != SQLITE_OK)
	{
		fprintf(cgiOut,"%s\n", sqlite3_errmsg(db));
		return -1;
	}

	sprintf(sql, "delete from stu where id = '%s'", stuId);

	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		fprintf(cgiOut,"%s\n", errmsg);
		sqlite3_close(db);
		return -1;
	}

	fprintf(cgiOut, "delete stu ok!\n");
	sqlite3_close(db);

	return 0;
}
