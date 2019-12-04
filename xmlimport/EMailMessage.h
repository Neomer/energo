#ifndef EMAILMESSAGE_H
#define EMAILMESSAGE_H

#include <QString>
#include <QList>
#include <QMap>

class EMailMessage;

class EMailMessageHeader
{
	public:
		EMailMessageHeader();
		QString getValue(QString key);
		bool parse(QString text);
		
	private:
		QMap<QString, QString> _keys;
};

enum EMailBodyType
{
	BT_NONE,
	BT_HTML,
	BT_TEXT,
	BT_ATTACHMENT
};

class EMailBody
{
	public:
		EMailBody();
		EMailBodyType getType();
		bool parse(QString text);
		QByteArray getContent();
		QByteArray getContent(int index);
		EMailBody * getBody(EMailBodyType type);
		QString getHeader(QString name);
		QString getFileName();
		
	private:
		void setHeader(EMailMessageHeader * header);
		bool parseContent(QString text);
		QByteArray encryptContent(QString type, QString text);
		QString encryptString(QString text);
		EMailMessageHeader * _hdr;
		QByteArray _body;
		QList<EMailBody *> _subbody;
		EMailBodyType _type;
		
		friend class EMailMessage;
};

class EMailMessage
{
	public:
		EMailMessage();
		EMailMessage(QString message);
		
		bool parse(QString message);
		
		bool hasAttachments();
		int attachmentCount();
		
		EMailBody * getBody(int index);
		EMailBody * getBody(EMailBodyType type);
		EMailBody * getBody(EMailBodyType type, int shift);
		
	private:
		EMailMessageHeader * _hdr;
		QList<EMailBody *> _body;
};

#endif // EMAILMESSAGE_H
