#ifndef DB_MYSQL_H
#define DB_MYSQL_H

#include <QHash>
#include <QStringList>
#include <string>

#include <my_global.h>
#include <winsock2.h>
#include <mysql.h>

#include <qstring.h> 
#include <qtextcodec.h>

#include <qmessagebox.h>

#pragma comment(lib, "libmysql.lib")
#include "../define.h"


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

	bool isConnection(void);
	bool connectDB(void);
	void disconnectDB(void);
	resultTable runQuery(const char *query);

};


#endif // DB_MYSQL_H
