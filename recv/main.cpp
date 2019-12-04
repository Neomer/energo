/*
QTextStream out(stdout);
out.setCodec(QTextCodec::codecForName("IBM 866"));
out << line;  
*/

#include <QObject>
#include <QtCore/QCoreApplication>
#include <QList>
#include <QStringList>
#include <QPluginLoader>
#include <QDir>
#include <QTcpSocket>
#include <QDateTime>
#include <QTextCodec>

#include <stdlib.h>

#include "../pgredrv/PgreSqlDrv.h"
#include "../includes/object_desc.h"
#include "../includes/CounterInterface.h"
#include "../includes/logs.h"
#include "../includes/dbconf.h"
#include "../includes/Alerts.h"
#include "../set4tm/Set4tmInterface.h"
#include "connection.h"

#include <QSettings>

#define TCP_DEFAULT_PORT	45678
#define RECV_DESYNC_DEFAULT_WARN	15
#define RECV_DESYNC_DEFAULT_CRIT	25

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("windows-1251"));
	QDir dir(a.applicationDirPath());
	
	log_file.setFileName(dir.absoluteFilePath(QString("logs/log_recv_").append(QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss")).append(".log")));
	qInstallMsgHandler(LogMsgHandler);
	
	if (argc < 2)
	{
		qWarning("%s", "Program works in console mod. Use this commands:\n-h= - database host\n-u= - database login\n-p= - database port\n-w= - database password\n-d= - database name\n-o= - object ID\n-f= - feeder ID\n-c= - counter ID");
		return 0;
	}
	
	QSettings * settings = new QSettings("energo.conf", QSettings::IniFormat, &a);
	
	QString host = settings->value("db.host", "127.0.0.1").toString(),
	        port = settings->value("db.port", "5432").toString(),
	        user = settings->value("db.user", "postgres").toString(),
			pass = settings->value("db.password", QString()).toString(),
	        dbname = settings->value("db.name", "energo").toString();
	
	char comm[3];
	memset(comm, 0, 3);
	bool ignore_time = false;
	for (int i = 1; i < argc; i++)
	{
		memcpy(comm, argv[i], 2);
		if (!strcmp(comm, "-h"))
			host = QString(argv[i]).split("=").at(1);
		else if (!strcmp(comm, "-p"))
			port = QString(argv[i]).split('=').at(1);
		else if (!strcmp(comm, "-u"))
			user = QString(argv[i]).split('=').at(1);
		else if (!strcmp(comm, "-d"))
			dbname = QString(argv[i]).split('=').at(1);
		else if (!strcmp(comm, "-w"))
			pass = QString(argv[i]).split('=').at(1);
		else if (!strcmp(comm, "-t"))
			ignore_time = true;
	}
	
	PgreSqlDrv * c = new PgreSqlDrv();
	if (!c->connect(host, user, pass, dbname))
	{
		qWarning("Main - Database is unuvailable!\n");
		return 0;
	}

	QString sql;

	// Подстановка в шаблоны данных из командной строки
    // TODO: проверка входных данных

	// ctr - список счетчиков для опроса
	QList<Counter_Desc *> ctr;
	for (int i = 1; i < argc; i++)
	{
		// Шаблоны запросов в базу данных
		QString sql_c = "select c.id, c.c_number as number, c.address, ct.name, ct.module, cn.type, o.conn_str, f.id as f_id, f.name as f_name, (f.kt_h / f.kt_l) as kt, (f.kn_h / f.kn_l) as kn, c.channels, o.id, o.recall, c.timeout_recv, c.timeout_send, cn.options, c.password, c.login, c.additional, c.allow_corr, c.corr_min, c.corr_max  from counter c left join counter_type ct on c.type=ct.id left join feeder f on c.feeder=f.id left join object o on f.object=o.id left join connection cn on o.connection=cn.id where c.id={cid} order by c.id;",
				sql_f = "select c.id, c.c_number as number, c.address, ct.name, ct.module, cn.type, o.conn_str, f.id as f_id, f.name as f_name, (f.kt_h / f.kt_l) as kt, (f.kn_h / f.kn_l) as kn, c.channels, o.id, o.recall, c.timeout_recv, c.timeout_send, cn.options, c.password, c.login, c.additional, c.allow_corr, c.corr_min, c.corr_max  from counter c left join counter_type ct on c.type=ct.id left join feeder f on c.feeder=f.id left join object o on f.object=o.id left join connection cn on o.connection=cn.id where f.id={fid} order by c.id;",
				sql_o = "select c.id, c.c_number as number, c.address, ct.name, ct.module, cn.type, o.conn_str, f.id as f_id, f.name as f_name, (f.kt_h / f.kt_l) as kt, (f.kn_h / f.kn_l) as kn, c.channels, o.id, o.recall, c.timeout_recv, c.timeout_send, cn.options, c.password, c.login, c.additional, c.allow_corr, c.corr_min, c.corr_max  from counter c left join counter_type ct on c.type=ct.id left join feeder f on c.feeder=f.id left join object o on f.object=o.id left join connection cn on o.connection=cn.id where o.id={oid} order by c.id;";
		QString arg = argv[i];
		QStringList argp = arg.split('=', QString::SkipEmptyParts);
		QString command = argp.at(0).toLower();
		if (command == "-c")
		{
			sql = sql_c.replace("{cid}", argp[1]);
		}
		else if (command == "-f")
		{
			sql = sql_f.replace("{fid}", argp[1]);
		}
		else if (command == "-o")
		{
			sql = sql_o.replace("{oid}", argp[1]);
		}
		else
		{
			//qWarning("Main - Unknown command: %s\n", argp.at(0).toAscii().constData());
			continue;
		}
	
		// Запрос в базу данных
		PgreSqlResult * r;
		if (!(r = c->exec(sql))->isValid())
		{
			qWarning("Main() - DB response failed!\n");
			qDebug("%s\n", c->getError().toAscii().constData());
		}
	
		// формируем список счетчиков для опроса
		// select c.id, c.c_number as number, c.address, ct.name, ct.module, o.connection, o.conn_str, f.name from ...
		while (r->notEoF())
		{
			// cd - описание счетчика
			Counter_Desc *cd = new Counter_Desc();
			cd->ID = r->getValue(0).toInt();
			cd->number = r->getValue(1);
			cd->address = r->getValue(2).toInt();
			cd->type = r->getValue(3);
			cd->module = r->getValue(4);
			cd->connection = (ConnectionType)r->getValue(5).toInt();
			cd->connection_string = r->getValue(6);
			cd->feeder = r->getValue(7).toInt();
			cd->feeder_name = r->getValue(8);
			cd->tr.KTt = r->getValue(9).toInt();
			cd->tr.KTn = r->getValue(10).toInt();
			cd->channels = r->getValue(11).toInt();
			cd->object = r->getValue(12).toInt();
			cd->recall = r->getValue(13).toInt();
			cd->timeout_receive = r->getValue(14).toInt();
			cd->timeout_send = r->getValue(15).toInt();
			cd->connection_opts = r->getValue(16);
			cd->password = r->getValue(17);
			cd->login = r->getValue(18);
			cd->params = r->getValue(19, "");
			cd->corr_allow = r->getValue(20, "0").toInt();
			cd->corr_min = r->getValue(21, "2").toInt();
			cd->corr_max = r->getValue(22, "10").toInt();
			ctr.append(cd);
			r->moveNext();
		}
		r->close();
	}

	qWarning("Start process... %i counter(s) queded.\n", ctr.count());
	PortSettings ps;
	Counter_Desc * p_cd;
	QPluginLoader *pl;
	
	ps.BaudRate = BAUD9600;
	ps.DataBits = DATA_8;
	ps.FlowControl = FLOW_HARDWARE;
	ps.Parity = PAR_NONE;
	ps.StopBits = STOP_1;
	ps.Timeout_Millisec = 2000;
	
	int old_obj = -1;
	Connection * conn = 0;

	for (int i = 1; i <= ctr.count(); i++)
	{
		p_cd = ctr.at(i - 1);
		qWarning("[%d] Begin %s\n", i, p_cd->number.toAscii().constData());
		if (!conn) conn = new Connection(p_cd->connection);
		ConnectionInitParams cip;
		QDateTime since;
		
		PgreSqlResult *r;

		sql = "select max_depth from counter where id={cid}";
		sql.replace("{cid}", QString::number(p_cd->ID));
		r = c->exec(sql);
		if (!r->isValid())
		{
			qDebug("Main() - Error on executing SQL query.\n%s\n", sql.toAscii().constData());
			qDebug("\n%s\n", c->getError().toAscii().constData());
		}
		if (r->numRows() == 0)
		{
			qDebug("Main() - Max depth is not set for counter!\n");
			continue;
		}
		qDebug("Main() - Set max depth for this counter: %d\n", r->getValue(0).toInt());
		since = QDateTime::currentDateTime().addDays(-1 * r->getValue(0).toInt());

		// Получения времени последних имеющихся данных
		sql = "select date, itv from data where date >= '{date}' and feeder={fid} and itv_length=30 order by date desc, itv desc limit 1;";
		sql.replace("{fid}", QString::number(p_cd->feeder));
		sql.replace("{date}", since.toString("yyyy-MM-dd"));
		r->close();
		
		if (!(r = c->exec(sql))->isValid())
		{
			qDebug("Main() - Error on executing SQL query.\n%s\n", sql.toAscii().constData());
			qDebug("\n%s\n", c->getError().toAscii().constData());
		}
		if (r->numRows() == 0)
		{
			qDebug("Main() - Database hasn't data for this feeder\n");
		}
		else
		{
			since = QDateTime::fromString(r->getValue(0), "yyyy-MM-dd");
			since = since.addSecs(r->getValue(1).toInt() * 1800);
		}
		r->close();
		if ((int)(since.secsTo(QDateTime::currentDateTime()) / 1800) == 0)
		{
			qWarning("[%d] No data to request\n", i);
			continue;
		}
		
/***********************************************
  
  1. Инициализация подключения
  
 ***********************************************/
		qDebug("Main() - Connection status: %d\n", (int)conn->isConnected());
		if ((p_cd->object != old_obj)||(!conn->isConnected()))
		{
			if (!conn) conn = new Connection(p_cd->connection);
			old_obj = p_cd->object;
			if (conn->isConnected()) conn->Close();
			switch (p_cd->connection)
			{
				case CT_GSM:
					cip.serial_name = p_cd->connection_opts;
					cip.serial_sets = ps;
					cip.serial_initstr = "ate0";
					qDebug("Main() - Initial with params:\nType: GSM\nname=%s init=%s\n",
						   cip.serial_name.toAscii().constData(),
						   cip.serial_initstr.toAscii().constData());
					break;
					
				case CT_DIRECT:
					cip.serial_name = p_cd->connection_opts;
					cip.serial_sets = ps;
					qDebug("Main() - Initial with params:\nType: DIRECT\nname=%s init=%s\n", 
						   cip.serial_name.toAscii().constData(),
						   cip.serial_initstr.toAscii().constData());
					break;
					
				case CT_TCPIP:
					qDebug("Main() - Initial with params:\nType: TCP/IP\nHost: %s\n",
						   p_cd->connection_string.toAscii().constData());
					break;
			}
			conn->setConnectionType(p_cd->connection);
			if (!conn->Init(&cip))
			{
				qWarning("[%i] Connection not initialized! MSG: %s\n", 
				         i, 
				         conn->GetLastError().toAscii().constData());
				continue;
			}
			qWarning("[%d] Connection successfully initialized\n", i);
			ConnectionParams cp;
			qWarning("[%d] Connect to remote device.\n", i);
			QStringList csp;
			switch (p_cd->connection)
			{
				case CT_GSM:
					cp.phone = p_cd->connection_string;
					break;
					
				case CT_DIRECT:
					break;
					
				case CT_TCPIP:
					csp = p_cd->connection_string.split(':', QString::SkipEmptyParts);
					cp.inet_addr = csp.at(0);
					if (csp.count() > 1)
						cp.inet_port = csp.at(1).toInt();
					else
						cp.inet_port = TCP_DEFAULT_PORT;
					qDebug("Main() - Host: %s Port: %d\n",
						   cp.inet_addr.toAscii().constData(),
						   cp.inet_port);
					break;
			}
		
/***********************************************
  
  2. Соединение с подстанцией
  
 ***********************************************/
			qDebug("Main() - Connection status: %d\n", (int)conn->isConnected());
			while ((!conn->Connect(&cp))&&(p_cd->recall--))
			{
				qWarning("[%i] Remote device not answer. Retry again %d time(s). MSG: %s\n",
						 i, 
				         p_cd->recall,
						 conn->GetLastError().toAscii().constData());
			}
			if (!conn->isConnected())
			{
				qWarning("[%i] Connection with remote device is failed! MSG: %s\n", 
				         i, 
				         conn->GetLastError().toAscii().constData());
				if (!c->exec(generateAlertRequest(
								 p_cd->object, 
								 AOT_Object, 
								 ALT_ReceiveError, 
								 ALL_Critical, 
								 QString("Не удалось соединится с подстанцией! Ответ устройства: ").append(
									 conn->GetLastError())))->isValid())
				{
					qDebug("Main() - SQL ERROR: %s",
						   c->getError().toAscii().constData());
				}
				conn->Close();
				continue;
			}
		}

/***********************************************
  
  3. Подключение плагина счетчика
  
 ***********************************************/
		conn->setReceiveTimeout(p_cd->timeout_receive);
		conn->setSendTimeout(p_cd->timeout_send);

		qDebug("[%d] Load counter's module:\nName: %s\nModule: %s\nPath: %s\n",
		       i,
		       p_cd->type.toAscii().constData(),
		       p_cd->module.toAscii().constData(),
		       dir.absoluteFilePath(p_cd->module).toAscii().constData());
		CounterInterface2 * counter;
		pl = new QPluginLoader(dir.absoluteFilePath(p_cd->module));
		if (!pl->load())
			qDebug("Main() - plugin is not loaded!");
		if (pl->instance())
		{
			counter = qobject_cast<CounterInterface2 *>(pl->instance());
			qWarning("[%i] Counter's module successfully loaded\n", i);
			ModuleInfo mi = counter->getModuleInfo();
			
			qDebug("[%i] Module info:\nVersion: %s\nDesc: %s\n",
			       i,
			       mi.version.toAscii().constData(),
			       mi.description.toAscii().constData());
			counter->setConnection(conn);
			counter->setParams(p_cd);
			QMap<QString, AddParam> params;
			QStringList pl = p_cd->params.split(";", QString::SkipEmptyParts);
			for (int pp = 0; pp < pl.count(); pp++)
			{
				QStringList plp = pl.at(pp).split(":");
				if (plp.count() != 2) 
					continue;
				params[plp.at(0)].value = plp.at(1);
			}
			
			counter->setAdditionalParameters(params);
			
/***********************************************
  
  4. Опрос счетчика
  
  4.1. Устанавливаем сессию
  
 ***********************************************/
			
			// Открываем сессию со счетчиком			
			if (!counter->InitSession())
			{
				qWarning("[%d] Session initialization failed!\n", i);
				if (!c->exec(generateAlertRequest(
								 p_cd->ID, 
								 AOT_Counter, 
								 ALT_ReceiveError, 
								 ALL_Critical, 
								 "Сессия с прибором не установлена!"))->isValid())
				{
					qDebug("Main() - SQL ERROR: %s",
						   c->getError().toAscii().constData());
				}
				continue;
			}
			qWarning("[%i] Check counter information\n", i);
			
/***********************************************
  
  4.2. Проверяем заводской номер счетчика
  
 ***********************************************/
			if (!counter->checkFactoryNum())
			{
				qWarning("[%i] Received counter's number is not equal to stored number\n", i);
				if (!c->exec(generateAlertRequest(
								 p_cd->ID, 
								 AOT_Counter, 
								 ALT_ReceiveError, 
								 ALL_Critical, 
								 "Заводской номер устройства не соответствует установленному в базе данных!"))->isValid())
				{
					qDebug("Main() - SQL ERROR: %s",
						   c->getError().toAscii().constData());
				}
				continue;
			}
			
/***********************************************
  
  4.3. Проверяем время
  
 ***********************************************/
			QDateTime dt;
			if (!counter->getTime(&dt))
			{
				qWarning("[%i] Time is not received\n", i);
				continue;
			}
			qWarning("[%i] Counter time is %s\n", 
			         i,
			         dt.toString("yyyy/MM/dd hh:mm:ss").toAscii().constData());
			int desync = abs(dt.secsTo(QDateTime::currentDateTime())),
					desync_signed = dt.secsTo(QDateTime::currentDateTime());
			qDebug("[%i] Difference between local and counter's times is %d sec(s)\n",
			       i,
			      desync);
			if (!c->exec(QString("update counter set desync=%1 where id=%2;").arg(
						QString::number(desync),
						QString::number(p_cd->ID)))->isValid())
			{
				qDebug("Main() - SQL ERROR: %s",
					   c->getError().toAscii().constData());
			}
			
			if (desync >= p_cd->corr_min)
			{
				if (p_cd->corr_allow)
				{
					int corr = qMin(desync, p_cd->corr_max) * (desync_signed / desync);
					qWarning("[%i] Time correction on %d sec(s)\n", i, corr);
					
					if (!counter->setTime(corr))
					{
						qWarning("[%i] Time correction failed!\n", i);
					}
				}
				else
					qWarning("[%i] Time correction isn't allowed by configuration!\n", i);
			}
				
			
			AlertLevel lvl;
			QString alert_txt;
			if (desync > settings->value("recv.desync.critical", RECV_DESYNC_DEFAULT_CRIT).toInt())
			{
				lvl = ALL_Critical;
				alert_txt = QString("Значительное расхождение локального времени и времени на приборе учета! Расхождение %1 сек.").arg(
								QString::number(desync));
			}
			else if (desync > settings->value("recv.desync.warning", RECV_DESYNC_DEFAULT_WARN).toInt())
			{
				lvl = ALL_Warning;
				alert_txt = QString("Большое расхождение локального времени и времени на приборе учета! Расхождение %1 сек.").arg(
				    QString::number(desync));			
			}
			else
				lvl = ALL_Normal;
			
			if (lvl != ALL_Normal)
				if (!c->exec(generateAlertRequest(
								 p_cd->ID, 
								 AOT_Counter, 
								 ALT_ReceiveError, 
								 lvl, 
								 alert_txt))->isValid())
				{
					qDebug("Main() - SQL ERROR: %s",
						   c->getError().toAscii().constData());
				}
			
			if ((abs(dt.secsTo(QDateTime::currentDateTime())) > settings->value("recv.desync.critical", RECV_DESYNC_DEFAULT_CRIT).toInt())&&(!ignore_time))
			{
				qWarning("[%i] Difference between local and counter's times is more than %d secs\n", 
						 i,
						 settings->value("recv.desync.critical", RECV_DESYNC_DEFAULT_CRIT).toInt());
				//conn->Close();
				continue;
			}
			qWarning("[%i] Request data from %s\n", 
			         i,
			         since.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData());
			
			qWarning("[%i] Load channel list\n", 
			         i);
/***********************************************
  
  4.4. Формируем информацию по канал учета
  
 ***********************************************/
			QList<ChannelInfo> channels;
			PgreSqlResult *r = c->exec(QString("select * from channel where counter=%1;").arg(p_cd->ID));
			while (r->notEoF())
			{
				ChannelInfo ci;
				ci.ID = r->getValue("id").toInt();
				ci.name = r->getValue("name");
				ci.number = r->getValue("index").toInt();
				ci.type = (ChannelDataType) r->getValue("type").toInt();
				ci.last_date = QDateTime::fromString(r->getValue("last_date"), "yyyy-MM-dd hh:mm:ss");
				channels.append(ci);
				r->moveNext();
			}
			qWarning("[%i] Total %i channel(s)\n", 
			         i,
					 channels.count());
			QList<ChannelData> data = counter->getData(since, channels);
			qWarning("[%i] Received %d intervals\n",
			         i,
			         data.size());
/***********************************************
  
  5. Занесение в БД
  
 ***********************************************/
			for (int d = 0; d < data.size(); d++)
			{
				for (int v = 0; v < data.at(d).values.length(); v++)
				{
					
					ChannelValue cd = data.at(d).values.at(v);
					double value = cd.value;
					switch (data.at(d).info.type)
					{
						case CDT_Electricity:
							value *= p_cd->tr.KTn * p_cd->tr.KTt;
							break;
							
						case CDT_Frequency:
							break;
							
						case CDT_PhaseAmp:
							value *= p_cd->tr.KTt;
							break;
							
						case CDT_PhaseVolt:
							value *= p_cd->tr.KTn;
							break;
							
						case CDT_CosineFi:
							break;
					}
	 
					sql = "insert into data (date, itv, feeder, channel, season, value, c_value, status, itv_length, dt) values ('%1', %2, %3, %4, %5, %6, %7, %8, %9, '%10');";
					sql = sql.arg(cd.hdr.dt.toString("yyyy-MM-dd"),
						QString::number(cd.hdr.dt.time().hour() * (60 / cd.hdr.interval) + cd.hdr.dt.time().minute() / cd.hdr.interval),
						QString::number(p_cd->feeder),
						QString::number(data.at(d).info.ID),
						QString::number((int)cd.hdr.season),
						QString::number(value, 'f', 6),
						QString::number(cd.c_value, 'f', 6),
						QString::number(cd.hdr.status),
						QString::number(cd.hdr.interval)).arg(
						cd.hdr.dt.toString("yyyy-MM-dd hh:mm:00"));
					r = c->exec(sql);
					if (!r->isValid())
					{
						qDebug("Main() - Error on executing SQL query.\n%s\n", sql.toAscii().constData());
						qDebug("\n%s\n", c->getError().toAscii().constData());
					}
				}
			}
			counter->CloseSession();
			/*
			if (!pl->unload())
			{
				qDebug("Main() - Plugin is not unloaded!");
			}
			delete pl;
			*/
		}
		else
			qWarning("[%i] Counter module isn't loaded!\n", i);
	}
	c->close();
	if (conn) 
		if (conn->isConnected()) conn->Close();
	qWarning("All counters processed!\n");
    return 0;
}
