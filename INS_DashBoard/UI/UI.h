#ifndef UI_H
#define UI_H

#include <QMainWindow>
#include <QPushButton>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QDebug>

#include "css3_code.h"
#include "DeviceManagment.h"
#include "Dashboard.h"
#include "qtimer.h"


#include "../DataStorage.h"

class UI : public QMainWindow
{
	Q_OBJECT

	DashLABEL		*Title;

	QVBoxLayout		vLayout0;
	QHBoxLayout		hLayout1[2];

	QPushButton		labelMenuBtn[2];

    QWidget			mainWidget;

	inline void initConnect(void);
	void resizeEvent(QResizeEvent *event);

public:
	Dashboard		*uiDashBoard;
	DeviceManagment *uiDevice;


	UI(QWidget *parent = 0);
    ~UI(void);

signals:
	
public slots:
	void viewDashBoard(void);
	void viewDeviceManagement(void);
	void loadInspectionList(QString);

	void DASHBOARD_Emergency_MODE();




};

#endif // UI_H
