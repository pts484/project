#ifndef VOICESENDER_H
#define VOICESENDER_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QUrl>
#include <QDataStream>
#include <QTcpSocket>
#include <QString>

class VoiceSender : public QObject
{
	Q_OBJECT

	QTcpSocket *socket;

public:

	QString		wavFilePath;

	VoiceSender(QObject *parent = nullptr);
	~VoiceSender();

signals:
	void sigSendEND();

public slots:

	void SendToVoiceFile();

	void connected();
	void disconnected();
	void bytesWritten(qint64 bytes);
	void readyRead();
};
#endif // VOICESENDER_H