#ifndef SICONPACKAGE_H
#define SICONPACKAGE_H

#include <QByteArray>
#include "../includes/modbus.h"

#define SICON10v2_FUNCTION_DIRECTREAD					0x00
#define SICON10v2_FLAG_DIRECTREAD_VECTOR				0x01
#define SICON10v2_FLAG_DIRECTREAD_WRITE					0x02
#define SICON10v2_FLAG_DIRECTREAD_VECTORFROMCURRENT		0x04

typedef unsigned char byte;

enum SiconPackageType
{
	Normal,
	Positive
};

class SiconPackage
{
	public:
		SiconPackage(SiconPackageType type = Normal);
		SiconPackage(QByteArray package);
		
		void appendData(QByteArray data);
		void appendData(char * data, int length);
		QByteArray getPackage();
		
		void setPath(short path);
		void setPath(SiconPackage other);
		short path();
		bool checkPath(SiconPackage other);
		
		void setPackageNumber(byte number, bool isFinalize = false);
		void setPackageNumber(SiconPackage other, bool isFinalize = false);		
		byte packageNumber();
		
		void setRequestNumber(byte number);
		void setRequestNumber(SiconPackage other);		
		byte requestNumber();
		
		void setControllerNumber(byte number);
		byte controllerNumber();
		
		void setUser(byte id);
		byte user();
		
		void setPassword(unsigned short password);
		unsigned short password();
		
		void setFunction(byte number, unsigned short flags = 0);
		byte function();
		
		bool isValid();
		
	private:
		QByteArray pack(QByteArray data);
		QByteArray unPack(QByteArray data, int index, int length);
		QByteArray crc16(QByteArray data);
		
		QByteArray _buff;
		SiconPackageType _type;
		short _path;
		byte _pnum, _rnum, _cnum, _pmod, _uid, _func;
		unsigned short _pass, _func_flags;
		bool _valid;
};

#endif // SICONPACKAGE_H
