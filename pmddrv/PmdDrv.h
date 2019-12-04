#ifndef PMDDRV_H
#define PMDDRV_H

#include "pmddrv_global.h"

#include "../recv/connection.h"
#include "../includes/CounterInterface.h"

#define PMDDRV_VERSION		tr("0.1a")

class PmdDrv  : public QObject, public CounterInterface2
{
	Q_OBJECT
	Q_INTERFACES(CounterInterface2)

public:
    PmdDrv();

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
	OraSqlDrv * _db;
	Counter_Desc _desc;
	Connection * _conn;
};

Q_DECLARE_INTERFACE(ACdrv,
                    "com.trolltech.Plugin.PMDdrv/1.0.0");


#endif // PMDDRV_H
