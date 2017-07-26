#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QObject>
#include <QHash>
#include <QList>
#include <QStringList>


typedef QHash<int, QStringList *> dbStorage;

class DataStorage : public QObject {
	Q_OBJECT

		dbStorage *dbStorage;



public:
	DataStorage(void);
	~DataStorage();
};

#endif // !DATASTORAGE_H