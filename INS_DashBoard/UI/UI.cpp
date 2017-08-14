#include "UI.h"
#include "define.h"



UI::UI(QWidget *parent) : QMainWindow(parent) {

	uiDashBoard = new Dashboard();
	uiDevice = new DeviceManagment();

    this->setGeometry(WINDOWS_POSX+30, WINDOWS_POSY+30, WINDOWS_SIZEX, 0);

    mainWidget.setParent(this);
    this->setCentralWidget(&mainWidget);
	
	//TITLE IMAGE
	Title = new DashLABEL(&mainWidget, &vLayout0, ":/DLABEL_TITLE", "");
	/////////////////////////////////////////////////////////////////
	//  Initialize Image Button
	labelMenuBtn[0].setParent(&mainWidget); 
	QPixmap pixmap0(":/DBTN_DASH_ON");
	QIcon ButtonIcon0(pixmap0);
	labelMenuBtn[0].setIcon(ButtonIcon0);
	labelMenuBtn[0].setIconSize(pixmap0.rect().size());
	labelMenuBtn[0].setFixedSize(pixmap0.rect().size());

	labelMenuBtn[1].setParent(&mainWidget);
	QPixmap pixmap(":/DBTN_DEVICE_OFF");
	QIcon ButtonIcon(pixmap);
	labelMenuBtn[1].setIcon(ButtonIcon);
	labelMenuBtn[1].setIconSize(pixmap.rect().size());
	labelMenuBtn[1].setFixedSize(pixmap.rect().size());

	hLayout1[0].setMargin(0);
	hLayout1[0].setSpacing(0);
	hLayout1[0].addWidget(&labelMenuBtn[0], 0, Qt::AlignLeft);
	hLayout1[0].addWidget(&labelMenuBtn[1], 0, Qt::AlignLeft);
	hLayout1[0].addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
	//////////////////////////////////////////////////////////////////

	//[1].setMargin(0);
	//hLayout1[1].setSpacing(0);
	hLayout1[1].addWidget(uiDashBoard);


	vLayout0.setMargin(0);
	vLayout0.setSpacing(0);
	vLayout0.addLayout(&hLayout1[0]);
	vLayout0.addLayout(&hLayout1[1]);

	mainWidget.setLayout(&vLayout0);

	initConnect();

	//first Update
	//viewDeviceManagement();
}

UI::~UI(void) {
	if (!uiDashBoard) delete uiDashBoard;
	if (!uiDevice)	  delete uiDevice;
}


inline void UI::initConnect(void) {

	connect(&labelMenuBtn[0], SIGNAL(clicked()), this, SLOT(viewDashBoard()));
	connect(&labelMenuBtn[1], SIGNAL(clicked()), this, SLOT(viewDeviceManagement()));
	connect(uiDevice, SIGNAL(sigDeviceID(QString)), this, SLOT(loadInspectionList(QString)));
}

void UI::viewDashBoard(void) {

	if (uiDashBoard->isVisible()) return;

	labelMenuBtn[0].setIcon(QIcon(":/DBTN_DASH_ON"));
	labelMenuBtn[1].setIcon(QIcon(":/DBTN_DEVICE_OFF"));

	hLayout1[1].replaceWidget(uiDevice, uiDashBoard);
	uiDashBoard->show();
	uiDevice->hide();
	
	qDebug() << "run viewDashBoard";
}
void UI::viewDeviceManagement(void) {

	if (uiDevice->isVisible()) return;

	labelMenuBtn[0].setIcon(QIcon(":/DBTN_DASH_OFF"));
	labelMenuBtn[1].setIcon(QIcon(":/DBTN_DEVICE_ON"));

	hLayout1[1].replaceWidget(uiDashBoard, uiDevice);
	uiDashBoard->hide();
	uiDevice->show();
	qDebug() << "run viewDeviceManagement";
}

void UI::resizeEvent(QResizeEvent *event) {
	qDebug() << "run Resize Event";
}

void UI::loadInspectionList(QString id) {


}

void UI::DASHBOARD_Emergency_MODE(void) {


}