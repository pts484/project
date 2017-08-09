#ifndef VOICESENDER_H
#define VOICESENDER_H

#include <QObject>
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
	VoiceSender(QObject *parent = nullptr);
	~VoiceSender();

	void SendToVoiceFile(QString HostName, int port);

public slots:
	void connected();
	void disconnected();
	void bytesWritten(qint64 bytes);
	void readyRead();
};
#endif // VOICESENDER_H