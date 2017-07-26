#ifndef DB_MYSQL_H
#define DB_MYSQL_H

#include <QHash>
#include <QStringList>

#include <my_global.h>
#include <winsock2.h>
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")

typedef struct {
	bool chk;
	unsigned int row;
	unsigned int col;
	QStringList recode;
} resultTable;

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

	bool connectDB(void);
	void disconnectDB(void);
	resultTable runQuery(const char *query);

};


#endif // DB_MYSQL_H
