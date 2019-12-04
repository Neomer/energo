#ifndef COUNTERINTERFACE_H
#define COUNTERINTERFACE_H

#include <QByteArray>
#include <QObject>
#include <QString>
#include <QDateTime>
#include <QList>
#include <QMap>

#include "../recv/connection.h"
#include "../includes/global.h"

struct ModuleInfo
{
	QString version;
	QString description;
};

struct CounterDataHeader
{
	QDateTime dt;
	byte interval;
	byte status;
	enum Season
	{
		Winter = 0,
		Summer = 1
	} season;
};

struct CounterData
{
	CounterDataHeader hdr;

	double P_Receive;
	double P_Send;
	double Q_Receive;
	double Q_Send;
};

enum ChannelDataType
{
	CDT_Electricity = 1,
	CDT_PhaseAmp = 2,
	CDT_PhaseVolt = 3,
	CDT_Frequency = 4,
	CDT_CosineFi = 5
};

struct ChannelInfo
{
	int ID;
	int number;
	ChannelDataType type;
	QDateTime last_date;
	QString name;
};

struct ChannelValue
{
	CounterDataHeader hdr;
	double value;
	double c_value;
};

struct ChannelData
{
	ChannelInfo info;
	QList<ChannelValue> values;
};

struct AddParam
{
	QString regExp;
	QString description;
	QString value;
};

class CounterInterface
{
public:
		virtual bool InitSession(QString password) = 0;
		virtual bool InitSession(char address, QString password) = 0;
		virtual bool CloseSession() = 0;
		virtual bool getTime(QDateTime * dt) = 0;
		virtual QList<CounterData> getData(QDateTime since, QList<ChannelInfo> channels) = 0;
		virtual unsigned long getFactoryNum() = 0;
		virtual bool getTRatio(TransformationRatio * tr) = 0;
		
		virtual QString getLastError() = 0;
		virtual void setAddress(char address) = 0;
		virtual void setConnection(Connection * connection) = 0;
		virtual ModuleInfo * getModuleInfo() = 0;
		
		virtual ~CounterInterface() {}
};

class CounterInterface2
{
	public:
		virtual bool InitSession() = 0;
		virtual bool CloseSession() = 0;
		virtual bool getTime(QDateTime * dt) = 0;
		virtual bool setTime(int diff) = 0;
		virtual bool checkFactoryNum() = 0;
	
		virtual QList<ChannelData> getData(QDateTime since, QList<ChannelInfo> channels) = 0;
		
		virtual QString getLastError() = 0;
		virtual void setConnection(Connection * connection) = 0;
		virtual ModuleInfo getModuleInfo() = 0;
		virtual void setParams(Counter_Desc * desc) = 0;
		virtual QMap<QString, AddParam> getAdditionalParameters() = 0;
		virtual void setAdditionalParameters(QMap<QString, AddParam> params) = 0;

		virtual ~CounterInterface2() {}
};


Q_DECLARE_INTERFACE(CounterInterface,
                    "com.trolltech.Plugin.CounterInterface/1.0.2");

Q_DECLARE_INTERFACE(CounterInterface2,
                    "com.trolltech.Plugin.CounterInterface2/1.0.0");


#endif // COUNTERINTERFACE_H
