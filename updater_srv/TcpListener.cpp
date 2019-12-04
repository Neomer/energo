#include "TcpListener.h"


TcpListener::TcpListener(QObject *parent) :
    QTcpServer(parent)
{
	connect(this, SIGNAL(newConnection()), SLOT(receiveConnection()));
	_subnet = QHostAddress::Any;
	_port = 6543;
}


void TcpListener::receiveConnection()
{
	qDebug("TcpListener::receiveConnection() - Attempt to connection...");
	TcpConnection * conn = new TcpConnection(nextPendingConnection(), this);
	_clients.append(conn);
} 
