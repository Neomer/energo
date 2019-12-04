#ifndef DATASRVDRV_H
#define DATASRVDRV_H

#include "../recv/connection.h"
#include "../includes/CounterInterface.h"

#define DSDRV_VERSION		tr("0.1a")

#include "TcpPackage.h"

class DataSrvDrv : public QObject, public CounterInterface2
{
	Q_OBJECT
	Q_INTERFACES(CounterInterface2)
	
	public:
		DataSrvDrv();
		
		bool InitSession();
		bool CloseSession();
		bool getTime(QDateTime * dt);
		bool checkFactoryNum();
	
		QList<ChannelData> getData(QDateTime since, QList<ChannelInfo> channels);
		
		QString getLastError();
		void setConnection(Connection * connection);
		ModuleInfo getModuleInfo();
		void setParams(Counter_Desc  * desc);
	
	private:
		TcpPackage * getFromServer();
		Counter_Desc _desc;
		Connection * _conn;
};


Q_DECLARE_INTERFACE(DataSrvDrv,
                    "com.trolltech.Plugin.DataSrvDrv/1.0.0");


#endif // DATASRVDRV_H
