#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char name[32] = "\0";
	char age[16] = "\0";
	char stuId[32] = "\0";
	int status = 0;

	status = cgiFormString("name",  name, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get name error!\n");
		return 1;
	}

	status = cgiFormString("age",  age, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get age error!\n");
		return 1;
	}

	status = cgiFormString("stuId",  stuId, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}

	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	char *errmsg;
	sqlite3 *db;
	int result;
	char sql[128] = "\0";


	if (sqlite3_open("./stu.db", &db) != SQLITE_OK)
	{
		fprintf(cgiOut,"--%s\n", sqlite3_errmsg(db));
		return -1;
	}


	if ((result = sqlite3_exec(db, "create table stu(id vchar(32) not null, name vchar(32) not null,\
		age integer not null)", NULL, NULL, &errmsg)) != SQLITE_OK)
	{
		if (result != 1)
		{
			fprintf(cgiOut,"++++%s\n", errmsg);
			sqlite3_close(db);
			return -1;
		}
	}

	sprintf(sql, "insert into stu values('%s', '%s', %d)", stuId, name, atoi(age));
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		fprintf(cgiOut, "%s\n", errmsg);
		sqlite3_close(db);
		return -1;
	}

	fprintf(cgiOut, "add student ok!\n");
	sqlite3_close(db);
	return 0;
}
