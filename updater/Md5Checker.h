#ifndef MD5CHECKER_H
#define MD5CHECKER_H

#include <QObject>
#include <QCryptographicHash>

class Md5Checker : public QObject
{
    Q_OBJECT
	
public:
	explicit Md5Checker(QObject *parent = 0);
	bool test(QString filename, QByteArray hash);

private:
	QCryptographicHash * _proc;
};

#endif // MD5CHECKER_H
