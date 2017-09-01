#ifndef UI_H
#define UI_H

#include <QMainWindow>
#include <QPushButton>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QDebug>

#include "css3_code.h"
#include "CustomWidget/CustomLabel.h"


#define WINDOWS_X 0
#define WINDOWS_Y 50
#define WINDOWS_W 1280
#define WINDOWS_H 1024

class UI : public QMainWindow
{
	Q_OBJECT

		QWidget cMainWidget;
		CustomLabel instance;

public:
	UI::UI(QWidget *parent = 0);
	UI::~UI(void);

};

#endif // UI_H
