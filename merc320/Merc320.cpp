#include "Merc320.h"
#include <QtPlugin>


Merc320::Merc320()
{
	this->_addr = 0;
	this->_err = "";
	this->_conn = 0;
}

bool Merc320::InitSession()
{
	if (!this->_conn) 
	{
		qDebug("Merc320::InitSession() - Connection don't set!\n");
		this->_err = "Connection don't set";
		return false;
	}
	if (this->_conn->getStatus() != GCS_DATA) 
	{
		qDebug("Merc320::InitSession() - Connection must be in GCS_DATA state!\n");
		this->_err = "Connection must be in GCS_DATA state";
		return false;
	}
	char b[] = {this->_desc.number, 0x00};
	QByteArray ba(b, 2), out;
	ba.append((const char *)this->getHash(b, 2), 2);
	this->_conn->Send(ba);
	if (!this->getFromCounter(&out, 2))
	{
		qDebug("Merc320::InitSession() - CRC16 is not correct\n");
		return false;
	}
	if (out.at(1) != 0)
	{
		return false;
	}
	
	char b1[] = {this->_desc.number, 0x01, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31};
	ba.clear();
	memcpy(b1 + 2, _desc.password.toAscii().constData(), _desc.password.length());
	ba.append(b1, 8).append((const char *)this->getHash(b1, 8), 2);
	this->_conn->Send(ba);
	if (!this->getFromCounter(&out, 2))
	{
		qDebug("Merc320::InitSession() - CRC16 is not correct\n");
		return false;
	}
	if (out.at(1) != 0)
	{
		qDebug("Merc320::InitSession() - Counter answer with _error code!\n");
		_err = "Counter answer with _error code";
		return false;
	}
	return true;
}

bool Merc320::CloseSession()
{
	if (!this->_conn) 
	{
		qDebug("Set4tmPlugin::CloseSession() - Connection don't set!\n");
		this->_err = "Connection don't set";
		return false;
	}
	if (this->_conn->getStatus() != GCS_DATA) 
	{
		qDebug("Set4tmPlugin::CloseSession() - Connection must be in GCS_DATA state!\n");
		this->_err = "Connection must be in GCS_DATA state";
		return false;
	}
	char b[] = {this->_desc.address, 0x02};
	QByteArray ba(b, 2), out;
	ba.append((const char *)this->getHash(b, 2), 2);
	this->_conn->Send(ba);
	if (!this->getFromCounter(&out, 2))
	{
		qDebug("Set4tmPlugin::CloseSession() - CRC16 is not correct\n");
		return false;
	}
	if (out.at(1) != 0)
	{
		qDebug("Set4tmPlugin::CloseSession() - Counter answer with error code!\n");
		_err = "Counter answer with error code";
		return false;
	}
	return true;
}

void Merc320::setConnection(Connection *connection)
{
	_conn = connection;
}

ModuleInfo Merc320::getModuleInfo()
{
	ModuleInfo mi;
	
	mi.description = "Плагин для опроса счетчиков типа Меркурий 320";
	mi.version = MERC320PLUGIN_VERSION;
	return mi;
}

void Merc320::setParams(Counter_Desc *desc)
{
	_desc = *desc;
}

QMap<QString, AddParam> Merc320::getAdditionalParameters()
{
	QMap<QString, AddParam> ret;
	
	return ret;
}

void Merc320::setAdditionalParameters(QMap<QString, AddParam> params)
{
	_params = params;
}

unsigned char *Merc320::getHash(char *data, int length)
{
	static const WORD wCRCTable[] = {
	0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
	0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
	0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
	0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
	0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
	0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
	0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
	0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
	0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
	0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
	0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
	0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
	0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
	0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
	0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
	0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
	0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
	0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
	0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
	0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
	0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
	0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
	0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
	0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
	0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
	0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
	0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
	0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
	0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
	0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
	0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
	0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };
	
	BYTE nTemp;
	WORD wCRCWord = 0xFFFF;
	int i = 0;
	
	while ((length--) > 0)
	{
		nTemp = data[i++] ^ wCRCWord;
		wCRCWord >>= 8;
		wCRCWord ^= wCRCTable[nTemp];
	}
	return (BYTE *)&wCRCWord;
}

unsigned char *Merc320::getCS(char *data, int length)
{
}

unsigned short Merc320::updCRC(unsigned char c, unsigned short *oldCRC)
{
	unsigned char srCRCHi[256] = {
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40};
	
	unsigned char srCRCLo[256] = {
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
	0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
	0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
	0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
	0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
	0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
	0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
	0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
	0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40};

	unsigned char *arrCRC;
	arrCRC = (unsigned char *)oldCRC;
	
	unsigned char i = arrCRC[1] ^ c;
	arrCRC[1] = arrCRC[0] ^ srCRCHi[i];
	arrCRC[0] = srCRCLo[i];
	return *oldCRC;
}

bool Merc320::getFromCounter(QByteArray *buffer, quint32 maxsize)
{
	QByteArray ba;
	char crc[2];
	QByteArray tmp;
	maxsize += 3; // Адрес и CRC
	do
	{
		tmp = this->_conn->Receive();
		if (tmp.size() > 0)
		{
			if ((quint32)ba.size() > maxsize) ba.clear();
			ba.append(tmp);
			memcpy(crc, ba.constData() + (ba.length() - 2), 2);
		}
	}
	while ((memcmp(crc, this->getHash((char *)ba.constData(), ba.length() - 2), 2) != 0)&&(tmp.size() > 0));
	buffer->clear();
	buffer->append(ba);
	return memcmp(crc, this->getHash((char *)ba.constData(), ba.length() - 2), 2) == 0;
}

QByteArray Merc320::createRequest(char *data, long length)
{
	QByteArray ba(data, length);
	ba.append((const char *)this->getHash(data, length), 2);
	return ba;
}

QByteArray Merc320::createRequest(byte *data, long length)
{
	QByteArray ba((char *)data, length);
	ba.append((const char *)this->getHash((char *)data, length), 2);
	return ba;
}

QDateTime Merc320::fromCounterDT(byte *buffer, QString format)
{
	QDateTime dt = QDateTime::fromTime_t(0);
	byte tmp;
	QChar c;
	int h = 0, m = 0, s = 0, d = 1, mn = 1, y = 1999;
	format = format.toLower();
	for (int i = 0; i < format.length(); i++)
	{
		bcd2dec(buffer + i, 2, &tmp);
		c = format.at(i).toAscii();
		if (c == QChar('y')) // year
			y = 2000 + tmp;
		else if (c == 'm') // month
			mn = tmp;
		else if (c == 'd') // day
			d = tmp;
		else if (c == 'h') //hour
			h = tmp;
		else if (c == 'i') // minute
			m = tmp;
		else if (c == 's') // second
			s = tmp;
		else
			continue;
	}
	dt.setDate(QDate(y, mn, d));
	dt.setTime(QTime(h, m, s));
	return dt;
}

double Merc320::fromCounterData(quint32 value, CounterDataHeader *hdr, byte A, TransformationRatio *tr)
{
}

bool Merc320::getTime(QDateTime *dt)
{
	if (!dt) dt = new QDateTime(QDateTime::fromTime_t(0));

	if (!this->_conn) 
	{
		qDebug("Merc320::getTime() - Connection don't set!\n");
		this->_err = "Connection don't set";
		dt = new QDateTime(QDateTime::fromTime_t(0));
		return false;
	}
	if (this->_conn->getStatus() != GCS_DATA) 
	{
		qDebug("Merc320::getTime() - Connection must be in GCS_DATA state!\n");
		this->_err = "Connection must be in GCS_DATA state";
		dt = new QDateTime(QDateTime::fromTime_t(0));
		return false;
	}
	char b[] = {this->_desc.address, 0x04, 0x00};
	QByteArray ba = createRequest(b, 3), out;
	this->_conn->Send(ba);
	if (!this->getFromCounter(&out, 8))
	{
		qDebug("Merc320::getTime() - CRC16 is not correct\n");
		dt = new QDateTime(QDateTime::fromTime_t(0));
		return false;
	}
	byte * b1 = (byte *) out.constData();
	dt->setTime_t(0);
	dt->setMSecsSinceEpoch(dt->msecsTo(this->fromCounterDT(b1 + 1, "sih dmy")));
	return true;	
}

bool Merc320::checkFactoryNum()
{
	if (!this->_conn) 
	{
		qDebug("Merc320::checkFactoryNum() - Connection don't set!\n");
		this->_err = "Connection don't set";
		return 0;
	}
	if (this->_conn->getStatus() != GCS_DATA) 
	{
		qDebug("Merc320::checkFactoryNum() - Connection must be in GCS_DATA state!\n");
		this->_err = "Connection must be in GCS_DATA state";
		return 0;
	}
	char b[] = {this->_desc.address, 0x08, 0x00}, * ret;
	QByteArray out;
	this->_conn->Send(createRequest(b, 3));
	if (!this->getFromCounter(&out, 7))
	{
		qDebug("Merc320::checkFactoryNum() - CRC16 is not correct\n");
		return 0;
	}
	ret = (char *)out.constData();
	unsigned long v;
	memcpy(&v, ret + 1, 4);
	return swapBytes(v) == _desc.number;
}

QList<ChannelData> Merc320::getData(QDateTime since, QList<ChannelInfo> channels)
{
}

QString Merc320::getLastError()
{
	return _err;
}

Q_EXPORT_PLUGIN(Merc320);
