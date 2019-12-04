#include "debugreader.h"

DebugReader::DebugReader(QObject *parent) :
    QIODevice(parent)
{
	
}

qint64 DebugReader::readData(char *data, qint64 maxlen)
{
	emit onReadyRead();
}

qint64 DebugReader::writeData(const char *data, qint64 len)
{
	emit onReadyRead();
}
