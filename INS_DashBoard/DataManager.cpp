#include "DataManager.h"


DataManager::DataManager(QObject *parent)
	: QObject(parent) {
}

DataManager::DataManager(UI *_ui, AudioRecorder *_ar, DataStorage *_ds, VoiceSender *_vs, DB_MySQL *_db, QObject *parent)
	: QObject(parent) {

	talkTIme = 0;

	setClassLink(_ui, _ar, _ds, _vs, _db);

	pDM_vs->moveToThread(&wavFileSendThread);

	setConnection();


	pDM_db->connectDB();
	update_DashBoard();
}

DataManager::~DataManager() {

	if (pDM_db->isConnection()) pDM_db->disconnectDB();

	disconnect(&wavFileSendThread, SIGNAL(started()), pDM_vs, SLOT(SendToVoiceFile()));
	disconnect(pDM_vs, SIGNAL(sigSendEND()), &wavFileSendThread, SLOT(quit()));
}

void DataManager::setClassLink(UI *_ui, AudioRecorder *_ar, DataStorage *_ds, VoiceSender *_vs, DB_MySQL *_db) {
	pDM_ui = _ui;
	pDM_ar = _ar;
	pDM_ds = _ds;
	pDM_vs = _vs;
	pDM_db = _db;

	pDM_uiDash		= _ui->uiDashBoard;
	pDM_uiDevice	= _ui->uiDevice;

	pCount = &_ds->mCountData;
}

inline void DataManager::setConnection(void) {

	connect(pDM_uiDash, SIGNAL(sigPressPTTBtn()), this, SLOT(onPressPTTBtn()));
	connect(pDM_uiDash, SIGNAL(sigReleasePTTBtn()), this, SLOT(onReleasePTTBtn()));

	connect(pDM_uiDash, SIGNAL(sigReleaseOPTIONBtn()), this, SLOT(onReleaseOPTIONBtn()));
	connect(pDM_uiDash, SIGNAL(sigReleaseMODEBtn()), this, SLOT(onReleaseMODEBtn()));
	
	connect(&wavFileSendThread, SIGNAL(started()), pDM_vs, SLOT(SendToVoiceFile()));
	connect(pDM_vs, SIGNAL(sigSendEND()), &wavFileSendThread, SLOT(quit()));
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

void DataManager::update_DashBoard(void) {
	qDebug() << "update_DashBoard";

	//read DB Data
	dbDataBuf = pDM_db->runQuery("select * from taginfo");
	
	if (!dbDataBuf.chk) {
		qDebug() << "DB READ ERROR !";
		return;
	}
	//create UI List Item 
	for (int i = 0; i < dbDataBuf.recode.size(); ++i) {
		QStringList &pObj = dbDataBuf.recode.takeAt(i);
		pDM_ds->mTagBuffer.addRecode(pObj.at(ColumeIndex_TAG::TagID), pObj);
	}

	//Tag Enable/Disable count Check
	pDM_ds->mTagBuffer.checkToActive(ACTIVE_INTERVAL, ColumeIndex_TAG::TagDATE);
	pDM_ds->checkToPeople();

	QStandardItemModel *pTagModel = pDM_ds->mTagBuffer.getModel();
	pDM_ui->uiDashBoard->getTagView()->setModel(pTagModel);
	pDM_ds->mTagBuffer.updateModel();

	QStandardItemModel *pAPModel = pDM_ds->mAPBuffer.getModel();
	pDM_ui->uiDashBoard->getAPView()->setModel(pAPModel);
	pDM_ds->mAPBuffer.updateModel();

	QStringList TagHead, APHead;
	TagHead << STR_KOR("TAG ID") << STR_KOR("TAG 이름") << STR_KOR("마지막 배터리 상태");
	APHead << STR_KOR("AP ID") << STR_KOR("AP 이름") << STR_KOR("데크");

	pDM_ds->mTagBuffer.setViewHeader(TagHead);
	pDM_ds->mAPBuffer.setViewHeader(APHead);

	DashLISTView *pTargetList = pDM_ui->uiDashBoard->getTagView();
	//pTargetList->setVisibleHeader();

	pDM_ui->uiDashBoard->updateDASHBOARD(
		QString::number(pCount->nTagEnable),
		QString::number(pCount->nTagDisable),
		QString::number(pCount->nAPEnable),
		QString::number(pCount->nAPDisable),
		QString::number(pCount->nPeopleTotal),
		QString::number(pCount->nPeopleEnable),
		QString::number(pCount->nPeopleDisable)
	);

	dbDataBuf.recode.clear();
}

void DataManager::update_DeviceManagment(void) {

}

void DataManager::update_InspectionList(void) {

}
