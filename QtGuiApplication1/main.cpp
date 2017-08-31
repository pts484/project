#include "TagLocationSimulatior.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TagLocationSimulatior w;
	w.show();
	return a.exec();
}
