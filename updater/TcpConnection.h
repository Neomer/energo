#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QThread>
#include "defines.h"
#include "Md5Checker.h"
#include "FileReceiver.h"

typedef unsigned char byte;

// В ответ отсылается MD5-хэш следующего файла, либо '.' в случае окончания списка
#define TCPCLIENT_RESPONSE_EQUAL	0  
// В ответ отсылается описание файла
#define TCPCLIENT_RESPONSE_DIFF		1
// В ответ отсылается очередная часть файла
#define TCPCLIENT_RESPONSE_FILE		2
// В ответ повторяется посылка текущей части файла
#define TCPCLIENT_RESPONSE_RETRY	3
// Заглушка для окончания проверки
#define TCPCLIENT_RESPONSE_END		4

struct UpdateFileInfo
{
	char name[MAX_FILE_SIZE];
	long length;
	byte hash[HASH_SIZE];
};

struct UpdateFilePart
{
	quint32 length;
	byte hash[HASH_SIZE];
	byte data[CHUNK_SIZE];
};

struct ClientResponse
{
	byte code;
};


class TcpConnection : public QObject
{
    Q_OBJECT
	
	public:
		explicit TcpConnection(QObject *parent = 0);

	signals:
		void onConnectionFail();
		void onConnectionSuccess();
		void onNewFile(QString name);
		void onProgress(int progress);
		void onFinish();
		

	private slots:
		void dataReceived();
		
	private:
		enum 
		{
			Connect,
			NextFile,
			Download
		} _action;

		void start();
		QTcpSocket * _sock;
		Md5Checker * _md5proc;
		FileReceiver * _recv;
};

#endif // TCPCONNECTION_H
