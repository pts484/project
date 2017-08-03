#ifndef DEVICEMANAGMENT_H
#define DEVICEMANAGMENT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTreeView>
#include <QTableView>
#include <QList>

#include <QStandardItemModel>
#include <QStandardItem>

#include <QImage>
#include <QPixmap>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QDebug>
#include "DataStorage.h"


class DeviceView : public QTreeView {
	Q_OBJECT
public:

	DeviceView();
	~DeviceView();

	QString selectId;

	QModelIndex sigCell;
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	

signals:
	void sigSelectDeviceID(QString);

public slots:
};

class DeviceManagment : public QWidget
{
	Q_OBJECT

	DataStorage		*mStorage;

	QVBoxLayout mainLayout;
	QHBoxLayout hLayout0;
	QVBoxLayout vLayout00, vLayout000;

	DeviceView	mDeviceList;
	QTableView	mCheckList;

	QPixmap		mImgShipDeck;
	QLabel		mCanvas;

	QPushButton mDechBtn[3];

	int listWidth;
	QStandardItemModel *treeModel;

	QStringList headerText;
	QStandardItemModel *listModel;


	inline void initLayout();
	inline void initTreeView();
	inline void initListView();
	inline void initListHeader();

	void resizeEvent(QResizeEvent *event);

public:
	
	DeviceManagment(DataStorage *dataStorage, QWidget *parent=0);
	~DeviceManagment();

	void UpdateDeviceView(void);
	void UpdateInspecView(void);

signals:
	void sigDeviceID(QString);

public slots:


};
#endif //DEVICEMANAGMENT_H