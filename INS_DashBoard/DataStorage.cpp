#include "DataStorage.h"

DataStorage::DataStorage(void){

	dbDeviceType = new deviceType();
	dbDeviceStorage = new dbStorage();
	pDB = new DB_MySQL();

	loadDeviceList();


}

DataStorage::~DataStorage(){

}

bool DataStorage::loadDeviceList(void) {

	pDB->connectDB();

	resultTable result = { false, 0, 0 };
	result.recode.clear();
	result = pDB->runQuery("select * FROM SafetyDeviceManagment");

	if (!result.chk) return false;
	if (result.recode.size() <= 0) return false;

	for (int row = 0; row < result.row; ++row) {

		dbVelue *tmp = new dbVelue();

		for (int col = 0; col < result.col; ++col) {
			
			*tmp << new QStandardItem(result.recode.at(((result.col * row) + col)));

		}
		*dbDeviceStorage << tmp;
		tmp = 0;

		qDebug() << dbDeviceStorage->at(row) << " : " << (dbDeviceStorage->at(row))->at(0)->text();		
	}


	result = { false, 0, 0 };
	result.recode.clear();
	result = pDB->runQuery("select type FROM EnumSafetyDevice");

	pDB->disconnectDB();

	if (!result.chk) return false;
	if (result.recode.size() <= 0) return false;

	qDebug() << result.chk << ":" << result.row << ":" << result.col << ":" << result.recode;


	for (int row = 0; row < result.row; ++row) {

		D_TYPE *tmp = new D_TYPE();
		
		tmp->num = row+1;
		tmp->type = new QStandardItem(result.recode.at(row));
		*dbDeviceType << tmp;
		
		//qDebug() << tmp->num << " : " << tmp->type->text();
		qDebug() << dbDeviceType->at(row) << " : " << (dbDeviceType->at(row))->type->text() << 
			(dbDeviceType->at(row))->num;
	}



	emit sig_UpdateDeviceList();

	return true;
}

void DataStorage::updateDeviceModel(void) {

}