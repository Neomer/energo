#ifndef INSTANCECONTROLLER_H
#define INSTANCECONTROLLER_H

#include <QString>
#include <QProcess>

class InstanceController : public QObject
{
	Q_OBJECT
		
	public:
		InstanceController();
		
		bool isRun();
		bool start(QStringList args);
		bool finish();
		QString getMsg();
		
	signals:
		void finished();
		void readyRead();
		
	private slots:
		void procReadyRead();
		
	private:
		QProcess * m_proc;
		
	private slots:
		void procFinished(int result);
};

#endif // INSTANCECONTROLLER_H
