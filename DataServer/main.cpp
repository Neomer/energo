#include <QtCore/QCoreApplication>
#include <QFile>

#include "../pgredrv/PgreSqlDrv.h"

#include "default_settings.h"
#include "TcpListener.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	int port = DATASRV_DEF_PORT;
	
	for (int i = 1; i < argc; i++)
	{
		QString arg = argv[i];
		QStringList argp = arg.split('=', QString::SkipEmptyParts);
		QString command = argp.at(0).toLower();
		if (command == "-port")
		{
			port = argp.at(1).toInt();
		}
		else
		{
			qWarning("Unknown command: %s\n", argp.at(0).toAscii().constData());
			continue;
		}
	}
	
	QFile file("db");
	
	file.open(QIODevice::ReadOnly);
	
	QString dbhost = file.readLine();
	PgreSqlDrv * drv = new PgreSqlDrv();
	if (!drv->connect(dbhost, "postgres", "1234", "energo", true))
	{
		qWarning("Database is not available!");
		a.exec();
	}
	
	TcpListener * srv = new TcpListener(drv, &a);
	if (!srv->listen(QHostAddress::Any, port))
	{
		qWarning("Port already busy!");
		a.exec();
	}
	
    return a.exec();
}
