#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QDebug>
#include <QObject>
#include <QHash>
#include <QList>
#include <QStringList>
#include <QDateTime>
#include <QTableView>

#include <qstring.h>
#include <QStandardItem>
#include <QStandardItemModel>

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include<time.h>

#include "define.h"

/*********************************/
/* This Class is Singleton Class */
/*********************************/

typedef struct {
	bool isActive;
	QStringList recode;
}rowGroup;

typedef struct {
	QGraphicsPixmapItem	*icon;
	QList<QStandardItem *> data;
}deviceData;

typedef QList<QStandardItem *>			  rowData;
typedef QHash<QString, QStandardItem *>   RootType;

typedef QHash<QString, rowGroup>		  HashBuffer;
typedef QHash<QString, deviceData>		  HashTBuffer;


class Buffer : public HashBuffer {

	uint		mTotal;
	uint		mEnable;
	uint		mDisable;

	QStandardItemModel	viewModel;

public:
	
	Buffer(void);
	~Buffer(void);

	const QStringList& findRecode(QString key);
	void addRecode(QString key, QStringList &recode, int colIndex, const uint &Inteval = ACTIVE_INTERVAL);
	void deleteRecode(QString key);

	void updateModel(void);
	inline void checkToNumber(void);

	void setViewHeader(QStringList list);

	uint getTotal(void) { return mTotal; }
	uint getEnable(void) { return mEnable; }
	uint getDisable(void) { return mDisable; }

	QStandardItemModel* getModel(void) { return &viewModel; }
	const HashBuffer* getBuffer(void) { return this; }

	void Clear(void);

	void updateBuffer(resultTable *result);

};

class DeviceBuffer : public HashTBuffer {

	QGraphicsScene		*pCurrentDECK;
	QGraphicsScene		mDeviceOnDECK[NUMBER_OF_DECK];
	QStandardItemModel	treeModel;
	RootType			rootItem;

	void drawImage(QGraphicsPixmapItem *item, QString imgSrc, float _scale, int _x, int _y, bool movement);

public:
	
	void addDevice(QString key, QStringList &device);
	void delDevice(QString key);

	void setViewHeader(QStringList list);

	void updateModel();
	void updateType();
	void updateBuffer(resultTable *result);

	void			selectScene(int num);
	QGraphicsScene* getScene(int num) { return &mDeviceOnDECK[num]; }
	QStandardItemModel* getModel() { return &treeModel; }

	DeviceBuffer();
	~DeviceBuffer();

};

class DataStorage : public QObject {
	Q_OBJECT

public:

	uint	mSafety;
	uint	mDenger;

	//DashBoard --------------------------//
	Buffer mTagBuffer;
	Buffer mAPBuffer;

	//Device Managment -------------------//
	QStringList mDeviceType;
	DeviceBuffer mDeckDeviceBuffer;


	DataStorage(void);
	~DataStorage(void);

	//DashBoard Function --------------------------//
	void checkToPeople(void);

	//Device Managment Function -------------------//
	void setDeviceType(QStringList &_type) { mDeviceType = _type; };


signals:
public slots:
	

};

#endif // !DATASTORAGE_H

