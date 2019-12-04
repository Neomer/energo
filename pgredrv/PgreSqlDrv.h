#ifndef PGRESQLDRV_H
#define PGRESQLDRV_H

#include "export.h"

#include <QObject>
#include <QTextCodec>

#include "PgreSqlResult.h"
#include "../includes/pgre/libpq-fe.h"

class PGRESQLDRV_SHARED_EXPORT PgreSqlDrv  : public QObject
{
	Q_OBJECT
	
public:
    PgreSqlDrv();
	~PgreSqlDrv();
	
	// Подключение к БД
	bool connect(QString host, QString login, QString pass, bool reconnect = true);
	bool connect(QString host, QString login, QString pass, QString dbname, bool reconnect = true);
	
	// Выполнение SQL скрипта
	PgreSqlResult * exec(QString query);
	PgreSqlResult * exec(const char * query);
	
	// Установка кодировки
	QTextCodec * codec();
	void setCodec(QTextCodec * codec);
	
	bool isConnected();
	QString getError();
	
	void close();
	
protected:
	PGconn * m_connection;
	QTextCodec * m_codec;
	bool m_reconnect;
	QString m_cstr;
	
	friend class PgreSqlResult;
};

/*Q_DECLARE_INTERFACE(PgreSqlDrv,
                   "com.trolltech.Plugin.ReportEngine/1.0.0");
*/
#endif // PGRESQLDRV_H
