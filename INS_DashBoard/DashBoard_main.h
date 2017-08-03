#ifndef DASHBOARD_MAIN_H
#define DASHBOARD_MAIN_H

#include <QObject>
#include "DataStorage.h"
#include "UI/UI.h"
#include "VoiceRecode/PTT.h"

class DashBoard_main : public QObject
{
    Q_OBJECT

    UI			*pUIMain;
	PTT			*pPTT;
	DataStorage *mStorage;
	
public:
    DashBoard_main(void);
    ~DashBoard_main(void);
};

#endif // DASHBOARD_MAIN_H
