#include <QtGui/QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QTextCodec>
#include <QMutex>
#include <QtDebug>
#include <QObject>
#include <QDesktopWidget>

#include <stdlib.h>

#include "mainwindow.h"
#include "loginform.h"
#include "debugwindow.h"

DebugWindow * dbgw = 0;

void msgHandler(QtMsgType type, const char *msg)
{
	if (dbgw)
		dbgw->addRow(QString(msg));
}

int main(int argc, char *argv[])
{
	qInstallMsgHandler(msgHandler);
    
	QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));
	
	MainWindow w;
	a.setQuitOnLastWindowClosed(true);
	LoginForm lf(&w);
	
	QObject::connect(&lf, SIGNAL(onClose()), &w, SLOT(login_form_close()));
	QObject::connect(&lf, SIGNAL(onDBConnected(PgreSqlDrv*)), &w, SLOT(db_connected(PgreSqlDrv*)));
	QObject::connect(&lf, SIGNAL(onAuthFail()), &w, SLOT(login_fail()));
	lf.setWindowModality(Qt::ApplicationModal);

	dbgw = new DebugWindow(&w);
	
	dbgw->setGeometry(0, 20, dbgw->geometry().width(), dbgw->geometry().height());
	// Показать отладочное окно
	//dbgw->show();
	w.setWindowState(Qt::WindowMaximized);
	w.setDebugWindow(dbgw);
	w.show();
	lf.show();
	
    return a.exec();
}
