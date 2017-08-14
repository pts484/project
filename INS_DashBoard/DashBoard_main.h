#ifndef DASHBOARD_MAIN_H
#define DASHBOARD_MAIN_H

#include <QObject>
#include "DataStorage.h"
#include "DataManager.h"
#include "UI/UI.h"
#include "AudioRecode/audiorecorder.h"
#include "VoiceSender.h"
#include "db/db_mysql.h"

class DashBoard_main : public QObject
{
    Q_OBJECT

    UI				*pUIMain;
	DataStorage		*mStorage;
	AudioRecorder	*pAudioRecoder;
	VoiceSender		*pVoiceSender;
	DB_MySQL		*pMySQL;
	DataManager		*pDataManager;
	
public:
    DashBoard_main(void);
    ~DashBoard_main(void);
};

#endif // DASHBOARD_MAIN_H
