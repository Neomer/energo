#ifndef ORASQLRESULT_H
#define ORASQLRESULT_H

#define OCI_CHARSET_ANSI
#define OCI_API __stdcall

#include "oradrv_global.h"
#include <QTextCodec>
#include "../includes/oracle/ocilib.h"

class ORADRVSHARED_EXPORT OraSqlResult
{
	public:
		OraSqlResult(QTextCodec * codec, OCI_Statement * result);
		OraSqlResult(QTextCodec *codec);
		
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
		
		
	private:
		OCI_Statement * _st;
		OCI_Resultset * _rs;
		QTextCodec * _codec;
		bool _is_eof;
		long _pos;
};

#endif // ORASQLRESULT_H
