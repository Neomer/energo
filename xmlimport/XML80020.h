#ifndef XML80020_H
#define XML80020_H

#include <QDomDocument>
#include <QDateTime>

class XML80020MeasuringChannelData
{
	public:
		XML80020MeasuringChannelData(QDomNode node);
		QString getValue();
		QTime getStartTime();
		QTime getEndTime();
		int getInterval();
		bool isSummer();
        void setTimeCorrection(int value);
		
	private:
		QDomNode _node;
		bool _parsed;
        int _time;
};

class XML80020MeasuringChannel
{
	public:
		XML80020MeasuringChannel(QDomNode node);
		QString getCode();
		QString getDesc();
		
		XML80020MeasuringChannelData * nextPeriod();
		
	private:
		QDomNode _node;
		bool _parsed;
		QList<XML80020MeasuringChannelData *> _points;
		int _ptr;
};

class XML80020MeasuringPoint
{
	public:
		XML80020MeasuringPoint(QDomNode node);
		QString getCode();
		QString getName();
		
		XML80020MeasuringChannel * nextChannel(QString code = QString());
		
	private:
		QDomNode _node;
		bool _parsed;
		QList<XML80020MeasuringChannel *> _points;
		int _ptr;
};

class XML80020Area
{
	public:
		XML80020Area(QDomNode node);
		QString getObjectID();
		QString getObjectName();
		XML80020MeasuringPoint * nextPoint();
	
	private:
		QDomNode _node;
		bool _parsed;
		QList<XML80020MeasuringPoint *> _points;
		int _ptr;
};

class XML80020
{
	public:
		enum XML80020DL
		{
			DL_WINTER = 0,
			DL_SUMMER = 1,
			DL_EXCHANGE = 2,
			DL_ERROR = -1
		};
		XML80020(QByteArray data);
		
		bool isValid();
		
		QString getSenderName();
		QString getSenderID();
		QDate getDate();
		QDateTime getGenerationDT();
		XML80020DL getDL();
		
		XML80020Area * nextArea();
		
	private:
		QDomDocument * _xml;
		bool _parsed;
		QDomNode _sender,
				 _datetime;
		QList<XML80020Area *> _data;
		int _data_ptr;
};

#endif // XML80020_H
