#ifndef REPORTQUERY_H
#define REPORTQUERY_H

#include <QString>
#include <QStringList>
#include <QtXml/QDomElement>
#include <QTextCodec>

#include "../includes/pgre/libpq-fe.h"

class ReportQuery
{
public:
	ReportQuery(PGconn * connection);
    ReportQuery(PGconn * connection, QDomElement query);
	
	bool setQuery(QDomElement query);
	bool setQuery(QString query);
	
	int getNumRows();
	int getNumFields();
	QString getName();
	int absolutePosition();

	QString getValue(QString field);
	QString getValue(int field);
	QStringList getRow();
	QStringList getFields();
	
	bool EoF();
	bool BoF();
	bool moveNext();
	bool movePrev();
	void moveFirst();
	void moveLast();
	
	void close();
	
private:
	QString m_name;
	QDomElement m_query;
	PGconn * m_conn;
	PGresult * m_result;
	QTextCodec * m_codec;
	int m_read_ptr;
	int m_count;
	int m_fcount;
};

#endif // REPORTQUERY_H
