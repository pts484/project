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



class UI : public QMainWindow
{
    Q_OBJECT
		
	QVBoxLayout		vLayout0;
	QHBoxLayout		hLayout1[2];

	QPushButton		labelMenuBtn[2];

    QWidget			mainWidget;
	Dashboard		*uiDashBoard;
	DeviceManagment *uiDevice;


	inline void initConnect(void);

	void resizeEvent(QResizeEvent *event);

public:
    UI(QWidget *parent = 0);
    ~UI(void);

signals:
	
public slots:
	void viewDashBoard(void);
	void viewDeviceManagement(void);

};

#endif // UI_H
