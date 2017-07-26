#include "DashBoard_main.h"


DashBoard_main::DashBoard_main(void)
{
	pUIMain = new UI();
	pDB = new DB_MySQL();
	pPTT = new PTT();
	mStorage = new DataStorage();
	


	pUIMain->show();
}

DashBoard_main::~DashBoard_main(void)
{

}
