#ifndef GSMCONNECTION_H
#define GSMCONNECTION_H

#include <QtDebug>

#include <QObject>
#include <QThread>
#include <QWaitCondition>
#include <QIODevice>
#include <QByteArray>
#include <QMutex>
#include <QList>
#include "../QextSerialPort/src/qextserialport.h"
#include <QtPlugin>
#include <QTimer>
#include <QList>

#include "GSMConnectionInterface.h"
#include "GSMSender.h"

/*!
  Класс для остановки потока
 */
class SleeperThread : public QThread
{
public:
	static void msleep(unsigned long msecs)
	{
		QThread::msleep(msecs);
	}
};

#define MAX_RESPONSE_TIME	20

/*!
  Класс обеспечивает соединение между двумя GSM-модемами, 
  подключенными к COM-портам.
 */
class GSMConnection : public QObject, public GSMConnectionInterface
{
Q_OBJECT
Q_INTERFACES(GSMConnectionInterface)
	
public:
	GSMConnection();
	void AcceptSettings2(GSMSettings *sets);	
	bool Create(QString name, PortSettings settings);
	QString GetLastError();
	GSMConnectionState getStatus();
	
	bool Open(QIODevice::OpenMode mode);
	void Close();
	
	/*!
	  Инициализирует начальные настройки в модеме.
	 */
	bool Initialize(QString init_string);
	
	GSMCallResult Connect(QString phone);
	bool Disconnect();
	
	int Send(char * data, int len);
	int Send(char * data, int start, int len);
	int Send(QString data);
	int Send(QByteArray data);
	
	int Send(QString data, bool CRLF);
	int Send(QByteArray data, bool CRLF);
	void RetryLast();
	
	void setSendTimeout(int timeout);
	
	QByteArray Receive();
	QByteArray GetBuffer();
	QByteArray GetBuffer(long msec);
	
	static const char * addCRLF(QString text)
	{
		text.append("\x0D\x0A");
		return text.toAscii().constData();
	}
	
private slots:
	void onSerialReadyRead();
	void onDevStateChange(bool status);
	void onSendComplete(qint64 size);
	void SendFromQueue();

private:
	bool checkOnStdAns(QByteArray data);
	bool checkOnStdAns(QString data);
	
protected:
	QextSerialPort * port;
	PortSettings sets;
	QString err;
	GSMConnectionState state;
	QMutex * mtx_read;
	QString buf;
	bool data_received;
	QList<QString> std_ans;
	QTimer * tmr;
	QList<QByteArray> send_queue;
	GSMSender *sender;
	GSMSettings settings;
};

#endif // GSMCONNECTION_H
