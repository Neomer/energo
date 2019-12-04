#include <QtGui/QApplication>
#include "SchemeEditorMW.h"
//#include "LoadScreen.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	Q_INIT_RESOURCE(resources);
	
	QTextCodec::setCodecForTr(QTextCodec::codecForName("windows-1251"));

	SchemeEditorMW w;
	w.show();

	return a.exec();
}
