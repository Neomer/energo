#include "Buffer.h"

Buffer::Buffer(Connection *connection, int len)
{
	this->m_conn = connection;
	this->m_maxlen = len;
}

QByteArray Buffer::readData(int length)
{
	while (this->ba.size() < length)
	{
		this->appendData();
	}
}

void Buffer::appendData()
{
}
