#include "Dashboard.h"

Dashboard::Dashboard(QWidget *parent)
	: QWidget(parent)
{

	//init FONT
	fontID = QFontDatabase::addApplicationFont(":/YUNGOTHIC350");
	family = QFontDatabase::applicationFontFamilies(fontID).at(0);
	monospace.setFamily(family);
	monospace.setPixelSize(100);
	monospace.setLetterSpacing(QFont::AbsoluteSpacing, 30);
	////////////////////////////
	monotime.setFamily(family);
	monotime.setPixelSize(90);

	initLayout();
	

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
	DashLISTView *view1 = new DashLISTView(this, &vLayoutLeft, layoutWidth, 160);

	DashLABEL *pApTitle  = new DashLABEL(this, &vLayoutLeft, ":/DLABEL_AP",  "");
	cntAP_On  = new DashInfoLABEL(this, &vLayoutLeft, ":/DICON_AP_ON", layoutWidth);
	cntAP_OFF = new DashInfoLABEL(this, &vLayoutLeft, ":/DICON_AP_OFF", layoutWidth);
	DashLISTView *view2 = new DashLISTView(this, &vLayoutLeft, layoutWidth, 160);

	vLayoutLeft.addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

	cntTAG_On->setFont(&monospace);
	cntTAG_Off->setFont(&monospace);
	cntAP_On->setFont(&monospace);
	cntAP_OFF->setFont(&monospace);

	//////////////////////////////////////////////////////////////////////////////////
	// Dash BOARD CENTER :::  Information

	vLayoutCenter.setSpacing(0);
	vLayoutCenter.setMargin(0);

	DashLABEL *a = new DashLABEL(this, &vLayoutCenter, ":/DLABEL_DISASTER", "");
	DashIconLABEL * ca = new DashIconLABEL(this, &vLayoutCenter, \
		":/DLABEL_DISASTER_CAUSE", ":/DICON_SAFETY", "00:00:00", layoutWidth, 0);
	

	DashIconLABEL * cb = new DashIconLABEL(this, &vLayoutCenter, \
		":/DLABEL_DISASTER_TIME", ":/DICON_SAFETY", "00:00:00", layoutWidth, 0);

	vLayoutCenter.addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

	ca->setFont(&monotime);
	cb->setFont(&monotime);

	//////////////////////////////////////////////////////////////////////////////////
	// Dash BOARD RIGHT ::: People Information

	vLayoutRight.setSpacing(0);
	vLayoutRight.setMargin(0);

	DashLABEL *ra = new DashLABEL(this, &vLayoutRight, ":/DLABEL_PEOPLE", "");

	DashPeopleLABEL *rb = new DashPeopleLABEL(this, &vLayoutRight, layoutWidth, 0);
	
	DashIconLABEL * rc = new DashIconLABEL(this, &vLayoutRight, \
		":/DLABEL_PEOPLE_TIME", ":/DICON_SAFETY", "00:00:00", layoutWidth, 0);

	vLayoutRight.addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

	rb->setFont(&monospace);
	rc->setFont(&monotime);

	//////////////////////////////////////////////////////////////////////////////////
	// Dash BOARD DOWN ::: PTT BUTTON

	downBtnBar.setParent(this);
	QPixmap pixmap0(":/DDOWNBTN_PTT_ON");
	QIcon ButtonIcon0(pixmap0);
	downBtnBar.setIcon(ButtonIcon0);
	downBtnBar.setIconSize(pixmap0.rect().size());
	downBtnBar.setFixedSize(pixmap0.rect().size());
	downBtnBar.setStyleSheet("QPushButton{ border: 0px;}");


	//PTTBtn.setParent(this);
	//QPixmap pixmap(":/DBTN_DEVICE_OFF");
	//QIcon ButtonIcon(pixmap);
	//PTTBtn.setIcon(ButtonIcon);
	//PTTBtn.setIconSize(pixmap.rect().size());
	//PTTBtn.setFixedSize(pixmap.rect().size());


	vMain.addWidget(&downBtnBar, 0 , Qt::AlignLeft);

}

void Dashboard::resizeEvent(QResizeEvent *event) {
	qDebug() << "run Dashboard Event";
}






//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashLABEL 
//////////////////////////////////////////////////////////////////////////////////////
DashLABEL::DashLABEL() {
}

DashLABEL::DashLABEL(QWidget *parent, QLayout *layout, QString imgSrc, QString text, Qt::Alignment align){

	
	this->setParent(parent);

	if (imgSrc.size() > 0) {

		QImage img;
		QSize imgSize;
		imgBuf = new QPixmap();

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
