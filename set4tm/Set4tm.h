#ifndef SET4TM_H
#define SET4TM_H

#include <QByteArray>
#include <QObject>
#include <QDateTime>
#include <stdlib.h>
#include <QMap>

#include "set4tm_global.h"
#include "Set4tm.h"
#include "Set4tmInterface.h"
#include "../recv/connection.h"
#include "../includes/modbus.h"
#include "global.h"

#define SET4TMPLUGIN_VERSION		tr("1.0")
#define SET4TMPLUGIN_MAX_DIFFDATE	2 

#define SET4TM_RWRI_TYPE_POWER			0x00
#define SET4TM_RWRI_TYPE_VOLTAGE		0x01
#define SET4TM_RWRI_TYPE_AMP			0x02
#define SET4TM_RWRI_TYPE_COSINE			0x03
#define SET4TM_RWRI_TYPE_FREQ			0x04

#define SET4TM_RWRI_PARAM_NULL			0x00

#define SET4TM_RWRI_PARAM_POWER_P		0x00
#define SET4TM_RWRI_PARAM_POWER_Q		0x01
#define SET4TM_RWRI_PARAM_POWER_S		0x02

#define SET4TM_RWRI_PARAM_VOLTAGE_PHASE			0x00
#define SET4TM_RWRI_PARAM_VOLTAGE_BETPAHSE		0x01
#define SET4TM_RWRI_PARAM_VOLTAGE_LINE			0x02
#define SET4TM_RWRI_PARAM_VOLTAGE_BATTERY		0x03

#define SET4TM_RWRI_PARAM_COSINE_COS	0x00
#define SET4TM_RWRI_PARAM_COSINE_SIN	0x01
#define SET4TM_RWRI_PARAM_COSINE_TAN	0x02

class Set4tmPlugin : public QObject, public Set4tmInterface
{
Q_OBJECT
Q_INTERFACES(Set4tmInterface)
Q_INTERFACES(CounterInterface2)
	
public:
	Set4tmPlugin();

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
	
	~Set4tmPlugin();

private:
	// Подсчет Modbus CRC16
    unsigned char * getHash(unsigned char *data, int length, bool append = false);
	// Подсчет КС
	unsigned char * getCS(char * data, int length);
	unsigned short updCRC(unsigned char c, unsigned short * crc);
	bool getFromCounter(QByteArray * buffer, quint32 maxsize);
	QByteArray createRequest(char * data, long length);
	QByteArray createRequest(byte * data, long length);
	QDateTime fromCounterDT(byte * buffer, QString format);
	double fromCounterData(quint32 value, CounterDataHeader *hdr, byte A, TransformationRatio *tr);
	byte createRWRI(byte type, byte param, byte phase);

	Counter_Desc m_desc;
	char m_addr;
	QString err;
	Connection * m_conn;
	QMap<QString, AddParam> _params;
};

#endif // SET4TM_H
