#include <QtPlugin>
#include "ACdrv.h"
#include <qmath.h>

#define PI 3.1415926535

inline double to_rad(double grad)
{
	return grad * PI / 180;
}

ACdrv::ACdrv()
{
	_db = new OraSqlDrv();
}

bool ACdrv::InitSession()
{
	return _db->connect(_desc.connection_string, _desc.login, _desc.password);
}

bool ACdrv::CloseSession()
{
	_db->close();
	return true;
}

bool ACdrv::getTime(QDateTime * dt)
{
	QDateTime d = QDateTime::currentDateTime(); 
	dt->setDate(d.date());
	dt->setTime(d.time());
	return true;
}

bool ACdrv::setTime(int diff)
{
	return false;
}

bool ACdrv::checkFactoryNum()
{
	OraSqlResult * r = _db->exec(QString("select * from SH where N_SH=%1").arg(_desc.number));
	bool ret = r->hasRows();
	r->close();
	return ret;
}

QList<ChannelData> ACdrv::getData(QDateTime since, QList<ChannelInfo> channels)
{
	QList<ChannelData> ret;

	bool shortprofiles = false, ok;
	if (_params.keys().contains("shortprofiles")) 
	{
		shortprofiles = (int)_params.value("shortprofiles").value.toInt(&ok);
		if (!ok)
			shortprofiles = false;
	}
	
	qDebug("ACdrv::getData() - Request data from database...");
	OraSqlResult * r = _db->exec(QString("select DD_MM_YYYY, N_INTER_RAS, INTERV, N_GR_TY, VAL, POK_START from buf_v_int where N_SH=%1 and dd_mm_yyyy>=TO_DATE('%2', 'YYYY-MM-DD') and INTERV=30 and SYB_RNK=3 order by dd_mm_yyyy, n_inter_ras, n_gr_ty").arg(
									 _desc.number, 
									 since.toString("yyyy-MM-dd")));

	for (int ch = 0; ch < channels.count(); ch++)
	{
		ChannelData cd;
		cd.info = channels.at(ch);
		ret.append(cd);
	}
	
	qDebug("ACdrv::getData() - Data received!");

	bool need_not_el = false;
	while (r->notEoF())
	{
		for (int ch = 0; ch < channels.count(); ch++)
		{
			if (channels.at(ch).type != CDT_Electricity)
			{
				need_not_el = true;
				continue;
			}
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

				qDebug("ACdrv::getData() - Data to %s Channel %d Value %f\n",
					   cv.hdr.dt.toString("yyyy-MM-dd hh:mm").toAscii().constData(),
					   channels.at(ch).number,
					   cv.value);
				ret[ch].values.append(cv);
			}
		}
		r->moveNext();
	}

	if (shortprofiles)
	{
		qDebug("ACdrv::getData() - Request short intervals...");
		r = _db->exec(QString("select DD_MM_YYYY, N_INTER, INTERV, N_GR_TY, VAL, 0 from buf_v_ob where N_SH=%1 and dd_mm_yyyy>=TO_DATE('%2', 'YYYY-MM-DD') and INTERV=30 and SYB_RNK=3 order by dd_mm_yyyy, n_inter_ras, n_gr_ty").arg(
										_desc.number, 
										 since.toString("yyyy-MM-dd")));
	
		for (int ch = 0; ch < channels.count(); ch++)
		{
			ChannelData cd;
			cd.info = channels.at(ch);
			ret.append(cd);
		}
		
		qDebug("ACdrv::getData() - Data received!");
	
		while (r->notEoF())
		{
			for (int ch = 0; ch < channels.count(); ch++)
			{
				if (channels.at(ch).type != CDT_Electricity)
				{
					continue;
				}
				if (channels.at(ch).number == r->getValue(3).toInt())
				{
					ChannelValue cv;
					cv.hdr.interval = r->getValue(2).toInt();
					cv.hdr.dt = QDateTime::fromString(r->getValue("DD_MM_YYYY"), "yyyy-MM-dd hh:mm:ss").addSecs((r->getValue("N_INTER").toInt() - 1) * 60 * r->getValue("INTERV").toInt());
					cv.hdr.season = CounterDataHeader::Winter;
					cv.hdr.status = 0;
					cv.value = r->getValue(4).toDouble();
					cv.c_value = r->getValue(5).toDouble();
					printf("Data to %s channel %d\n",
						   cv.hdr.dt.toString("yyyy-MM-dd hh:mm").toAscii().constData(),
						   channels.at(ch).number);
	
					qDebug("ACdrv::getData() - Data to %s Channel %d Value %f\n",
						   cv.hdr.dt.toString("yyyy-MM-dd hh:mm").toAscii().constData(),
						   channels.at(ch).number,
						   cv.value);
					ret[ch].values.append(cv);
				}
			}
			r->moveNext();
		}
	}
	
	if (need_not_el)
	{
		qDebug("ACdrv::getData() - Request nonelectrical parameters...");
		r = _db->exec(QString("select ts.*, sh.K_T, sh.K_N from test_seti ts left join sh on sh.N_SH=ts.N_SH where ts.N_SH=%1 and ts.dd_mm_yyyy>=TO_DATE('%2', 'YYYY-MM-DD') and INTERV=30 and SYB_RNK=3 order by dd_mm_yyyy").arg(
										_desc.number, 
										 since.toString("yyyy-MM-dd")));
	
		if (!r->isValid())
		{
			qDebug("ACdrv::getData() - SQL ERROR!");
		}
		else
		{
			qDebug("ACdrv::getData() - Data received!");
			
			if (r->hasRows())
			{
				
				for (int ch = 0; ch < channels.count(); ch++)
				{
					ChannelData cd;
					ChannelValue cv;
					cd.info = channels.at(ch);
					cv.hdr.dt = QDateTime::fromString(r->getValue("TESTTIME"), "yyyy-MM-dd hh:mm:ss");
					cv.hdr.interval = 1;
					cv.hdr.season = CounterDataHeader::Winter;
					cv.hdr.status = 0;
					cv.c_value = 0;
					switch (channels.at(ch).type)
					{
						case CDT_Electricity:
							continue;
							
						case CDT_Frequency:
							cv.value = r->getValue("FREQ").toDouble();
							break;
							
						case CDT_PhaseAmp:
							switch (channels.at(ch).number)
							{
								case 0:
									cv.value = r->getValue("IA").toDouble() * r->getValue("K_T").toDouble();
									break;
									
								case 1:
									cv.value = r->getValue("IA").toDouble() * r->getValue("K_T").toDouble();
									break;
									
								case 2:
									cv.value = r->getValue("IB").toDouble() * r->getValue("K_T").toDouble();
									break;
									
								case 3:
									cv.value = r->getValue("IC").toDouble() * r->getValue("K_T").toDouble();
									break;
									
								default:
									qDebug("ACdrv::getData() - Wrong channel number for PHASE AMP type!");
									continue;
									break;
							}

							break;
							
						case CDT_PhaseVolt:
							switch (channels.at(ch).number)
							{
								case 0:
									cv.value = r->getValue("UA").toDouble() * r->getValue("K_N").toDouble();
									break;
									
								case 1:
									cv.value = r->getValue("UA").toDouble() * r->getValue("K_N").toDouble();
									break;
									
								case 2:
									cv.value = r->getValue("UB").toDouble() * r->getValue("K_N").toDouble();
									break;
									
								case 3:
									cv.value = r->getValue("UC").toDouble() * r->getValue("K_N").toDouble();
									break;
									
								default:
									qDebug("ACdrv::getData() - Wrong channel number for PHASE VOLTAGE type!");
									continue;
									break;
							}
							break;
							
						case CDT_CosineFi:
							switch (channels.at(ch).number)
							{
								case 0:
									cv.value = qCos(to_rad(r->getValue("PFANGA").toDouble()));
									break;
									
								case 1:
									cv.value = qCos(to_rad(r->getValue("PFANGA").toDouble()));
									break;
									
								case 2:
									cv.value = qCos(to_rad(r->getValue("PFANGB").toDouble()));
									break;
									
								case 3:
									cv.value = qCos(to_rad(r->getValue("PFANGC").toDouble()));
									break;
									
								default:
									qDebug("ACdrv::getData() - Wrong channel number for PHASE COSINE type!");
									continue;
									break;
							}
							break;
					}
					cd.values.append(cv);
					ret.append(cd);
				}
			}
		}		
	
	}
	return ret;
}

QString ACdrv::getLastError()
{
	return tr("");
}

void ACdrv::setConnection(Connection * connection)
{
	_conn = connection;
}

ModuleInfo ACdrv::getModuleInfo()
{
	ModuleInfo mi;
	
	mi.version = tr("0.1a");
	mi.description = tr("Драйвер для выгрузки данных из БД Альфа ЦЕНТР");
	
	return mi;
}

void ACdrv::setParams(Counter_Desc * desc)
{
	_desc = *desc;
}

QMap<QString, AddParam> ACdrv::getAdditionalParameters()
{
	QMap<QString, AddParam> ret;
	
	AddParam p;
	p.description = "Читать короткие профили";
	p.value = "0";
	ret["shortprofiles"] = p;
	
	return ret;
}

void ACdrv::setAdditionalParameters(QMap<QString, AddParam> params)
{
	_params = params;
}

Q_EXPORT_PLUGIN(ACdrv)
