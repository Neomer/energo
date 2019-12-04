#include <QtCore/QCoreApplication>
#include "TcpListener.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	TcpListener * srv = new TcpListener();
	srv->listen(QHostAddress::Any, 6543);
    return a.exec();
}
