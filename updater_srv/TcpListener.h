#ifndef TCPLISTENER_H
#define TCPLISTENER_H

#include <QList>
#include <QTcpServer>
#include "TcpConnection.h"

class TcpListener : public QTcpServer
{
	Q_OBJECT
	
	public:
		TcpListener(QObject * parent = 0);
		
	private slots:
		void receiveConnection();
	
	private:
		QTcpServer * _srv;
		QHostAddress _subnet;
		quint16 _port;
		QList<TcpConnection *> _clients;
		
	protected:
		//void incomingConnection(int handle);
};

#endif // TCPLISTENER_H
