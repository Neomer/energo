#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <QtNetwork/QTcpSocket>
#include <qextserialport.h>

enum ConnectionType
{
    CT_GSM,
    CT_TCPIP,
    CT_DIRECT
};

class Connection
{
public:
    Connection(ConnectionType type);
    bool Init(QString init_str);
	bool Connect(QStirng conn_str);
    Send();
    Receive();
    Close();
};

#endif // CONNECTION_H
