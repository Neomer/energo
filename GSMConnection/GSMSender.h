#ifndef GSMSENDER_H
#define GSMSENDER_H

#define NO_DEBUG

#include <QThread>
#include <QList>
#include <QString>
#include <QByteArray>
#include <QMutex>
#include <stdio.h>
#include "../qextserialport/src/qextserialport.h"

class GSMSender : public QThread
{
public:
    GSMSender(QextSerialPort * port);
	void addToQueue(QByteArray data);
	void setTimeout(long timeout);
	void retryLast();
	
protected:
	void run();
	QextSerialPort * port;
	QList<QByteArray> queue;
	long timeout;
	QMutex *mtx;
	QByteArray last;
};

#endif // GSMSENDER_H
