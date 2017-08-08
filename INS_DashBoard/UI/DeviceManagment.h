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

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QPixmap>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QDebug>
#include "DataStorage.h"


class DashLABEL;


class DECKView : public QGraphicsView{
	Q_OBJECT


	QGraphicsScene *scene;
	QGraphicsPixmapItem *Icons;

public:

	DECKView(QWidget *parent = Q_NULLPTR);
	~DECKView();

	void drawImage(QString imgSrc, float _scale, int _x, int _y, bool movement);


};

class DECKButton : public QPushButton {
	Q_OBJECT

	QFont *font;

	QHBoxLayout mainLayout;
	DashLABEL *Icon;
	DashLABEL *Text;
	
public:
	
	DECKButton() {}
	DECKButton(QString text, QFont *font);
	~DECKButton();
	
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
};

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

	int fontID;
	QString family;
	QFont monospace;

	DataStorage	*mStorage;

	QVBoxLayout mainLayout;
	QHBoxLayout hLayout0;
	QVBoxLayout vLayout00, vLayout000;

	DeviceView	mDeviceList;
	QTableView	mCheckList;

	DECKView	*mImgShipDeck;
	QLabel		mCanvas;

	DECKButton *mDechBtn[3];

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