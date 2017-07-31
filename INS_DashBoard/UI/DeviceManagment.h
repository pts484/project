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

	
	void mouseReleaseEvent(QMouseEvent *event);
	public slots:
	void aa(void);
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
	QStandardItemModel *listModel;


	inline void initLayout();
	inline void initTreeView();
	inline void initListView();

	void resizeEvent(QResizeEvent *event);

public:
	
	DeviceManagment(DataStorage *dataStorage, QWidget *parent=0);
	~DeviceManagment();

	void UpdateDeviceView(void);
	void UpdateInspecView(void);

};
#endif //DEVICEMANAGMENT_H