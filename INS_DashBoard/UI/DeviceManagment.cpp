#include "DeviceManagment.h"


DeviceView::DeviceView() {
	selectId = "";
}
DeviceView::~DeviceView() {}


void DeviceView::mouseDoubleClickEvent(QMouseEvent *event) {

	emit sigSelectDeviceID(selectId);
	selectId = "";
}

void DeviceView::mouseReleaseEvent(QMouseEvent *event) {

	QModelIndex i;
	selectId = this->currentIndex().sibling(this->currentIndex().row(), 1).data().toString();
}

void DeviceView::mouseMoveEvent(QMouseEvent *event) {
}




////////////////////////////////////////////////////////////////////////////////////////////////////
//DeviceManagment
////////////////////////////////////////////////////////////////////////////////////////////////////
DeviceManagment::DeviceManagment(DataStorage *dataStorage, QWidget *parent):QWidget(parent)
{

	mStorage = dataStorage;
	initLayout();
	initTreeView();
	initListView();

	connect(&mDeviceList, SIGNAL(sigSelectDeviceID(QString)), this, SIGNAL(sigDeviceID(QString)));
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

	listWidth = mainLayout.sizeHint().width();
}

inline void DeviceManagment::initTreeView() {

	//init Header
	QStringList instanceHeader;
	instanceHeader << STR_KOR("장비이름") << STR_KOR("장비번호");
	treeModel = new QStandardItemModel(&mDeviceList);
	treeModel->setHorizontalHeaderLabels(instanceHeader);

	mDeviceList.setSelectionMode(QAbstractItemView::SingleSelection);
	mDeviceList.setSelectionBehavior(QAbstractItemView::SelectRows);
	//mDeviceList.setDragEnabled(true);
	
	mDeviceList.setModel(treeModel);
	mDeviceList.setMaximumWidth(300);

	//Edit Locked
	mDeviceList.setEditTriggers(QAbstractItemView::NoEditTriggers);

}

inline void DeviceManagment::initListView() {

	//init Header
	listModel = new QStandardItemModel(&mCheckList);
	mCheckList.setModel(listModel);
	mCheckList.resizeRowsToContents();
	mCheckList.setSelectionMode(QAbstractItemView::SingleSelection);
	mCheckList.setSelectionBehavior(QAbstractItemView::SelectRows);


	listWidth = mCheckList.size().width();
	headerText << STR_KOR("점검일자") << STR_KOR("장비번호") \
	<< STR_KOR("장비이름") \
	<< STR_KOR("장비위치") \
	<< STR_KOR("담당자") \
	<< STR_KOR("점검 전") \
	<< STR_KOR("점검 후") \
	<< STR_KOR("점검내역");

	initListHeader();

	//Edit Locked
	mCheckList.setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void DeviceManagment::initListHeader() {

	listWidth = mCheckList.size().width();
	listModel->setHorizontalHeaderLabels(headerText);

	mCheckList.setColumnWidth(0, listWidth * 0.1);
	mCheckList.setColumnWidth(1, listWidth * 0.1);
	mCheckList.setColumnWidth(2, listWidth * 0.1);
	mCheckList.setColumnWidth(3, listWidth * 0.1);
	mCheckList.setColumnWidth(4, listWidth * 0.1);
	mCheckList.setColumnWidth(5, listWidth * 0.1);
	mCheckList.setColumnWidth(6, listWidth * 0.1);
	mCheckList.setColumnWidth(7, listWidth * 0.25);
}

void DeviceManagment::UpdateDeviceView(void){

	deviceType *type = mStorage->dbDeviceType;
	dbStorage  *data = mStorage->dbDeviceStorage;

	if ((type->size() <= 0) || (data->size() <= 0)) return;

	int rowCnt = treeModel->rowCount();

	if (rowCnt > 0) {
		for (int i = 0; i < rowCnt; ++i) {
			treeModel->removeRow(i);
		}
	}

	QStandardItem *rootNode = treeModel->invisibleRootItem();

	for (int i = 0; i < type->size(); ++i) {

		QStandardItem *DviceType = type->at(i)->type;
		rootNode->appendRow(DviceType);

		for (int j = 0; j < data->size(); ++j) {
			if (type->at(i)->num == (data->at(j)->at(5)->text()).toInt()) {

				QList<QStandardItem *> DviceList;
				DviceList << data->at(j)->at(1) << data->at(j)->at(0);
				DviceType->appendRow(DviceList);
			}
		}
		mCheckList.setRowHeight(i, 10);
	}
	mDeviceList.expandAll();
}

void DeviceManagment::UpdateInspecView(void) {

	dbStorage  *data = mStorage->dbInspecStorage;
	int size = data->size();
	qDebug() << "dbInspecStorage size :: " << size;
	
	if(listModel->rowCount() > 0){
		listModel->clear();
	}

	QList<QStandardItem *> *rows;
	for (int i = 0; i < size; ++i) {
		
		rows = data->at(i);
		listModel->appendRow(*rows);
	}

	initListHeader();
}

void DeviceManagment::resizeEvent(QResizeEvent *event) {
	qDebug() << "run DeviceManangement";

	initListHeader();

	listWidth = mDeviceList.size().width();
	mDeviceList.setColumnWidth(0, listWidth * 0.6);
	mDeviceList.setColumnWidth(1, listWidth * 0.39);
}