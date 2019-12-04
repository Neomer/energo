#ifndef SICONC10V2_H
#define SICONC10V2_H

#include <QObject>
#include "siconC10v2_global.h"
#include "../includes/global.h"
#include "../includes/CounterInterface.h"
#include "../recv/connection.h"
#include "SiconPackage.h"

#define SICON10v2_VERSION	"0.1b"

class SiconC10v2 : public QObject, public CounterInterface2
{
	Q_OBJECT
	Q_INTERFACES(CounterInterface2)
	
	public:
		SiconC10v2();
		~SiconC10v2();
		
		bool InitSession();
		bool CloseSession();
		bool getTime(QDateTime * dt);
		bool setTime(int diff);
		bool checkFactoryNum();
	
		QList<ChannelData> getData(QDateTime since, QList<ChannelInfo> channels);
		
		QString getLastError();
		void setConnection(Connection * connection);
		ModuleInfo getModuleInfo();
		void setParams(Counter_Desc * desc);
		
		unsigned long getFactoryNum();
		bool getTRatio(TransformationRatio * tr);
		
		void setAddress(char address);
		QMap<QString, AddParam> getAdditionalParameters();
		void setAdditionalParameters(QMap<QString, AddParam> params);
		
	private:
		QByteArray createRequest(QByteArray data);
		QByteArray createRequest(char * data, int length);

		Counter_Desc m_desc;
		Connection * _conn;
		QString _err;
		char _addr;
		QMap<QString, AddParam> _params;
};

Q_DECLARE_INTERFACE(SiconC10v2,
                    "com.trolltech.Plugin.SiconC10v2/1.0.0");


#endif // SICONC10V2_H
