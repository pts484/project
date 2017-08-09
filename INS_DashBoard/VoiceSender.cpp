#include "VoiceSender.h"

VoiceSender::VoiceSender(QObject *parent)
	: QObject(parent)
{
	socket = new QTcpSocket(this);
	connect(socket, SIGNAL(connected()), this, SLOT(connected()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
	connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
}

VoiceSender::~VoiceSender()
{
	disconnect(socket, SIGNAL(connected()), this, SLOT(connected()));
	disconnect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	disconnect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
	disconnect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
	if (!socket) delete socket;
}


void VoiceSender::SendToVoiceFile(QString HostName, int port){
	

	qDebug() << "Connecting,..";

	socket->connectToHost(HostName, port);

	if (!socket->waitForDisconnected(1000))
	{
		qDebug() << "Error: " << socket->errorString();
	}
}

void VoiceSender::connected()
{
	qDebug() << "Connected!";

	socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");

	QString filepath("C:\Users\tspark\Documents\clip_0001.wav");

	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "file open faild";
	}
	QDataStream in(&file);    // read the data serialized from the file
	QString str;
	qint32 a;
	in >> str >> a;
}

void VoiceSender::disconnected()
{
	if (socket->isOpen()) {
		socket->close();
		qDebug() << "Disconnected!";
	}
}

void VoiceSender::bytesWritten(qint64 bytes)
{
	qDebug() << "We wrote: " << bytes;
}

void VoiceSender::readyRead()
{
	qDebug() << "Reading...";
	qDebug() << socket->readAll();
}
