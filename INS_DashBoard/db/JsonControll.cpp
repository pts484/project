#include "JsonControll.h"

JsonControll::JsonControll(QObject *parent)
	: QObject(parent) {
	
	pNetMan = new QNetworkAccessManager(this);
	pNetRequest = new QNetworkRequest();
	mDataBuffer.clear();

	connect(pNetMan, SIGNAL(finished(QNetworkReply *)), this, SLOT(receiveJsonData(QNetworkReply *)));
}

JsonControll::~JsonControll() {
}

uint JsonControll::sendRequest(QString query, uint _Kind) {

	nDataKind = _Kind;

	result.chk = false;
	result.recode.clear();

	pNetRequest->setUrl(QUrl(query));
	pNetMan->get(*pNetRequest);

	return nDataKind;
}



void JsonControll::receiveJsonData(QNetworkReply *reply) {
//this lambda is called when the reply is received
//it can be a slot in your GUI window class
//check for errors


	if (reply->error() != QNetworkReply::NoError) {
		qDebug() << "Error";
		pNetMan->clearAccessCache();
	} else {
		//parse the reply JSON and display result in the UI
		QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();

		
		switch (nDataKind) {
		case 0:
			result = jsonParser(jsonObject, gTAG_INDEX, "EZ0600R");
			emit sigSend_DASHBOARD();
			break;
		case 1:
			result = jsonParser(jsonObject, gDEVICE_INDEX, "DeviceList");
			emit sigSend_DEVICELIST();
			break;
		case 2:
			result = jsonParser(jsonObject, gDEVICE_INDEX, "??????");
			emit sigSend_INSPACTIONLIST();
			break;
		default:
			result = jsonParser(jsonObject, gTAG_INDEX, "EZ0600R");
			emit sigSend_DASHBOARD();
			break;
		}
	}

	reply->deleteLater();

}



inline resultTable JsonControll::jsonParser(QJsonObject &rObj, const colIndex *indexKind, QString key) {

	QJsonArray jsonArray = rObj[key].toArray();

	for (int i = 0; i < jsonArray.size(); ++i) {
		QJsonValue jsonValue = jsonArray[i];
		QJsonObject mObj = jsonValue.toObject();

		QStringList mSTRList;
		QJsonObject::ConstIterator it = mObj.constBegin();

		for (int j = 0; it != mObj.constEnd(); ++it, ++j) {
			mSTRList << mObj[indexKind[j].key].toString();

		}
		result.recode << mSTRList;
	}
	result.chk = true;
	qDebug() << "get JSON Data size >> " << result.recode.size();
	return result;
}
