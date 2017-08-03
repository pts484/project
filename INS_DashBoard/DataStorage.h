#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QDebug>
#include <QObject>
#include <QHash>
#include <QList>
#include <QStringList>


#include <QStandardItem>
#include "../db/db_mysql.h"
#include "define.h"


typedef struct {
	int num;
	QStandardItem *type;
} D_TYPE;

typedef QList<D_TYPE *> deviceType;

typedef QList<QStandardItem *> dbVelue;
typedef QList<dbVelue *>	   dbStorage;

class DataStorage : public QObject {
	Q_OBJECT

	DB_MySQL  *pDB;

	bool loadDeviceList(void);
	void updateDeviceModel(void);

public:

	dbStorage	*dbInspecStorage;
	dbStorage	*dbDeviceStorage;
	deviceType	*dbDeviceType;

	DataStorage(void);
	~DataStorage();

signals:
	void sig_UpdateDeviceList(void);

public slots:
	bool loadInspectionList(QString);

};

#endif // !DATASTORAGE_H