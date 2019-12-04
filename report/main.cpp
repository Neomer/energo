#include <QtGui/QApplication>
#include <QTextCodec>

#include "MainWindow.h"
#include "loginform.h"

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(resources);	
	
    QApplication a(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));
	
	MainWindow w;
	a.setQuitOnLastWindowClosed(true);
	LoginForm lf(&w);
	
	QObject::connect(&lf, SIGNAL(onDBConnected(PgreSqlDrv*)), &w, SLOT(db_connected(PgreSqlDrv*)));
	QObject::connect(&lf, SIGNAL(onAuthFail()), &w, SLOT(login_fail()));
	lf.setWindowModality(Qt::ApplicationModal);

	w.setWindowState(Qt::WindowMaximized);
	w.show();
	if (argc == 1) lf.show();
	//QObject::connect(&lf, SIGNAL(destroyed()), &w, SLOT(login_form_closed()));
	QObject::connect(&lf, SIGNAL(onClose()), &w, SLOT(login_form_closed()));
	
    return a.exec();
}
