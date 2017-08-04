#ifndef DASHBOARD_H
#define DASHBOARD_H0

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QFontDatabase>
#include <QGroupBox>
#include <QTableView>
#include <QLabel>
#include <QPushButton>

#include <QWidget>

#include <QDebug>

typedef unsigned int uINT;


//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashLABEL 
//////////////////////////////////////////////////////////////////////////////////////
class DashLABEL : public QLabel {
	Q_OBJECT

	QPixmap *imgBuf;

public:
	DashLABEL(void);
	DashLABEL(QWidget *parent, QLayout *layout, QString imgSrc, QString text, Qt::Alignment align = Qt::AlignLeft);
	~DashLABEL();

};

//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashInfoLABEL 
//////////////////////////////////////////////////////////////////////////////////////
class DashInfoLABEL : public QLabel {
	Q_OBJECT

	QHBoxLayout layout;
	DashLABEL *Icon;
	DashLABEL *Text;

public:
	DashInfoLABEL(QWidget *parent = 0, QLayout *parentLayout = 0, QString imgSrc = "", uINT w=0);
	~DashInfoLABEL();

	void setText(QString str) {	Text->setText(str);	}
	void setFont(QFont *font) { Text->setFont(*font); }

};

//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashLISTView 
//////////////////////////////////////////////////////////////////////////////////////
class DashLISTView : public QLabel {
	Q_OBJECT


public:
	DashLISTView(QWidget *parent = 0, QLayout *parentLayout = 0, uINT w = 0, uINT h = 0);
	~DashLISTView();


};

//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashIconLABEL 
//////////////////////////////////////////////////////////////////////////////////////
class DashIconLABEL : public QLabel {
	Q_OBJECT

	QVBoxLayout vLayout;

	DashLABEL *Title;
	DashLABEL *Icon;
	DashLABEL *Text;

public:
	DashIconLABEL(void);
	DashIconLABEL(QWidget *parent, QLayout *layout, \
		QString imgSrc_Title, QString imgSrc_Icon, QString text, \
		uINT w, uINT h);
	~DashIconLABEL();

	void setText(QString str) { Text->setText(str); }
	void setFont(QFont *font) { Text->setFont(*font); }
	
};



//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashPeopleLABEL 
//////////////////////////////////////////////////////////////////////////////////////
class DashPeopleLABEL : public QLabel {
	Q_OBJECT

	QVBoxLayout vLayout;

	DashLABEL *Title;
	DashInfoLABEL *cntPeopleTotal;
	DashInfoLABEL *cntPeopleSafe;
	DashInfoLABEL *cntPeopleDanger;

public:
	DashPeopleLABEL(void);
	DashPeopleLABEL(QWidget *parent, QLayout *layout, uINT w, uINT h);
	~DashPeopleLABEL();

	void setFont(QFont *font) {
		cntPeopleTotal->setFont(font);
		cntPeopleSafe->setFont(font);
		cntPeopleDanger->setFont(font);
	}

};














//////////////////////////////////////////////////////////////////////////////////////
//   CLASS Dashboard 
//////////////////////////////////////////////////////////////////////////////////////
class Dashboard : public QWidget
{
	Q_OBJECT
		
	int fontID;
	QString family;
	QFont monospace;
	QFont monotime;

	QVBoxLayout vMain;
	QHBoxLayout hMain;

	uINT layoutWidth;
	QVBoxLayout vLayoutLeft;
	QVBoxLayout vLayoutCenter;
	QVBoxLayout vLayoutRight;

	//////////////////////////////////
	// Dash BOARD LEFT ::: TAG_AP State Infomation Table
	DashInfoLABEL *cntTAG_On;
	DashInfoLABEL *cntTAG_Off;
	QTableView mTAGView;

	DashInfoLABEL *cntAP_On;
	DashInfoLABEL *cntAP_OFF;
	QTableView mAPView;

	/////////////////////////////////////////
	// Dash BOARD CENTER :::  Information
	inline void initLayout(void);


	QPushButton downBtnBar;
	QPushButton PTTBtn;;

	void resizeEvent(QResizeEvent *event);

public:
	
	Dashboard(QWidget *parent = 0);
	~Dashboard();

	void getUIButton(QPushButton[]);

};



#endif //DASHBOARD_H
