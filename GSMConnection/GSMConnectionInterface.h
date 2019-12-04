#ifndef GSMCONNECTIONINTERFACE_H
#define GSMCONNECTIONINTERFACE_H

#include <QObject>
#include <QThread>
#include <QWaitCondition>
#include <QIODevice>
#include <QByteArray>
#include <QMutex>
#include <QList>
#include "../QextSerialPort/src/qextserialport.h"

#ifndef _GSMCONNECTIONSTATE
#define _GSMCONNECTIONSTATE
enum GSMConnectionState
{
	GCS_INITIALIZATION,
	GCS_CONNECTING,
	GCS_DATA,
	GCS_ERROR,
	GCS_CLOSED
};

enum GSMCallResult
{
	GCR_OK,
	GCR_BUSY,
	GCR_NO_CARRIER,
	GCR_ERROR
};

struct GSMSettings
{
	long send_interval;
	int retry;
};

#endif

/*!
  Класс обеспечивает соединение между двумя GSM-модемами, 
  подключенными к COM-портам.
 */
class GSMConnectionInterface
{
public:
	virtual bool Create(QString name, PortSettings settings) = 0;
	virtual QString GetLastError() = 0;
	virtual GSMConnectionState getStatus() = 0;
	
	virtual bool Open(QIODevice::OpenMode mode) = 0;
	virtual void Close() = 0;
	
	/*!
	  Инициализирует начальные настройки в модеме.
	 */
	virtual bool Initialize(QString init_string) = 0;
	
	virtual GSMCallResult Connect(QString phone) = 0;
	virtual bool Disconnect() = 0;
	
	virtual int Send(char * data, int len) = 0;
	virtual int Send(char * data, int start, int len) = 0;
	virtual int Send(QString data) = 0;
	virtual int Send(QByteArray data) = 0;
	
	virtual int Send(QString data, bool CRLF) = 0;
	virtual int Send(QByteArray data, bool CRLF) = 0;
	virtual void RetryLast() = 0;
	
	virtual void setSendTimeout(int timeout) = 0;
	
	virtual QByteArray Receive() = 0;
	virtual QByteArray GetBuffer() = 0;
	virtual QByteArray GetBuffer(long msec) = 0;
};

Q_DECLARE_INTERFACE(GSMConnectionInterface,
                    "com.trolltech.Plugin.GSMConnectionInterface/1.0.2");


#endif // GSMCONNECTIONINTERFACE_H
