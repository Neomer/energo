#include "TcpListener.h"

TcpListener::TcpListener(PgreSqlDrv *connection, QObject *parent) :
    QTcpServer(parent)
{
	_conn = connection;
	connect(this, SIGNAL(newConnection()), this, SLOT(onConnectionReceive()));
}

void TcpListener::setPort(int port)
{
	_port = port;
}

void TcpListener::onConnectionReceive()
{
	QTcpSocket * client = nextPendingConnection();
	qDebug("TcpListener::onConnectionReceive() - New connection: %d", (int)client);
	TcpConnectionProc * conn = new TcpConnectionProc(_conn, client, this);
	_clients.append(conn);
}
