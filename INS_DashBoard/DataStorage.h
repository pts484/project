#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QObject>
#include <QList>
#include <QStringList>

//typedef QList<QStringList>;

class DataStorage : public QObject {
	Q_OBJECT




public:
	DataStorage(void);
	~DataStorage();
};

#endif // !DATASTORAGE_H