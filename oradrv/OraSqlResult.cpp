#include "OraSqlResult.h"
#include <QStringList>
#include <QDateTime>

OraSqlResult::OraSqlResult(QTextCodec *codec)
{
	_codec = codec;
	_st = 0;
	_rs = 0;
	_is_eof = true;
	_pos = -1;
}

OraSqlResult::OraSqlResult(QTextCodec *codec, OCI_Statement *result)
{
	_codec = codec;
	_st = result;
	_rs = OCI_GetResultset(_st);
	_is_eof = !OCI_FetchNext(_rs);
	_pos = 0;
}

// Функции обработки колонок
QStringList OraSqlResult::getFields()
{
	QStringList sl;
	if (!_rs) return sl;
	for (int i = 0; i < OCI_GetColumnCount(_rs); i++)
	{
		sl.append(OCI_ColumnGetName(OCI_GetColumn(_rs, i)));
	}
	return sl;
}

QString OraSqlResult::getFieldName(int index)
{
	if (!_rs) return "";
	return OCI_ColumnGetName(OCI_GetColumn(_rs, index));
}

int OraSqlResult::getFieldIndex(QString name)
{
	if (!_rs) return -1;
	return getFieldIndex(name.toAscii().constData()) - 1;
}

int OraSqlResult::getFieldIndex(const char * name)
{
	if (!_rs) return -1;
	return (int)OCI_GetColumnIndex(_rs, name);
}


// Функции получения значений
QString OraSqlResult::getValue(int index, QString _default)
{
	QString ret = "1234566780123";
	time_t * t = new time_t();
	tm * _t = new tm();
	QDateTime dt;
	if (!_rs) return "";
	
	index++;
	qDebug("OraSqlResult::getValue() - Get value from column %d type %d length %d\n", 
		   index,
		   OCI_GetColumnType(OCI_GetColumn(_rs, index)),
		   OCI_GetDataLength(_rs, index));
	
	switch (OCI_GetColumnType(OCI_GetColumn(_rs, index)))
	{
		case OCI_CDT_NUMERIC:
			if (OCI_IsNull(_rs, index))
				ret = "0";
			else
				ret = QString::number(OCI_GetDouble(_rs, index));
			break;
			
		case OCI_CDT_DATETIME:
			OCI_DateToCTime(OCI_GetDate(_rs, index), _t, t);
			dt = QDateTime::fromTime_t(*t);
			ret = dt.toString("yyyy-MM-dd hh:mm:ss");
			break;
			
		case OCI_CDT_TEXT:
			if (OCI_IsNull(_rs, index))
				ret = "";
			else
				ret = QString(OCI_GetString(_rs, index));
			break;
			
		case OCI_CDT_TIMESTAMP:
			if (OCI_IsNull(_rs, index))
				ret = QDateTime::fromTime_t(0).toString("yyyy-MM-dd hh:mm:ss");
			else
			{
				OCI_TimestampToCTime(OCI_GetTimestamp(_rs, index), 0, t);
				ret = QDateTime::fromTime_t(*t).toString("yyyy-MM-dd hh:mm:ss");
			}
			break;
			
		//case OCI_CDT
	}
	qDebug("OraSqlResult::getValue() - Returned: %s\n",
		   ret.toAscii().constData());
	//delete t;
	//delete _t;
	return ret;
}

QString OraSqlResult::getValue(QString field, QString _default)
{
	return getValue(getFieldIndex(field) - 1, _default);
}

QString OraSqlResult::getValue(const char * field, QString _default)
{
	return getValue(getFieldIndex(field) - 1, _default);
}

// Проверка валидности результата
bool OraSqlResult::isValid()
{
	if ((!_rs)||(!_st)) return false;
	return _st != 0;
}

bool OraSqlResult::hasRows()
{
	if ((!_rs)||(!_st)) return false;
	if (_pos != 0)
		return true;
	
	return !_is_eof;
}

// Функции навигации
bool OraSqlResult::moveTo(int index)
{
	if ((!_rs)||(!_st)) return false;
	if (index < _pos) return false;
	while ((OCI_FetchNext(_rs))&&(index--));
	return false;
}

bool OraSqlResult::moveNext()
{
	if ((!_rs)||(!_st)) return false;
	_pos++;
	_is_eof = !OCI_FetchNext(_rs);
	return !_is_eof;
}

bool OraSqlResult::movePrev()
{
	return false;
}

bool OraSqlResult::moveFirst()
{
	return false;
}

bool OraSqlResult::moveLast()
{
	return false;
}

// Прочие функции
int OraSqlResult::absolutePos()
{
	return _pos;
}

bool OraSqlResult::eof()
{
	return _is_eof;
}

bool OraSqlResult::notEoF()
{
	return !_is_eof;
}

int OraSqlResult::numRows()
{
	return -1;
}

int OraSqlResult::numFields()
{
	if ((!_rs)||(!_st)) return 0;
	return OCI_GetColumnCount(_rs);
}

void OraSqlResult::close()
{
	if ((!_rs)||(!_st)) return;
	OCI_ReleaseResultsets(_st);
	OCI_StatementFree(_st);
}

