/*************************************************************************
  Scheduler.pro
  
  Программа для организации автоматизированного опроса подстанций.
  
  По расписанию запускает программу опроса счетчиков recv.exe, передавая
  ей в качестве аргументов необходимые подстанции.
  ************************************************************************/

#include <QtGui/QApplication>
#include <QTextCodec>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));
	
	Q_INIT_RESOURCE(resources);
	
	MainWindow w;
	w.show();
	
    return a.exec();
}
