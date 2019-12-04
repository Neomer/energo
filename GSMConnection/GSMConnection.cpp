#include "GSMConnection.h"
#include <QDateTime>

GSMConnection::GSMConnection()
{
	this->state = GCS_CLOSED;
	this->mtx_read = new QMutex(QMutex::NonRecursive);
	this->tmr = new QTimer();
	this->sender = 0;
}

void GSMConnection::AcceptSettings2(GSMSettings *sets)
{
	qDebug("GSMConnection::AcceptSettings() - Change settings to itv=%ld retry=%d\n", sets->send_interval, sets->retry);
	this->settings = *sets;
	this->sender->setTimeout(sets->send_interval);
}

/***********************************************************
    SLOTS
 
*/
void GSMConnection::SendFromQueue()
{
	if (send_queue.isEmpty()) return;
	QByteArray ba = send_queue.at(0);
	send_queue.removeFirst();
	int sent = this->port->write(ba.constData(), ba.length());
	qDebug("GSMConnection::SendFromQueue() - Sending from queue %d byte(s)\n", ba.length());
	if (sent < 0)
	{
		qDebug("GSMConnection::SendFromQueue() - Sending data error : %s\n", this->port->errorString().toAscii().constData());
		err = this->port->errorString();
	}
}

void GSMConnection::onSerialReadyRead()
{
	/*
	int len = 0;
	while (!(len= this->port->bytesAvailable()));
	char buf[len];
	memset(buf, 0, len);
	this->port->read(buf, len);
	this->buf.append(QString::fromAscii(buf, len));
	qDebug("GSMConnection::onReadyRead() - %i byte(s) received from device.", len);
	if (this->buf.indexOf("\x0D\x0A") != -1)
	{
		this->buf.replace("\x0D\x0A", "");
		this->data_received = true;
		qDebug("GSMConnection::onReadyRead() - Message received.\r\n-> %s", this->buf.toAscii().constData());
	}
 */
	
}

void GSMConnection::onDevStateChange(bool status)
{
	this->buf = "";
	if (status)
	{
		qDebug("GSMConnection::onDevStateChange() - Device was turned on\n");
		this->state = GCS_INITIALIZATION;
	}
    else
	{
		qDebug("GSMConnection::onDevStateChange() - device was turned off\n");
		this->err = "Device was turned off";
		this->state = GCS_ERROR;
	}
}

void GSMConnection::onSendComplete(qint64 size)
{
	qDebug("GSMConnection::Send() - Sent %i byte(s)\n", (int)size);
}


/***********************************************************
    METHODS
 
*/

bool GSMConnection::Create(QString name, PortSettings settings)
{
	if ((this->state != GCS_ERROR) && (this->state != GCS_CLOSED)) 
	{
		qDebug("GSMConnection::Create() - Wrong device state for this operation!\n");
		err = "Wrong device state for creating!";
		return false;
	}

	this->settings.retry = 3;
	this->settings.send_interval = 1000;
	this->sets = settings;
	this->port = new QextSerialPort(name, settings, QextSerialPort::Polling);
	this->sender = new GSMSender(this->port);
	this->sender->setTimeout(this->settings.send_interval);
	this->state = GCS_INITIALIZATION;
	this->mtx_read = new QMutex();

	this->std_ans.append("OK\x0D\x0A");
	this->std_ans.append("ERROR\x0D\x0A");
	this->std_ans.append("NO CARRIER\x0D\x0A");
	this->std_ans.append("BUSY\x0D\x0A");
	this->std_ans.append("CONNECT 9600");
	
	if (!this->port->open(QIODevice::ReadWrite | QIODevice::Unbuffered))
	{
		qDebug("GSMConnection::Create() - Can't open port!\n");
		err = "Can't open COM-port!";
		this->state = GCS_ERROR;
		return false;
	}
	if (!(port->lineStatus() & LS_DSR)) 
	{
		qDebug("GSMConnection::Create() - Device is not turned on\n");
		return false;
	}
	qDebug("GSMConnection::Create() - Connected to %s\n", name.toAscii().constData());
	//connect(this->port, SIGNAL(readyRead()), this, SLOT(onSerialReadyRead()));
	connect(this->port, SIGNAL(dsrChanged(bool)), this, SLOT(onDevStateChange(bool)));
	connect(this->port, SIGNAL(bytesWritten(qint64)), this, SLOT(onSendComplete(qint64)));
	connect(this->tmr, SIGNAL(timeout()), this, SLOT(SendFromQueue()));
	this->tmr->start(1000);
	return true;
}

bool GSMConnection::Open(QIODevice::OpenMode mode)
{
	if (!this->port->open(QIODevice::ReadWrite | QIODevice::Unbuffered))
	{
		qDebug("GSMConnection::Open() - Can't open port!\n");
		err = "Can't open COM-port!";
		this->state = GCS_ERROR;
		return false;
	}
	this->state = GCS_INITIALIZATION;
	qDebug("GSMConnection::Open() - Connected to serial port\n");
	return true;
}

/*!
  Инициализирует локальный GSM-модем
  */
bool GSMConnection::Initialize(QString init_string)
{
	this->Send(init_string);
	QString buf(this->GetBuffer(2000));
	if (buf.indexOf("OK") != -1)
	{
		this->state = GCS_CONNECTING;
		return true;
	}
	else
		return false;
}

/*!
  Устанавливает соединение с удаленным GSM-модемом
 */
GSMCallResult GSMConnection::Connect(QString phone)
{
	this->Send(QString("atd").append(phone));
	QString res(this->Receive());
	if ((res == "OK")||(res.indexOf("CONNECT 9600") != -1))
	{
		this->state = GCS_DATA;
		return GCR_OK;
	}
	else if (res == "BUSY")
		return GCR_BUSY;
	else if (res == "NO CARRIER")
		return GCR_NO_CARRIER;
	else
		return GCR_ERROR;
}

/*!
  Разрывает соединение с удаленным GSM-модемом
 */
bool GSMConnection::Disconnect()
{
	if (this->state == GCS_ERROR) return false;
	/*if (this->state != GCS_DATA)
	{
		qDebug("GSMConnection::Disconnect() - Wrong operation on this state!\n");
		this->err = "Wrong operation on this state!";
		return false;
	}*/
	QString ret;
	this->port->write("+++", 3);
	ret = QString(this->GetBuffer(2000));
	this->Send(QString("ATH"));
	ret = QString(this->Receive());
	if (ret.indexOf("OK") != -1)
		this->state = GCS_CONNECTING;
	else
	{
		this->err = "Switching device to AT-mode failed!";
		return false;
	}
	return true;
}


/*!
  Отправляет данные на удаленный GSM-модем
 */
int GSMConnection::Send(char *data, int len)
{
	if ((this->state == GCS_ERROR)||(this->state == GCS_CLOSED))
	{
		qDebug("GSMConnection::Send() - Trying to send data without connection!\n");
		err = "Connection rejected!";
		return -1;
	}
	this->data_received = false;
	this->buf = "";
	qDebug("GSMConnection::Send() - Sending %i byte(s):\n", len);
	for (int i = 0; i < len; i++) qDebug("%.2x|", ((unsigned char *)data)[i]);
	qDebug("\n");
	int sent = this->port->write(data, len);
	if (sent < 0)
	{
		qDebug("GSMConnection::Send() - Sending data error: %s\n", this->port->errorString().toAscii().constData());
		err = this->port->errorString();
	}
	return sent;
}

/*!
  Отправляет данные на удаленный GSM-модем
 */

int GSMConnection::Send(char *data, int start, int len)
{
	if ((this->state == GCS_ERROR)||(this->state == GCS_CLOSED))
	{
		qDebug("GSMConnection::Send() - Trying to send data without connection!\n");
		err = "Connection rejected!";
		return -1;
	}
	this->data_received = false;
	this->buf = "";
	qDebug("GSMConnection::Send() - Sending %i byte(s): %s\n", len, data + start);
	int sent = this->port->write(data + start, len);
	if (sent < 0)
	{
		qDebug("GSMConnection::Send() - Sending data error: %s\n", this->port->errorString().toAscii().constData());
		err = this->port->errorString();
	}
	return sent;
}

/*!
  Отправляет данные на удаленный GSM-модем
 */
int GSMConnection::Send(QString data)
{
	if ((this->state == GCS_ERROR)||(this->state == GCS_CLOSED))
	{
		qDebug("GSMConnection::Send() - Trying to send data without connection!\n");
		err = "Connection rejected!";
		return -1;
	}
	this->data_received = false;
	this->buf = "";
	data.append("\x0D\x0A");
	qDebug("GSMConnection::Send() - Sending %i byte(s): %s\n", data.length(), data.toAscii().constData());
	sender->addToQueue(data.toAscii());
	/*int sent = this->port->write(data.toAscii().constData(), data.length());
	if (sent < 0)
	{
		qDebug() << "GSMConnection::Send() - Sending data error : " << this->port->errorString();
		err = this->port->errorString();
	}*/
	return data.length();
}

/*!
  Отправляет данные на удаленный GSM-модем
 */
int GSMConnection::Send(QByteArray data)
{
	if ((this->state == GCS_ERROR)||(this->state == GCS_CLOSED))
	{
		qDebug("GSMConnection::Send() - Trying to send data without connection!\n");
		err = "Connection rejected!";
		return -1;
	}
	this->data_received = false;
	this->buf = "";
	data.append(QString("\x0D\x0A"));
	qDebug("GSMConnection::Send() - Sending %i byte(s):\n", data.length());
	for (int i = 0; i < data.length(); i++)
	{
		qDebug("%.2X|", (unsigned char)data.at(i));
	}
	qDebug("\n");
	int sent = this->port->write(data.constData(), data.length());
	if (sent < 0)
	{
		qDebug() << "GSMConnection::Send() - Sending data error : " << this->port->errorString();
		err = this->port->errorString();
	}
	return sent;
}

/*!
  Отправляет данные на удаленный GSM-модем
 */
int GSMConnection::Send(QString data, bool CRLF)
{
	if ((this->state == GCS_ERROR)||(this->state == GCS_CLOSED))
	
	{
		qDebug("GSMConnection::Send() - Trying to send data without connection!\n");
		err = "Connection rejected!";
		return -1;
	}
	this->data_received = false;
	this->buf = "";
	if (CRLF) data.append("\x0D\x0A");
	qDebug("GSMConnection::Send() - Sending %i byte(s): %s\n", data.length(), data.toAscii().constData());
	int sent = this->port->write(data.toAscii().constData(), data.length());
	if (sent < 0)
	{
		qDebug() << "GSMConnection::Send() - Sending data error : " << this->port->errorString();
		err = this->port->errorString();
	}
	return sent;
}

/*!
  Отправляет данные на удаленный GSM-модем
 */
int GSMConnection::Send(QByteArray data, bool CRLF)
{
	if ((this->state == GCS_ERROR)||(this->state == GCS_CLOSED))
	{
		qDebug("GSMConnection::Send() - Trying to send data without connection!\n");
		err = "Connection rejected!";
		return -1;
	}
	this->data_received = false;
	this->buf = "";
	if (CRLF) data.append(QString("\x0D\x0A"));
	qDebug("GSMConnection::Send() - Sending %i byte(s):\n", data.length());
	sender->addToQueue(data);
	return data.length();
}



QByteArray GSMConnection::Receive()
{
	this->mtx_read->lock();
	int len = 0;
	QByteArray ret;
	QDateTime dt = QDateTime::currentDateTime();
	do 
	{
		while (!(len= this->port->bytesAvailable()))
		{
			SleeperThread::msleep(100);
		}
		char buf[len];
		memset(buf, 0, len);
		this->port->read(buf, len);
		ret.append(buf, len);
		qDebug("GSMConnection::Receive() - %i byte(s) received from device.\n", len);
		qDebug("GSMConnection::Receive() - Message received.\r\n-> %s\n", ret.constData());
	} 
	while ((!this->checkOnStdAns(ret))&&(dt.secsTo(QDateTime::currentDateTime()) < MAX_RESPONSE_TIME));
	this->buf = QString(ret).replace("\x0D\x0A", "");
	this->mtx_read->unlock();
	return this->buf.toAscii();
}

QByteArray GSMConnection::GetBuffer()
{
	this->mtx_read->lock();
	int len = 0;
	QByteArray ret;
	while (!(len= this->port->bytesAvailable()));
	char buf[len];
	this->port->read(buf, len);
	ret.append(buf, len);
	qDebug("GSMConnection::GetBuffer() - %i byte(s) received from device.\n", len);
	qDebug("GSMConnection::GetBuffer() - Message received.\n");
	for (int i = 0; i < len; i++) qDebug("%.2X|", ((unsigned char *)buf)[i]);
	qDebug("\n");
	this->mtx_read->unlock();
	return ret;
}

/*
GSMConnection::GetBuffer() - 19 byte(s) received from device.
GSMConnection::GetBuffer() - Message received.
16|00|21|00|00|00|24|00|00|13|18|10|11|00|1E|6A|FF|E8|91|
GSMConnection::GetBuffer() - Received empty string. Send again 2 time(s)
GSMSender::addToQueue() - Added new package to queue: 8 byte(s)
GSMSender::run() - Sending 8 byte(s)
Send:
16|06|03|3C|70|10|6E|A9|
GSMConnection::GetBuffer() - 19 byte(s) received from device.
GSMConnection::GetBuffer() - Message received.
16|00|21|00|00|00|24|00|00|13|18|10|11|00|1E|6A|FF|E8|91|
GSMConnection::GetBuffer() - Received empty string. Send again 2 time(s)
GSMSender::addToQueue() - Added new package to queue: 8 byte(s)
GSMSender::run() - Sending 8 byte(s)
Send:
16|06|03|3C|70|10|6E|A9|
GSMConnection::GetBuffer() - 19 byte(s) received from device.
GSMConnection::GetBuffer() - Message received.
16|00|21|00|00|00|24|00|00|13|18|10|11|00|1E|6A|FF|E8|91|
GSMConnection::GetBuffer() - Received empty string. Send again 2 time(s)
GSMSender::addToQueue() - Added new package to queue: 8 byte(s)
GSMSender::run() - Sending 8 byte(s)
Send:
16|06|03|3C|70|10|6E|A9|
GSMConnection::GetBuffer() - 19 byte(s) received from device.
GSMConnection::GetBuffer() - Message received.
16|00|21|00|00|00|24|00|00|13|18|10|11|00|1E|6A|FF|E8|91|
GSMConnection::GetBuffer() - Received empty string. Send again 2 time(s)
GSMSender::addToQueue() - Added new package to queue: 8 byte(s)
GSMSender::run() - Sending 8 byte(s)
Send:
16|06|03|3C|70|10|6E|A9|
GSMConnection::GetBuffer() - 19 byte(s) received from device.
GSMConnection::GetBuffer() - Message received.
16|00|21|00|00|00|24|00|00|13|18|10|11|00|1E|6A|FF|E8|91|
GSMConnection::GetBuffer() - Received empty string. Send again 2 time(s)
GSMSender::addToQueue() - Added new package to queue: 8 byte(s)
GSMSender::run() - Sending 8 byte(s)
Send:
16|06|03|3C|70|10|6E|A9|
GSMConnection::GetBuffer() - 19 byte(s) received from device.
GSMConnection::GetBuffer() - Message received.
16|00|21|00|00|00|24|00|00|13|18|10|11|00|1E|6A|FF|E8|91|
GSMConnection::GetBuffer() - Received empty string. Send again 2 time(s)
GSMSender::addToQueue() - Added new package to queue: 8 byte(s)
GSMSender::run() - Sending 8 byte(s)
Send:
16|06|03|3C|70|10|6E|A9|
GSMConnection::GetBuffer() - 19 byte(s) received from device.
GSMConnection::GetBuffer() - Message received.
16|00|21|00|00|00|24|00|00|13|18|10|11|00|1E|6A|FF|E8|91|
GSMConnection::GetBuffer() - Received empty string. Send again 2 time(s)
GSMSender::addToQueue() - Added new package to queue: 8 byte(s)
GSMSender::run() - Sending 8 byte(s)
Send:
16|06|03|3C|70|10|6E|A9|
GSMConnection::GetBuffer() - 19 byte(s) received from device.
GSMConnection::GetBuffer() - Message received.
16|00|21|00|00|00|24|00|00|13|18|10|11|00|1E|6A|FF|E8|91|
GSMConnection::GetBuffer() - Received empty string. Send again 2 time(s)
GSMSender::addToQueue() - Added new package to queue: 8 byte(s)
GSMSender::run() - Sending 8 byte(s)
Send:
16|06|03|3C|70|10|6E|A9|
GSMConnection::GetBuffer() - 19 byte(s) received from device.
GSMConnection::GetBuffer() - Message received.
16|00|21|00|00|00|24|00|00|13|18|10|11|00|1E|6A|FF|E8|91|
GSMConnection::GetBuffer() - Received empty string. Send again 2 time(s)
GSMSender::addToQueue() - Added new package to queue: 8 byte(s)
GSMSender::run() - Sending 8 byte(s)
*/

QByteArray GSMConnection::GetBuffer(long msec)
{
	qDebug("GSMConnection::GetBuffer() - [Thread 0x%.4X] Try to lock mutex\n", (int) QThread::currentThreadId());
	this->mtx_read->lock();
	QByteArray ret;
	char retry = this->settings.retry;
	
	while ((ret.size() == 0)&&((retry--) > 0))
	{
		SleeperThread::msleep(msec);
		
		int len = this->port->bytesAvailable();
		if (len > 0)
		{
			char buf[len];
			this->port->read(buf, len);
			ret.append(buf, len);
			qDebug("GSMConnection::GetBuffer() - %i byte(s) received from device.\n", len);
			qDebug("Receive:\n");
			char tmp[len * 3 + 3];
			for (int i = 0; i < len; i++) sprintf(tmp + i * 3, "%.2X|", ((unsigned char *)buf)[i]);
			qDebug("%s\n", tmp);
		}
		else
		{
			qDebug("GSMConnection::GetBuffer() - Received empty string. Send again %d time(s)\n", retry);
			if (retry > 0) this->sender->retryLast();
		}
	}
	this->mtx_read->unlock();
	qDebug("GSMConnection::GetBuffer() - [Thread 0x%.4X] Mutex unlocked\n", (int) QThread::currentThreadId());
	return ret;
}

/*!
  Возвращает последнюю ошибку
 */
QString GSMConnection::GetLastError()
{
	return err;
}

/*!
  Возвращает текущее состояние соединения
 */
GSMConnectionState GSMConnection::getStatus()
{
	return this->state;
}

/*!
  Закрывает COM-порт
 */
void GSMConnection::Close()
{
	if (this->state == GCS_ERROR) return;
	this->Send(QString("ath0"));
	QString ret(this->Receive());
	if (ret == "OK")
	{
		this->state = GCS_CLOSED;
		this->port->close();
		qDebug("GSMConnection::Close() - Port successfully closed. State changed to GCS_CLOSED.\n");
	}
	else
		qDebug("GSMConnection::Close() - Port closing failed!\n");
}

bool GSMConnection::checkOnStdAns(QByteArray data)
{
	return this->checkOnStdAns(QString(data));
}

bool GSMConnection::checkOnStdAns(QString data)
{
	for (int i = 0; i < this->std_ans.length(); i++)
	{
		if (data.indexOf(this->std_ans.at(i)) != -1) return true;
	}
	return false;
}

void GSMConnection::RetryLast()
{
	this->sender->retryLast();
}

void GSMConnection::setSendTimeout(int timeout)
{
	this->sender->setTimeout(timeout);
}

Q_EXPORT_PLUGIN(GSMConnection);
