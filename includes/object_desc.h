#ifndef OBJECT_DESC_H
#define OBJECT_DESC_H

#include <QString>
#include "../includes/global.h"
#include "../qextserialport/src/qextserialport.h"

struct ConnectionParams
{
	QString inet_addr;
	quint16 inet_port;
	QString phone;
};

struct ConnectionInitParams
{
	QString serial_name;
	PortSettings serial_sets;
	QString serial_initstr;
};


enum ConnectionType
{
	CT_DIRECT = 1,
    CT_GSM = 2,
    CT_TCPIP = 3
};


struct Counter_Desc 
{
	// Данные по счетчику
	int ID;
	QString number;
	short address;
	QString login;
	QString password;
	QString type;
	QString module;
	QString params;
	int timeout_receive;
	int timeout_send;
	int corr_min;
	int corr_max;
	bool corr_allow;
	
	// Данные по подстанции
	int object;
	int recall;
	ConnectionType connection;
	QString connection_string;
	QString connection_opts;

	// Данные по фидеру
	int feeder;
	QString feeder_name;
	int channels;
	TransformationRatio tr;
};

#endif // OBJECT_DESC_H
