#include "Dashboard.h"

Dashboard::Dashboard(QWidget *parent)
	: QWidget(parent)
{
	initLayout();

}

Dashboard::~Dashboard()
{
}

inline void Dashboard::initLayout(void) {
	this->setLayout(&hLayout);

	hLayout.addLayout(&vLayoutTAG);
	hLayout.addLayout(&vLayoutSimul);
	hLayout.addLayout(&vLayoutPeople);

	for (int i = 0; i < 12; ++i) {
		label_tagValue[i].setText("NONE");
		label_tagValue[i].setParent(this);
		vLayoutTAG.addWidget(&label_tagValue[i], i, 0);

		label_simulValue[i].setText("NONE");
		label_simulValue[i].setParent(this);
		vLayoutSimul.addWidget(&label_simulValue[i], i, 1);

		label_peopleValue[i].setText("NONE");
		label_peopleValue[i].setParent(this);
		vLayoutPeople.addWidget(&label_peopleValue[i], i, 2);
	}
}
inline void Dashboard::layoutTAGInfo(void) {
}

void Dashboard::resizeEvent(QResizeEvent *event) {
	qDebug() << "run Dashboard Event";
}