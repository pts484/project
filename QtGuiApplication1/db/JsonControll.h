#ifndef JSONCONTRLL_H
#define JSONCONTRLL_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>

#include <QThread>

#include "../define.h"

class JsonControll : public QObject
{
	Q_OBJECT

	uint				  nDataKind;
	resultTable			  result;

	QNetworkAccessManager *pNetMan;
	QNetworkRequest		  *pNetRequest;
	QByteArray			  mDataBuffer;

	inline resultTable jsonParser(QJsonObject &rObj, const colIndex *indexKind, QString key);

public:

	QNetworkAccessManager *getNetManager() { return pNetMan; }
	resultTable &getResult() { return result; }
	uint sendRequest(QString query, uint _Kind = 0);
	

	JsonControll(QObject *parent = 0);
	~JsonControll();

signals:
	void sigSend_DASHBOARD();
	void sigSend_DEVICELIST();
	void sigSend_INSPACTIONLIST();

public slots:
	void receiveJsonData(QNetworkReply *);


};
#endif
