#ifndef DB_MYSQL_H
#define DB_MYSQL_H

#include <my_global.h>
#include <winsock2.h>
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")

class DB_MySQL{

	MYSQL		mysql;
	MYSQL		*connection;
	MYSQL_RES   *sql_result;
	MYSQL_ROW   sql_row;
	int			query_stat;


	inline void checkConnection(void);

public:

	DB_MySQL(void);
	~DB_MySQL(void);

	bool connectDB(MYSQL *mysql);
	void disconnectDB(MYSQL *mysql);
	void runQuery(MYSQL *mysql, const char *query);

};

#endif // DB_MYSQL_H
