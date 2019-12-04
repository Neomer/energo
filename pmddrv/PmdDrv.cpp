#include "PmdDrv.h"
#include <QtPlugin>
#include <QSqlDatabase>

PmdDrv::PmdDrv()
{
	QSqlDatabase * _db = new QSqlDatabase("QODBC");
	_db->setHostName();
}

bool PmdDrv::InitSession()
{
	return _db->connect(_desc.connection_string, _desc.login, _desc.password);
}

bool PmdDrv::CloseSession()
{
	_db->close();
	return true;
}

bool PmdDrv::getTime(QDateTime * dt)
{
	QDateTime d = QDateTime::currentDateTime(); 
	dt->setDate(d.date());
	dt->setTime(d.time());
	return true;
}

bool PmdDrv::checkFactoryNum()
{
	OraSqlResult * r = _db->exec(QString("select * from SH where N_SH=%1").arg(QString::number(_desc.number)));
	bool ret = r->hasRows();
	r->close();
	return ret;
}

QList<ChannelData> PmdDrv::getData(QDateTime since, QList<ChannelInfo> channels)
{
	QList<ChannelData> ret;
	qDebug("PmdDrv::getData() - Request data from database...");
	OraSqlResult * r = _db->exec(QString("select DD_MM_YYYY, N_INTER_RAS, INTERV, N_GR_TY, VAL, POK_START from buf_v_int where N_SH=%1 and dd_mm_yyyy>=TO_DATE('%2', 'YYYY-MM-DD') and INTERV=30 order by dd_mm_yyyy, n_inter_ras, n_gr_ty").arg(QString::number(_desc.number), since.toString("yyyy-MM-dd")));

	for (int ch = 0; ch < channels.count(); ch++)
	{
		ChannelData cd;
		cd.info = channels.at(ch);
		ret.append(cd);
	}
	
	qDebug("PmdDrv::getData() - Data received!");

	while (r->notEoF())
	{
		for (int ch = 0; ch < channels.count(); ch++)
		{
			if (channels.at(ch).number == r->getValue(3).toInt())
			{
				ChannelValue cv;
				cv.hdr.interval = r->getValue(2).toInt();
				cv.hdr.dt = QDateTime::fromString(r->getValue("DD_MM_YYYY"), "yyyy-MM-dd hh:mm:ss").addSecs((r->getValue("N_INTER_RAS").toInt() - 1) * 1800);
				cv.hdr.season = CounterDataHeader::Winter;
				cv.hdr.status = 0;
				cv.value = r->getValue(4).toDouble();
				cv.c_value = r->getValue(5).toDouble();
				printf("Data to %s channel %d\n",
					   cv.hdr.dt.toString("yyyy-MM-dd hh:mm").toAscii().constData(),
					   channels.at(ch).number);

				qDebug("PmdDrv::getData() - Data to %s Channel %d Value %f\n",
					   cv.hdr.dt.toString("yyyy-MM-dd hh:mm").toAscii().constData(),
					   channels.at(ch).number,
					   cv.value);
				ret[ch].values.append(cv);
			}
		}
		r->moveNext();
	}
	return ret;
}

QString PmdDrv::getLastError()
{
	return tr("");
}

void PmdDrv::setConnection(Connection * connection)
{
	_conn = connection;
}

ModuleInfo PmdDrv::getModuleInfo()
{
	ModuleInfo mi;
	
	mi.version = tr("0.1a");
	mi.description = tr("Драйвер для выгрузки данных из БД Альфа ЦЕНТР");
	
	return mi;
}

void PmdDrv::setParams(Counter_Desc * desc)
{
	_desc = *desc;
}

Q_EXPORT_PLUGIN(PmdDrv)
