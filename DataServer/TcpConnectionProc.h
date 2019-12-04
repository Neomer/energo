#ifndef TCPCONNECTIONPROC_H
#define TCPCONNECTIONPROC_H

#include <QObject>

#include <QTcpSocket>
#include <QThread>
#include "../pgredrv/PgreSqlDrv.h"

#include "TcpPackage.h"

struct UserInfo
{
	int id;
	QString login;
	QString password;
};

class TcpConnectionProc : public QObject
{
    Q_OBJECT
	
	public:
		TcpConnectionProc(PgreSqlDrv * connection, QTcpSocket * client, QObject *parent = 0);
	
	private slots:
		void dataReceived();
		void socketStateChanged(QAbstractSocket::SocketState state);
		void bytesSent(qint64 length);
	
	private:
		void run();
		QTcpSocket * _cli;
		TcpPackage * _pkg;
		PgreSqlDrv * _conn;
		UserInfo * _info;
};


#endif // TCPCONNECTIONPROC_H
