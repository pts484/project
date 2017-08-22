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

class JsonControll : public QObject
{
	Q_OBJECT
		QVariantMap m_jsonResult;
		QNetworkAccessManager *pNetworkAccessManager;


public:

	JsonControll(QObject *parent = 0);
	~JsonControll() {};

	QNetworkReply* sendRequest(QString url);

	void setJsonResult(QVariantMap jsonResult);
	QVariantMap getJsonResult();

public slots:
	void finishedSlot(QNetworkReply *reply);

};
#endif