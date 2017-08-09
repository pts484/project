#include "DashBoard_main.h"


DashBoard_main::DashBoard_main(void)
{
	mStorage		= new DataStorage();
	pUIMain			= new UI(mStorage);
	pAudioRecoder   = new AudioRecorder(pUIMain);
	pVoiceSender	= new VoiceSender();
	
	pDataManager	= new DataManager(pUIMain, pAudioRecoder, mStorage, pVoiceSender);

	//pAudioRecoder->show();
	pUIMain->show();
}

DashBoard_main::~DashBoard_main(void){
}
