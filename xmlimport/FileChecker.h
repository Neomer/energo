#ifndef FILECHECKER_H
#define FILECHECKER_H

#include <QTimer>
#include <QDir>
#include <QFile>
#include <QThread>

#include "XML80020.h"
#include "../pgredrv/PgreSqlDrv.h"
#include "MainWindow.h"
#include "../includes/dbconf.h"

#define FILECHECKER_PERIOD		5000

class FileChecker : public QThread
{
		Q_OBJECT
	public:
		FileChecker(QString path, QObject *parent = 0);
		void startLoop();
		void stopLoop();
		
	private slots:
		void tick();
		void restartLoop();
		
	signals:
		void generateMessage(QString text);
		
	private:
		void run();
		QTimer * _tmr;
		QString _path;
		QDir _dir;
		PgreSqlDrv * _db;
		MainWindow * _mw;
};

#endif // FILECHECKER_H
