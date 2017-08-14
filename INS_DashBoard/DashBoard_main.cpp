#include "DashBoard_main.h"


DashBoard_main::DashBoard_main(void)
{
	mStorage		= new DataStorage();
	pUIMain			= new UI();
	pAudioRecoder   = new AudioRecorder(pUIMain);
	pVoiceSender	= new VoiceSender();
	pMySQL			= new DB_MySQL();

	pDataManager	= new DataManager(pUIMain, pAudioRecoder, mStorage, pVoiceSender, pMySQL);

	//pAudioRecoder->show();
	pUIMain->show();
}

DashBoard_main::~DashBoard_main(void){
}
