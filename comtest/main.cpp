#include <QtCore/QCoreApplication>
#include <QPluginLoader>
#include <QDir>
#include <QDateTime>

#include "../qextserialport/src/qextserialport.h"
#include "../GSMConnection/GSMConnectionInterface.h"
#include "../set4tm/Set4tmInterface.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	PortSettings set;
	set.BaudRate = BAUD9600;
	set.DataBits = DATA_8;
	set.FlowControl = FLOW_HARDWARE;
	set.Parity = PAR_NONE;
	set.StopBits = STOP_1;
	set.Timeout_Millisec = 2000;
	QByteArray ret_a;
	QString ret;

	QDir dir(a.applicationDirPath());
	QPluginLoader pl(dir.absoluteFilePath("GSMConnection.dll")), 
	        plset(dir.absoluteFilePath("set4tmplugin.dll"));
	GSMConnectionInterface * c;
	Set4tmInterface *set4tm;
	
	if (pl.instance())
	{
		qDebug("Main() - GSM plugin sucessfully loaded!");
		c = qobject_cast<GSMConnectionInterface *>(pl.instance());
	}
	else
	{
		qDebug("Main() - Can't load GSM plugin!");
		return a.exec();
	}
	
	if (plset.instance())
	{
		qDebug("Main() - Set4tm plugin sucessfully loaded!");
		set4tm = qobject_cast<Set4tmInterface *>(plset.instance());
	}
	else
	{
		qDebug("Main() - Can't load Set4tm plugin!");
		return a.exec();
	}
	
	
	c->Create("COM1", set);
	if (c->getStatus() == GCS_ERROR)
	{
		qDebug("Main() - Open COM1 failed!");
		return a.exec();
	}
	qDebug("Main() - Initializing GSM modem...");
	if (!c->Initialize("ate0"))
	{
		qDebug("Main() - Initialization failed!");
		return a.exec();
	}
	qDebug("Main() - Initializition successful!");
	
	qDebug("Main() - Receiving signal's level of mobile service");
	c->Send(QString("at+csq"));
	qDebug("Main() - Msg received: %s", c->Receive().constData());
	
	qDebug("Main() - Calling to remote modem...");
	GSMCallResult cr = c->Connect(QString("89124447421"));
	switch (cr)
	{
		case GCR_OK:
			qDebug("Main() - Connection successful!");
			break;
			
		case GCR_BUSY:
			qDebug("Main() - Remote modem is busy");
			break;			
			
		case GCR_NO_CARRIER:
			qDebug("Main() - have no connection with remote phone");
			break;			
			
		case GCR_ERROR:
			qDebug("Main() - Unknown error!");
			break;			
	}
	if (cr == GCR_OK)
	{
		qDebug("Main() - Try to start the session with counter...");
		//set4tm->setConnection(c);
		if (set4tm->InitSession(12, QString("000000")))
		{
			qDebug("Main() - Session succesfully started!");
			QDateTime dt = set4tm->getTime();
			qDebug("Counter time is %s. Difference with local time is %d sec(s).", 
			       dt.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData(), 
			       abs(dt.secsTo(QDateTime::currentDateTime())));
			printf("Main() - Factory num %.10ld\n", set4tm->getFactoryNum());
			TransformationRatio tr = set4tm->getTRatio();
			printf("Main() - Transformation ratio [KTN=%d KTT\%d]\n", tr.KTn, tr.KTt);
			
			//set4tm->getActive();
			if (set4tm->CloseSession())
				qDebug("Main() - Session succesfully finished!");
			else
				qDebug("Main() - Can't finish session with counter!");
		}
		else
			qDebug("Main() - Can't start session with counter!");
	}
	qDebug("Main() - Disconnecting from remote modem...");
	c->Disconnect();
	c->Close();
    return a.exec();
}
