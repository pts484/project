#include "JsonControll.h"

JsonControll::JsonControll(QObject *parent)
	: QObject(parent) {
	pNetworkAccessManager = new QNetworkAccessManager(this);
	QObject::connect(pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
}

/*
* Sends a request
*/
QNetworkReply* JsonControll::sendRequest(QString url) {
	QUrl httpRequest(url);
	QNetworkRequest request;
	request.setSslConfiguration(QSslConfiguration::defaultConfiguration()); // Set default ssl config
	request.setUrl(httpRequest); // Set the url
	QNetworkReply *reply = pNetworkAccessManager->get(QNetworkRequest(httpRequest));

	return reply;
}

/*
* Runs when the request is finished and has received a response
*/
void JsonControll::finishedSlot(QNetworkReply *reply) {
	// Reading attributes of the reply
	// e.g. the HTTP status code
	QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	// Or the target URL if it was a redirect:
	QVariant redirectionTargetUrl =
		reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
	// see CS001432 on how to handle this

	// no error received?
	if (reply->error() == QNetworkReply::NoError) {
		// Reading the data from the response
		QByteArray bytes = reply->readAll();
		QString jsonString(bytes); // string

		qDebug() << bytes;

		bool ok;
		//QVariantMap jsonResult = Json::parse(jsonString, ok).toMap();
		if (!ok) {
			qFatal("An error occured during parsing");
			exit(1);
		}

		// Set the jsonResult
		setJsonResult(m_jsonResult);
	}
	// Some http error received
	else {
		// handle errors here
	}

	// We receive ownership of the reply object
	// and therefore need to handle deletion.
	delete reply;
}

/*
* Set the json result so that other functions can get it
*/
void JsonControll::setJsonResult(QVariantMap jsonResult) {
	m_jsonResult = jsonResult;
}

/*
* Get the json result
* Return null if there is no result
*/
QVariantMap JsonControll::getJsonResult() {
	return m_jsonResult;
}
