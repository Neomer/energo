#include "PgreSqlResult.h"

bool between(int value, int v1, int v2)
{
	return (value >= v1) && (value <= v2);
}

PgreSqlResult::PgreSqlResult(QTextCodec * codec, PGresult *result)
{
	this->m_result = result;
	this->m_codec = codec;
	if (isValid())
	{
		this->m_rows = PQntuples(result);
		this->m_fields = PQnfields(result);
		this->m_reader = 0;
	}
	else
		this->m_reader = PGRESQLRESULT_FAILED;		
}

PgreSqlResult::~PgreSqlResult()
{
	
}

bool PgreSqlResult::isValid()
{
	return PQresultStatus(this->m_result) != PGRES_FATAL_ERROR;
}

int PgreSqlResult::getFieldIndex(QString name)
{
	return getFieldIndex(this->m_codec->fromUnicode(name).constData());
}

int PgreSqlResult::getFieldIndex(const char *name)
{
	if (!isValid()) return -1;
	return PQfnumber(this->m_result, name);
}

QString PgreSqlResult::getFieldName(int index)
{
	if (!isValid()) return QObject::tr("");
	if ((index >= 0)&&(index < this->m_fields)) 
		return m_codec->toUnicode(PQfname(this->m_result, index));
	return QObject::tr("");
}

QStringList PgreSqlResult::getFields()
{
	QStringList ret;
	
	for (int i = 0; i < this->m_fields; i++)
		ret.append(m_codec->toUnicode(PQfname(this->m_result, i)));
	
	return ret;
}

QString PgreSqlResult::getValue(const char *field, QString _default)
{
	int nf = getFieldIndex(field);
	if (nf == -1) return _default;
	return m_codec->toUnicode(PQgetvalue(this->m_result, m_reader, nf));
}

QString PgreSqlResult::getValue(int index, QString _default)
{
	if (!isValid()) return _default;
	if ((index < 0)||(index >= m_fields)) return _default;
	return m_codec->toUnicode(PQgetvalue(this->m_result, m_reader, index));
}

QString PgreSqlResult::getValue(QString field, QString _default)
{
	int nf = getFieldIndex(field);
	if (nf == -1) return _default;
	return m_codec->toUnicode(PQgetvalue(this->m_result, m_reader, nf));
}

bool PgreSqlResult::moveTo(int index)
{
	if (!isValid()) return false;
	if ((index >= 0)&&(index < this->m_rows))
		this->m_reader = index;
	else
		return false;
	return true;
}

bool PgreSqlResult::moveNext()
{
	if (!isValid()) return false;
	if (this->m_reader < this->m_rows)
		this->m_reader++;
	else
		return false;
	return true;
}

bool PgreSqlResult::movePrev()
{
	if (!isValid()) return false;
	if (this->m_reader > 0)
		this->m_reader--;
	else
		return false;
	return true;
}

bool PgreSqlResult::moveFirst()
{
	if (!isValid()) return false;
	this->m_reader = 0;
	return true;
}

bool PgreSqlResult::moveLast()
{
	if (!isValid()) return false;
	this->m_reader = this->m_rows - 1;
	if (this->m_reader < 0) this->m_reader = 0;
	return true;
}

int PgreSqlResult::absolutePos()
{
	return this->m_reader;
}

bool PgreSqlResult::eof()
{
	return (this->m_reader >= this->m_rows)||(this->m_reader == PGRESQLRESULT_FAILED);
}

bool PgreSqlResult::notEoF()
{
	return (this->m_reader < this->m_rows)&&(this->m_reader != PGRESQLRESULT_FAILED);
}

int PgreSqlResult::numFields()
{
	return this->m_fields;
}

int PgreSqlResult::numRows()
{
	return this->m_rows;
}

bool PgreSqlResult::hasRows()
{
	return this->m_rows > 0;
}

void PgreSqlResult::close()
{
	PQclear(this->m_result);
}
