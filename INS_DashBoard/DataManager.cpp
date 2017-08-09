#include "DataManager.h"


DataManager::DataManager(QObject *parent)
	: QObject(parent)
{
}

DataManager::DataManager(UI *_ui, AudioRecorder *_ar, DataStorage *_ds, VoiceSender *_vs, QObject *parent)
	: QObject(parent)
{
	setLinkedClass(_ui, _ar, _ds, _vs);

	setConnection();

	pDM_vs->SendToVoiceFile("kotoko.iptime.org", 80);


}

DataManager::~DataManager()
{
}

void DataManager::setLinkedClass(UI *_ui, AudioRecorder *_ar, DataStorage *_ds, VoiceSender *_vs) {
	pDM_ui = _ui;
	pDM_ar = _ar;
	pDM_ds = _ds;
	pDM_vs = _vs;

	pDM_uiDash		= _ui->uiDashBoard;
	pDM_uiDevice	= _ui->uiDevice;

}

inline void DataManager::setConnection(void) {

	connect(pDM_uiDash, SIGNAL(sigPressPTTBtn()), this, SLOT(onPressPTTBtn()));
	connect(pDM_uiDash, SIGNAL(sigReleasePTTBtn()), this, SLOT(onReleasePTTBtn()));

}


/***************************************************************************/
/* SLOT Funtion															   */
/***************************************************************************/
void DataManager::onPressPTTBtn(void) {
	qDebug() << "pressed PTT BAR Button";
	pDM_ar->startRecord();
}

void DataManager::onReleasePTTBtn(void) {
	qDebug() << "click PTT BAR Button";
	pDM_ar->stopRecord();

	emit sigRecoding_Done();
}