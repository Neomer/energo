#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include "InstanceController.h"
#include "ScheduleList.h"

class Timer : public QObject
{
	Q_OBJECT
	
	public:
		Timer(InstanceController * instc, ScheduleList * schl);
	
	signals:
	
	public slots:
		void runTask();
	
	private:
		InstanceController * m_ic;
		ScheduleList * m_sl;
		QTimer * m_timer;
	
};

#endif // TIMER_H
