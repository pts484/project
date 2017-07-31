#include "UI.h"
#include "define.h"



UI::UI(DataStorage *dataStorage, QWidget *parent) : QMainWindow(parent)
{

	mStorage = dataStorage;
    this->setGeometry(WINDOWS_POSX+30, WINDOWS_POSY+30, WINDOWS_SIZEX, 900);

    mainWidget.setParent(this);
    this->setCentralWidget(&mainWidget);

	//Menu Layout - hLayout1[0]
	labelMenuBtn[0].setParent(&mainWidget);
	labelMenuBtn[0].setText("DASH BORAD");

	labelMenuBtn[1].setParent(&mainWidget);
	labelMenuBtn[1].setText(tr("Equip Management"));

	uiDashBoard = new Dashboard();
	uiDevice = new DeviceManagment(dataStorage);

	//Default View = DashBoard
	uiDashBoard->show();
	uiDevice->hide();

	hLayout1[0].addWidget(&labelMenuBtn[0]);
	hLayout1[0].addWidget(&labelMenuBtn[1]);
	hLayout1[1].addWidget(uiDashBoard);

	vLayout0.addLayout(&hLayout1[0]);
	vLayout0.addLayout(&hLayout1[1]);

	mainWidget.setLayout(&vLayout0);

	initConnect();

	//first Update
	uiDevice->UpdateDeviceView();
}

UI::~UI(void) {
	if (!uiDashBoard) delete uiDashBoard;
	if (!uiDevice)	  delete uiDevice;
}


inline void UI::initConnect(void) {

	connect(&labelMenuBtn[0], SIGNAL(clicked()), this, SLOT(viewDashBoard()));
	connect(&labelMenuBtn[1], SIGNAL(clicked()), this, SLOT(viewDeviceManagement()));
}

void UI::viewDashBoard(void) {

	if (uiDashBoard->isVisible()) return;

	hLayout1[1].replaceWidget(uiDevice, uiDashBoard);
	uiDashBoard->show();
	uiDevice->hide();
	
	qDebug() << "run viewDashBoard";
}
void UI::viewDeviceManagement(void) {

	if (uiDevice->isVisible()) return;

	hLayout1[1].replaceWidget(uiDashBoard, uiDevice);
	uiDashBoard->hide();
	uiDevice->show();
	qDebug() << "run viewDeviceManagement";
}

void UI::resizeEvent(QResizeEvent *event) {
	qDebug() << "run Resize Event";
}