#include "Md5Checker.h"
#include <QtCore/QCoreApplication>

Md5Checker::Md5Checker(QObject *parent) :
    QObject(parent)
{
	_hashproc = new QCryptographicHash(QCryptographicHash::Md5);
	_dir.setPath(QDir::currentPath());
	_files = _dir.entryList(QDir::Files);
	_ptr = 0;
	_file = new QFile(_dir.absolutePath().append("\\").append(_files.at(_ptr)));
	QFile * exc = new QFile("exceptions.upd");
	if (exc->open(QIODevice::ReadOnly))
	{
		while (!exc->atEnd())
		{
			QString line = exc->readLine().replace('\n', "").replace('\r', "");
			qDebug("Md5Checker::Md5Checker() - remove file %s",
				   line.toAscii().constData());
			_files.removeOne(line);
		}
	}
	qDebug("Md5Checker::Md5Checker() - %d files queued", _files.length());
}

QByteArray Md5Checker::getFile()
{
	if (_file->open(QIODevice::ReadOnly))
		return _file->readAll();
	else
		return QByteArray();
}

QByteArray Md5Checker::getFileChunk(int size)
{
	QByteArray ret;
	if (_file->open(QIODevice::ReadOnly))
	{
		ret = _file->read(size);
		_read_ptr += ret.size();
		_file->close();
	}
	else
	{
		ret = QByteArray();
	}
	return ret;
}

QByteArray Md5Checker::getHash()
{
	QByteArray ret;
	if (_file->open(QIODevice::ReadOnly))
	{
		ret = _hashproc->hash(_file->readAll(), QCryptographicHash::Md5);
		_file->close();
	}
	else
	{
		ret = QByteArray();
	}
	return ret;
}

QString Md5Checker::getName()
{
	return _files.at(_ptr);
}

bool Md5Checker::next()
{
	if (_file->isOpen()) _file->close();
	if (_ptr < _files.size() - 1) 
	{
		_ptr++;
	}
	else
		return false;
	_file = new QFile(_dir.absolutePath().append("\\").append(_files.at(_ptr)));
	_read_ptr = 0;
	return true;
}

QByteArray Md5Checker::getNextHash()
{
	next();
	return getHash();
}
