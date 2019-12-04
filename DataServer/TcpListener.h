#ifndef TCPLISTENER_H
#define TCPLISTENER_H

#include <QTcpServer>

#include "default_settings.h"
#include "TcpConnectionProc.h"

class TcpListener : public QTcpServer
{
    Q_OBJECT
	
	public:
		TcpListener(PgreSqlDrv * connection, QObject *parent = 0);
		void setPort(int port);
		
	private slots:
		void onConnectionReceive();
		
	private:
		int _port;
		PgreSqlDrv * _conn;
		QList<TcpConnectionProc *> _clients;
};

#endif // TCPLISTENER_H
