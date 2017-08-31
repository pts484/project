#include "TagLocationSimulatior.h"
/*****************************************************************************/
/* OBJECT                                                                    */
/*****************************************************************************/
static qulonglong defulteID = 7718106562511;

UI_OBJECT::UI_OBJECT(QWidget *parent, QLayout *_layout, uint num){

	flag = true;

	simulatorID = num;

	db_Interface = new DB_MySQL();
	//spacer = new QSpacerItem(0,0);

	isRuning = false;
	isApply = false;

	posX = 0.0;
	posY = 0.0;
	posZ = 0.0;

	TagID = "";
	interval = 1000;

	this->setParent(parent);
	_layout->addWidget(this);

	this->setLayout(&layout);

	layout.addWidget(&nNum);
	layout.addWidget(&nstrTagID);
	layout.addWidget(&nTagID);
	layout.addWidget(&nstrInterval);
	layout.addWidget(&nInterval);
	layout.addWidget(&nApply);
	layout.addWidget(&nStart);
	layout.addWidget(&nStop);
	layout.addWidget(&nDelete);
	//layout.addSpacerItem(spacer);
	layout.addWidget(&nLocationVlaueX);
	layout.addWidget(&nLocationVlaueY);
	layout.addWidget(&nLocationVlaueZ);

	qDebug() << defulteID;
	nTagID.setText(QString::number(defulteID++));
	nInterval.setText(QString::number(interval));
	nNum.setText(QString::number(simulatorID));
	nstrTagID.setText("TAG ID :");
	nstrInterval.setText("Interval;");
	nApply.setText("Apply");
	nStart.setText("Run");
	nStop.setText("Stop");
	nDelete.setText("delete");

	nLocationVlaueX.setText("X : 00.0000000");
	nLocationVlaueY.setText("Y : 00.0000000");
	nLocationVlaueZ.setText("Z : 00.0000000");


	nStart.setDisabled(true);
	nStop.setDisabled(true);

	this->setFixedSize(QSize(1000, 50));

	connect(&timer,		SIGNAL(timeout()),		this, SLOT(onQuery()));
	connect(&nApply,	SIGNAL(clicked()),		this, SLOT(onApply()));
	connect(&nStart,	SIGNAL(clicked()),		this, SLOT(onStart()));
	connect(&nStop,		SIGNAL(clicked()),		this, SLOT(onStop()));
	connect(&nDelete,	SIGNAL(clicked()),		this, SLOT(onDelete()));
}

UI_OBJECT::~UI_OBJECT() {

	
	db_Interface->disconnectDB();
	timer.stop();
	delete db_Interface;

	//delete spacer;

};

void UI_OBJECT::onApply(void) {

	if (nTagID.text().length() != 13) {
		qDebug() << "currupt";
		return;
	} else {
		TagID = nTagID.text();
	}


	if (nInterval.text().toInt() < 500 ) {
		interval = 500;
	} else {
		interval = nInterval.text().toInt();
	}

	qDebug() << TagID << " :: " << interval;

	isApply = true;
	nStart.setDisabled(false);
	nStop.setDisabled(false);
}

void UI_OBJECT::onQuery() {

	QString curTime = QDateTime::currentDateTime().toString(TIME_FORMAT);

	posX = fRand(0.0, 70.5);
	posY = fRand(0.0, 12.3);
	posZ = fRand(0.0, 4.0);

	QString instance_Query = QString("UPDATE %1 SET CalcDate = '%6', XPOS = %2, YPOS = %3, ZPOS = %4 WHERE TagNo = %5")
		.arg(TABLENAME)
		.arg(QString::number(posX))
		.arg(QString::number(posY))
		.arg(QString::number(posZ))
		.arg(TagID)
		.arg(curTime);

	db_Interface->updateQuery(instance_Query.toUtf8());
	
	nLocationVlaueX.setText(QString("X : [%1]").arg(posX, 9, 'f', -1, QChar('0')));
	nLocationVlaueY.setText(QString("Y : [%1]").arg(posY, 9, 'f', -1, QChar('0')));
	nLocationVlaueZ.setText(QString("Z : [%1]").arg(posZ, 9, 'f', -1, QChar('0')));

}

void UI_OBJECT::onStart() {

	nStart.setText("Running");
	nStart.setDisabled(true);
	nApply.setDisabled(true);
	nTagID.setDisabled(true);
	nInterval.setDisabled(true);

	nStop.setDisabled(false);
	
	timer.start(interval);

}
void UI_OBJECT::onStop() {
	
	nStart.setText("Run");
	nStart.setDisabled(false);
	nApply.setDisabled(false);
	nTagID.setDisabled(false);
	nInterval.setDisabled(false);

	nStop.setDisabled(true);

	timer.stop();
	}

void UI_OBJECT::onDelete() {
	
	emit sigDelete(simulatorID);
}

double UI_OBJECT::fRand(double fMin, double fMax) {
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

/*****************************************************************************/
/* MAIN                                                                      */
/*****************************************************************************/
Simulation::Simulation(QWidget *parent, QLayout *_layout, uint num) {

	pLayout = _layout;

	simulatorID = num;
	TagWorker = new UI_OBJECT(parent, pLayout, num);
	this->moveToThread(&thread);

	connect(&thread, SIGNAL(started()), this, SLOT(onRunning()));
	connect(this, SIGNAL(finish()), this, SLOT(onDone()));

	pLayout->addWidget(TagWorker);
}

Simulation::~Simulation() {

	pLayout->removeWidget(TagWorker);
	TagWorker->onStop();
	TagWorker->onDelete();

	if (thread.isRunning()) {
		emit finish();
		thread.quit();
	}

	delete TagWorker;

}

void Simulation::onRunning(void) {

	if (thread.isRunning())
		qDebug() << "Running Thread ID [" << thread.currentThreadId() << "]";
}

void Simulation::onDone(void) {

	thread.quit();
	if (!thread.isRunning())
		qDebug() << "Running Thread ID [" << thread.currentThreadId() << "] is EXIT(0)";
}

/*****************************************************************************/
/* MAIN                                                                      */
/*****************************************************************************/

TagLocationSimulatior::TagLocationSimulatior(QWidget *parent)
	: QMainWindow(parent) {

	number = 0;

	addBtn.setText("Add Simulator");
	//layout.setAlignment(Qt::AlignTop);
	layout.addWidget(&addBtn);

	this->setCentralWidget(&centralW);
	centralW.setLayout(&layout);


	connect(&addBtn, SIGNAL(clicked()), this, SLOT(addSimulatior()));


	qDebug() << "Main Thread ID ::" <<this->thread()->currentThreadId();
}


void TagLocationSimulatior::simulationIsDone(void) {
	qDebug() << "simul is done";
}

void TagLocationSimulatior::addSimulatior(void) {

	Simulation *pObj = new Simulation(&centralW, &layout, number++);

	connect(pObj->TagWorker, SIGNAL(sigDelete(uint)), this, SLOT(delSimulatior(uint)));
	
	pObj->thread.start();
	Simuls << pObj;

	if (Simuls.size() == NUMBER_OF_SIMULATION) {
		addBtn.setText("Maximum");
		addBtn.setDisabled(true);
		return;
	}
}

void TagLocationSimulatior::delSimulatior(uint id) {

	//qDebug() << id << " :: simul is Deleted";
	QList<Simulation *>::iterator it = Simuls.begin();

	Simulation *nObj;

	for (int p = 0; it != Simuls.end(); ++it, ++p) {

		if (id == Simuls[p]->simulatorID) {
			nObj = Simuls.takeAt(p);

			delete nObj;
			break;
		}
	}

	if (Simuls.size() < NUMBER_OF_SIMULATION) {
		addBtn.setText("add Simulation");
		addBtn.setDisabled(false);
	}
}