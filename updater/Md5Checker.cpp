#include "Md5Checker.h"
#include <QFile>
#include <QDir>

Md5Checker::Md5Checker(QObject *parent) :
    QObject(parent)
{
	_proc = new QCryptographicHash(QCryptographicHash::Md5);
}

bool Md5Checker::test(QString filename, QByteArray hash)
{
	QFile * f = new QFile(filename);
	if (!f->open(QIODevice::ReadOnly))
		return false;
	return _proc->hash(f->readAll(), QCryptographicHash::Md5) == hash;
}
