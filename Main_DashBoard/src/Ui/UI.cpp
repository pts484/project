#include "UI.h"

UI::UI(QWidget *parent) : QMainWindow(parent) {

	this->setWindowTitle("");

    this->setGeometry(WINDOWS_X, WINDOWS_Y, WINDOWS_W, WINDOWS_H);

    this->setCentralWidget(&cMainWidget);

	CustomLabel *instance = new CustomLabel(&cMainWidget);

}

UI::~UI(void) {

}
