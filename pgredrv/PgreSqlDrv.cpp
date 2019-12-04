#include "PgreSqlDrv.h"
#include <QtPlugin>

PgreSqlDrv::PgreSqlDrv()
{
	this->m_codec = QTextCodec::codecForName("UTF-8");
	this->m_connection = 0;
}

PgreSqlDrv::~PgreSqlDrv()
{
	//if (m_connection) delete m_connection;
}

bool PgreSqlDrv::connect(QString host, QString login, QString pass, bool reconnect)
{
	QString cs = "host=%1 user=%2 password=%3";
	m_reconnect = reconnect;
	m_cstr = cs.arg(host).arg(login).arg(pass);
	this->m_connection = PQconnectdb(m_cstr.toAscii().constData());
	return PQstatus(this->m_connection) == CONNECTION_OK;
}

bool PgreSqlDrv::connect(QString host, QString login, QString pass, QString dbname, bool reconnect)
{
	QString cs = "host=%1 user=%2 password=%3 dbname=%4";
	m_reconnect = reconnect;
	m_cstr = cs.arg(host).arg(login).arg(pass).arg(dbname);
	this->m_connection = PQconnectdb(m_cstr.toAscii().constData());
	return PQstatus(this->m_connection) == CONNECTION_OK;
}

bool PgreSqlDrv::isConnected()
{
	return PQstatus(this->m_connection) == CONNECTION_OK;
}

PgreSqlResult * PgreSqlDrv::exec(const char *query)
{
	if ((!isConnected())&&(m_reconnect))
	{
		this->m_connection = PQconnectdb(m_cstr.toAscii().constData());
	}
	return new PgreSqlResult(this->m_codec, PQexec(this->m_connection, this->m_codec->fromUnicode(query).constData()));
}

PgreSqlResult * PgreSqlDrv::exec(QString query)
{
	return exec(query.toAscii().constData());
}

void PgreSqlDrv::close()
{
	PQfinish(this->m_connection);
}

QTextCodec * PgreSqlDrv::codec()
{
	return m_codec;
}

void PgreSqlDrv::setCodec(QTextCodec *codec)
{
	this->m_codec = codec;
}

QString PgreSqlDrv::getError()
{
	return QString(PQerrorMessage(this->m_connection));
}

//Q_EXPORT_PLUGIN(PgreSqlDrv);
