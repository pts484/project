#include "DeviceManagment.h"


DeviceView::DeviceView() {
	connect(this, SIGNAL(clicked()), this, SLOT(aa()));
}

DeviceView::~DeviceView() {
}

void DeviceView::mouseReleaseEvent(QMouseEvent *event) {
	//this->setSelectionBehavior(QAbstractItemView::SelectRows);
	//this->setSelectionMode(SelectionMode::SingleSelection);
	qDebug() << this->currentIndex().sibling(this->currentIndex().row(), 0).data().toString();
}

void DeviceView::aa(void) {
	qDebug() << "aaaa";
}


DeviceManagment::DeviceManagment(DataStorage *dataStorage, QWidget *parent):QWidget(parent)
{

	mStorage = dataStorage;
	initLayout();
	initTreeView();
	initListView();
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
	QStringList headerText;
	headerText << STR_KOR("장비이름") << STR_KOR("장비번호");
	treeModel = new QStandardItemModel();
	treeModel->setHorizontalHeaderLabels(headerText);
	mDeviceList.setModel(treeModel);

	mDeviceList.setMaximumWidth(300);

	//Edit Locked
	//mDeviceList.setSelectionMode(QAbstractItemView::SingleSelecti on);
	//mDeviceList.setSelectionBehavior(QAbstractItemView::SelectRow s);
	mDeviceList.setEditTriggers(QAbstractItemView::NoEditTriggers);

}

inline void DeviceManagment::initListView() {

	//init Header
	listModel = new QStandardItemModel();
	mCheckList.setModel(listModel);
	
	listModel->setHorizontalHeaderItem(0, new QStandardItem(STR_KOR("점검일자")));
	listModel->setHorizontalHeaderItem(1, new QStandardItem(STR_KOR("장비번호")));
	listModel->setHorizontalHeaderItem(2, new QStandardItem(STR_KOR("장비이름")));
	listModel->setHorizontalHeaderItem(3, new QStandardItem(STR_KOR("담당자")));
	listModel->setHorizontalHeaderItem(4, new QStandardItem(STR_KOR("점검 전")));
	listModel->setHorizontalHeaderItem(5, new QStandardItem(STR_KOR("점검 후")));
	listModel->setHorizontalHeaderItem(6, new QStandardItem(STR_KOR("점검내역")));

	mCheckList.setColumnWidth(0, listWidth * 0.1);
	mCheckList.setColumnWidth(1, listWidth * 0.1);
	mCheckList.setColumnWidth(2, listWidth * 0.1);
	mCheckList.setColumnWidth(3, listWidth * 0.1);
	mCheckList.setColumnWidth(4, listWidth * 0.1);
	mCheckList.setColumnWidth(5, listWidth * 0.1);
	mCheckList.setColumnWidth(6, listWidth * 0.35);

	//Edit Locked
	mCheckList.setEditTriggers(QAbstractItemView::NoEditTriggers);
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
	}
	mDeviceList.expandAll();
}

void DeviceManagment::UpdateInspecView(void) {

	deviceType *type = mStorage->dbDeviceType;
	dbStorage  *data = mStorage->dbDeviceStorage;

	
}

void DeviceManagment::resizeEvent(QResizeEvent *event) {
	qDebug() << "run DeviceManangement";
	listWidth = mCheckList.size().width();
	mCheckList.setColumnWidth(0, listWidth * 0.1);
	mCheckList.setColumnWidth(1, listWidth * 0.1);
	mCheckList.setColumnWidth(2, listWidth * 0.1);
	mCheckList.setColumnWidth(3, listWidth * 0.1);
	mCheckList.setColumnWidth(4, listWidth * 0.1);
	mCheckList.setColumnWidth(5, listWidth * 0.1);
	mCheckList.setColumnWidth(6, listWidth * 0.39);

	listWidth = mDeviceList.size().width();
	mDeviceList.setColumnWidth(0, listWidth * 0.6);
	mDeviceList.setColumnWidth(1, listWidth * 0.39);
}