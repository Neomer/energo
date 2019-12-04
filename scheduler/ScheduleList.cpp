#include "ScheduleList.h"

ScheduleList::ScheduleList()
{
}

Schedule * ScheduleList::first()
{
	return m_list.at(0);
}

Schedule * ScheduleList::takeFirst()
{
	return m_list.takeAt(0);
}

void ScheduleList::clear()
{
	m_list.clear();
}

int ScheduleList::count()
{
	return m_list.count();
}

void ScheduleList::push(Schedule * item)
{
	int idx = 0;
	for (int i = 0; i < this->m_list.count(); i++)
	{
		if (this->m_list.at(i)->getStartTime() < item->getStartTime())
			idx = i + 1;
	}
	this->m_list.insert(idx, item);
}

void ScheduleList::onScheduleStart()
{
}
