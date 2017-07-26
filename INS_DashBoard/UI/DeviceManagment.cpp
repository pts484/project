#include "DeviceManagment.h"

DeviceManagment::DeviceManagment(QWidget *parent):QWidget(parent)
{
	initLayout();

	treeModel = new QStandardItemModel();
	mDeviceList.setModel(treeModel);

	index = treeModel->index(0, 0);
	treeModel->appendRow(new QStandardItem("1"));
	treeModel->appendRow(new QStandardItem("2"));
	treeModel->appendRow(new QStandardItem("3"));
	treeModel->appendRow(new QStandardItem("4"));
	//treeModel->setRootIndex();
	treeModel->appendRow(new QStandardItem("1"));
	treeModel->appendRow(new QStandardItem("2"));

}

DeviceManagment::~DeviceManagment()
{
}


inline void DeviceManagment::initLayout() {
	this->setLayout(&mainLayout);

	QImage img;
	
	if (img.load("res/img/B_DECK.png")) {
		mImgShipDeck = QPixmap::fromImage(img);
		mImgShipDeck = mImgShipDeck.scaled(1300, 600);
	}else{
		qDebug() << "Image Load Faild";
	}


	mainLayout.addLayout(&hLayout0);
	mainLayout.addWidget(&mCheckList);

	hLayout0.addLayout(&vLayout00);
	hLayout0.addWidget(&mCanvas);

	mCanvas.setPixmap(mImgShipDeck);
	mCanvas.setMinimumSize(1300, 600);
	mCanvas.setMaximumSize(1300, 600);

	vLayout00.addLayout(&vLayout000);
	vLayout00.addWidget(&mDeviceList);

	

	vLayout000.addWidget(&mDechBtn[0]);
	vLayout000.addWidget(&mDechBtn[1]);
	vLayout000.addWidget(&mDechBtn[2]);

	mDechBtn[0].setText("DEAC A");
	mDechBtn[1].setText("DEAC B");
	mDechBtn[2].setText("DEAC C");

}

void DeviceManagment::resizeEvent(QResizeEvent *event) {
	qDebug() << "run DeviceManangement";
}