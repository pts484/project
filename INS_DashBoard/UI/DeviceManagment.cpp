#include "DeviceManagment.h"
#include "Dashboard.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//DECKView
////////////////////////////////////////////////////////////////////////////////////////////////////

DECKView::DECKView(QWidget *parent){

	this->setParent(parent);
	this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	this->setDragMode(QGraphicsView::ScrollHandDrag);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


	pCurrentDECK = new QGraphicsScene(parent);
	pCurrentDECK->setItemIndexMethod(QGraphicsScene::NoIndex);
	
	this->setScene(pCurrentDECK);
	this->setFixedSize(1300, 700);

	drawImage(":/SHIP_DECK_B", 0.5, 0, 0, false);
	drawImage(":/DE_ICON_BOAT", 0.15, 1000, 1000, true);

	this->show();
}
DECKView::~DECKView() {
}

void DECKView::drawImage(QString imgSrc, float _scale, int _x, int _y, bool movement) {

	QImage img;
	QPixmap imgBuf;

	if (img.load(imgSrc)) {
		imgBuf = QPixmap::fromImage(img);
	}
	else {
		img.load(":/FAILED");
		imgBuf = QPixmap::fromImage(img);
		qDebug() << imgSrc << " Image Load Faild";
	}
	//imgBuf.scaled(imgBuf.size().width() * 0.1, imgBuf.size().height() * 0.1);

	Icons = new QGraphicsPixmapItem();
	Icons->setPixmap(QPixmap(imgBuf));
	Icons->setPos(_x, _y);
	Icons->setScale(_scale);

	if (movement) {
		Icons->setFlag(QGraphicsItem::ItemIsMovable);
	}
	
	pCurrentDECK->addItem(Icons);
	
}

void DECKView::mousePressEvent(QMouseEvent *event) {
	QGraphicsView::mousePressEvent(event);
	qDebug() << "On MAP Double Cliick";
	
	QGraphicsItem *selectObject;
	selectObject = pCurrentDECK->mouseGrabberItem();
	qDebug() << selectObject;

}

void DECKView::wheelEvent(QWheelEvent *event) {

	const QPointF p0scene = mapToScene(event->pos());

	qreal factor = qPow(1.2, event->delta() / 240.0);
	scale(factor, factor);

	const QPointF p1mouse = mapFromScene(p0scene);
	const QPointF move = p1mouse - event->pos(); // The move
	horizontalScrollBar()->setValue(move.x() + horizontalScrollBar()->value());
	verticalScrollBar()->setValue(move.y() + verticalScrollBar()->value());

}

////////////////////////////////////////////////////////////////////////////////////////////////////
//DECKButton
////////////////////////////////////////////////////////////////////////////////////////////////////

DECKButton::DECKButton(QString text, QFont *font) {

	mainLayout.setMargin(0);
	mainLayout.setSpacing(0);

	this->font = font;

	Icon = new DashLABEL(this, &mainLayout, ":/DEICON_DECK", "");
	Text = new DashLABEL(this, &mainLayout, "", text, Qt::AlignCenter);

	Text->setFont(*font);
	Text->setStyleSheet("DashLABEL{color : #546E7A;}");

	this->setStyleSheet("DECKButton{border : 1px solid #6E848E; \
									   background-color: #FFFFFF;}");

	this->setLayout(&mainLayout);
	this->setMinimumSize(mainLayout.sizeHint());
	this->setMaximumSize(mainLayout.sizeHint());
}

DECKButton::~DECKButton() {

	if (!Icon) delete Icon;
	if (!Text) delete Text;
}

void DECKButton::mousePressEvent(QMouseEvent *event) {
	this->setStyleSheet("DECKButton{border : 1px solid #6E848E; \
									   background-color: #14B5C8;}");
	Text->setStyleSheet("DashLABEL{ color: #FFFFFF; }");
}
void DECKButton::mouseReleaseEvent(QMouseEvent *event) {
	this->setStyleSheet("DECKButton{border : 1px solid #6E848E; \
									   background-color: #FFFFFF;}");
	Text->setStyleSheet("DashLABEL{ color: #546E7A; }");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//DeviceView
////////////////////////////////////////////////////////////////////////////////////////////////////
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
DeviceManagment::DeviceManagment(QWidget *parent):QWidget(parent)
{

	//init FONT ////////////////////////////////////////////
	fontID = QFontDatabase::addApplicationFont(":/YUNGOTHIC350");
	family = QFontDatabase::applicationFontFamilies(fontID).at(0);
	monospace.setFamily(family);
	monospace.setPixelSize(22);
	monospace.setLetterSpacing(QFont::AbsoluteSpacing, 5);

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


	mainLayout.setSpacing(1);
	hLayout0.setSpacing(1);
	vLayout00.setSpacing(1);
	vLayout000.setSpacing(1);

	mainLayout.addLayout(&hLayout0);
	mainLayout.addWidget(&mCheckList);
	//DashLABEL *BottomBar = new DashLABEL(this, &mainLayout, ":/DE_BOTTOMBAR", "");
	
	mImgShipDeck = new DECKView(this);

	hLayout0.setAlignment(Qt::AlignLeft);
	hLayout0.addLayout(&vLayout00);
	hLayout0.addWidget(mImgShipDeck);
	
	vLayout00.addLayout(&vLayout000);
	vLayout00.addWidget(&mDeviceList);


	mDechBtn[0] = new DECKButton(STR_KOR("데크 A"), &monospace);
	mDechBtn[1] = new DECKButton(STR_KOR("데크 B"), &monospace);
	mDechBtn[2] = new DECKButton(STR_KOR("데크 C"), &monospace);

	vLayout000.addWidget(mDechBtn[0]);
	vLayout000.addWidget(mDechBtn[1]);
	vLayout000.addWidget(mDechBtn[2]);

	listWidth = mainLayout.sizeHint().width();

	mDechBtn[0]->setMaximumWidth(listWidth);
	mDechBtn[1]->setMaximumWidth(listWidth);
	mDechBtn[2]->setMaximumWidth(listWidth);
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

}

void DeviceManagment::UpdateInspecView(void) {

}

void DeviceManagment::resizeEvent(QResizeEvent *event) {
	qDebug() << "run DeviceManangement";

	initListHeader();

	listWidth = mDeviceList.size().width();
	mDeviceList.setColumnWidth(0, listWidth * 0.6);
	mDeviceList.setColumnWidth(1, listWidth * 0.39);



}