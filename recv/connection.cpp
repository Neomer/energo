#include "connection.h"
#include "../includes/pgre/libpq-fe.h"
#include <QStringList>
#include <stdlib.h>


Connection::Connection(ConnectionType type, QObject * parent) :
   QObject(parent)
{
    this->m_type = type;
	this->com = 0;
	this->sock = 0;
	this->gsm = 0;
}

// »нициализирует устройство св€зи.
bool Connection::Init(ConnectionInitParams *params)
{
	QPluginLoader *pl;
    switch (this->m_type)
    {
		case CT_DIRECT:
			if (params->serial_name != "")
			{
				this->com = new QextSerialPort(params->serial_name, 
											   params->serial_sets, 
											   QextSerialPort::Polling);
				if (!this->com->open(QIODevice::ReadWrite | QIODevice::Unbuffered))
				{
					qDebug("Connection::Init() - Can't open port!\n");
					err = "Can't open COM-port!";
					return false;
				}
			}
			else
			{
				qDebug("Connection::Init() - Open virtual serial port");
				this->com = CONNECTION_VIRTUAL_SERIAL_PORT;
			}
			break;
			
		case CT_TCPIP:
			this->sock = new QTcpSocket();
			break;
			
		case CT_GSM:
			pl = new QPluginLoader(QDir::currentPath().append("/GSMConnection.dll"));
			if (!pl->instance())
			{
				qDebug("Connection::Init() - Can't load GSM module!\n");
				this->err = "GSM module was not loaded";
				return false;
			}
			this->gsm = qobject_cast<GSMConnectionInterface *>(pl->instance());
			if (!this->gsm->Create(params->serial_name, params->serial_sets))
			{
				qDebug("Connection::Init() - Can't initialize GSM connection. GSM::Create() return's false.\n");
				this->err = "COM-port busy";
				return false;
			}
			this->gsm->Disconnect();
			if (!this->gsm->Initialize(params->serial_initstr))
			{
				qDebug("Connection::Init() - Can't initialize GSM connection. GSM::Initialize() return's false.\n");
				this->err = "Can't initialize GSM connection";
				return false;
			}
			break;
				
		default:
			qDebug("Connection::Init() - Unknown connection type.\n");
			this->err = "Unknown connection type";
			return false;
			break;
    }
	return true;
}

// —оедин€ет локальное устройство св€зи с удаленным
bool Connection::Connect(ConnectionParams *params)
{
	switch (this->m_type)
	{
		case CT_DIRECT:
			if (!this->com)
			{
				qDebug("Connection::Connect() - Using serial port without initialization!\n");
				this->err = "Using serial port without initialization";
				return false;
			}
			break;
			
		case CT_TCPIP:
			if (!this->sock) 
			{
				qDebug("Connection::Connect() - Using socket without initialization!\n");
				this->err = "Using socket without initialization";
				return false;
			}
			this->sock->connectToHost(QHostAddress(params->inet_addr), params->inet_port, QIODevice::ReadWrite);
			if (!this->sock->waitForConnected(5000))
			{
				qDebug("Connection::Connect() - Remote device is not responsed.\n");
				this->err = "Can't connect to the remote host";
				return false;
			}
			if (this->sock->state() != QAbstractSocket::ConnectedState)
			{
				qDebug("Connection::Connect() - Remote device is not responsed.\n");
				this->err = "Can't connect to the remote host";
				return false;
			}
			break;

		case CT_GSM:
			if (!this->gsm) 
			{
				qDebug("Connection::Connect() - Using GSM without initialization!\n");
				this->err = "Using GSM without initialization";
				return false;
			}
			switch (this->gsm->Connect(params->phone))
			{
				case GCR_BUSY:
					qDebug("Connection::Connect() - GSM::Connect return's GCR_BUSY.\n");
					this->err = "Remote modem is BUSY";
					return false;
				
				case GCR_NO_CARRIER:
					qDebug("Connection::Connect() - GSM::Connect return's GCR_NO_CARRIER.\n");
					this->err = "Remote modem has NO CARRIER";
					return false;
					
				case GCR_ERROR:
					qDebug("Connection::Connect() - GSM::Connect return's GCR_ERROR. \nGSM::getError() - %s\n", 
					       this->gsm->GetLastError().toAscii().constData());
					this->err = "Remote modem is busy";
					return false;
					
				default:
					return true;
			}
			break;
			
		default:
			qDebug("Connection::Connect() - Unknown connection type.\n");
			this->err = "Unknown connection type";
			return false;
	}
	return true;
}

// «акрывает соединение
bool Connection::Close()
{
	switch (this->m_type)
	{
		case CT_DIRECT:
			if (!this->com)
			{
				qDebug("Connection::Close() - Using serial port without initialization!\n");
				this->err = "Using serial port without initialization";
				return false;
			}
			if (this->com != CONNECTION_VIRTUAL_SERIAL_PORT) this->com->close();
			break;
			
		case CT_TCPIP:
			if (!this->sock) 
			{
				qDebug("Connection::Close() - Using socket without initialization!\n");
				this->err = "Using socket without initialization";
				return false;
			}
			this->sock->close();
			break;
		
		case CT_GSM:
			if (!this->gsm) 
			{
				qDebug("Connection::Close() - Using GSM without initialization!\n");
				this->err = "Using GSM without initialization";
				return false;
			}
			this->gsm->Disconnect();
			this->gsm->Close();
			break;

		default:
			qDebug("Connection::Close() - Unknown connection type.\n");
			this->err = "Unknown connection type";
			return false;
	}
	return true;
}


QString Connection::GetLastError()
{
	QString ret = this->err;
	return ret;
}

QByteArray Connection::Receive()
{
	QByteArray ba;
	qint64 len;
	char * buf;
	char tmp[2000];
	
	switch (this->m_type)
	{
		case CT_DIRECT:
			if (!this->com)
			{
				qDebug("Connection::Receive() - Using serial port without initialization!\n");
				this->err = "Using serial port without initialization";
				return ba;
			}
			
			if (this->com == CONNECTION_VIRTUAL_SERIAL_PORT)
				return ba;
			while (!(len = this->com->bytesAvailable()));
			qDebug("Connection::Receive() - Received %ld byte(s)\n", (long)len);
			buf = new char[len];
			this->com->read(buf, len);
			ba.append(buf, len);
			qDebug("Receive:\n");
			for (int i = 0; i < ba.size(); i++) sprintf(tmp + i * 3, "%.2X|", (unsigned char)buf[i]);
			qDebug("%s\n", tmp);
			delete buf;
			break;
			
		case CT_TCPIP:
			if (!this->sock) 
			{
				qDebug("Connection::Receive() - Using socket without initialization!\n");
				this->err = "Using socket without initialization";
				return ba;
			}
			if (this->sock->state() != QTcpSocket::ConnectedState)
			{
				qDebug("Connection::Receive() - Socket is not connected!\n");
				this->err = "Socket is not connected";
				return ba;
			}
			if (this->sock->waitForReadyRead(1000))
			{
				ba.append(this->sock->read(this->sock->bytesAvailable()));
				qDebug("Receive:\n");
				for (int i = 0; i < ba.size(); i++) sprintf(tmp + i * 3, "%.2X|", (unsigned char)ba.at(i));
				qDebug("%s\n", tmp);
			}
			break;
		
		case CT_GSM:
			if (!this->gsm) 
			{
				qDebug("Connection::Receive() - Using GSM without initialization!\n");
				this->err = "Using GSM without initialization";
				return ba;
			}
			ba = this->gsm->GetBuffer(this->m_timeout);
			break;
			
		default:
			qDebug("Connection::Receive() - Unknown connection type.\n");
			this->err = "Unknown connection type";
	}
	return ba;
}

int Connection::Send(QByteArray buf)
{
	unsigned char * b;
	char tmp[2000];
	quint64 sent;
	switch (this->m_type)
	{
		case CT_DIRECT:
			if (!this->com)
			{
				qDebug("Connection::Send() - Using serial port without initialization!\n");
				this->err = "Using serial port without initialization";
				return -1;
			}
			if (this->com == CONNECTION_VIRTUAL_SERIAL_PORT)
				return -1;
			qDebug("Connection::Send() - Sending %d byte(s)\n", buf.size());
			b = (unsigned char *)buf.constData();
			
			memset(tmp, 0, buf.size() * 3 + 1);
			qDebug("Send:\n");
			for (int i = 0; i < buf.size(); i++) 
				sprintf(tmp + i * 3, "%.2X|", (unsigned char)b[i]);
			qDebug("%s\n", tmp);
			return this->com->write(buf.constData(), buf.size());
			break;
			
		case CT_TCPIP:
			if (!this->sock) 
			{
				qDebug("Connection::Send() - Using socket without initialization!\n");
				this->err = "Using socket without initialization";
				return -1;
			}
			if (this->sock->state() != QTcpSocket::ConnectedState)
			{
				qDebug("Connection::Send() - Socket is not connected!\n");
				this->err = "Socket is not connected";
				return -1;
			}
			sent = this->sock->write(buf.constData(), buf.size()); 
			if (!this->sock->waitForBytesWritten(3000))
			{
				qDebug("Connection::Send() - Data not written!\n");
				this->err = "Data not written";
				return -1;
			}
			qDebug("Connection::Send() - Bytes sent %d\n", sent);
			return sent;
			break;
		
		case CT_GSM:
			if (!this->gsm) 
			{
				qDebug("Connection::Send() - Using GSM without initialization!\n");
				this->err = "Using GSM without initialization";
				return -1;
			}
			return this->gsm->Send(buf, false);
			break;
			
		default:
			qDebug("Connection::Send() - Unknown connection type.\n");
			this->err = "Unknown connection type";
			qDebug("Connection::Send() - WTF?\n");
			return -1;
			break;
	}
	qDebug("Connection::Send() - WTF?\n");
}

int Connection::getStatus()
{
	return GCS_DATA;
}

bool Connection::isInitialized()
{
	switch (this->m_type)
	{
		case CT_DIRECT:
			return this->com == 0;
			
		case CT_TCPIP:
			return this->sock == 0;
		
		case CT_GSM:
			return this->gsm == 0;
			
		default:
			qDebug("Connection::isConnected() - Unknown connection type.\n");
			this->err = "Unknown connection type";
			return false;
	}
}

bool Connection::isConnected()
{
	switch (this->m_type)
	{
		case CT_DIRECT:
			if (!this->com)
			{
				qDebug("Connection::isConnected() - Using serial port without initialization!\n");
				this->err = "Using serial port without initialization";
				return false;
			}
			return true;
			
		case CT_TCPIP:
			if (!this->sock) 
			{
				qDebug("Connection::isConnected() - Using socket without initialization!\n");
				this->err = "Using socket without initialization";
				return false;
			}
			return this->sock->state() == QTcpSocket::ConnectedState;
		
		case CT_GSM:
			if (!this->gsm) 
			{
				qDebug("Connection::isConnected() - Using GSM without initialization!\n");
				this->err = "Using GSM without initialization";
				return false;
			}
			// GCS_DATA - модем в состо€нии передачи данных
			// GCS_ERROR - ошибка св€зи с локальным модемом
			return (this->gsm->getStatus() == GCS_DATA);
			
		default:
			qDebug("Connection::isConnected() - Unknown connection type.\n");
			this->err = "Unknown connection type";
			return false;
	}
}

bool Connection::setConnectionType(ConnectionType type)
{
	if ((isConnected())&&(m_type != CT_DIRECT))
	{
		qDebug("Connection::setConnectionType() - Connection already used by devices");
		return false;
	}
	this->m_type = type;
	return true;
}

void Connection::setReceiveTimeout(int timeout)
{
	this->m_timeout = timeout;
}

void Connection::setSendTimeout(int timeout)
{
	switch (this->m_type)
	{
		case CT_DIRECT:
			if (!this->com)
			{
				qDebug("Connection::setSendTimeout() - Using serial port without initialization!\n");
				this->err = "Using serial port without initialization";
				return;
			}
			break;
			
		case CT_TCPIP:
			break;		
		
		case CT_GSM:
			if (!this->gsm) 
			{
				qDebug("Connection::setSendTimeout() - Using GSM without initialization!\n");
				this->err = "Using GSM without initialization";
				return;
			}
			this->gsm->setSendTimeout(timeout);
			break;
			
		default:
			qDebug("Connection::setSendTimeout() - Unknown connection type.\n");
			this->err = "Unknown connection type";
			return;
	}
}

void Connection::closeConnection()
{
	Close();
}
