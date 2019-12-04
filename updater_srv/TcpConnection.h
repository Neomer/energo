#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include "Md5Checker.h"

typedef unsigned char byte;


// В ответ отсылается MD5-хэш следующего файла, либо '.' в случае окончания списка
#define TCPCLIENT_RESPONSE_EQUAL	0  
// В ответ отсылается описание файла
#define TCPCLIENT_RESPONSE_DIFF		1
// В ответ отсылается очередная часть файла
#define TCPCLIENT_RESPONSE_FILE		2
// В ответ повторяется посылка текущей части файла
#define TCPCLIENT_RESPONSE_RETRY	3

struct ClientResponse
{
	byte code;
};

struct UpdateFileInfo
{
	char name[MAX_FILE_NAME];
	long length;
	byte hash[HASH_SIZE];
};

#define CHUNK_SIZE		50 * 10240

struct UpdateFilePart
{
	quint32 length;
	byte hash[HASH_SIZE];
	byte data[CHUNK_SIZE];
};

class TcpConnection : public QObject
{
    Q_OBJECT
	
	public:
		TcpConnection(QTcpSocket * socket, QObject * parent = 0);
	
	//signals:
	
	public slots:
		void dataReceived();
		void socketStateChanged(QAbstractSocket::SocketState state);
	
	private:
		Md5Checker * _file;
		QTcpSocket * _sock;
};

#endif // TCPCONNECTION_H
