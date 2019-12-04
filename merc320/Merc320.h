#ifndef MERC320_H
#define MERC320_H

#include "merc320_global.h"
#include <QObject>
#include "../includes/global.h"
#include "../includes/CounterInterface.h"
#include "../recv/connection.h"
#include "../includes/modbus.h"

#define MERC320PLUGIN_VERSION	"0.1b"

class Merc320 : public QObject, public CounterInterface2
{
	Q_OBJECT
	Q_INTERFACES(CounterInterface2)

	public:
		Merc320();
		bool InitSession();
		bool CloseSession();
		bool getTime(QDateTime * dt);
		bool checkFactoryNum();
	
		QList<ChannelData> getData(QDateTime since, QList<ChannelInfo> channels);
		
		QString getLastError();
		void setConnection(Connection * connection);
		ModuleInfo getModuleInfo();
		void setParams(Counter_Desc * desc);
		QMap<QString, AddParam> getAdditionalParameters();
		void setAdditionalParameters(QMap<QString, AddParam> params);
		
	private:
		// Подсчет Modbus CRC16
	    unsigned char * getHash(char * data, int length);
		// Подсчет КС
		unsigned char * getCS(char * data, int length);
		unsigned short updCRC(unsigned char c, unsigned short * crc);
		bool getFromCounter(QByteArray * buffer, quint32 maxsize);
		QByteArray createRequest(char * data, long length);
		QByteArray createRequest(byte * data, long length);
		QDateTime fromCounterDT(byte * buffer, QString format);
		double fromCounterData(quint32 value, CounterDataHeader *hdr, byte A, TransformationRatio *tr);
	
		Counter_Desc _desc;
		char _addr;
		QString _err;
		Connection * _conn;
		QMap<QString, AddParam> _params;
};

Q_DECLARE_INTERFACE(Merc320,
                    "com.trolltech.Plugin.Merc320/1.0.0");


#endif // MERC320_H
