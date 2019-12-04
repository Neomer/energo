#include <QtPlugin>

#include "Energomera.h"


#define BUFFER_SIZE		1024


Energomera::Energomera()
{
	this->_conn = 0;
}

bool Energomera::InitSession()
{
	/*
Send:(<01>B0<03>u)
Send:(/?76870094!<0D><0A>)
	*/
	
	if (!this->_conn) 
	{
		qDebug("Energomera::InitSession() - Connection don't set!\n");
		this->_err = "Connection don't set";
		return false;
	}
	if (this->_conn->getStatus() != GCS_DATA) 
	{
		qDebug("Energomera::InitSession() - Connection must be in GCS_DATA state!\n");
		this->_err = "Connection must be in GCS_DATA state";
		return false;
	}
	byte buf[BUFFER_SIZE];
	memset(buf, 0, BUFFER_SIZE);
/*
	memcpy(buf, "\x01\x00\x00\x03\x00", 15);
	buf[1] = 'B';
	buf[2] = '0';
	buf[4] = 'u';
	this->_conn->Send((const char *)buf);
*/
	memset(buf, 0, BUFFER_SIZE);
	memcpy(buf, "/?148!\x0D\x0A", 10);
	this->_conn->Send((const char *)buf);
	QByteArray r = this->_conn->Receive();
	
    qDebug(QString("Energomera::InitSession() - %1\n").arg(QString(r)).toAscii().constData());
    
	return false;
}

bool Energomera::CloseSession()
{
	return true;
}

bool Energomera::getTime(QDateTime *dt)
{
	*dt = QDateTime::currentDateTime();
	return true;
}

bool Energomera::setTime(int diff)
{
	return true;
}

bool Energomera::checkFactoryNum()
{
	return true;
}

QList<ChannelData> Energomera::getData(QDateTime since, QList<ChannelInfo> channels)
{
	QList<ChannelData> ret;
	
	return ret;
}


ModuleInfo Energomera::getModuleInfo()
{
	ModuleInfo mi;
	mi.description = "Плагин для опроса счетчиков ЦЭ6850М";
	mi.version = ENERGOMERA_VERSION;
	return mi;
}

void Energomera::setParams(Counter_Desc *desc)
{
	m_desc = *desc; 
}


void Energomera::setAdditionalParameters(QMap<QString, AddParam> params)
{
	_params = params;
}

QByteArray Energomera::createRequest(QByteArray data)
{
}

QByteArray Energomera::createRequest(char *data, int length)
{
}


QMap<QString, AddParam> Energomera::getAdditionalParameters()
{
	return _params;
}


void Energomera::setConnection(Connection *connection)
{
	_conn = connection;
}


QString Energomera::getLastError()
{
	return this->_err;
}

Q_EXPORT_PLUGIN(Energomera);
