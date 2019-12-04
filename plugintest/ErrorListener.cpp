#include "ErrorListener.h"

ErrorListener::ErrorListener(QObject *parent) :
    QIODevice(parent)
{
	this->open(QIODevice::ReadWrite);
}

qint64 ErrorListener::readData(char *data, qint64 maxlen)
{
	printf("ErrorListener::writeData() - Ready read\n");
	data = "rerere";
	return 6;
}

qint64 ErrorListener::writeData(const char *data, qint64 len)
{
	printf("ErrorListener::writeData() - Ready write\n");
	//emit readyRead();
	printf("ErrorListener::writeData() - %s\n", data);
	return len;
}

qint64 ErrorListener::bytesAvailable()
{
	return 6;
}

void ErrorListener::run()
{
	printf("ErrorListener::run() - Start loop\n");
	
	char c;
	while (true)
	{
		io->getChar(&c);
		if (c)
		{
			printf("ErrorListener::run() - Found data in STDERR");
			QByteArray s = io->readLine();
			printf("ErrorListener::run() - Received %s\n", s.constData());
		}
	}
}
