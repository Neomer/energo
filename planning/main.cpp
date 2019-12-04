#include <QtGui/QApplication>
#include "PlanningMW.h"
#include "PlanningLoginForm.h"
#include <QSettings>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));

	QSettings * settings = new QSettings("energo.conf", QSettings::IniFormat, &a);
	
	PlanningMW w(settings);
	w.show();
	
	PlanningLoginForm lf(settings, &w);
	lf.setModal(true);
	lf.setWindowModality(Qt::ApplicationModal);
	
	QObject::connect(&lf, SIGNAL(connectToDatabase(PgreSqlDrv*, int)), 
					 &w, SLOT(databaseConnected(PgreSqlDrv *, int)));
	
	QObject::connect(&lf, SIGNAL(onClose()),
					 &w, SLOT(loginFormClosed));
	
	lf.show();
	
	return a.exec();
}
