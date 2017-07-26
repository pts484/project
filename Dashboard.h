#ifndef DASHBOARD_H
#define DASHBOARD_H0

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QGroupBox>
#include <QLabel>

#include <QWidget>

#include <QDebug>

class Dashboard : public QWidget
{
	Q_OBJECT

	QHBoxLayout hLayout;

	//////////////////////////////////
	//TAG_AP State Infomation Table
	QGridLayout vLayoutTAG;
	QGridLayout vLayoutSimul;
	QGridLayout vLayoutPeople;

	QLabel label_tagValue[12];
	QLabel label_simulValue[12];
	QLabel label_peopleValue[12];

	inline void initLayout(void);
	inline void layoutTAGInfo(void);

	void resizeEvent(QResizeEvent *event);

public:
	
	Dashboard(QWidget *parent = 0);
	~Dashboard();

};

#endif //DASHBOARD_H