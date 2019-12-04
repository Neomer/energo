#include "FileReceiver.h"

FileReceiver::FileReceiver()
{
	_file = new QFile();
}

void FileReceiver::append(QByteArray data)
{
	if (_file->isOpen())
	{
		_file->write(data);
	}
}

void FileReceiver::close()
{
	_file->close();
	_file->rename(_filename.append(TEMP_EXTENSION), _filename);
}

void FileReceiver::open(QString filename)
{
	_filename = filename;
	_file->setFileName(filename.append(TEMP_EXTENSION));
	_file->open(QIODevice::WriteOnly);
}
