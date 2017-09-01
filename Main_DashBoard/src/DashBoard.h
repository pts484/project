#ifndef DASHBOARD_H_
#define DASHBOARD_H_

#include <QObject>
#include "Ui/Ui_Interface.h"

class DashBoard : public QObject {
	Q_OBJECT

		UI			 cWindow;
		Ui_Interface inUI_Interface;

public:
	DashBoard(QObject *parent = 0);
	~DashBoard();
};

#endif