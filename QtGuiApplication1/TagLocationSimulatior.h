#ifndef MAIN_H_
#define MAIN_H_

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <qlineedit.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDateTime>

#include <QTimer>

#include <QString>
#include <QList>

#include <Qthread>


#include "db/db_mysql.h"


#define TABLENAME			"taginfo"
#define TIME_FORMAT			"yyyy-MM-dd hh:mm:ss.000zzz" 
#define NUMBER_OF_SIMULATION 30





/*****************************************************************************/
/* OBJECT                                                                    */
/*****************************************************************************/
class UI_OBJECT : public QLabel {

	Q_OBJECT

		bool flag;

		DB_MySQL *db_Interface;

		bool isRuning;
		bool isApply;

		QHBoxLayout layout;
		QLabel		nNum;
		QLabel		nstrTagID;
		QLineEdit	nTagID;
		QLabel		nstrInterval;
		QLineEdit	nInterval;
		QPushButton nApply;
		QPushButton nStart;
		QPushButton nStop;
		QPushButton nDelete;
		QLabel		nLocationVlaueX;
		QLabel		nLocationVlaueY;
		QLabel		nLocationVlaueZ;

		QSpacerItem *spacer;

		uint	interval;
		double posX, posY, posZ;
		QString	TagID;

		QTimer timer;

signals:
		void sigQuery(QString query);
		void sigDelete(uint);

		
public:
	uint simulatorID;

	UI_OBJECT(QWidget *parent, QLayout *_layout, uint num);
	~UI_OBJECT();

	double fRand(double fMin, double fMax);

private slots:
	void onQuery();
	void onApply(void);

public slots:
	void onStart();
	void onStop();
	void onDelete();
};

/*****************************************************************************/
/* Simulator                                                                 */
/*****************************************************************************/
class Simulation : public QObject {
	Q_OBJECT

public:

	QLayout *pLayout;

	uint		simulatorID;
	QThread		thread;
	UI_OBJECT	*TagWorker;

	Simulation() {};
	Simulation(QWidget *parent, QLayout *_layout, uint num);
	~Simulation();


signals:
	void finish();

public slots:
	void onRunning();
	void onDone();
};

/*****************************************************************************/
/* MAIN                                                                      */		
/*****************************************************************************/
class TagLocationSimulatior : public QMainWindow
{
	Q_OBJECT

	QWidget centralW;
	QVBoxLayout layout;

	QPushButton addBtn;

	QList<Simulation *> Simuls;

	uint number;

public:
	TagLocationSimulatior(QWidget *parent = Q_NULLPTR);



private slots:
	
	void simulationIsDone();


	void addSimulatior();
	void delSimulatior(uint);


};

#endif // !MAIN_H_