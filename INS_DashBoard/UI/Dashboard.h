#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QTimerEvent>
#include <QTime>
#include <QTimer>


#include <QFontDatabase>
#include <QGroupBox>
#include <QTableView>
#include <QLabel>
#include <QPushButton>

#include <QWidget>

#include <QDebug>

#include "../define.h"

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

	void setIcon(QString imgSrc);

};

//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashInfoLABEL 
//////////////////////////////////////////////////////////////////////////////////////
class DashInfoLABEL : public QLabel {
	Q_OBJECT

	QHBoxLayout layout;
	DashLABEL *Icon;
	
	
public:
	DashLABEL *Text;
	DashInfoLABEL(QWidget *parent = 0, QLayout *parentLayout = 0, QString imgSrc = "", uINT w=0);
	~DashInfoLABEL();

	void setIcon(QString imgSrc) { Icon->setIcon(imgSrc); }
	void setText(QString str) {	Text->setText(str);	}
	void setFont(QFont *font) { Text->setFont(*font); }

};

//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashLISTView 
//////////////////////////////////////////////////////////////////////////////////////
class DashLISTView : public QTableView {
	Q_OBJECT


public:
	DashLISTView(QWidget *parent = 0, QLayout *parentLayout = 0, uINT w = 0, uINT h = 0);
	~DashLISTView();

	void setVisibleHeader(uint x, ...);

};

//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashIconLABEL 
//////////////////////////////////////////////////////////////////////////////////////
class DashIconLABEL : public QLabel {
	Q_OBJECT

	QBasicTimer *timer;
	int interval;

	bool isKeepGoing;
	bool isTimeOver;

	QVBoxLayout vLayout;

	DashLABEL *Title;
	DashLABEL *Icon;
	DashLABEL *Text;

	void timerEvent(QTimerEvent *event) override;

public:
	DashIconLABEL(void);
	DashIconLABEL(QWidget *parent, QLayout *layout, \
		QString imgSrc_Title, QString imgSrc_Icon, QString text, \
		uINT w, uINT h);
	~DashIconLABEL();

	void setIcon(QString img) { Icon->setPixmap(img); }
	void setText(QString str) { Text->setText(str); }
	void setFont(QFont *font) { Text->setFont(*font); }

	void onEmergency(uINT Disaster, bool isCutTime, uINT interval, bool keepgoing);
	void onSafety(void);
	void onClear(void);

signals:
	void sigTIME_OVER(void);

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
	DashPeopleLABEL();
	DashPeopleLABEL(QWidget *parent, QLayout *layout, uINT w, uINT h);
	~DashPeopleLABEL();

	void setText(QString _total, QString _safe, QString _denger) {
		cntPeopleTotal->setText(_total);
		cntPeopleSafe->setText(_safe);
		cntPeopleDanger->setText(_denger);
	}


	void setFont(QFont *font) {
		cntPeopleTotal->setFont(font);
		cntPeopleSafe->setFont(font);
		cntPeopleDanger->setFont(font);
	}

	void onEmergency(void);
	void onSafety(void);

};

//////////////////////////////////////////////////////////////////////////////////////
//   CLASS DashImgButton 
//////////////////////////////////////////////////////////////////////////////////////
class DashImgButton : public QPushButton {
	Q_OBJECT

	bool isPush;
	bool oneClick;
	QString imgOn, imgPress;

public :
	DashImgButton(QWidget *parent, QLayout *layout, bool toggle, QString imgSrc = ":/DDOWNBTN_PTT_ON", QString imgPressSrc = ":/DDOWNBTN_PTT_PRESS", bool onClicked = false);
	~DashImgButton();

signals:
	void sigPressed();
	void sigClicked();
	void sigToggle();

public slots:
	void pressedBtn(void);
	void clickedBtn(void);
	void toggleBtn(void);

};



//////////////////////////////////////////////////////////////////////////////////////
//   CLASS Dashboard 
//////////////////////////////////////////////////////////////////////////////////////
class Dashboard : public QWidget
{
	Q_OBJECT

	bool isEmergencyMode;

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
	DashLISTView *mTAGView;

	DashInfoLABEL *cntAP_On;
	DashInfoLABEL *cntAP_Off;
	DashLISTView *mAPView;

	/////////////////////////////////////////
	// Dash BOARD CENTER :::  Information

	DashIconLABEL *centerA;
	DashIconLABEL *centerB;

	/////////////////////////////////////////
	// Dash BOARD RIGHT

	DashPeopleLABEL *RightA;
	DashIconLABEL	*RightB;

	inline void initLayout(void);

	void resizeEvent(QResizeEvent *event);

public:
	
	DashImgButton *bottomBarBtn;
	DashImgButton *PTTBtn;

	DashImgButton *EmergencyBtn;
	DashImgButton *MICOptionBtn;

	Dashboard(QWidget *parent = 0);
	~Dashboard();

	DashLISTView* getTagView(void) { return mTAGView; }
	DashLISTView* getAPView(void) { return mAPView; }


signals:
	void sigPressPTTBtn(void);
	void sigReleasePTTBtn(void);

	void sigPressMODEBtn(void);
	void sigReleaseMODEBtn(void);

	void sigPressOPTIONBtn(void);
	void sigReleaseOPTIONBtn(void);
	
public slots :
	void onDownBar(void);

	void Dashboard::updateDASHBOARD(QString _tagOn, QString _tagOff, \
									QString _apOn, QString _apOff, \
									QString _ppTotal, QString _ppSafe, QString _ppDenger);

	void DASHBOARD_Emergency_MODE(uINT GoldenTime);
	void DASHBOARD_SAFETY_MODE(void);
	void DASHBOARD_CLEAR_MODE(void);

};



#endif //DASHBOARD_H
