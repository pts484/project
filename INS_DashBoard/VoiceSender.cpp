#include "VoiceSender.h"
#include "define.h"

VoiceSender::VoiceSender(QObject *parent)
	: QObject(parent)
{

	wavFilePath = "";

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


void VoiceSender::SendToVoiceFile() {
	
	qDebug() << "/************* On Thread **************/";
	qDebug() << "/* Thread ID : " << QThread::currentThread() << " : " << QThread::currentThreadId();
	qDebug() << "Connecting,..";

	socket->connectToHost(PPT_HOST, PPT_PORT);
	if (socket->waitForConnected(MAX_CONNECTING_TIME)){
		qDebug("Connected!");
	}
}

void VoiceSender::connected()
{
	qDebug() << "Connected!";
	QString filepath(wavFilePath);

	QFile file(filepath);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "[READ File Fail] --> Don't Send";

	} else {

		QByteArray bytes = file.readAll();

		qDebug() << "[READ File Success] --> " << bytes.size() << "byte : " << wavFilePath;
		
		int sendByte = socket->write(bytes);
		socket->flush();

		if (bytes.size() == sendByte) {
			qDebug() << "file Complete transmission !";
		} else {
			qDebug() << "file Incomplete transmission !";
		}
		emit sigSendEND();
	}

	socket->disconnectFromHost();
}

void VoiceSender::disconnected()
{
	if (socket->state() == QAbstractSocket::UnconnectedState ||
		socket->waitForDisconnected(MAX_CONNECTING_TIME))
	{
		qDebug() << "Disconnecting...!";
		if (socket->isOpen()) {
			socket->close();
			qDebug() << "Disconnected!";
		}
	} else {
		qDebug() << "Error: " << socket->errorString();
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
