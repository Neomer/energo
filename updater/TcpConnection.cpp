#include "TcpConnection.h"
#include <QMessageBox>
#include "defines.h"

TcpConnection::TcpConnection(QObject *parent) :
    QObject(parent)
{
	_sock = new QTcpSocket();
	_md5proc = new Md5Checker(this);
	_action = Connect;
	_recv = 0;
	connect(_sock, SIGNAL(readyRead()), this, SLOT(dataReceived()));
	start();
}

void TcpConnection::start()
{
	_sock->connectToHost(QHostAddress(QString("127.0.0.1")), 6543, QIODevice::ReadWrite);
	if (!_sock->waitForConnected(1000))
	{
		emit onConnectionFail();
		return;
	}
	if (_sock->state() != QAbstractSocket::ConnectedState)
	{
		emit onConnectionFail();
		return;
	}
	emit onConnectionSuccess();
	ClientResponse cr;
	cr.code = TCPCLIENT_RESPONSE_EQUAL;
	_sock->write((const char *)&cr, sizeof(cr));
	_action = NextFile;
}

void TcpConnection::dataReceived()
{
	ClientResponse cr;
	UpdateFileInfo fi;
	UpdateFilePart fp;
	QByteArray ba;
	switch (_action)
	{
		case NextFile:
			_sock->read((char *)&fi, sizeof(fi));
			if (fi.length != -1)
			{
				emit onNewFile(fi.name);
				if (_md5proc->test(QString(fi.name), QByteArray((const char *)fi.hash, HASH_SIZE)))
				{
					emit onProgress(100);
					cr.code = TCPCLIENT_RESPONSE_EQUAL;
				}
				else
				{
					emit onProgress(0);
					cr.code = TCPCLIENT_RESPONSE_FILE;
					_action = Download;
					_recv = new FileReceiver();
					_recv->open(fi.name);
				}
			}
			else
				cr.code = TCPCLIENT_RESPONSE_END;
			break;
			
		case Download:
			_sock->read((char *)&fp, sizeof(fp));
			if (fp.length == 0)
			{
				_recv->close();
				cr.code = TCPCLIENT_RESPONSE_EQUAL;
				_action = NextFile;
			}
			else
			{
				ba = QByteArray((char *)fp.data, fp.length);
				_recv->append(ba);
			}
			break;
			
		default:
			break;
	}
	if (cr.code != TCPCLIENT_RESPONSE_END)
		_sock->write((const char *)&cr, sizeof(cr));
	else
		emit onFinish();
}
