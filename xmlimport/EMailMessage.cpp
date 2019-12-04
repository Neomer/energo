#include "EMailMessage.h"
#include <QStringList>
#include <QTextCodec>

inline QByteArray fromQuotedPrintable(QString text)
{
	text = text.replace("=\r\n", "");
	int pos;
	while ((pos = text.indexOf(QRegExp("=[A-F0-9]{2}"))) != -1)
	{
		QString part = text.mid(pos, 3);
		int hex = part.right(2).toInt(0, 16);
		text = text.replace(part, QString::fromLatin1((const char *)&hex, 1));
	}
	return text.toAscii();
}



EMailMessageHeader::EMailMessageHeader()
{
	
}

bool EMailMessageHeader::parse(QString text)
{
	int end = text.indexOf("\r\n\r\n"),
		ptr = 0, ptr1 = 0;
	if (end == -1) end = text.length();
	
	QString line, tmp;
	while ((ptr = text.indexOf("\r\n", ptr1)) != -1)
	{
		tmp = text.mid(ptr1, ptr - ptr1);
		if (tmp == "") tmp = " ";
		if (tmp.at(0) != '\t')
		{
			if (line != "")
			{
				qDebug("%s", line.toAscii().constData());
				int sep = line.indexOf(':');
				_keys.insert(line.left(sep).toUpper(), line.right(line.length() - sep - 1));
			}
			line = tmp;
			tmp = "";
		}
		else
		{
			line.append(tmp.right(tmp.length() - 1));
			tmp = "";
		}
		ptr1 = ptr + 2;
		if (ptr >= end) 
		{
			line.append(tmp);
			if (line != "")
			{
				qDebug("%s", line.toAscii().constData());
				int sep = line.indexOf(':');
				_keys.insert(line.left(sep).toUpper(), line.right(line.length() - sep - 1).trimmed());
			}
			break;
		}
	}
	return true;
}

QString EMailMessageHeader::getValue(QString key)
{
	key = key.toUpper();
	if (!_keys.contains(key))
		return "";
	
	return _keys[key];
}

EMailBody::EMailBody()
{
	_type = BT_NONE;
	_hdr = 0;
}

EMailBodyType EMailBody::getType()
{
	return _type;
}

void EMailBody::setHeader(EMailMessageHeader *header)
{
	_hdr = header;
}

bool EMailBody::parseContent(QString text)
{
	return true;
}

bool EMailBody::parse(QString text)
{
	if (!_hdr)
	{
		_hdr = new EMailMessageHeader();
		if (!_hdr->parse(text)) return false;
		text = text.mid(text.indexOf("\r\n\r\n") + 4);
	}
	
	QString ctype = _hdr->getValue("Content-Type");
	
	if (ctype.indexOf("multipart/mixed") != -1)
	{
		_type = BT_NONE;
	}
	else if (ctype.indexOf("multipart/alternative") != -1)
	{
		if (text.indexOf("This is a multi-part message in MIME format.") == 0)
		{
			text = text.mid(text.indexOf("\r\n\r\n") + 4);
		}
		_type = BT_NONE;
		int bpos = ctype.indexOf("boundary=");
		QString boundary = ctype.mid(bpos + 10, ctype.length() - bpos - 11).append("\r\n");
		
		QStringList bodies = text.split(boundary, QString::SkipEmptyParts);
		
		for (int i = 1; i < bodies.count(); i++)
		{
			EMailBody * body = new EMailBody();
			if (body->parse(bodies.at(i)))
				_subbody.append(body);
		}
	}
	else
	{
		if (ctype.indexOf("text/html") >= 0)
			_type = BT_HTML;
		else if (ctype.indexOf("text/plain") >= 0)
			_type = BT_TEXT;
		else if (ctype.indexOf("application/octet-stream") >= 0)
			_type = BT_ATTACHMENT;
		else
			_type = BT_NONE;
			
		QString cte = "";
		int codecpos = ctype.indexOf("charset="),
				endcodec = ctype.indexOf(";", codecpos);
		if (endcodec == -1)
			endcodec = ctype.length();
		QString codecname = ctype.mid(codecpos + 8, endcodec - codecpos - 8).replace("\"", "");
		QTextCodec * codec = QTextCodec::codecForTr();
		if (codecpos != -1)
			codec = QTextCodec::codecForName(codecname.toAscii().constData());
		
		if (!codec)
			codec = QTextCodec::codecForTr();
		
		if ((cte = _hdr->getValue("Content-Transfer-Encoding")) != "")
			_body = codec->toUnicode(encryptContent(cte, text)).toAscii();
		else
			_body = text.toAscii();
		
	}
	return true;
}

QByteArray EMailBody::getContent()
{
	return _body;
}

QByteArray EMailBody::getContent(int index)
{
	return _subbody.at(index)->getContent();
}

EMailBody *EMailBody::getBody(EMailBodyType type)
{
	for (int i = 0; i < _subbody.count(); i++)
	{
		if (_subbody.at(i)->getType() == type)
			return _subbody.takeAt(i);
	}
	return 0;
}

QString EMailBody::getFileName()
{
	if (_type != BT_ATTACHMENT)
		return QString();
	
	QRegExp re("filename=\".{1,}\"");
	
	if (re.indexIn(_hdr->getValue("Content-Disposition")) == -1)
		return QString();
	
	QString filename = re.capturedTexts().at(0);
	
	return this->encryptString(filename);
	
}


QByteArray EMailBody::encryptContent(QString type, QString text)
{
	type = type.toUpper().trimmed();
	if (type == "8BIT")
	{
		return text.toAscii();
	}
	else if (type == "8BIT")
	{
		return text.toAscii();
	}
	else if (type == "QUOTED-PRINTABLE")
	{
		text = text.replace("=\r\n", "");
		int pos;
		while ((pos = text.indexOf(QRegExp("=[A-F0-9]{2}"))) != -1)
		{
			QString part = text.mid(pos, 3);
			int hex = part.right(2).toInt(0, 16);
			text = text.replace(part, QString::fromLatin1((const char *)&hex, 1));
		}
		return text.toAscii();
	}
	else if (type == "BASE64")
	{
		return QByteArray::fromBase64(text.toAscii());
	}
	else 
	{
		return text.toAscii();
	}
}

QString EMailBody::encryptString(QString text)
{
	QString ret;
	QRegExp relines("=\?.*\?="); // Выбор всех строк для декодировки
	relines.setMinimal(true);
	relines.indexIn(text);
	for (int i = 0; i < relines.capturedTexts().count(); i++)
	{
		QString line = relines.capturedTexts().at(i);
		QStringList lineparts = line.split('?');
		if (lineparts.count() < 4)
			continue;
		QTextCodec * codec = QTextCodec::codecForName(lineparts.at(1).toAscii().constData());
		if (!codec)
			codec = QTextCodec::codecForTr();
		if (lineparts.at(2) == "B")
		{
			ret.append(QByteArray::fromBase64(lineparts.at(3).toAscii()));
		}
		else if (lineparts.at(2) == "Q")
		{
			ret.append(fromQuotedPrintable(lineparts.at(3)));
		}
	}
	return ret;
}

EMailMessage::EMailMessage()
{
	_hdr = 0;
}

EMailMessage::EMailMessage(QString message)
{
	_hdr = 0;
	parse(message);
}

bool EMailMessage::parse(QString message)
{
	if (_hdr) delete _hdr;
	_hdr = new EMailMessageHeader();
	if (!_hdr->parse(message))
		return false;
	
	message = message.mid(message.indexOf("\r\n\r\n") + 4);
	
	QString ctype = _hdr->getValue("Content-Type");
	if ((ctype.indexOf("multipart/mixed") != -1)||(ctype.indexOf("multipart/alternative") != -1))
	{
		int bpos = ctype.indexOf("boundary=");
		QString boundary = ctype.mid(bpos + 10, ctype.length() - bpos - 11).append("\r\n");
		
		QStringList bodies = message.split(boundary, QString::SkipEmptyParts);
		
		for (int i = 1; i < bodies.count(); i++)
		{
			EMailBody * body = new EMailBody();
			if (body->parse(bodies.at(i)))
				_body.append(body);
		}
	}
	else
	{
		EMailBody * body = new EMailBody();
		body->setHeader(_hdr);
		if (!body->parse(message))
			return false;
		_body.append(body);
	}
	return true;
}

EMailBody * EMailMessage::getBody(EMailBodyType type)
{
	for (int i = 0; i < _body.count(); i++)
	{
		if (_body.at(i)->getType() == type)
			return _body.takeAt(i);
		EMailBody * ret = _body.at(i)->getBody(type);
		if (ret)
			return ret;
	}
	return 0;
}

