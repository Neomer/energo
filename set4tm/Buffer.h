#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include <QByteArray>
#include "../recv/connection.h"

class Buffer
{
public:
	Buffer(Connection * connection, int maxlength);
	
	QByteArray readData(int length);
	
private:
	void appendData();
	Connection * m_conn;
	QByteArray ba;
	int m_maxlen;
};

#endif // BUFFER_H
