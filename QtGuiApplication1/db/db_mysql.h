#ifndef DB_MYSQL_H
#define DB_MYSQL_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QStringList>
#include <string>
#include <QByteArray>

#include <my_global.h>
#include <winsock2.h>
#include <mysql.h>

#include <qstring.h> 
#include <qtextcodec.h>

#include <qmessagebox.h>

#pragma comment(lib, "libmysql.lib")
#include "define.h"

class requestQueue : public QList<QByteArray> {

	uint requestID;

public:
	requestQueue();
	~requestQueue();

	uint getRequestID(void) {return requestID;}
	const QByteArray getStrQuery_popBack();
	QByteArray getQueryKind();
	void requestQuery(QByteArray query);
};

	
class DB_MySQL : public QObject {
	Q_OBJECT

	bool		isReading;

	resultTable resultBuffer;

	requestQueue mQueryQueue;

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

	void requestQuery(QByteArray query);
	resultTable runQuery(const char *query);
	bool updateQuery(const char *query);

signals:
	void sigGETDATA(resultTable *);

public slots:
	void Running_receiveDB();

};


#endif // DB_MYSQL_H