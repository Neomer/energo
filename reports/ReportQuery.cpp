#include "ReportQuery.h"

ReportQuery::ReportQuery(PGconn * connection, QDomElement query)
{
	this->m_conn = connection;
	this->m_read_ptr = 0;
	this->m_count = 0;
	this->m_fcount = 0;
	this->m_result = 0;
	this->m_codec = QTextCodec::codecForName("UTF-8");
	setQuery(query);
}

ReportQuery::ReportQuery(PGconn *connection)
{
	this->m_conn = connection;
	this->m_query = QDomElement();
	this->m_result = 0;
	this->m_read_ptr = 0;
	this->m_count = 0;
	this->m_fcount = 0;
	this->m_codec = QTextCodec::codecForName("UTF-8");
}

bool ReportQuery::setQuery(QDomElement query)
{
	if (this->m_result) PQclear(this->m_result);
	this->m_query = query;
	if (PQstatus(this->m_conn) != CONNECTION_OK)
	{
		qDebug("ReportQuery::setQuery() - Database connection closed!");
		return false;
	}
	this->m_result = PQexec(this->m_conn, query.text().toAscii().constData());
	if (PQresultStatus(this->m_result) == PGRES_FATAL_ERROR)
	{
		qDebug("ReportQuery::setQuery() - Database execution failed!\n%s\n%s",
		       query.text().toAscii().constData(),
		       PQerrorMessage(this->m_conn));
		return false;
	}
	this->m_read_ptr = 0;
	this->m_count = PQntuples(this->m_result);
	this->m_fcount = PQnfields(this->m_result);
	this->m_name = query.attribute(QString("name"));
	return true;
}

bool ReportQuery::setQuery(QString query)
{
	if (this->m_result) PQclear(this->m_result);
	this->m_query.setNodeValue(query);
	if (PQstatus(this->m_conn) != CONNECTION_OK)
	{
		qDebug("ReportQuery::setQuery() - Database connection closed!");
		return false;
	}
	this->m_result = PQexec(this->m_conn, m_codec->fromUnicode(query).constData());
	if (PQresultStatus(this->m_result) == PGRES_FATAL_ERROR)
	{
		qDebug("ReportQuery::setQuery() - Database execution failed!\n%s\n%s",
		       query.toAscii().constData(),
		       PQerrorMessage(this->m_conn));
		return false;
	}
	this->m_read_ptr = 0;
	this->m_count = PQntuples(this->m_result);
	this->m_fcount = PQnfields(this->m_result);
	this->m_name = "";
	return true;
}


int ReportQuery::getNumRows()
{
	return this->m_count;
}

int ReportQuery::getNumFields()
{
	return this->m_fcount;
}

QString ReportQuery::getName()
{
	return this->m_name;
}

QString ReportQuery::getValue(QString field)
{
	if (!EoF())
	{
		int nf = PQfnumber(this->m_result, field.toAscii().constData());
		if (nf == -1) return QString();
		return m_codec->toUnicode(PQgetvalue(this->m_result, this->m_read_ptr, nf));
	}
	else
		return QString();
}

QString ReportQuery::getValue(int field)
{
	if (!EoF())
	{
		if ((field >= 0)&&(field < this->m_fcount))
			return m_codec->toUnicode(PQgetvalue(this->m_result, this->m_read_ptr, field));
		else
			return QString();
	}
	else
		return QString();
}

QStringList ReportQuery::getRow()
{
	QStringList ret;
	if (!EoF())
		for (int i = 0; i < this->m_fcount; i++)
			ret.append(m_codec->toUnicode(PQgetvalue(this->m_result, this->m_read_ptr, i)));
		this->m_read_ptr++;
	return ret;
}

QStringList ReportQuery::getFields()
{
	QStringList ret;
	for (int i = 0; i < m_fcount; i++)
		ret.append(m_codec->toUnicode(PQfname(this->m_result, i)));
	return ret;
}

int ReportQuery::absolutePosition()
{
	return this->m_read_ptr;
}

bool ReportQuery::BoF()
{
	return this->m_count == 0;
}

bool ReportQuery::EoF()
{
	return (this->m_read_ptr - this->m_count >= 0) || (this->m_read_ptr < 0);
}

void ReportQuery::moveFirst()
{
	this->m_read_ptr = 0;
}

void ReportQuery::moveLast()
{
	this->m_read_ptr = this->m_count - 1;
}

bool ReportQuery::moveNext()
{
	this->m_read_ptr++;
	return EoF();
}

bool ReportQuery::movePrev()
{
	this->m_read_ptr--;
	return EoF();
}

void ReportQuery::close()
{
	PQclear(this->m_result);
	//delete this->m_result;
}
