#include "TcpConnection.h"
#include <qmath.h>

TcpConnection::TcpConnection(QTcpSocket *socket, QObject *parent) :
    QObject(parent)
{
	_sock = socket;
	qDebug("TcpConnection::TcpConnection() - State is %d", _sock->state());
	
	connect(_sock, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
			this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
	connect(_sock, SIGNAL(readyRead()), this, SLOT(dataReceived()));
	
	_file = new Md5Checker();
}

void TcpConnection::dataReceived()
{
	ClientResponse cr;
	_sock->read((char *)&cr, sizeof(ClientResponse));
	UpdateFileInfo fi;
	UpdateFilePart fp;
	QByteArray ba;
	switch (cr.code)
	{
		case TCPCLIENT_RESPONSE_EQUAL:
			if (_file->next())
			{
				memcpy(fi.hash, _file->getHash().constData(), HASH_SIZE);
				memcpy(fi.name, _file->getName().toAscii().constData(), qMin<int>(_file->getName().size()+ 1, MAX_FILE_NAME));
				fi.length = _file->getFile().size();
				_sock->write((const char *)&fi, sizeof(fi));
			}
			else
			{
				fi.length = -1;
				_sock->write((const char *)&fi, sizeof(fi));
			}
			break;
			
		case TCPCLIENT_RESPONSE_FILE:
			ba = _file->getFileChunk(CHUNK_SIZE);
			fp.length = ba.size();
			memcpy(fp.data, ba.constData(), ba.size());
			_sock->write((const char *)&fp, sizeof(fp));
			break;
	}
}

void TcpConnection::socketStateChanged(QAbstractSocket::SocketState state)
{
	qDebug("TcpConnection::socketStateChanged() - State changed to %d", state);
}
