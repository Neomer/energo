#include "InstanceController.h"
#include <QApplication>

InstanceController::InstanceController()
{
	m_proc = new QProcess(qApp);
	m_proc->setProcessChannelMode(QProcess::MergedChannels);
	m_proc->setReadChannel(QProcess::StandardOutput);
	connect(m_proc, SIGNAL(finished(int)), this, SLOT(procFinished(int)));
	connect(m_proc, SIGNAL(readyRead()), this, SLOT(procReadyRead()));
	//connect(m_proc, SIGNAL(readyReadStandardOutput()), this, SLOT(procReadyRead()));
	//connect(m_proc, SIGNAL(readyReadStandardError()), this, SLOT(procReadyRead()));
}

bool InstanceController::isRun()
{
	return m_proc->state() == QProcess::Running;
}

bool InstanceController::start(QStringList args)
{
	if (isRun()) return false;

	m_proc->start("recv.exe", args);
	
	return m_proc->waitForStarted(5000);
}

bool InstanceController::finish()
{
	m_proc->kill();
	return m_proc->waitForFinished(5000);
}

QString InstanceController::getMsg()
{
	int len = m_proc->bytesAvailable();
	if (len == 0)
		return "";
	char buf[len];
	m_proc->read(buf, len);
	buf[len] = 0;
	return QString(buf);
}

void InstanceController::procFinished(int result)
{
	emit finished();
}

void InstanceController::procReadyRead()
{
	emit readyRead();
}
