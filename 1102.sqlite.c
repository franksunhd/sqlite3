#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>

#define M 32
#define N 128

int do_insert(sqlite3 *db);
int do_delete(sqlite3 *db);
int do_delete1(sqlite3 *db);
int do_show(sqlite3 *db);
int call_back(void *param, int column, char **value, char **name);
int do_show_1(sqlite3 *db);
int do_update(sqlite3 *db);

int main(int argc, char *argv[])
{
	sqlite3 *db;
	char *errmsg;
	char clean[M];
	int cmd;

	if (sqlite3_open("./my.db", &db) != SQLITE_OK)
	{
		printf("%s\n", sqlite3_errmsg(db));
		return -1;
	}

	int ret;
	//sql语句在编写时,如果需要分行写,那么需要添加连接符'\',而且连接符的后边不要带有空格
	if ((ret = sqlite3_exec(db, "create table stu(id integer, name vchar(32) not null,\
		score integer not null)", NULL, NULL, &errmsg)) != SQLITE_OK)
	{
		if (ret != 1)
		{
			printf("%s\n", errmsg);
			sqlite3_close(db);
			return -1;
		}
	}

	while (1)
	{
		printf("\e[32m*** 1:insert  2:delete  3:show  4:update  5:quit ***\e[0m\n");
		printf("please input your cmd > ");

		if (scanf("%d", &cmd) != 1)
		{
			puts("input error");
			fgets(clean, sizeof(clean), stdin);
			continue;
		}

		switch (cmd)
		{
		case 1:
			do_insert(db);
			break;
		case 2:
			//do_delete(db);
			do_delete1(db);
			break;
		case 3:
			do_show(db);
			//do_show_1(db);
			break;
		case 4:
			do_update(db);
			break;
		case 5:
			goto RET;
		default:
			break;
		}
	}

RET:
	sqlite3_close(db);
	return 0;
}

int do_insert(sqlite3 *db)
{
	int id;
	char name[M] = {0};
	int score;
	char sql[N] = {0};
	char *errmsg;
    char clean[M];

	printf("input  student id > ");
	while(scanf("%d", &id)!=1){
        puts("input error");
        fgets(clean,sizeof(clean),stdin);
        printf("please input student id again > ");
        if(scanf("%d",&id)!=0){
            break;
        }
    }

	printf("input  student name > ");
	scanf("%s", name);

	printf("input  student score > ");
	scanf("%d", &score);

	sprintf(sql, "insert into stu values(%d, '%s', %d)", id, name, score);
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return -1;
	}

	printf("\e[32minsert OK !\e[0m\n");
	return 0;
}

int do_delete(sqlite3 *db)
{
	int id;
	char sql[N] = {0};
	char *errmsg;

	printf("please input student id > ");
	scanf("%d", &id);

	sprintf(sql, "delete from stu where id = %d", id);

	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return -1;
	}

	printf("\e[32mdelete OK !\e[0m\n");
	return 0;
}

int do_delete1(sqlite3 *db)
{
    char sql[N] = {0};
    char name[M] = {0};
    char *errmsg;

    printf("please input student name > ");
    scanf("%s",name);
    do_show(db);
    
    sprintf(sql,"delete from stu where name = '%s' \n",name);
    printf(sql);


    if(sqlite3_exec(db,sql,NULL, NULL,&errmsg)!=SQLITE_OK)
    {
        printf("%s\n",errmsg);
        return -1;
    }

    printf("\e[32m delete OK !\e[0m\n");
    return 0;
}


















int do_show(sqlite3 *db)
{
	char *errmsg;
	int a = 0;

	if (sqlite3_exec(db, "select * from stu", call_back, &a, &errmsg ) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return -1;
	}

	printf("\e[32mshow OK !\e[0m\n");
	return 0;
}

int call_back(void *param, int column, char **value, char **name)
{
	int a;
	int i = 0;
	a = (*(int*)param)++;

	if ( a == 0)
	{
		for (i = 0; i < column; i++)
		{
			printf("%-15s", *(name++));
		}

		putchar(10);
	}

	for (i = 0; i < column; i++)
	{
		printf("%-15s", *(value++));
	}

	putchar(10);
	return 0;
}

int do_show_1(sqlite3 *db)
{
	char *errmsg;
	char **result, **temp;
	int nrow;
	int ncolumn;
	int i, j;

	if (sqlite3_get_table(db, "select * from stu", &result, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return -1;
	}
	else
	{
		temp = result;
		for (i = 0; i < nrow + 1; i++)
		{
			for (j = 0; j < ncolumn; j++)
				printf("%-15s", *(temp++));
			putchar(10);
		}
	}

	sqlite3_free_table(result);
	printf("\e[32mshow OK !\e[0m\n");

	return 0;
}

int do_update(sqlite3 *db)
{
	int id;
	int score;
	char sql[N] = {0};
	char *errmsg;

	printf("please input student id >> ");
	scanf("%d", &id);

	printf("please input student score >> ");
	scanf("%d", &score);

	sprintf(sql, "update stu set score = %d  where id = %d", score, id);

	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return -1;
	}

	puts("update OK !");
	return 0;
}
