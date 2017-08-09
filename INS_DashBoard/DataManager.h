#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

#include "DataStorage.h"
#include "UI/UI.h"
#include "UI/Dashboard.h"
#include "UI/DeviceManagment.h"
#include "AudioRecode/audiorecorder.h"
#include "VoiceSender.h"

class DataManager : public QObject
{
	Q_OBJECT

	UI				*pDM_ui;
	AudioRecorder	*pDM_ar;
	DataStorage		*pDM_ds;
	VoiceSender		*pDM_vs;

	Dashboard		*pDM_uiDash;
	DeviceManagment	*pDM_uiDevice;

	inline void setConnection(void);

public:
	DataManager(QObject *parent = nullptr);
	DataManager(UI *, AudioRecorder *, DataStorage *, VoiceSender *, QObject *parent = nullptr);
	~DataManager();


	void setLinkedClass(UI *, AudioRecorder *, DataStorage *, VoiceSender *);

signals:

	void sigRecoding_Done();

private slots :

	void onPressPTTBtn(void);
	void onReleasePTTBtn(void);

};

#endif // DATAMANAGER_H_H