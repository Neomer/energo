/***************************************************
 *
 * Плагин для опроса счетчиков типа СЭБ-1ТМ.01(02),
 * ПСЧ-3ТМ.05, ПСЧ-4ТМ.05, СЭТ-4ТМ.01(02, 03)
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
