#ifndef PGRESQLRESULT_H
#define PGRESQLRESULT_H

#include <QObject>
#include <QStringList>

#include "export.h"
#include "../includes/pgre/libpq-fe.h"
#include <QTextCodec>

#define PGRESQLRESULT_FAILED		-1

class PGRESQLDRV_SHARED_EXPORT PgreSqlResult : public QObject
{
	Q_OBJECT
	
	public:
		PgreSqlResult(QTextCodec * codec, PGresult * result);
		~PgreSqlResult();
		
		// ������� ��������� �������
		QStringList getFields();
		QString getFieldName(int index);
		int getFieldIndex(QString name);
		int getFieldIndex(const char * name);
		
		// ������� ��������� ��������
		QString getValue(int index, QString _default = "");
		QString getValue(QString field, QString _default = "");
		QString getValue(const char * field, QString _default = "");
		
		// �������� ���������� ����������
		bool isValid();
		bool hasRows();
		
		// ������� ���������
		bool moveTo(int index);
		bool moveNext();
		bool movePrev();
		bool moveFirst();
		bool moveLast();
		
		// ������ �������
		int absolutePos();
		bool eof();
		bool notEoF();
		int numRows();
		int numFields();
		void close();
		
	protected:
		QTextCodec * m_codec;
		PGresult * m_result;
		int m_rows;
		int m_fields;
		int m_reader;
};

#endif // PGRESQLRESULT_H
