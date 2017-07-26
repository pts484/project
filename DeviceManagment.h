#ifndef DEVICEMANAGMENT_H
#define DEVICEMANAGMENT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTreeView>
#include <QListView>

#include <QImage>
#include <QPixmap>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QDebug>

class DeviceManagment : public QWidget
{
	Q_OBJECT

	QVBoxLayout mainLayout;
	QHBoxLayout hLayout0;
	QVBoxLayout vLayout00, vLayout000;

	QTreeView	mDeviceList;
	QListView	mCheckList;

	QPixmap		mImgShipDeck;
	QLabel		mCanvas;

	QPushButton mDechBtn[3];



	inline void initLayout();

	void resizeEvent(QResizeEvent *event);

public:
	DeviceManagment(QWidget *parent=0);
	~DeviceManagment();
};
#endif //DEVICEMANAGMENT_H