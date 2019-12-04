#ifndef ERRORLISTENER_H
#define ERRORLISTENER_H

#include <QIODevice>
#include <QFile>
#include <QThread>
#include <QByteArray>
#include <QProcess>

class ErrorListener : public QIODevice
{
    Q_OBJECT
	
public:
    explicit ErrorListener(QObject *parent = 0);
	qint64 readData(char *data, qint64 maxlen);
	qint64 writeData(const char *data, qint64 len);
	qint64 bytesAvailable();
	void run();

signals:

public slots:

protected:
	QFile *io;	
};

#endif // ERRORLISTENER_H
