#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QDebug>
#include <QObject>
#include <QHash>
#include <QList>
#include <QStringList>
#include <QDateTime>

#include <QStandardItem>
#include <QStandardItemModel>

#include<time.h>

#include "define.h"

/*********************************/
/* This Class is Singleton Class */
/*********************************/

typedef QList<QStandardItem *>			rowData;

typedef struct {
	bool isActive;
	rowData recode;
}rowGroup;

typedef QHash<QString, rowGroup>		ViewBuffer;
typedef QHash<QString, QStringList>		HashBuffer;

class Buffer : public HashBuffer {

	uint		*pTotal;
	uint		*pEnable;
	uint		*pDisable;

	ViewBuffer			viewItems;
	QStandardItemModel	viewModel;

public:
	
	Buffer(void);
	~Buffer(void);

	const QStringList& findRecode(QString key);
	void addRecode(QString key, QStringList &recode);
	void deleteRecode(QString key);

	void updateModel(void);
	void checkToActive(const uint &Inteval, int index);
	void checkToNumber(void);


	QStandardItemModel* getModel(void) { return &viewModel; }
	const ViewBuffer* getViewItems(void) { return &viewItems; }
	const HashBuffer* getBuffer(void) { return this; }

	void Clear(void);
	void Clear(uint *_Total, uint *_Enable, uint *_Disable);

};


class DataStorage : public QObject {
	Q_OBJECT

public:

	Buffer mTagBuffer;
	Buffer mAPBuffer;
	CountSection mCountData;

	DataStorage(void);
	~DataStorage(void);


	const CountSection* getCountSection(void) { return &mCountData; }

signals:
	

public slots:
	

};

#endif // !DATASTORAGE_H

