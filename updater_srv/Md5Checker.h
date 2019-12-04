#ifndef MD5CHECKER_H
#define MD5CHECKER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QCryptographicHash>

#define HASH_SIZE		16
#define MAX_FILE_NAME	256

class Md5Checker : public QObject
{
    Q_OBJECT
	
	public:
		explicit Md5Checker(QObject *parent = 0);
		QByteArray getHash();
		QString getName();
		QByteArray getFile();
		QByteArray getNextHash();
		QByteArray getFileChunk(int size);
		bool next();
	
	private:
		QDir _dir;
		QStringList _files;
		QFile * _file;
		QCryptographicHash * _hashproc;
		int _ptr, _read_ptr;
};

#endif // MD5CHECKER_H
