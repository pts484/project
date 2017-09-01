#include <QApplication>
#include "src/DashBoard.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DashBoard main;

	return a.exec();
}
