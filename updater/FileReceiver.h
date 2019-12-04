#ifndef FILERECEIVER_H
#define FILERECEIVER_H

#include <QFile>

#define TEMP_EXTENSION		".tmp"

class FileReceiver
{
	public:
		FileReceiver();
		void open(QString filename);
		void append(QByteArray data);
		void close();
		
	private:
		QFile * _file;
		QString _filename;
};

#endif // FILERECEIVER_H
