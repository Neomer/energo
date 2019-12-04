#include "GSMConnection.h"

GSMConnection::GSMConnection(QString name, PortSettings settings)
{
	this->sets = settings;
	this->port = new QextSerialPort(name, settings, QextSerialPort::EventDriven);
	this->state = GCS_INITIALIZATION;
}

GSMConnection::GSMConnection(QString name, PortSettings settings, QString init_string)
{
	this->sets = settings;
	this->port = new QextSerialPort(name, settings, QextSerialPort::EventDriven);
	this->state = GCS_INITIALIZATION;
	if (!this->port->open(QIODevice::ReadWrite))
	{
		qDebug("GSMConnection::GSMConnection() - Can't open port!");
		err = "Can't open COM-port!";
		return;
	}
	QObject::connect(port, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	this->Initialize(init_string);
}

bool GSMConnection::Initialize(QString init_string)
{
	this->port->write(this->addCRLF(init_string), init_string.length() + 2);
	return true;
}

void GSMConnection::onReadyRead()
{
	int len = this->port->bytesAvailable();
	char buf[len];
	memset(buf, 0, len);
	this->port->read(buf, len);
	qDebug("GSMConnection::onReadyRead() - %i byte(s) received from device. \r\n%s", len, buf);
	
	switch (this->state)
	{
		case GCS_INITIALIZATION:
			if (!strcmp(buf, "ERROR\x0D\x0A"))
			{
				qDebug("GSMConnection::onReadyRead() - Received ERROR!");
			}
			break;
	}
}

QString GSMConnection::GetLastError()
{
	return err;
}
