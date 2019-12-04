#ifndef TCPPACKAGE_H
#define TCPPACKAGE_H

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned char byte;

#define TCP_PKG_HASHSIZE	2
#define TCP_PKGCODE_AUTH	0
#define TCP_PKGCODE_AUTH_FAIL		0
#define TCP_PKGCODE_AUTH_SUCCESS	1

#define TCP_PKGCODE_CNUM	1
#define TCP_PKGCODE_TIME	2
#define TCP_PKGCODE_DATA	3

#include <QByteArray>
#include <QObject>

class TcpPackage
{
public:
	TcpPackage();
	
	void append(QByteArray data);
	bool isValid();
	byte getCode();
	void setCode(int value);
	
	void clear();
	
	QString getString();
	char getChar(bool * ok = 0);
	byte getByte(bool *ok = 0);
	int getInt(bool * ok = 0);
	long getLong(bool * ok = 0);
	long long getLongLong(bool * ok = 0);
	double getDouble(bool * ok = 0);
	
	void addData(byte value);
	void addData(QString value);
	void addData(int value);
	void addData(long value);
	void addData(long long value);
	void addData(double value);
	
	QByteArray compile();
	
private:
	QByteArray _buf;
	byte _code;
	int _ptr;
};


#endif // TCPPACKAGE_H
