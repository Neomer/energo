#ifndef ACDRV_H
#define ACDRV_H

#include "../recv/connection.h"
#include "../includes/CounterInterface.h"
#include "acdrv_global.h"
#include "../oradrv/OraDrv.h"

#define ACDRV_VERSION		tr("0.1a")

class ACdrv : public QObject, public CounterInterface2
{
	Q_OBJECT
	Q_INTERFACES(CounterInterface2)

	public:
		ACdrv();
		
		bool InitSession();
		bool CloseSession();
		bool getTime(QDateTime * dt);
		bool setTime(int diff);
		bool checkFactoryNum();
	
		QList<ChannelData> getData(QDateTime since, QList<ChannelInfo> channels);
		
		QString getLastError();
		void setConnection(Connection * connection);
		ModuleInfo getModuleInfo();
		void setParams(Counter_Desc  * desc);
		QMap<QString, AddParam> getAdditionalParameters();
		void setAdditionalParameters(QMap<QString, AddParam> params);
	
	private:
		OraSqlDrv * _db;
		Counter_Desc _desc;
		Connection * _conn;
		QMap<QString, AddParam> _params;
};

Q_DECLARE_INTERFACE(ACdrv,
                    "com.trolltech.Plugin.ACdrv/1.0.0");

#endif // ACDRV_H
