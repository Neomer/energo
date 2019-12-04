#include "XML80020.h"

XML80020::XML80020(QByteArray data)
{
	_xml = new QDomDocument();
	if (!(_parsed = _xml->setContent(data)))
	{
		qDebug("XML80020::XML80020() - XML parsing error!");
		return;
	}
	QDomNodeList nl;
	if ((nl = _xml->elementsByTagName("sender")).count() == 0)
	{
		qDebug("XML80020::XML80020() - XML wrong format! Missing SENDER tag.");
		_parsed = false;
		return;
	}
	_sender = nl.at(0);
	
	if ((nl = _xml->elementsByTagName("datetime")).count() == 0)
	{
		qDebug("XML80020::XML80020() - XML wrong format! Missing DATETIME tag.");
		_parsed = false;
		return;
	}
	_datetime = nl.at(0);
	nl = _xml->elementsByTagName("area");
	for (int i = 0; i < nl.count(); i++)
	{
		XML80020Area * area = new XML80020Area(nl.at(i));
		_data.append(area);
	}
	_data_ptr = 0;
}

bool XML80020::isValid()
{
	return _parsed;
}

QString XML80020::getSenderName()
{
	if (!_parsed)
		return "";
	
	for (int i = 0; i < _sender.childNodes().count(); i++)
	{
		QString tag = _sender.childNodes().at(i).toElement().tagName();
		if (tag == "name")
			return _sender.childNodes().at(i).toElement().text();
	}
	qDebug("XML80020::getSenderName() - Missing sender's name tag!");
	return "";
}

QString XML80020::getSenderID()
{
	if (!_parsed)
		return "";
	
	for (int i = 0; i < _sender.childNodes().count(); i++)
	{
		QString tag = _sender.childNodes().at(i).toElement().tagName();
		if (tag == "inn")
			return _sender.childNodes().at(i).toElement().text();
	}
	qDebug("XML80020::getSenderID() - Missing sender's identifier tag!");
	_parsed = false;
	return "";
}

QDate XML80020::getDate()
{
	if (!_parsed)
		return QDate::fromJulianDay(0);
	
	for (int i = 0; i < _datetime.childNodes().count(); i++)
	{
		QString tag = _datetime.childNodes().at(i).toElement().tagName();
		if (tag == "day")
			return QDate::fromString(_datetime.childNodes().at(i).toElement().text(), "yyyyMMdd");
	}
	qDebug("XML80020::getDate() - Missing package date tag!");
	_parsed = false;
	return QDate::fromJulianDay(0);
}

QDateTime XML80020::getGenerationDT()
{
	if (!_parsed)
		return QDateTime::fromTime_t(0);
	
	for (int i = 0; i < _datetime.childNodes().count(); i++)
	{
		QString tag = _datetime.childNodes().at(i).toElement().tagName();
		if (tag == "timestamp")
			return QDateTime::fromString(_datetime.childNodes().at(i).toElement().text(), "yyyyMMddhhmmss");
	}
	qDebug("XML80020::getGenerationDT() - Missing package creation date tag!");
	_parsed = false;
	return QDateTime::fromTime_t(0);
}

XML80020::XML80020DL XML80020::getDL()
{
	if (!_parsed)
		return DL_ERROR;
	
	for (int i = 0; i < _datetime.childNodes().count(); i++)
	{
		QString tag = _datetime.childNodes().at(i).toElement().tagName();
		if (tag == "daylightsavingtime")
			return (XML80020DL)_datetime.childNodes().at(i).toElement().text().toInt();
	}
	qDebug("XML80020::getDL() - Missing package daylightsavingtime tag!");
	_parsed = false;
	return DL_ERROR;
}

XML80020Area *XML80020::nextArea()
{
	if (_data.count() <= _data_ptr)
		return 0;
	
	return _data.at(_data_ptr++);
}

XML80020Area::XML80020Area(QDomNode node)
{
	_node = node;
	_parsed = true;
	for (int i = 0; i < _node.childNodes().count(); i++)
	{
		QString tag = _node.childNodes().at(i).toElement().tagName();
		if (tag == "measuringpoint")
			_points.append(new XML80020MeasuringPoint(_node.childNodes().at(i)));
	}
	_ptr = 0;
}

QString XML80020Area::getObjectID()
{
	if (!_parsed)
		return "";
	
	for (int i = 0; i < _node.childNodes().count(); i++)
	{
		QString tag = _node.childNodes().at(i).toElement().tagName();
		if (tag == "inn")
			return _node.childNodes().at(i).toElement().text();
	}
	qDebug("XML80020Area::getObjectID() - Missing area object ID tag!");
	_parsed = false;
	return "";
}

QString XML80020Area::getObjectName()
{
	if (!_parsed)
		return "";
	
	for (int i = 0; i < _node.childNodes().count(); i++)
	{
		QString tag = _node.childNodes().at(i).toElement().tagName();
		if (tag == "name")
			return _node.childNodes().at(i).toElement().text();
	}
	qDebug("XML80020Area::getObjectName() - Missing area object name tag!");
	return "";
}

XML80020MeasuringPoint *XML80020Area::nextPoint()
{
	if (_points.count() <= _ptr)
		return 0;
	
	return _points.at(_ptr++);
}

XML80020MeasuringPoint::XML80020MeasuringPoint(QDomNode node)
{
	_node = node;
	_parsed = true;
	for (int i = 0; i < _node.childNodes().count(); i++)
	{
		QString tag = _node.childNodes().at(i).toElement().tagName();
		if (tag == "measuringchannel")
			_points.append(new XML80020MeasuringChannel(_node.childNodes().at(i)));
	}
	_ptr = 0;
}

QString XML80020MeasuringPoint::getCode()
{
	if (!_parsed)
		return "";
	
	return _node.toElement().attribute("code");
	
	for (int i = 0; i < _node.attributes().count(); i++)
	{
		QDomNode n = _node.toElement().attributes().item(i);
		if (n.toElement().nodeName() == "code")
			return n.toElement().text();
	}
	qDebug("XML80020MeasuringPoint::getCode() - Missing measuring point code tag!");
	_parsed = false;
	return "";
}

QString XML80020MeasuringPoint::getName()
{
	if (!_parsed)
		return "";
	
	return _node.toElement().attribute("name");

	QDomNode n =_node.toElement().attributes().namedItem("name");
	if (!n.isNull())
		return n.toElement().text();
	else
	{
		qDebug("XML80020MeasuringPoint::getName() - Missing measuring point name tag!");
		return "";
	}
}

XML80020MeasuringChannel *XML80020MeasuringPoint::nextChannel(QString code)
{
	if (code.isEmpty())
	{
		if (_points.count() <= _ptr)
			return 0;

		return _points.at(_ptr++);
	}
	else
	{
		for (int i = 0; i < _points.count(); i++)
		{
			if (_points.at(i)->getCode().toInt() == code.toInt())
				return _points.at(i);
		}
		return 0;
	}
}

XML80020MeasuringChannel::XML80020MeasuringChannel(QDomNode node)
{
	_node = node;
	_parsed = true;
	for (int i = 0; i < _node.childNodes().count(); i++)
	{
		QString tag = _node.childNodes().at(i).toElement().tagName();
		if (tag == "period")
			_points.append(new XML80020MeasuringChannelData(_node.childNodes().at(i)));
	}
	_ptr = 0;
}

QString XML80020MeasuringChannel::getCode()
{
	if (!_parsed)
		return "";
	
	return _node.toElement().attribute("code");
}

QString XML80020MeasuringChannel::getDesc()
{
	if (!_parsed)
		return "";
	
	return _node.toElement().attribute("desc");
}

XML80020MeasuringChannelData *XML80020MeasuringChannel::nextPeriod()
{
	if (_points.count() <= _ptr)
		return 0;

	return _points.at(_ptr++);
}

XML80020MeasuringChannelData::XML80020MeasuringChannelData(QDomNode node)
{
	_node = node;
	_parsed = true;
    _time = 0;
}

QString XML80020MeasuringChannelData::getValue()
{
	if (!_parsed)
		return "";
	
	for (int i = 0; i < _node.childNodes().count(); i++)
	{
		QString tag = _node.childNodes().at(i).toElement().tagName();
		if (tag == "value")
			return _node.childNodes().at(i).toElement().text().replace(",", ".");
	}
	qDebug("XML80020MeasuringChannelData::getValue() - Missing value tag!");
	return "";
}

QTime XML80020MeasuringChannelData::getStartTime()
{
	if (!_parsed)
		return QTime();
	
	QString attr = _node.toElement().attribute("start");
	if (attr.isEmpty())
		return QTime();
	
	return ret = QTime::fromString(attr, "hhmm").addSecs(3600 * _time);
}

QTime XML80020MeasuringChannelData::getEndTime()
{
	if (!_parsed)
		return QTime();
	
	QString attr = _node.toElement().attribute("end");
	if (attr.isEmpty())
		return QTime();
	
	return QTime::fromString(attr, "hhmm").addSecs(3600 * _time);
}

int XML80020MeasuringChannelData::getInterval()
{
	if (!_parsed)
		return -1;
	
	QString attr = _node.toElement().attribute("start");
	if (attr.isEmpty())
		return -1;
	
	QTime time = QTime::fromString(attr, "hhmm");
	return (time.minute() * 60 + (time.hour() + _time) * 3600) / 1800;
}

bool XML80020MeasuringChannelData::isSummer()
{
	if (!_parsed)
		return "";
	
	for (int i = 0; i < _node.childNodes().count(); i++)
	{
		QString tag = _node.childNodes().at(i).toElement().tagName();
		if (tag == "value")
		{
			QString attr = _node.childNodes().at(i).toElement().attribute("summer", "1");
			return (bool)attr.toInt();
		}
	}
    return true;
}

void XML80020MeasuringChannelData::setTimeCorrection(int value)
{
    _time = value;
}

