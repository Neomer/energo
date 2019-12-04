#include "Schedule.h"
#include <QMessageBox>

#define ENERGO_SCHDL_OBJECT		"-o=%1"
#define ENERGO_SCHDL_FEEDER		"-f=%1"
#define ENERGO_SCHDL_COUNTER	"-c=%1"

Schedule::Schedule(QTreeWidgetItem *node, QObject *parent)
	:	QObject(parent)
{
	this->m_start = QDateTime::fromMSecsSinceEpoch(0);
	this->m_shift = 0;
	this->m_periodicity = 1440;
	_inst = new InstanceController();
	connect(_inst, SIGNAL(readyRead()), this, SIGNAL(messageReceived()));
	_node = node;
	_tmr = new QTimer(this);
	_log = QString();
}

Schedule::Schedule(QTreeWidgetItem * node, Schedule *other, QObject *parent)
	:	QObject(parent)
{
	this->m_name = other->m_name;
	this->m_obj = other->m_obj;
	this->m_periodicity = other->m_periodicity;
	this->m_start = other->m_start;
	this->m_shift = other->m_shift;
	_inst = new InstanceController();
	connect(_inst, SIGNAL(readyRead()), this, SIGNAL(messageReceived()));
	_node = node;
	_tmr = new QTimer(this);
	_log = QString();
}

void Schedule::setName(QString name)
{
	this->m_name = name;
}

QString Schedule::name()
{
	return m_name;
}

void Schedule::setPeriodicity(int period)
{
	this->m_periodicity = period;
	QDateTime today = QDateTime::currentDateTime();
	today = today.addSecs(-1 * (today.time().hour() * 3600 + today.time().minute() * 60 + today.time().second()));
	int min_left = (int)today.secsTo(QDateTime::currentDateTime()) / 60;
	m_start = today.addSecs(((((int)min_left / m_periodicity) + 1) * m_periodicity) * 60 + m_shift);

	_tmr->stop();
	long secs = QDateTime::currentDateTime().secsTo(getStartTime());
	//_tmr->singleShot(secs * 1000, this, SLOT(start()));
}

int Schedule::periodicity()
{
	return this->m_periodicity;
}

QDateTime Schedule::getStartTime()
{
	return m_start;
}

bool Schedule::start()
{
	if (_inst->isRun())
		if (!_inst->finish())
			return false;
	
	if (!_inst->start(cmdString()))
		return false;
	_log = QString();
	m_last_start = QDateTime::currentDateTime();

	m_start = this->m_start.addSecs(m_periodicity * 60);
	emit started();
	connect(_inst, SIGNAL(finished()), this, SIGNAL(finished()));
	
	long secs = QDateTime::currentDateTime().secsTo(getStartTime());
	_tmr->singleShot(secs * 1000, this, SLOT(start()));

	return true;
}

bool Schedule::startManual()
{
	if (isRun())
		return false;

	if (!_inst->start(cmdString()))
		return false;

	_log = QString();
	m_last_start = QDateTime::currentDateTime();

	emit started();
	connect(_inst, SIGNAL(finished()), this, SIGNAL(finished()));
	return true;
}

bool Schedule::startManual(int id, TreeElement type)
{
	if (isRun())
		return false;
	
	QStringList ret;
	switch (type)
	{
		case TE_Object:
			if (!m_obj.contains(id)) 
				return false;
			
			ret.append(QString(ENERGO_SCHDL_OBJECT).arg(QString::number(id)));
			if (!_inst->start(ret))
				return false;
			break;
			
		case TE_Factory:
			return false;
			break;
	}
	m_last_start = QDateTime::currentDateTime();
	emit started();
	connect(_inst, SIGNAL(finished()), this, SIGNAL(finished()));
}

bool Schedule::stop()
{
	if (isRun())
		return _inst->finish();
	
	return true;
}

QDateTime Schedule::lastStart()
{
	return m_last_start;
}

QString Schedule::getMessage()
{
	return _inst->getMsg();
}

bool Schedule::isRun()
{
	return _inst->isRun();
}

void Schedule::setObjects(QList<int> objects)
{
	this->m_obj = objects;
}

void Schedule::appendObject(int object)
{
	m_obj.append(object);
}

QStringList Schedule::cmdString()
{
	QStringList ret;
	
	for (int i = 0; i < m_obj.count(); i++)
		ret.append(QString(ENERGO_SCHDL_OBJECT).arg(QString::number(m_obj.at(i))));
	return ret;
}

QTreeWidgetItem *Schedule::node()
{
	return _node;
}

int Schedule::shift()
{
	return m_shift;
}

void Schedule::setShift(int shift)
{
	m_start.addSecs(-1 * m_shift);
	m_shift = shift;
	m_start = m_start.addSecs(shift);

	_tmr->stop();
	long secs = QDateTime::currentDateTime().secsTo(getStartTime());
	_tmr->singleShot(secs * 1000, this, SLOT(start()));
}
