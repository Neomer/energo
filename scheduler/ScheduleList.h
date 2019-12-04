#ifndef SCHEDULELIST_H
#define SCHEDULELIST_H

#include <QList>
#include "Schedule.h"

class ScheduleList : public QObject
{
	Q_OBJECT
	
	public:
		ScheduleList();
		
		Schedule * first();
		Schedule * takeFirst();
		void push(Schedule * item);
		void clear();
		
		int count();
		
	private slots:
		void onScheduleStart();
	
	private:
		QList<Schedule *> m_list;
};

#endif // SCHEDULELIST_H
