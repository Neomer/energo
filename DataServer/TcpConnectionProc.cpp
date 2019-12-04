#include "TcpConnectionProc.h"
#include <QDateTime>

TcpConnectionProc::TcpConnectionProc(PgreSqlDrv *connection, QTcpSocket *client, QObject *parent) :
    QObject(parent)
{
	if (!client) 
		return;
	_cli = client;
	_conn = connection;
	_pkg = 0;
	_info = 0;
	connect(client, SIGNAL(readyRead()), this, SLOT(dataReceived()));
	connect(client, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
			this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
	connect(client, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesSent(qint64)));
}

void TcpConnectionProc::dataReceived()
{
	TcpPackage * response;
	QByteArray ba = _cli->read(_cli->bytesAvailable());
	qDebug("TcpConnectionProc::dataReceived() - Received %d byte(s)",
		   ba.length());
	
	if (!_pkg) _pkg = new TcpPackage();
	if (_pkg->isValid()) _pkg->clear();
	_pkg->append(ba);
	if (_pkg->isValid())
	{
		bool ok;
		int cnum;
		QString user, pwd;
		PgreSqlResult * r;
		QDateTime since;
		switch (_pkg->getCode())
		{
			case TCP_PKGCODE_AUTH:
				user = _pkg->getString();
				pwd = _pkg->getString();
				if (_info) delete _info;
				_info = new UserInfo();
				r = _conn->exec(QString("select id, login, password from users where login='%1' and password=md5('%2') limit 1;").arg(user, pwd));
				if (!r->isValid())
				{
					qDebug("TcpConnectionProc::dataReceived() - SQL ERROR: %s\n%s",
						   _conn->getError().toAscii().constData(),
						   "");
				}
				response = new TcpPackage();
				response->setCode(TCP_PKGCODE_AUTH);
				if (r->hasRows())
				{
					qDebug("TcpConnectionProc::dataReceived() - Authorization success. User: %s",
						   user.toAscii().constData());
					_info->id = r->getValue(0).toInt();
					_info->login = user;
					_info->password = pwd;
					response->addData((byte)TCP_PKGCODE_AUTH_SUCCESS);
				}
				else
				{
					qDebug("TcpConnectionProc::dataReceived() - Authorization denied! User: %s Password: %s",
						   user.toAscii().constData(),
						   pwd.toAscii().constData());
					response->addData((byte)TCP_PKGCODE_AUTH_FAIL);
				}
				break;
				
			case TCP_PKGCODE_CNUM:
				response = new TcpPackage();
				if (!_info)
				{
					response->setCode(TCP_PKGCODE_AUTH);
					response->addData((byte)TCP_PKGCODE_AUTH_FAIL);
				}
				else
				{
					cnum = _pkg->getLongLong();
					r = _conn->exec(QString("select c.c_number from user_access ua left join channel ch on ch.id=ua.channel left join counter c on c.id=ch.counter where ua.user_id=%1 and c.c_number=%2;").arg(QString::number(_info->id), QString::number(cnum)));
					if (!r->isValid())
					{
						qDebug("TcpConnectionProc::dataReceived() - SQL ERROR: %s\n%s",
							   _conn->getError().toAscii().constData(),
							   "");
					}
					response->setCode(TCP_PKGCODE_CNUM);
					if (r->hasRows())
					{
						qDebug("TcpConnectionProc::dataReceived() - Counter %d access approved for user '%s'",
							   cnum,
							   _info->login.toAscii().constData());
						response->addData((byte)TCP_PKGCODE_AUTH_SUCCESS);
					}
					else
					{
						qDebug("TcpConnectionProc::dataReceived() - Counter %d access denied for user '%s'",
							   cnum,
							   _info->login.toAscii().constData());
						response->addData((byte)TCP_PKGCODE_AUTH_FAIL);
					}
					r->close();
				}
				break;
				
			case TCP_PKGCODE_TIME:
				response = new TcpPackage();
				if (!_info)
				{
					response->setCode(TCP_PKGCODE_AUTH);
					response->addData((byte)TCP_PKGCODE_AUTH_FAIL);
				}
				else
				{
					response->setCode(TCP_PKGCODE_TIME);
					response->addData((long)QDateTime::currentDateTime().toTime_t());
				}
				break;
				
			case TCP_PKGCODE_DATA:
				response = new TcpPackage();
				if (!_info)
				{
					response->setCode(TCP_PKGCODE_AUTH);
					response->addData((byte)TCP_PKGCODE_AUTH_FAIL);
				}
				else
				{
					// Проверка доступа
					// cnum == channel ID
					cnum = _pkg->getInt();
					since = QDateTime::fromTime_t((uint)_pkg->getLong());
					r = _conn->exec(QString("select * from user_access ua where ua.user_id=%1 and ua.channel=%2;").arg(QString::number(_info->id), QString::number(cnum)));
					if (!r->isValid())
					{
						qDebug("TcpConnectionProc::dataReceived() - SQL ERROR: %s\n%s",
							   _conn->getError().toAscii().constData(),
							   "");
					}
					if (r->hasRows())
					{
						qDebug("TcpConnectionProc::dataReceived() - Request data by channel %d since %s",
							   cnum,
							   since.toString("yyyy-MM-dd hh:mm").toAscii().constData());
						response->setCode(TCP_PKGCODE_DATA);
						r->close();
						r = _conn->exec(QString("select * from data d where d.channel=%1 and to_dt(d.date, d.itv)>'%2' order by date, itv;").arg(QString::number(cnum), since.toString("yyyy-MM-dd hh:mm:ss")));
						if (!r->isValid())
						{
							qDebug("TcpConnectionProc::dataReceived() - SQL ERROR: %s\n%s",
								   _conn->getError().toAscii().constData(),
								   "");
						}
						while (r->notEoF())
						{
							since = QDateTime::fromString(r->getValue("date"), "yyyy-MM-dd");
							response->addData((long)since.toTime_t());
							response->addData(r->getValue("itv").toInt());
							response->addData(r->getValue("itv_length").toInt());
							response->addData(r->getValue("value").toDouble());
							response->addData(r->getValue("c_value").toDouble());
							r->moveNext();
						}
					}
					else
					{
						qDebug("TcpConnectionProc::dataReceived() - Channel %d access denied for user '%s'",
							   cnum,
							   _info->login.toAscii().constData());
						response->setCode(TCP_PKGCODE_CNUM);
						response->addData((byte)TCP_PKGCODE_AUTH_FAIL);
					}
				}
				break;
			
		}
		ba = response->compile();
		_cli->write(ba.constData(), ba.size());
		if (!_cli->waitForBytesWritten(5000))
		{
			qDebug("TcpConnectionProc::dataReceived() - Data not written!");
		}
	}
}

void TcpConnectionProc::socketStateChanged(QAbstractSocket::SocketState state)
{
	qDebug("TcpConnection::socketStateChanged() - State changed to %d", state);
}

void TcpConnectionProc::bytesSent(qint64 length)
{
	qDebug("TcpConnection::bytesSent() - Bytes count sent %d", length);
}
