#include "GSMSender.h"

GSMSender::GSMSender(QextSerialPort *port)
{
	this->port = port;
	this->timeout = 1000;
	this->start();
	this->mtx = new QMutex();
}

void GSMSender::setTimeout(long timeout)
{
	qDebug("GSMSender::setTimeout() - Timeout changed to %ld\n", timeout);
	this->timeout = timeout;
}

void GSMSender::addToQueue(QByteArray data)
{
	this->mtx->lock();
	this->queue.append(data);
	qDebug("GSMSender::addToQueue() - Added new package to queue: %d byte(s) Total msgs in queue: %d\n", 
	       data.size(),
	       this->queue.length());
	this->mtx->unlock();
}

void GSMSender::retryLast()
{
	if (this->last.size() > 0) addToQueue(this->last);
}

void GSMSender::run()
{
	char * buf;
	while(true)
	{
		this->msleep(this->timeout);
		this->mtx->lock();
		if (!queue.isEmpty())
		{
			QByteArray ba = queue.takeAt(0);
			this->last = ba;
			qDebug("GSMSender::run() - Sending %d byte(s)\n", ba.size());
			qint64 sent = 0;
			sent = this->port->write(ba.constData(), ba.length());
			int retry = 5;
			while ((ba.length() - sent > 0)&&(retry-- > 0))
			{
				qDebug("GSMSender::run() - Not all data was sent!");
				sent += this->port->write(ba.constData() + sent, ba.length() - sent);
			}
			buf = (char *)ba.constData();
			qDebug("Send:\n");
			char tmp[ba.size() * 3 + 3];
			for (int i = 0; i < ba.size(); i++) sprintf(tmp + i * 3, "%.2X|", ((unsigned char *)buf)[i]);
			qDebug("%s\n", tmp);
		}
		//else
		//	qDebug("GSMSender::run() - Queue is empty. Make sleep for 1 sec.");
		this->mtx->unlock();
	}
}
