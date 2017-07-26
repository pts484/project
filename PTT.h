#ifndef PTT_H
#define PTT_H

#include <QObject>
#include <QAudioRecorder>

class PTT : public QObject
{
	Q_OBJECT


		QAudioRecorder *audioRecorder;

public:
	PTT(QObject *parent = 0);
	~PTT();
}; 

#endif // END PTT_H
