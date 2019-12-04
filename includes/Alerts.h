#ifndef ALERTS_H
#define ALERTS_H

#include <QString>
#include <QDateTime>
#include <QTextCodec>

#ifdef QCOREAPPLICATION_H
	#include <QtCore/QCoreApplication>
#else
	#include <QApplication>
#endif

enum AlertLevel
{
	ALL_Normal = 0,
	ALL_Warning = 1,
	ALL_Critical = 2
};

enum AlertType
{
	ALT_Infomation = 1,
	ALT_Warning = 2,
	ALT_Error = 3,
	ALT_ReceiveError = 4
};

enum AlertObjType
{
	AOT_Counter = 1,
	AOT_Object = 2
};

inline QString generateAlertRequest(int object, AlertObjType objtype, AlertType type, AlertLevel level, QString text)
{
	return QString("insert into alert (date, object, objecttype, level, type, text, module) values ('%1', %2, %3, %4, %5, '%6', '%7');").arg(
				QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"),
				QString::number(object),
				QString::number((int)objtype),
				QString::number((int)level),
				QString::number((int)type),
				text,
				qApp->applicationName());
}


#endif // ALERTS_H
