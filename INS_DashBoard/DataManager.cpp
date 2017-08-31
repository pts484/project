#include "DataManager.h"


DataManager::DataManager(QObject *parent)
	: QObject(parent) {
}

DataManager::DataManager(UI *_ui, AudioRecorder *_ar, DataStorage *_ds, 
						 VoiceSender *_vs, DB_MySQL *_db, JsonControll *_json,
						 QObject *parent)
	: QObject(parent) {

	talkTIme = 0;

	setClassLink(_ui, _ar, _ds, _vs, _db, _json);

	pDM_vs->moveToThread(&wavFileSendThread);
	pDM_db->moveToThread(&dataReceiveThread);

	pDM_uiDash->getTagView()->setModel(pDM_ds->mTagBuffer.getModel());
	pDM_uiDash->getAPView()->setModel(pDM_ds->mAPBuffer.getModel());
	pDM_uiDevice->getDeviceListView()->setModel(pDM_ds->mDeckDeviceBuffer.getModel());
	setConnection();
	

	//DashBoard data Read
	dataReceiveThread.start();

	//device List Data Read
	pDM_db->requestQuery(DEVICELIST_DATA);

	//DashBoard update start
	mUpdateTimer.start(1000);
}

DataManager::~DataManager() {

	if (pDM_db->isConnection()) pDM_db->disconnectDB();

	disconnect(&wavFileSendThread, SIGNAL(started()), pDM_vs, SLOT(SendToVoiceFile()));
	disconnect(pDM_vs, SIGNAL(sigSendEND()), &wavFileSendThread, SLOT(quit()));
}

void DataManager::setClassLink(UI *_ui, AudioRecorder *_ar, DataStorage *_ds,
							   VoiceSender *_vs, DB_MySQL *_db, JsonControll *_json) {
	pDM_ui = _ui;
	pDM_ar = _ar;
	pDM_ds = _ds;
	pDM_vs = _vs;
	pDM_db = _db;
	pDM_json = _json;

	pDM_uiDash		= _ui->uiDashBoard;
	pDM_uiDevice	= _ui->uiDevice;

	//pCount = &_ds->mCountData;
}

inline void DataManager::setConnection(void) {

	connect(pDM_uiDash, SIGNAL(sigPressPTTBtn()), this, SLOT(onPressPTTBtn()));
	connect(pDM_uiDash, SIGNAL(sigReleasePTTBtn()), this, SLOT(onReleasePTTBtn()));

	connect(pDM_uiDash, SIGNAL(sigReleaseOPTIONBtn()), this, SLOT(onReleaseOPTIONBtn()));
	connect(pDM_uiDash, SIGNAL(sigReleaseMODEBtn()), this, SLOT(onReleaseMODEBtn()));
	
	connect(&wavFileSendThread, SIGNAL(started()), pDM_vs, SLOT(SendToVoiceFile()));
	connect(pDM_vs, SIGNAL(sigSendEND()), &wavFileSendThread, SLOT(quit()));

	// request db
	connect(&dataReceiveThread, SIGNAL(started()), pDM_db, SLOT(Running_receiveDB()));

	// update dashboard;
	connect(&mUpdateTimer, SIGNAL(timeout()), this, SLOT(reading_DB()));
	connect(pDM_db, SIGNAL(sigGETDATA(resultTable *)), this, SLOT(UPDATE_DATA(resultTable *)));

	//update Device Managment
	connect(pDM_uiDevice, SIGNAL(sigDeviceID(QString)), this, SLOT());
	
}

void DataManager::timerEvent(QTimerEvent *event) {
	talkTIme++;
	qDebug() << "talking time : " <<  talkTIme << "sec";
}

/***************************************************************************/
/* SLOT Funtion															   */
/***************************************************************************/
void DataManager::onPressPTTBtn(void) {
	qDebug() << "pressed PTT BAR Button";
	pDM_vs->wavFilePath = pDM_ar->startRecord();

	talkTimer.start(1000, this);
}

void DataManager::onReleasePTTBtn(void) {
	qDebug() << "click PTT BAR Button";

	//Change Dashboard bottom PTT Btn
	pDM_uiDash->bottomBarBtn->toggleBtn();
	pDM_uiDash->EmergencyBtn->hide();
	pDM_uiDash->MICOptionBtn->hide();
	pDM_ar->hide();

	talkTimer.stop();
	if (talkTIme <= PPT_TALKTIME_SEC) {
		return;
	}
	else {
		talkTIme = 0;
	}

	pDM_ar->stopRecord();
	emit sigRecoding_Done();

	// Sending Recode File
	qDebug() << QThread::currentThread() << " : " << QThread::currentThreadId();

	wavFileSendThread.start();
}

void DataManager::onReleaseOPTIONBtn(void) {

	if (pDM_ar->isVisible()) {
		pDM_ar->hide();
	} else {
		pDM_ar->show();
	}
}
void DataManager::onReleaseMODEBtn(void) {
	
	pDM_uiDash->DASHBOARD_Emergency_MODE(80000);
	pDM_uiDash->bottomBarBtn->toggleBtn();
	pDM_uiDash->PTTBtn->hide();
	pDM_uiDash->EmergencyBtn->hide();
	pDM_uiDash->MICOptionBtn->hide();

	pDM_ar->hide();
}

void DataManager::update_DashBoard(resultTable result) {
	//qDebug() << "update_DashBoard";
	
	//dbDataBuf = result;

	//update Tag Data
	pDM_ds->mTagBuffer.updateBuffer(&result);

	pDM_ds->checkToPeople();
	pDM_ui->uiDashBoard->updateDASHBOARD(
		QString::number(pDM_ds->mTagBuffer.getEnable()),
		QString::number(pDM_ds->mTagBuffer.getDisable()),
		QString::number(pDM_ds->mAPBuffer.getEnable()),
		QString::number(pDM_ds->mAPBuffer.getDisable()),
		QString::number(pDM_ds->mTagBuffer.getEnable() + pDM_ds->mTagBuffer.getDisable()),
		QString::number(pDM_ds->mSafety),
		QString::number(pDM_ds->mDenger)
	);
	dbDataBuf.recode.clear();
	dbDataBuf.chk = false;

	/** Table View Header update  *************************************************/
	QStringList TagHead, APHead, DeviceHead;
	for each (auto& strKey in gTAG_INDEX) {
		TagHead << strKey.name;
	}
	for each (auto& strKey in gAP_INDEX) {
		APHead << strKey.name;
	}
	for each (auto& strKey in gDEVICE_INDEX) {
		DeviceHead << strKey.name;
	}

	pDM_ds->mTagBuffer.setViewHeader(TagHead);
	pDM_ds->mAPBuffer.setViewHeader(APHead);
	pDM_ds->mDeckDeviceBuffer.setViewHeader(DeviceHead);

	DashLISTView *pTargetList = pDM_ui->uiDashBoard->getTagView();
	pTargetList->setVisibleHeader(4, TAG_NO, CALC_DATE, SRC, BAT_V);

	pDM_uiDevice->setVisibleHeader(2, DeviceID, DeviceName);
	/*******************************************************************************/
}


void DataManager::update_DeviceManagment(resultTable result) {
	qDebug() << "update_DeviceManagment";
	
	pDM_ds->mDeckDeviceBuffer.updateBuffer(&result);
	pDM_uiDevice->getDeviceListView()->expandAll();
	pDM_uiDevice->getDECKView()->setScene(pDM_ds->mDeckDeviceBuffer.getScene(0));

}

void DataManager::update_InspectionList(resultTable result) {
	qDebug() << "update_InspectionList";
}

void DataManager::reading_DB(void) {
	pDM_db->requestQuery(DASHBOARD_DATA);
}

void DataManager::request_DeviceInspacktion_List(void) {
	pDM_db->requestQuery(DASHBOARD_DATA);
}

void DataManager::UPDATE_DATA(resultTable *result) {

	switch (result->dataKind) {
		case DASHBOARD_DATA:
			update_DashBoard(*result);
			break;
		case DEVICELIST_DATA:
			update_DeviceManagment(*result);
			break;
		case INSPACKTION_DATA:
			update_InspectionList(*result);
			break;
		case NONE_DATA:
			break;
	}	
}
