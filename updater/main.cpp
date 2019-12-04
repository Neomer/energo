#include <QtGui/QApplication>
#include "MainWindow.h"
#include <QDesktopWidget>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
	QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));
	
	QDesktopWidget dsc;
	
	MainWindow w(&dsc);
	QRect r(QPoint(dsc.width() * 0.5 - w.width() * 0.5, dsc.height() * 0.5 - w.height() * 0.5), QPoint(w.width(), w.height()));
	w.setGeometry(r);
    w.show();
	w.start();
	
    return a.exec();
}
