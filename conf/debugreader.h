#ifndef DEBUGREADER_H
#define DEBUGREADER_H

#include <QIODevice>

class DebugReader : public QIODevice
{
    Q_OBJECT
		
	public:
		explicit DebugReader(QObject *parent = 0);

		qint64 readData(char *data, qint64 maxlen);
		qint64 writeData(const char *data, qint64 len);
	
	signals:
		void onReadyRead();

	public slots:

};

#endif // DEBUGREADER_H
