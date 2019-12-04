#include <QtGui/QApplication>
#include "MainWindow.h"
#include <QTextCodec>

MainWindow * w;

void msgHandler(QtMsgType type, const char *msg)
{
	w->appendLog(QString(msg));
}

int main(int argc, char *argv[])
{
	//qInstallMsgHandler(msgHandler);
	
	QApplication a(argc, argv);
	
	QTextCodec::setCodecForTr(QTextCodec::codecForName("windows-1251"));
	
	w = new MainWindow();
    w->show();

    return a.exec();
}
