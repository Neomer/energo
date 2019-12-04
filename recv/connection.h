#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <QtNetwork/QTcpSocket>
#include "../qextserialport/src/qextserialport.h"
#include <QThread>
#include <QTimer>
#include <QList>
#include <QByteArray>
#include <QPluginLoader>
#include <QDir>
#include <QObject>
#include <QtNetwork/QHostAddress>

#include "../includes/object_desc.h"
#include "../GSMConnection/GSMConnectionInterface.h"

#define CONNECTION_VIRTUAL_SERIAL_PORT		(QextSerialPort *) -1

class Connection : public QObject
{
	Q_OBJECT
	
public:
    Connection(ConnectionType type, QObject * parent = 0);
    bool Init(ConnectionInitParams *params);
	bool Connect(ConnectionParams *params);
    int Send(QByteArray buf);
	QByteArray Receive();
    bool Close();

	bool isConnected();
	bool isInitialized();

	QString GetLastError();
	int getStatus();
	bool setConnectionType(ConnectionType type);
	void setReceiveTimeout(int timeout);
	void setSendTimeout(int timeout);
	
private:
	QextSerialPort * com;
	QTcpSocket * sock;
	GSMConnectionInterface * gsm;
	QString err;
	int m_timeout;

public slots:
	void closeConnection();	

protected:
	ConnectionType m_type;
};


#endif // CONNECTION_H
