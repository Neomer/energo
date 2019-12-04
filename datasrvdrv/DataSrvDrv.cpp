#include "DataSrvDrv.h"
#include <QtPlugin>


DataSrvDrv::DataSrvDrv()
{
}

bool DataSrvDrv::InitSession()
{
	TcpPackage * pkg = new TcpPackage();
	pkg->setCode(TCP_PKGCODE_AUTH);
	pkg->addData(_desc.login);
	pkg->addData(_desc.password);
	QByteArray ba = pkg->compile();
	if (_conn->Send(ba) != ba.size())
	{
		qDebug("DataSrvDrv::InitSession() - Not all data was sent!");
		return false;
	}
	
	pkg = getFromServer();
	
	if (!pkg->isValid())
		return false;
	
	return ((pkg->getCode() == TCP_PKGCODE_AUTH)&&(pkg->getByte() == TCP_PKGCODE_AUTH_SUCCESS));
}

bool DataSrvDrv::CloseSession()
{
	return true;
}

bool DataSrvDrv::getTime(QDateTime * dt)
{
	TcpPackage * pkg = new TcpPackage();
	pkg->setCode(TCP_PKGCODE_TIME);
	QByteArray ba = pkg->compile();
	if (_conn->Send(ba) != ba.size())
	{
		qDebug("DataSrvDrv::InitSession() - Not all data was sent!");
		return false;
	}
	
	pkg = getFromServer();
	
	if (!pkg->isValid())
		return false;
	
	if (pkg->getCode() != TCP_PKGCODE_TIME)
		return false;
	
	QDateTime d = QDateTime::fromTime_t((uint)pkg->getLong());
	dt->setDate(d.date());
	dt->setTime(d.time());
	return true;
}

bool DataSrvDrv::checkFactoryNum()
{
	TcpPackage * pkg = new TcpPackage();
	pkg->setCode(TCP_PKGCODE_CNUM);
	pkg->addData((long long)_desc.number);
	QByteArray ba = pkg->compile();
	if (_conn->Send(ba) != ba.size())
	{
		qDebug("DataSrvDrv::InitSession() - Not all data was sent!");
		return false;
	}
	
	pkg = getFromServer();
	
	if (!pkg->isValid())
		return false;
	
	return ((pkg->getCode() == TCP_PKGCODE_CNUM)&&(pkg->getByte() == TCP_PKGCODE_AUTH_SUCCESS));
}

QList<ChannelData> DataSrvDrv::getData(QDateTime since, QList<ChannelInfo> channels)
{
	QList<ChannelData> ret;
	
	for (int ch = 0; ch < channels.count(); ch++)
	{
		ChannelData cd;
		cd.info = channels.at(ch);
		ret.append(cd);
	}
	
	for (int ch = 0; ch < channels.count(); ch++)
	{
		TcpPackage * pkg = new TcpPackage();
		bool ok;
		pkg->setCode(TCP_PKGCODE_DATA);
		pkg->addData(channels.at(ch).number);
		pkg->addData((long)since.toTime_t());
		QByteArray ba = pkg->compile();
		if (_conn->Send(ba) != ba.size())
		{
			qDebug("DataSrvDrv::getData() - Not all data was sent!");
			return ret;
		}
		
		pkg = getFromServer();
		
		if (!pkg->isValid())
			return ret;
		
		switch (pkg->getCode())
		{
			case TCP_PKGCODE_AUTH:
				qDebug("DataSrvDrv::getData() - Authorization is missed!");
				return ret;
				break;
			
			case TCP_PKGCODE_CNUM:
				qDebug("DataSrvDrv::getData() - Channel access denied!");
				continue;
				break;
		}
		
		while (!pkg->isEmpty())
		{
			QDateTime dt = QDateTime::fromTime_t((uint)pkg->getLong());
			int itv = pkg->getInt(),
				itvlen = pkg->getInt();
			dt.addSecs(itv * itvlen * 60);
			ChannelValue cv;
			cv.hdr.interval = itvlen;
			cv.hdr.dt = dt;
			cv.hdr.season = CounterDataHeader::Winter;
			cv.hdr.status = 0;
			cv.value = pkg->getDouble();
			cv.c_value = pkg->getDouble();
			printf("Data to %s channel %d\n",
				   cv.hdr.dt.toString("yyyy-MM-dd hh:mm").toAscii().constData(),
				   channels.at(ch).number);

			qDebug("DataSrvDrv::getData() - Data to %s Channel %d Value %f\n",
				   cv.hdr.dt.toString("yyyy-MM-dd hh:mm").toAscii().constData(),
				   channels.at(ch).number,
				   cv.value);
			ret[ch].values.append(cv);
			
		}
	}
	
	return ret;
}

QString DataSrvDrv::getLastError()
{
	return tr("");
}

void DataSrvDrv::setConnection(Connection * connection)
{
	_conn = connection;
}

ModuleInfo DataSrvDrv::getModuleInfo()
{
	ModuleInfo mi;
	
	mi.version = tr("0.1a");
	mi.description = tr("1234");
	
	return mi;
}

void DataSrvDrv::setParams(Counter_Desc * desc)
{
	_desc = *desc;
}

TcpPackage * DataSrvDrv::getFromServer()
{
	TcpPackage * pkg = new TcpPackage();
	int retry = _desc.recall + 1;
	while ((!pkg->isValid())&&(retry--))
	{
		pkg->append(_conn->Receive());
	}
	return pkg;
}

Q_EXPORT_PLUGIN(DataSrvDrv)
