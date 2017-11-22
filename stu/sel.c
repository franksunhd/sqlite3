#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "cgic.h"

int call_back(void *param, int column, char **value, char **name);

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	fprintf(cgiOut, "<head><meta charset=\"utf-8\"/><title>查询结果</title>\
			<style>table {width:400px; margin: 50px auto; border: 1px solid gray; border-collapse: collapse; border-spacing: none; text-align:center;}\
			tr,td,th{border: 1px solid gray;}\
			</style>\
			</head>");

	char name[32] = "\0";
	int status = 0;

	status = cgiFormString("name",  name, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get name error!\n");
		return 1;
	}

	sqlite3 *db;
	char *errmsg;
	char sql[128];
	int a = 0;

	if (sqlite3_open("./stu.db", &db) != SQLITE_OK)
	{
		fprintf(cgiOut,"%s\n", sqlite3_errmsg(db));
		return -1;
	}

	if (name[0] == '*') 
	{
		sprintf(sql, "select * from stu");
	}
	else 
	{
		sprintf(sql, "select * from stu where name = '%s'", name);
	}

	if (sqlite3_exec(db, sql, call_back, &a, &errmsg ) != SQLITE_OK)
	{
		fprintf(cgiOut, "%s\n", errmsg);
		sqlite3_close(db);
		return -1;
	}


	fprintf(cgiOut, "</table>");
	sqlite3_close(db);
	return 0;
}

int call_back(void *param, int column, char **value, char **name)
{
	int a;
	int i = 0;
	a = (*(int*)param)++;

	if ( a == 0)
	{
		fprintf(cgiOut, "<table>");

		fprintf(cgiOut, "<tr>");
		for (i = 0; i < column; i++)
		{
			fprintf(cgiOut, "<th>%s</th>", *(name++));
		}
		fprintf(cgiOut, "</tr>");
	}

	fprintf(cgiOut, "<tr>");
	for (i = 0; i < column; i++)
	{
		fprintf(cgiOut,"<td>%s</td>", *(value++));
	}
	fprintf(cgiOut, "</tr>");

	return 0;
}



