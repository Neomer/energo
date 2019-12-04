#include "SiconPackage.h"
#include <stdlib.h>

#define SICON10V2_PKGSTART		0x02
#define SICON10V2_PKGEND		0x03
#define SICON10V2_PKGNORM		0x06
#define SICON10V2_HASHSIZE		2

#define SICON10V2_MAXPKGSIZE	38
#define SICON10V2_MINPKGSIZE	8

SiconPackage::SiconPackage(SiconPackageType type)
{
	_type = type;
	_path = 0x0AAA;
	_valid = true;
	_rnum = 0x81;
	_cnum = 0;
	_pnum = 1;
	_pmod = 0x80;
	_func_flags = _func = 0;
}

SiconPackage::SiconPackage(QByteArray package)
{
	// Проверяем размер пакета
	if ((package.length() > SICON10V2_MAXPKGSIZE))
	{
		qDebug("SiconPackage::SiconPackage() - Package too long! Data was truncated");
		package = package.left(SICON10V2_MAXPKGSIZE);
	}
	else if (package.length() < SICON10V2_MINPKGSIZE)
	{
		qDebug("SiconPackage::SiconPackage() - Package too short!");
		_valid = false;
		return;
	}
	
	// Проверяем границы пакета
	if ((package.at(0) != SICON10V2_PKGSTART)||(package.at(package.length() - 1) != SICON10V2_PKGEND))
	{
		qDebug("SiconPackage::SiconPackage() - Invalid package boundaries");
		_valid = false;
		return;
	}
	
	// Проверяем путь
	
	// Проверяем CRC16
	if (crc16(QByteArray(package.constData() + 3, package.size() - 6)) != QByteArray(package.constData() + package.size() - 3, 2))
	{
		qDebug("SiconPackage::SiconPackage() - CRC16 check failed!");
		_valid = false;
		return;
	}
	
	// Распаковывем данные
	memcpy(&_rnum, package.constData() + 3, 1);
	memcpy(&_pnum, package.constData() + 4, 1);
	appendData(unPack(package, 5, package.size() - 8));
}

void SiconPackage::setPath(short path)
{
	_path = path;
}

void SiconPackage::setPath(SiconPackage other)
{
	_path = swapBits(other.path(), 4);
}

short SiconPackage::path()
{
	return _path;
}

bool SiconPackage::checkPath(SiconPackage other)
{
	return _path == swapBits(other.path(), 4);
}

void SiconPackage::setPackageNumber(byte number, bool isFinalize)
{
	if (isFinalize)
		_pmod = 0x80;
	else
		_pmod = 0x06;
	_pnum = number;
}

void SiconPackage::setPackageNumber(SiconPackage other, bool isFinalize)
{
	if (isFinalize)
		_pmod = 0x80;
	else
		_pmod = 0x06;
	_pnum = other.packageNumber() + 1;
}

byte SiconPackage::packageNumber()
{
	return _pnum;
}

void SiconPackage::setRequestNumber(byte number)
{
	_rnum = number;
}

void SiconPackage::setRequestNumber(SiconPackage other)
{
	if (other.requestNumber() == 0xFF)
		_rnum = 0x81;
	else
		_rnum = other.requestNumber() + 1;
}

byte SiconPackage::requestNumber()
{
	return _rnum;
}

void SiconPackage::setControllerNumber(byte number)
{
	_cnum = number;
}

byte SiconPackage::controllerNumber()
{
	return _cnum;
}

void SiconPackage::setUser(byte id)
{
	_uid = id;
}

byte SiconPackage::user()
{
	return _uid;
}

bool SiconPackage::isValid()
{
	return _valid;
}

void SiconPackage::setPassword(unsigned short password)
{
	_pass = password;
}

unsigned short SiconPackage::password()
{
	return _pass;
}


void SiconPackage::setFunction(byte number, unsigned short flags)
{
	_func = number;
	_func_flags = flags;
}

byte SiconPackage::function()
{
	return _func;
}

void SiconPackage::appendData(char *data, int length)
{
	_buff.push_back(QByteArray(data, length));
}

void SiconPackage::appendData(QByteArray data)
{
	_buff.push_back(data);
}

QByteArray SiconPackage::crc16(QByteArray data)
{
	QByteArray ret;
	ret.resize(SICON10V2_HASHSIZE);
	
	short b, crc = 0;
	
	for (int i = 0; i < data.size(); i++)
	{
		b = data.at(i);
		crc = crc ^ (b << 8);
		for (int j = 1; j < 9; j++)
		{
			if (crc & 0x8000)
			{
				crc = crc << 1;
				crc = crc ^ 0x1021;
			}
			else
				crc = crc << 1;
		}
	}
	crc |= 0x8080;
	
	memcpy((char *)ret.constData(), &crc, SICON10V2_HASHSIZE);
	return ret;
}

QByteArray SiconPackage::pack(QByteArray data)
{
	QByteArray ret;
	
	//Упаковываем данные	
	byte c = 0;
	int idx = 0;
	for (int i = 1; idx < data.size(); i++)
	{
		//qDebug("i=%d idx=%d", i, idx);
		if (i % 8 != 0)
		{
			//qDebug("Sdvig: %d", i % 7);
			c |= (0x80 & data.at(idx)) >> (i % 8);
			ret.push_back((char)0x80 | data.at(idx));
			idx++;
		}
		else
		{
			ret.push_back((char)0x80 | c);
			c = 0;
		}
		//qDebug("C=%.2X ", c);
	}
	if (data.size() % 7 != 0) ret.push_back((char)0x80 | c);
	return ret;
}

QByteArray SiconPackage::unPack(QByteArray data, int index, int length)
{
	QByteArray ret, ba(data.constData() + index, length);
	
	int cb = qMin(7, ba.size() - 1);
	unsigned char b, num = cb;
	qDebug("SiconPackage::unPack() - Control byte: %x; Packed bytes: %d", (unsigned char)ba.at(cb), num);
	
	for (int i = 0; i < ba.length(); i++)
	{
		if (i != cb)
		{
			b = (ba.at(i) & 0x7F) | ((ba.at(cb) & (0x01 << (cb - i + 6 - num))) << (num - cb + i + 1));
			qDebug("SiconPackage::unPack() - Source byte: %x => %x", (unsigned char)ba.at(i), b);
			ret.append(b);
		}
		else
		{
			num = qMin(cb + 8, ba.size() - 1) - cb - 1;
			cb = qMin(cb + 8, ba.size() - 1);
			qDebug("SiconPackage::unPack() - Control byte: %x; Packed bytes: %d", (unsigned char)ba.at(cb), num);
		}
	}
	return ret;
}

QByteArray SiconPackage::getPackage()
{
	char b[] = {SICON10V2_PKGSTART, 0, 0, _rnum, _pnum + _pmod, _cnum};
	writePackage(b + 1, _path);
	
	// Формируем корректный пакет
	QByteArray ret(b, 6);
	ret.append(pack(_buff));
	ret.append(crc16(QByteArray(ret.constData() + 3, ret.size() - 3)));
	ret.append(SICON10V2_PKGEND);
	
	return ret;
}

