#ifndef ENERGOMERA_H
#define ENERGOMERA_H

#include "energomera_global.h"
#include "../includes/global.h"
#include "../includes/CounterInterface.h"
#include "../recv/connection.h"

#include <stdlib.h>

#define ENERGOMERA_VERSION	"0.1b"

typedef unsigned char byte;

class Energomera : public QObject, public CounterInterface2
{
	Q_OBJECT
	Q_INTERFACES(CounterInterface2)

	public:
		Energomera();

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

#endif // ENERGOMERA_H
