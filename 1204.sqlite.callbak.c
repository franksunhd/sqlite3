#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int call_back(void *param, int column, char **value, char **name);

int main()
{
	// 定义数据库句柄
	sqlite3 *db;
	char *errmsg;
	char sql[128];
	int a = 0;
	//出错判断
	if (sqlite3_open("./my.db", &db) != SQLITE_OK)
	{
		//打印出错原因
		printf("%s\n", sqlite3_errmsg(db));
		return -1;
	}
		
	
	//执行sql语句
	if (sqlite3_exec(db, "select * from stu", call_back, &a, &errmsg ) != SQLITE_OK)
	{
		//不是已经存在的错误，那么必须退出
		printf("%s\n", errmsg);
		//关闭数据库
		sqlite3_close(db);
		return -1;
	}
	//关闭数据库
	sqlite3_close(db);
	return 0;
}


//每次查询到符合条件的都会被调用一次
int call_back(void *param, int column, char **value, char **name)
{
	int a;
	int i = 0;
	a = (*(int*)param)++;

	if ( a == 0)
	{
		//输出该表格的列名, column 是列的个数
		for (i = 0; i < column; i++)
		{
			printf("%-8s", *(name)++);
		}
		printf("\n");
	}

	//输出符合条件的一条数据
	for (i = 0; i < column; i++)
	{
		printf("%-8s", *(value)++);
	}

	printf("\n");
	return 0;
}



