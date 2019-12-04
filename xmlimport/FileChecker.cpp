#include "FileChecker.h"
#include <QSettings>
#include <QMessageBox>

FileChecker::FileChecker(QString path, QObject *parent) :
	QThread(parent)
{
	_path = path;
	_dir = QDir(path);
	
	_dir.mkdir("processed");
	
	QStringList filters;
	filters << "*.xml" << "*.xml80020";
	_dir.setNameFilters(filters);
	
	_tmr = new QTimer(this);
	_mw = (MainWindow *)parent;
	_db = new PgreSqlDrv();
	QSettings * settings = new QSettings("energo.conf", QSettings::IniFormat, this);

	QString host = settings->value("db.host", QString("127.0.0.1")).toString(),
	        port = settings->value("db.port", QString("5432")).toString(),
	        user = settings->value("db.user", QString("postgres")).toString(),
			pass = settings->value("db.password", QString()).toString(),
	        dbname = settings->value("db.name", QString("energo")).toString();
	if (!_db->connect(host, user, pass, dbname, true))
	{
		QMessageBox::critical(_mw, tr("Ошибка!"), tr("Невозможно подключиться к БД!"));
	}
	
	connect(this, SIGNAL(finished()), this, SLOT(restartLoop()));
}

void FileChecker::startLoop()
{
	emit generateMessage("Timer is started\n");
	_tmr->singleShot(FILECHECKER_PERIOD, this, SLOT(tick()));
}

void FileChecker::stopLoop()
{
	emit generateMessage("Timer is stopped\n");
	_tmr->stop();
}

void FileChecker::tick()
{
	this->start();
}

void FileChecker::restartLoop()
{
	_tmr->singleShot(FILECHECKER_PERIOD, this, SLOT(tick()));
}

void FileChecker::run()
{
	_dir.refresh();
	QStringList files = _dir.entryList();
	if (files.count() != 0)
	{
		for (int i = 0; i < files.count(); i++)
		{
			emit generateMessage(QString("Found new file %1\n").arg(
							   _dir.cleanPath(_dir.absoluteFilePath(files.at(i)))));
			qDebug("FileChecker::tick() - Found new file %s", 
				   _dir.cleanPath(_dir.absoluteFilePath(files.at(i))).toAscii().constData());
			QFile * file = new QFile(_dir.cleanPath(_dir.absoluteFilePath(files.at(i))).replace("/", "\\"));
			if (file->open(QIODevice::ReadOnly))
			{
				XML80020 * xml = new XML80020(file->readAll());
				if (!xml->isValid())
				{
					emit generateMessage(tr("Ошибка чтения файла!"));
				}
				else
				{
					emit generateMessage(QString("Package info:\nFrom: %1 [%2]\nDate: %3 (%4)\nCreated: %5\n").arg(
								  xml->getSenderName(),
								  xml->getSenderID(),
								  xml->getDate().toString("yyyy-MM-dd"),
								  QString::number((int)xml->getDL()),
								  xml->getGenerationDT().toString("yyyy-MM-dd hh:mm:ss")));
				}
                
                PgreSqlResult * sender = _db->exec(QString("select * from import_xml where uid=").append(xml->getSenderID()));
                
                
				XML80020Area * area;
				if ((area = xml->nextArea()) != 0)
				{
					emit generateMessage(QString("Area info:\nObject: %1 [%2]\n").arg(
								  area->getObjectName(),
								  area->getObjectID()));
				}
				XML80020MeasuringPoint * pnt;
				
				while ((pnt = area->nextPoint()) != 0)
				{
					emit generateMessage(QString("Measuring point info:\nCode: %1\nName: %2\n").arg(
								  pnt->getCode(),
								  pnt->getName()));
					PgreSqlResult * r = _db->exec(QString("select mp.id point, mc.channel, f.id feeder, pcp.code pointcode, pcc.code channelcode from measuringpoint mp left join measuringchannel mc on mc.mpoint=mp.id left join channel ch on ch.id = mc.channel left join counter c on c.id=ch.counter left join feeder f on f.id=c.feeder left join point_codes pcp on pcp.point = mp.id left join point_codes pcc on pcc.point = ch.id where pcp.code='%1';").arg(
													 pnt->getCode()));
					if (!r->isValid())
					{
						emit generateMessage(QString("SQL ERROR:\n%1").arg(_db->getError()));
					}
					else
					{
						if (!r->hasRows())
						{
							emit generateMessage("Code is missed in database!\n");
						}
						else
						{
							while (r->notEoF())
							{
								XML80020MeasuringChannel * ch;
								if ((ch = pnt->nextChannel(r->getValue("channelcode"))) != 0)
								{
									emit generateMessage(QString("Found data for accepted channel:\nCode: %1\nName: %2\nChannel ID: %3\n").arg(
												  ch->getCode(),
												  ch->getDesc(),
												  r->getValue("channel")));
									XML80020MeasuringChannelData * data;
									while ((data = ch->nextPeriod()) != 0)
									{
										emit generateMessage(QString("Interval: %1; Value: %2\n").arg(
													  QString::number(data->getInterval()),
													  data->getValue()));
										_db->exec(QString("insert into data (date, itv, feeder, channel, value, c_value, status, itv_length, season) values ('%1', %2, %3, %4, %5, 0, 0, 30, %6);").arg(
													  xml->getDate().toString("yyyy-MM-dd"),
													  QString::number(data->getInterval()),
													  r->getValue("feeder"),
													  r->getValue("channel"),
													  data->getValue(),
													  QString::number(data->isSummer())));
									}
								}
								r->moveNext();
							}
						}
					}
				}
				file->close();
				file->copy(_dir.absolutePath().append("/processed/").append(files.at(i)));
				file->remove();
			}
		}
	}
}

