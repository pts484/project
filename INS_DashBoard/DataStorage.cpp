#include "DataStorage.h"

DataStorage::DataStorage(void){

	dbDeviceType = new deviceType();
	dbDeviceStorage = new dbStorage();
	dbInspecStorage = new dbStorage();
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
		
		qDebug() << dbDeviceType->at(row) << " : " << (dbDeviceType->at(row))->type->text() << 
			(dbDeviceType->at(row))->num;
	}
	
	emit sig_UpdateDeviceList();

	return true;
}

void DataStorage::updateDeviceModel(void) {

}

bool DataStorage::loadInspectionList(QString deviceID) {

	static QString curID = "";
	
	if (curID == deviceID) {
		qDebug() << "same Device Id";
		return false;
	}
	else {
		curID = deviceID;
		qDebug() << "Changeed ID" << curID << " " << deviceID;
	}

	if (pDB->isConnection()) {
		qDebug() << " runable db Loading";
		curID = "";
		pDB->disconnectDB();
		return false;
	}
	pDB->connectDB();

	resultTable result = { false, 0, 0 };
	result.recode.clear();

	QByteArray query = "SELECT * FROM InspactionListView WHERE DeviceID = ";
	query += curID;

	//get DB DATA
	result = pDB->runQuery(query.constData());

	if (result.chk == false) {
		qDebug() << "resule Chk Error";
		return false;
	}
		if (result.recode.size() <= 0) {

		qDebug() << result.chk << ":" << result.row << ":" << result.col;
		qDebug() << "resule recode size " << result.recode.size();
		return false;
	}
		qDebug() << dbInspecStorage->size();
	if (dbInspecStorage->size() > 0) {
		for (int i = 0; i < dbInspecStorage->size(); ++i) {

			dbVelue *rmRow = dbInspecStorage->at(i);
			rmRow->clear();
			//for (int j = 0; j < rmRow->size(); ++j) {
			//	rmRow->removeAt(j);
			//}
			//dbInspecStorage->removeAt(i);
		}
		dbInspecStorage->clear();
	}
	

	for (int row = 0; row < result.row; ++row) {

		dbVelue *tmp = new dbVelue();

		for (int col = 0; col < result.col; ++col) {
			
			*tmp << new QStandardItem(result.recode.at(((result.col * row) + col)));
		}
		*dbInspecStorage << tmp;
		tmp = 0;

		qDebug() << dbInspecStorage->at(row) << " : " << (dbInspecStorage->at(row))->at(0)->text();
	}

	pDB->disconnectDB();

	return true;
}