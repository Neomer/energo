#include "Timer.h"

Timer::Timer(InstanceController *instc, ScheduleList *schl) :
    QObject()
{
	this->m_ic = instc;
	this->m_sl = schl;
	this->m_timer = new QTimer();
	long secs = QDateTime::currentDateTime().secsTo(schl->first()->getStartTime());
	qDebug("Timer::Timer() - Process will be started through %ld sec(s)", secs);
	this->m_timer->singleShot(secs * 1000, this, SLOT(runTask()));
}

void Timer::runTask()
{
	/*
	Schedule * schedule = new Schedule(m_sl->first()), * next;
	QStringList args = schedule->cmdString();
	m_sl->takeFirst();
	do
	{
		next = new Schedule(m_sl->first());
		if (next->getStartTime() == schedule->getStartTime())
		{
			args.append(next->cmdString());
			m_sl->takeFirst();
			next->start();
			m_sl->push(next);			
		}
	}
	while (next->getStartTime() == schedule->getStartTime());
	qDebug("Timer::runTask() - Starting process recv.exe...");
	if (m_ic->start(args))
		qDebug("Timer::runTask() - Process is started successfully");
	else
		qDebug("Timer::runTask() - Process start is failed");
	schedule->start();
	m_sl->push(schedule);
	long secs = QDateTime::currentDateTime().secsTo(m_sl->first()->getStartTime());
	qDebug("Timer::Timer() - Process will be started through %ld sec(s)", secs);
	this->m_timer->singleShot(secs * 1000, this, SLOT(runTask()));
	*/
}
