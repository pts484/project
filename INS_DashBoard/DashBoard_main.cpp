#include "DashBoard_main.h"


DashBoard_main::DashBoard_main(void)
{
	mStorage		= new DataStorage();
	pUIMain			= new UI();
	pAudioRecoder   = new AudioRecorder(pUIMain);
	pVoiceSender	= new VoiceSender();
	pMySQL			= new DB_MySQL();
	pJsonControll	= new JsonControll();

	pDataManager	= new DataManager(pUIMain, pAudioRecoder, mStorage, pVoiceSender, pMySQL, pJsonControll);

	pUIMain->show();
	pUIMain->viewDeviceManagement();
}

DashBoard_main::~DashBoard_main(void){
}
