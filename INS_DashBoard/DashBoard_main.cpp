#include "DashBoard_main.h"


DashBoard_main::DashBoard_main(void)
{
	mStorage = new DataStorage();
	pUIMain = new UI(mStorage);
	pPTT = new PTT();
	
	pUIMain->show();
}

DashBoard_main::~DashBoard_main(void){
}
