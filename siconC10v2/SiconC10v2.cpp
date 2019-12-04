#include "SiconC10v2.h"
#include <QtPlugin>

#define SICON10V2_PKGSTART		0x02
#define SICON10V2_PKGEND		0x03
#define SICON10V2_PKGNORM		0x06
#define SICON10V2_HASHSIZE		2

SiconC10v2::SiconC10v2()
{
}

SiconC10v2::~SiconC10v2()
{
	
}

bool SiconC10v2::InitSession()
{
	SiconPackage * pkg = new SiconPackage();
	
	pkg->setControllerNumber(m_desc.address);
	pkg->setRequestNumber(1);
	pkg->setPackageNumber(1, true);
	pkg->setUser(m_desc.login.toInt());
	pkg->setPassword(m_desc.password.toInt());
	
	pkg->setFunction(SICON10v2_FUNCTION_DIRECTREAD);
	
	QByteArray ba = pkg->getPackage();
	foreach (unsigned char c, ba)
	{
		printf("%.2X|", c);
	}
	printf("\n");	
}

QByteArray SiconC10v2::createRequest(char *data, int length)
{
	return createRequest(QByteArray(data, length));
}

QByteArray SiconC10v2::createRequest(QByteArray data)
{
}

bool SiconC10v2::CloseSession()
{
	return true;
}

bool SiconC10v2::getTime(QDateTime *dt)
{
	return true;
}

bool SiconC10v2::setTime(int diff)
{
}

bool SiconC10v2::checkFactoryNum()
{
	return true;
}

QList<ChannelData> SiconC10v2::getData(QDateTime since, QList<ChannelInfo> channels)
{
}

unsigned long SiconC10v2::getFactoryNum()
{
	return 0;
}

bool SiconC10v2::getTRatio(TransformationRatio *tr)
{
	tr->KTn = 1;
	tr->KTt = 1;
	return true;
}

QString SiconC10v2::getLastError()
{
	return _err;
}

void SiconC10v2::setAddress(char address)
{
	_addr = address;
}

QMap<QString, AddParam> SiconC10v2::getAdditionalParameters()
{
	return _params;
}

void SiconC10v2::setAdditionalParameters(QMap<QString, AddParam> params)
{
	_params = params;
}

void SiconC10v2::setConnection(Connection *connection)
{
	_conn = connection;
}

ModuleInfo SiconC10v2::getModuleInfo()
{
	ModuleInfo mi;
	mi.description = "Плагин для опроса УСПД Сикон вер. С10, С1 и С70 версий 2";
	mi.version = SICON10v2_VERSION;
	return mi;
}

void SiconC10v2::setParams(Counter_Desc *desc)
{
	this->m_desc = *desc;
}


Q_EXPORT_PLUGIN(SiconC10v2);
