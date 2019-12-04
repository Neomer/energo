#include <QtCore/QCoreApplication>
#include <QObject>
#include <QPluginLoader>
#include <QDir>
#include <QString>
#include <QDateTime>
#include <QtDebug>
#include <QFile>

#include "../set4tm/Set4tmInterface.h"
#include "ErrorListener.h"

#include <QMap>

void myMessageOutput(QtMsgType type, const char *msg)
{
    switch (type) {
		case QtDebugMsg:
			fprintf(stderr, "Debug: %s\n", msg);
			break;
		case QtWarningMsg:
			fprintf(stderr, "Warning: %s\n", msg);
			break;
		case QtCriticalMsg:
			fprintf(stderr, "Critical: %s\n", msg);
			break;
		case QtFatalMsg:
			fprintf(stderr, "Fatal: %s\n", msg);
			abort();
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	
	qInstallMsgHandler(myMessageOutput);
	
	qDebug("test debug %d", 5);
	qCritical("test critical");
	
	return a.exec();
}
