#ifndef ORADRV_H
#define ORADRV_H

#define OCI_CHARSET_ANSI
#define OCI_API __stdcall

#include "oradrv_global.h"
#include <QString>
#include <QTextCodec>

#include "../includes/oracle/ocilib.h"
#include "OraSqlResult.h"

class ORADRVSHARED_EXPORT OraSqlDrv {
	public:
		OraSqlDrv();
		
		// Подключение к БД
		bool connect(QString host, QString login, QString pass, bool reconnect = true);
		bool connect(QString host, QString login, QString pass, QString dbname, bool reconnect = true);
		
		// Выполнение SQL скрипта
		OraSqlResult * exec(QString query);
		OraSqlResult * exec(const char * query);
		
		// Применение изменений
		bool apply();
		
		// Установка кодировки
		QTextCodec * codec();
		void setCodec(QTextCodec * codec);
		
		bool isConnected();
		QString getError();
		
		void close();
		
	protected:
		//void errorProc(OCI_Error * err);
		OCI_Connection * _conn;
		QTextCodec * _codec;
		bool _reconnect;
		QString _cstr;
		
		friend class PgreSqlResult;
};

#endif // ORADRV_H
