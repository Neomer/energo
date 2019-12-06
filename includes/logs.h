#ifndef LOGS_H
#define LOGS_H

#include <QFile>
#include <QTextEncoder>
#include <QDateTime>
#include <QThread>
#include <QDebug>

#ifndef ENERGO_LOG_FILE
#define ENERGO_LOG_FILE
static QFile log_file("c:/tmp.log");
static QTextCodec * dbcodec = QTextCodec::codecForName("UTF-8");
static QTextCodec * ibmcodec = QTextCodec::codecForName("IBM 866");
#endif

#ifndef ENERGO_HANDLER
#define ENERGO_HANDLER
class Helper: public QThread {
public:
    static void msleep(int ms)
    {
        QThread::msleep(ms);
    }
};

void LogMsgHandler(QtMsgType type, const char *msg)
{
	QFile stdfile;
	stdfile.open(stdout, QIODevice::WriteOnly);
	QDebug dbg= QDebug(&stdfile);
	if (!log_file.open(QIODevice::Append))
		printf("DEBUG: Log file is not open: %s\n", log_file.fileName().toAscii().constData());
    switch (type) {
		case QtDebugMsg:
#ifndef ENERGO_NO_DEBUG			
		//fprintf(stderr, "%s", msg);
#endif
			if (log_file.isOpen())
			{
				QString s = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz] ").append(msg);
				if (s.at(s.length() - 1) != '\n') s.append('\n');
				log_file.write(s.toAscii().constData(), s.length());
			}
			break;
			
		case QtWarningMsg:
			dbg << msg;
			Helper::msleep(10);
			//fprintf(stdout, "%s", msg);
			if (log_file.isOpen())
			{
				QString s = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz] ").append(msg);
				if (s.at(s.length() - 1) != '\n') s.append('\n');
				log_file.write(s.toAscii().constData(), s.length());
			}
			break;
			
		case QtCriticalMsg:
			//fprintf(stderr, "%s\n", msg);
			if (log_file.isOpen())
			{
				QString s = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz] ").append("CRITICAL: ").append(msg);
				if (s.at(s.length() - 1) != '\n') s.append('\n');
				log_file.write(s.toAscii().constData(), s.length());
			}
			break;
			
		case QtFatalMsg:
			//fprintf(stderr, "%s\n", msg);
			if (log_file.isOpen())
			{
				QString s = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz] ").append("FATAL: ").append(msg);
				s.append(msg).append("\r\n");
				log_file.write(s.toAscii().constData(), s.length());
			}
			break;
    }
	log_file.close();
}
#endif

#endif // LOGS_H
