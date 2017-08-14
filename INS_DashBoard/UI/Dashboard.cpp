#include "Dashboard.h"

Dashboard::Dashboard(QWidget *parent)
	: QWidget(parent)
{

	isEmergencyMode = false;

	//init FONT ////////////////////////////////////////////
	fontID = QFontDatabase::addApplicationFont(":/YUNGOTHIC350");
	family = QFontDatabase::applicationFontFamilies(fontID).at(0);
	monospace.setFamily(family);
	monospace.setPixelSize(100);
	monospace.setLetterSpacing(QFont::AbsoluteSpacing, 30);
	////////////////////////////////////////////////////////
	monotime.setFamily(family);
	monotime.setPixelSize(90);

	initLayout();
	
	//this->setMaximumSize(1600, 1200);
	//this->setMinimumSize(1600, 1200);

	PTTBtn->hide();
	connect(bottomBarBtn, SIGNAL(clicked()), this, SLOT(onDownBar(void)));

	// PTT Signal connect
	connect(PTTBtn, SIGNAL(sigPressed()), this, SIGNAL(sigPressPTTBtn()));
	connect(PTTBtn, SIGNAL(sigClicked()), this, SIGNAL(sigReleasePTTBtn()));


}

Dashboard::~Dashboard()
{
}

inline void Dashboard::initLayout(void) {

	vMain.setSpacing(0);
	vMain.setMargin(0);
	this->setLayout(&vMain);
	vMain.addLayout(&hMain);
		
	hMain.setMargin(8);
	hMain.addLayout(&vLayoutLeft);
	hMain.addLayout(&vLayoutCenter);
	hMain.addLayout(&vLayoutRight);
	//hMain.setAlignment(Qt::AlignHCenter | Qt::AlignTop);

	//////////////////////////////////////////////////////////////////////////////////
	// Dash BOARD LEFT ::: TAG, AP Information
	vLayoutLeft.setSpacing(0);
	vLayoutLeft.setMargin(0);

	DashLABEL *pTagTitle = new DashLABEL(this, &vLayoutLeft, ":/DLABEL_TAG", "");
	layoutWidth = pTagTitle->size().width();

	cntTAG_On  = new DashInfoLABEL(this, &vLayoutLeft, ":/DICON_TAG_ON", layoutWidth);
	cntTAG_On->setText("0");
	cntTAG_Off = new DashInfoLABEL(this, &vLayoutLeft, ":/DICON_TAG_OFF", layoutWidth);
	mTAGView = new DashLISTView(this, &vLayoutLeft, layoutWidth, 132);

	DashLABEL *pApTitle  = new DashLABEL(this, &vLayoutLeft, ":/DLABEL_AP",  "");
	cntAP_On  = new DashInfoLABEL(this, &vLayoutLeft, ":/DICON_AP_ON", layoutWidth);
	cntAP_Off = new DashInfoLABEL(this, &vLayoutLeft, ":/DICON_AP_OFF", layoutWidth);
	mAPView = new DashLISTView(this, &vLayoutLeft, layoutWidth, 132);

	vLayoutLeft.addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

	cntTAG_On->setFont(&monospace);
	cntTAG_Off->setFont(&monospace);
	cntAP_On->setFont(&monospace);
	cntAP_Off->setFont(&monospace);

	//////////////////////////////////////////////////////////////////////////////////
	// Dash BOARD CENTER :::  Information

	vLayoutCenter.setSpacing(0);
	vLayoutCenter.setMargin(0);

	DashLABEL *a = new DashLABEL(this, &vLayoutCenter, ":/DLABEL_DISASTER", "");
	centerA = new DashIconLABEL(this, &vLayoutCenter, \
		":/DLABEL_DISASTER_CAUSE", ":/DICON_SAFETY", STR_KOR("정상 항해중"), layoutWidth, 0);
	
	centerB = new DashIconLABEL(this, &vLayoutCenter, \
		":/DLABEL_DISASTER_TIME", ":/DICON_SAFETY", STR_KOR("정상 항해중"), layoutWidth, 0);

	vLayoutCenter.addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

	centerA->setFont(&monotime);
	centerB->setFont(&monotime);

	//////////////////////////////////////////////////////////////////////////////////
	// Dash BOARD RIGHT ::: People Information

	vLayoutRight.setSpacing(0);
	vLayoutRight.setMargin(0);

	DashLABEL *ra = new DashLABEL(this, &vLayoutRight, ":/DLABEL_PEOPLE", "");

	RightA = new DashPeopleLABEL(this, &vLayoutRight, layoutWidth, 0);
	
	RightB = new DashIconLABEL(this, &vLayoutRight, \
		":/DLABEL_PEOPLE_TIME", ":/DICON_SAFETY", STR_KOR("정상 항해중"), layoutWidth, 0);

	vLayoutRight.addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

	RightA->setFont(&monospace);
	RightB->setFont(&monotime);

	//////////////////////////////////////////////////////////////////////////////////
	// Dash BOARD DOWN ::: PTT BUTTON

	bottomBarBtn = new DashImgButton(this, &vMain, true, ":/DDOWNBTN_PTT_ON", ":/DDOWNBTN_PTT_PRESS");
	PTTBtn       = new DashImgButton(this, 0, false, ":/DBTN_PTT_ON", ":/DBTN_PTT_PRESS");

	QSize size = QSize(1600, 1200)/2 - (PTTBtn->size() / 2);
	PTTBtn->setGeometry(size.width(), size.height()-200, PTTBtn->size().width(), PTTBtn->size().height());
}

void Dashboard::resizeEvent(QResizeEvent *event) {
	qDebug() << "run Dashboard Event";
	QSize size = QSize(1600, 1200) / 2 - (PTTBtn->size() / 2);
	PTTBtn->setGeometry(size.width(), size.height() - 200, PTTBtn->size().width(), PTTBtn->size().height());
}

void Dashboard::onDownBar(void) {

	if (PTTBtn->isVisible()) {
		PTTBtn->hide();
	} else {
		PTTBtn->show();
	}
}

void Dashboard::updateDASHBOARD(QString _tagOn, QString _tagOff, \
								QString _apOn, QString _apOff, \
								QString _ppTotal, QString _ppSafe, QString _ppDenger) {

	cntTAG_On->setText(_tagOn);
	cntTAG_Off->setText(_tagOff);

	cntAP_On->setText(_apOn);
	cntAP_Off->setText(_apOff);

	RightA->setText(_ppTotal, _ppSafe, _ppDenger);
}

void Dashboard::DASHBOARD_Emergency_MODE(uINT GoldenTime) {

	isEmergencyMode = true;

	centerA->onEmergency(1, true, 0, false);
	centerB->onEmergency(10, false, GoldenTime, true);
	RightB->onEmergency(10, false, GoldenTime, false);

	RightA->onEmergency();
}

void Dashboard::DASHBOARD_SAFETY_MODE(void) {

	isEmergencyMode = false;

	centerA->onSafety();
	centerB->onSafety();

	RightA->onSafety();
	RightB->onSafety();
		
	centerA->setText(STR_KOR("정상 항해중"));
	centerB->setText(STR_KOR("정상 항해중"));
	RightB->setText(STR_KOR("정상 항해중"));

}

void Dashboard::DASHBOARD_CLEAR_MODE(void) {

	isEmergencyMode = false;

	centerA->onClear();
	centerB->onClear();
	RightB->onClear();

	centerA->setIcon(":/DICON_SAFETY");
	centerB->setIcon(":/DICON_COMPLETE");
	RightB->setIcon(":/DICON_SAFETY");
}


//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashLABEL 
//////////////////////////////////////////////////////////////////////////////////////
DashLABEL::DashLABEL() {
}

DashLABEL::DashLABEL(QWidget *parent, QLayout *layout, QString imgSrc, QString text, Qt::Alignment align){

	imgBuf = 0;

	this->setParent(parent);

	if (imgSrc.size() > 0) {

		QImage img;
		QSize imgSize;
		if (imgBuf == 0) {
			imgBuf = new QPixmap();
		}

		if (img.load(imgSrc)) {
			*imgBuf = QPixmap::fromImage(img);
		}else {
			img.load(":/FAILED");
			*imgBuf = QPixmap::fromImage(img);
			qDebug() << imgSrc << " Image Load Faild";
		}

		imgSize = imgBuf->size();
		*imgBuf = imgBuf->scaled(imgSize);
		this->setMinimumSize(imgSize);
		this->setMaximumSize(imgSize);
		this->setPixmap(*imgBuf);
	}
	else {
		this->setText(text);
	}
	
	if(layout != 0){
		layout->addWidget(this);
	}

	this->setAlignment(align);
}

DashLABEL::~DashLABEL() {
	if (!imgBuf) {
		delete imgBuf;
	}
}

void DashLABEL::setIcon(QString imgSrc) {
	QImage img;
	QSize imgSize;
	if (imgBuf == 0) {
		imgBuf = new QPixmap();
	}
	if (img.load(imgSrc)) {
		*imgBuf = QPixmap::fromImage(img);
	}
	else {
		img.load(":/FAILED");
		*imgBuf = QPixmap::fromImage(img);
		qDebug() << imgSrc << " Image Load Faild";
	}

	imgSize = imgBuf->size();
	*imgBuf = imgBuf->scaled(imgSize);
	this->setMinimumSize(imgSize);
	this->setMaximumSize(imgSize);
	this->setPixmap(*imgBuf);
}



//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashInfoLABEL 
//////////////////////////////////////////////////////////////////////////////////////
DashInfoLABEL::DashInfoLABEL(QWidget *parent, QLayout *parentLayout, QString imgSrc, uINT w){
	
	this->setParent(parent);
	this->setLayout(&layout);

	Icon = new DashLABEL(this, &layout, imgSrc, "");
	Text = new DashLABEL(this, &layout, "", "000");
	Text->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	//Text->setMargin(35);
	Text->setStyleSheet("DashLABEL{color : #546E7A;}");
			
	this->setMinimumSize(w, Icon->size().height() + 2); // +2 is Top and Bottom boder line width 1px + 1px
	this->setMaximumSize(w, Icon->size().height() + 2);

	layout.setSpacing(0);
	layout.setMargin(0);

	layout.addWidget(Icon, 0, Qt::AlignLeft);
	layout.addWidget(Text, 0, Qt::AlignRight);

	this->setStyleSheet("DashInfoLABEL{border : 1px solid #6E848E; \
									   background-color: #FFFFFF;}");

	parentLayout->addWidget(this);
}

DashInfoLABEL::~DashInfoLABEL() {
	if (!Icon) delete Icon;
	if (!Text) delete Text;
}




//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashLISTView 
//////////////////////////////////////////////////////////////////////////////////////
DashLISTView::DashLISTView(QWidget *parent, QLayout *parentLayout, uINT w, uINT h) {
	parentLayout->addWidget(this);

	this->setParent(parent);
	this->setMinimumSize(w, h);
	this->setMaximumSize(w, h);
	this->setStyleSheet("DashLISTView{border : 1px solid #6E848E; \
									   background-color: #14B5C8;}");
}

DashLISTView::~DashLISTView() {
}




//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashIconLABEL 
//////////////////////////////////////////////////////////////////////////////////////
DashIconLABEL::DashIconLABEL() {
}

DashIconLABEL::DashIconLABEL(QWidget *parent, QLayout *layout, \
							 QString imgSrc_Title, QString imgSrc_Icon, QString text, \
							 uINT w, uINT h) {
	isKeepGoing = false;
	isTimeOver = false;
	timer = nullptr;
	int _h = 0;

	this->setParent(parent);
	layout->addWidget(this);
	this->setLayout(&vLayout);
	this->setStyleSheet("DashIconLABEL{ border : 1px solid #6E848E; \
										background-color: #FFFFFF;}");

	vLayout.setSpacing(0);
	vLayout.setMargin(0);

	Title = new DashLABEL(this, 0, imgSrc_Title, "", Qt::AlignLeft);
	vLayout.addWidget(Title, 0, Qt::AlignLeft);

	Icon  = new DashLABEL(this, 0, imgSrc_Icon, "", Qt::AlignCenter);
	vLayout.addWidget(Icon, 0, Qt::AlignCenter);

	Text  = new DashLABEL(this, &vLayout, "", text, Qt::AlignCenter);
	Text->setAlignment(Qt::AlignCenter);
	Text->setStyleSheet("DashLABEL{color : #546E7A;}");

	if(h == 0){
		_h = Icon->size().height() + Title->size().height() + 110;
	}else {
		_h = h;
	}
	this->setMinimumSize(w, _h);
	this->setMaximumSize(w, _h);

}

DashIconLABEL::~DashIconLABEL(){
	if (!Icon)  delete Icon;
	if (!Text)  delete Text;
	if (!Title) delete Title;
}

void DashIconLABEL::onEmergency(uINT Disaster, bool isCutTime, uINT interval, bool keepgoing) {

	this->interval = interval;
	isKeepGoing = keepgoing;

	switch (Disaster) {
	
		case 0:
			setIcon(":/DICON_SAFETY");
			break;
		case 1:
			setIcon(":/DICON_FIRE");
			break;
		case 10:
			setIcon(":/DICON_PICKTIME");
			break;
		case 11:
			setIcon(":/DICON_COMPLETE");
			break;
		case 12:
			setIcon(":/DICON_TIMEOVER");
			break;

		case 22:
			setIcon(":/DICON_SAFETY");
			break;
		case 23:
			setIcon(":/DICON_PICKTIME");
			break;
	}

	if (isKeepGoing) {

		if (timer == nullptr) {
			timer = new QBasicTimer();
		}
		timer->start(10, this);
		
	}
	else {
		QString strTime;

		if (isCutTime == false) {
			int runTime = interval;
			int ms = runTime % 1000;
			runTime = runTime / 1000;
			int ss = runTime % 60;
			runTime = runTime / 60;
			int mm = runTime % 60;

			strTime = QString("%1:%2:%3")
				.arg(mm, 2, 10, QChar('0'))
				.arg(ss, 2, 10, QChar('0'))
				.arg(ms / 10, 2, 10, QChar('0'));
		} else {
			strTime = QTime::currentTime().toString("hh:mm:ss");
		}

		setText(strTime);
	}
}
void DashIconLABEL::onSafety(void) {

	if (timer != nullptr) {
		
		timer->stop();

		delete timer;
		timer = nullptr;
	}
	setIcon(":/DICON_SAFETY");
	Text->setStyleSheet("DashLABEL{color : #546E7A;}");
}

void DashIconLABEL::onClear(void) {

	if (timer != nullptr) {

		timer->stop();

		delete timer;
		timer = nullptr;
	}
}

void DashIconLABEL::timerEvent(QTimerEvent *event) {

	if (isTimeOver == false) {
		if (interval > 0) {
			interval -= 10;
		} else {
			isTimeOver = true;
			setIcon(":/DICON_TIMEOVER");
			Text->setStyleSheet("DashLABEL{color : #FF0000;}");
			qDebug() << "onEmergency Time OVER!! ::";
			emit sigTIME_OVER();
		}
	} else {
		interval += 10;
	}

	int runTime = interval;
	int ms = runTime % 1000;
	runTime = runTime / 1000;
	int ss = runTime % 60;
	runTime = runTime / 60;
	int mm = runTime % 60;

	QString strTime = QString("%1:%2:%3")
		.arg(mm, 2, 10, QChar('0'))
		.arg(ss, 2, 10, QChar('0'))
		.arg(ms/10, 2, 10, QChar('0'));
	
	setText(strTime);
}

//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashPeopleLABEL 
//////////////////////////////////////////////////////////////////////////////////////
DashPeopleLABEL::DashPeopleLABEL() {
}

DashPeopleLABEL::DashPeopleLABEL(QWidget *parent, QLayout *layout, uINT w, uINT h) {

	int _h = 0;
	

	this->setParent(parent);
	layout->addWidget(this);
	this->setLayout(&vLayout);
	this->setStyleSheet("DashIconLABEL{ border : 1px solid #6E848E; \
										background-color: #FFFFFF;}");

	vLayout.setSpacing(0);
	vLayout.setMargin(0);

	Title			= new DashLABEL(this, &vLayout, ":/DLABEL_PEOPLE_TIME", "");
	vLayout.addWidget(Title, 0, Qt::AlignLeft);
	cntPeopleTotal  = new DashInfoLABEL(this, &vLayout, ":/DICON_PTOTAL", w);
	cntPeopleSafe   = new DashInfoLABEL(this, &vLayout, ":/DICON_PSAFETY_OFF", w);
	cntPeopleDanger = new DashInfoLABEL(this, &vLayout, ":/DICON_PDANGER_OFF", w);


	QString css3Code = "DashInfoLABEL{ border: 0px; \
									   background - color: #FFFFFF; }";
	cntPeopleTotal->setStyleSheet(css3Code);
	cntPeopleSafe->setStyleSheet(css3Code);
	cntPeopleDanger->setStyleSheet(css3Code);
	cntPeopleSafe->Text->setStyleSheet("DashLABEL{ color: #D3D9DC; }");
	cntPeopleDanger->Text->setStyleSheet("DashLABEL{ color: #D3D9DC; }");

		
	if (h == 0) {
		_h = Title->size().height();
		_h += cntPeopleTotal->size().height();
		_h += cntPeopleTotal->size().height();
		_h += cntPeopleTotal->size().height();
		_h += 1;
	}
	else {
		_h = h;
	}
	this->setMinimumSize(w, _h);
	this->setMaximumSize(w, _h);
	this->setStyleSheet("DashPeopleLABEL{ border : 1px solid #6E848E; \
										  background-color: #FFFFFF;}");

}

DashPeopleLABEL::~DashPeopleLABEL() {
}

void DashPeopleLABEL::onEmergency(void) {
	cntPeopleSafe->setIcon(":/DICON_PSAFETY_ON");
	cntPeopleDanger->setIcon(":/DICON_PDANGER_ON");
	cntPeopleSafe->Text->setStyleSheet("DashLABEL{ color: #546E7A; }");
	cntPeopleDanger->Text->setStyleSheet("DashLABEL{ color: #FF0000; }");
}
void DashPeopleLABEL::onSafety(void) {
	cntPeopleSafe->setIcon(":/DICON_PSAFETY_OFF");
	cntPeopleDanger->setIcon(":/DICON_PDANGER_OFF");
	cntPeopleSafe->Text->setStyleSheet("DashLABEL{ color: #D3D9DC; }");
	cntPeopleDanger->Text->setStyleSheet("DashLABEL{ color: #D3D9DC; }");
}

//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashImgButton 
//////////////////////////////////////////////////////////////////////////////////////
DashImgButton::DashImgButton(QWidget *parent, QLayout *layout, bool toggle, QString imgSrc, QString imgPressSrc) {

	isPush = toggle;

	imgOn = imgSrc;
	imgPress = imgPressSrc;


	this->setParent(parent);
	QPixmap pixmap0(imgOn);
	QIcon ButtonIcon0(pixmap0);
	this->setIcon(ButtonIcon0);
	this->setIconSize(pixmap0.rect().size());
	this->setFixedSize(pixmap0.rect().size());
	this->setStyleSheet("DashImgButton{ border: 0px;}");

	if (layout != 0)	layout->addWidget(this);

	if (isPush) {
		connect(this, SIGNAL(clicked()), this, SLOT(toggleBtn()));
	} else {
		connect(this, SIGNAL(pressed()), this, SLOT(pressedBtn()));
		connect(this, SIGNAL(clicked()), this, SLOT(clickedBtn()));
	}

}

DashImgButton::~DashImgButton() {
	if (isPush) {
		disconnect(this, SIGNAL(clicked()), this, SLOT(toggleBtn()));
	}
	else {
		disconnect(this, SIGNAL(pressed()), this, SLOT(pressedBtn()));
		disconnect(this, SIGNAL(clicked()), this, SLOT(clickedBtn()));
	}
}

void DashImgButton::pressedBtn(void) {
	
	QPixmap pixmap0(imgPress);
	QIcon ButtonIcon0(pixmap0);
	this->setIcon(ButtonIcon0);

	emit sigPressed();
}

void DashImgButton::clickedBtn(void) {
	
	QPixmap pixmap0(imgOn);
	QIcon ButtonIcon0(pixmap0);
	this->setIcon(ButtonIcon0);

	emit sigClicked();

	if (this->isVisible()) {
		this->hide();
	}
	else {
		this->show();
	}
}

void DashImgButton::toggleBtn(void) {
	qDebug() << "Toggle PTT BAR Button";

	if (isPush) {
		
		QPixmap pixmap0(imgPress);
		QIcon ButtonIcon0(pixmap0);
		this->setIcon(ButtonIcon0);
	} else {
		QPixmap pixmap0(imgOn);
		QIcon ButtonIcon0(pixmap0);
		this->setIcon(ButtonIcon0);
	}
	isPush = !isPush;

	emit sigToggle();
}
