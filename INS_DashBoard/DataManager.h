#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QThread>

#include "DataStorage.h"
#include "UI/UI.h"
#include "UI/Dashboard.h"
#include "UI/DeviceManagment.h"
#include "AudioRecode/audiorecorder.h"
#include "VoiceSender.h"
#include "db/db_mysql.h"

class DataManager : public QObject
{
	Q_OBJECT

	resultTable		dbDataBuf;
	CountSection	*pCount;

	QBasicTimer		talkTimer;
	int				talkTIme;

	QThread			wavFileSendThread;

	UI				*pDM_ui;
	AudioRecorder	*pDM_ar;
	DataStorage		*pDM_ds;
	VoiceSender		*pDM_vs;
	DB_MySQL		*pDM_db;

	Dashboard		*pDM_uiDash;
	DeviceManagment	*pDM_uiDevice;

	inline void setConnection(void);

	void timerEvent(QTimerEvent *event) override;

public:
	DataManager(QObject *parent = nullptr);
	DataManager(UI *, AudioRecorder *, DataStorage *, VoiceSender *, DB_MySQL *, QObject *parent = nullptr);
	~DataManager();


	void setClassLink(UI *, AudioRecorder *, DataStorage *, VoiceSender *, DB_MySQL	*);

signals:

	void sigRecoding_Done();

private slots :

	void onPressPTTBtn(void);
	void onReleasePTTBtn(void);

public slots :
	void update_DashBoard(void);

};

#endif // DATAMANAGER_H_H