/***************************************************
 *
 * ������ ��� ������ ��������� ���� ���-1��.01(02),
 * ���-3��.05, ���-4��.05, ���-4��.01(02, 03)
 *
 ***************************************************
 */

#ifndef SET4TNINTERFACE_H
#define SET4TNINTERFACE_H

#include <QByteArray>
#include <QObject>
#include <QString>
#include <QDateTime>

#include "../GSMConnection/GSMConnectionInterface.h"
#include "../includes/global.h"
#include "../includes/CounterInterface.h"

class Set4tmInterface : public CounterInterface2
{
public:
	virtual ~Set4tmInterface() {}
};

Q_DECLARE_INTERFACE(Set4tmInterface,
                    "com.trolltech.Plugin.Set4tmInterface/1.0.2");


#endif // SET4TNINTERFACE_H
