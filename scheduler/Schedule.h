#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QString>
#include <QDateTime>
#include <QList>
#include <QStringList>
#include "InstanceController.h"
#include <QTreeWidgetItem>
#include "QTimer.h"
#include "global.h"

class Schedule : public QObject
{
	Q_OBJECT
		
	public:
		Schedule(QTreeWidgetItem * node, QObject * parent = 0);
		Schedule(QTreeWidgetItem * node, Schedule * other, QObject * parent = 0);
		
		void setName(QString name);
		QString name();
		
		void setPeriodicity(int period);
		int periodicity();
		
		void setShift(int shift);
		int shift();
		
		QDateTime getStartTime();
		
		void setObjects(QList<int> objects);
		void appendObject(int object);
		
		QStringList cmdString();
		
		QTreeWidgetItem * node();
		
		void merge(Schedule * value);
		bool startManual();
		bool startManual(int id, TreeElement type);
		bool stop();
		QDateTime lastStart();

		QString getMessage();
		//QString getLog();
		
		bool isRun();

	public slots:
		bool start();
		
	signals:
		void started();
		void finished();
		void messageReceived();
		
	private:
		int m_id;
		QString m_name;
		QDateTime m_start, m_last_start;
		int m_periodicity;
		int m_shift;
		QList<int> m_obj;
		InstanceController * _inst;
		QTreeWidgetItem * _node;
		QTimer * _tmr;
		QString _log;
};

#endif // SCHEDULE_H
