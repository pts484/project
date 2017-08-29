#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include "DataStorage.h"
#include "UI/UI.h"
#include "UI/Dashboard.h"
#include "UI/DeviceManagment.h"
#include "AudioRecode/audiorecorder.h"
#include "VoiceSender.h"
#include "db/db_mysql.h"
#include "db/JsonControll.h"

class DataManager : public QObject
{
	Q_OBJECT

	CountSection	*pCount;

	resultTable		dbDataBuf;

	QTimer			mUpdateTimer;
	QBasicTimer		talkTimer;
	int				talkTIme;

	QThread			wavFileSendThread;
	QThread			dataReceiveThread;

	UI				*pDM_ui;
	AudioRecorder	*pDM_ar;
	DataStorage		*pDM_ds;
	VoiceSender		*pDM_vs;
	DB_MySQL		*pDM_db;
	JsonControll	*pDM_json;

	Dashboard		*pDM_uiDash;
	DeviceManagment	*pDM_uiDevice;

	inline void setConnection(void);

	void timerEvent(QTimerEvent *event) override;

public:

	DataManager(QObject *parent = nullptr);
	DataManager(UI *, AudioRecorder *, DataStorage *,
				VoiceSender *, DB_MySQL *, JsonControll *, QObject *parent = nullptr);
	~DataManager();


	void setClassLink(UI *, AudioRecorder *, DataStorage *,
					  VoiceSender *, DB_MySQL *, JsonControll *);


	void update_DashBoard(resultTable result);
	void update_DeviceManagment(resultTable result);
	void update_InspectionList(resultTable result);

signals:
	void sigRecoding_Done();

private slots :
	void onPressPTTBtn(void);
	void onReleasePTTBtn(void);

	void onReleaseOPTIONBtn(void);
	void onReleaseMODEBtn(void);


	void UPDATE_DATA(resultTable *);
	void reading_DB(void);
	void request_DeviceInspacktion_List();

public slots :
};

#endif // DATAMANAGER_H_H