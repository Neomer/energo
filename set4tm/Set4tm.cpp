#include <QtPlugin>
#include "Set4tm.h"

Set4tmPlugin::Set4tmPlugin()
{
	this->m_addr = 0;
	this->err = "";
	this->m_conn = 0;

	/*
	Постоянная счетчика, имп/кВт?ч(имп/квар?ч):
	0 – 5000 имп/кВт?ч;
	1 – 25000 имп/кВт?ч;
	2 – 1250 имп/кВт?ч;
	3 – 6250 имп/кВт?ч;
	4 – 500 имп/кВт?ч
	5 – 250 имп/кВт?ч
	6 – 6400 имп/кВт?ч;
	*/ 
	Set4tmConstA[0] = 5000;
	Set4tmConstA[1] = 25000;
	Set4tmConstA[2] = 1250;
	Set4tmConstA[3] = 6250;
	Set4tmConstA[4] = 500;
	Set4tmConstA[5] = 250;
	Set4tmConstA[6] = 6400;
	
	Set4tmBufferSize[0] = 24;
	Set4tmBufferSize[1] = 96;
	Set4tmBufferSize[2] = 47;
	Set4tmBufferSize[3] = 96;
	Set4tmBufferSize[4] = 16;
	Set4tmBufferSize[5] = 136;
	Set4tmBufferSize[6] = 140;
	Set4tmBufferSize[7] = 140;
	Set4tmBufferSize[8] = 96;
	Set4tmBufferSize[9] = 47;
	Set4tmBufferSize[10] = 140;
	Set4tmBufferSize[11] = 156;
}

Set4tmPlugin::~Set4tmPlugin()
{
	
}

void Set4tmPlugin::setParams(Counter_Desc *desc)
{
	this->m_desc = *desc;
	this->m_addr = desc->address;
}

bool Set4tmPlugin::CloseSession()
{
	if (!this->m_conn) 
	{
		qDebug("Set4tmPlugin::CloseSession() - Connection don't set!\n");
		this->err = "Connection don't set";
		return false;
	}
	if (this->m_conn->getStatus() != GCS_DATA) 
	{
		qDebug("Set4tmPlugin::CloseSession() - Connection must be in GCS_DATA state!\n");
		this->err = "Connection must be in GCS_DATA state";
		return false;
	}
	BYTE b[] = {this->m_addr, 0x02, 0x00, 0x00};
	this->getHash(b, 2, true);
	QByteArray ba((const char *)b, 4), out;
	this->m_conn->Send(ba);
	if (!this->getFromCounter(&out, 2))
	{
		qDebug("Set4tmPlugin::CloseSession() - CRC16 is not correct\n");
		return false;
	}
	Set4tmResponse res;
	memcpy(&res, out.constData(), out.length() - 2);
	if (res.code != 0)
	{
		qDebug("Set4tmPlugin::CloseSession() - Counter answer with error code!\n");
		err = "Counter answer with error code";
		return false;
	}
	return true;
}

QByteArray Set4tmPlugin::createRequest(BYTE *data, long length)
{
	BYTE tmp[length + 2];
	memcpy(tmp, data, length);
	this->getHash(tmp, length, true);
	
	QByteArray ba((const char *)tmp, length + 2);
	return ba;
}

QByteArray Set4tmPlugin::createRequest(char *data, long length)
{
	BYTE tmp[length + 2];
	memcpy(tmp, data, length);
	this->getHash(tmp, length, true);
	
	QByteArray ba((const char *)tmp, length + 2);
	return ba;
}

/*
QList<CounterData> Set4tmPlugin::getData(QDateTime since, QList<ChannelInfo> channels)
{
	CounterData cd;
	QList<CounterData> ret;
	byte b[1024];
	b[0] = this->m_addr;
	
	// Получение варианта исполнения счетчика
	memcpy(b + 1, "\x08\x12", 2);
	this->m_conn->Send(createRequest(b, 3));
	QByteArray out;
	if (!this->getFromCounter(&out, 3))
	{
		qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
		return ret;
	}

	byte * res = (byte *)out.constData();
	byte A = (byte)(res[2] & 0x0F), BS = (byte)(res[3] >> 4);
	qDebug("Set4tmPlugin::getData() - A: %d; BS: %d;\n", Set4tmConstA[A], Set4tmBufferSize[BS]);

	if (((A < 0)||(A > 6)||(BS < 0)||(BS > 11)))
	{
		qWarning("Counter construction is unidentified!");
		return ret;
	}
	
	// Получение внутренних КТ
	TransformationRatio tr;
	memcpy(b + 1, "\x08\x02", 2);
	this->m_conn->Send(createRequest(b, 3));
	if (!this->getFromCounter(&out, 8))
	{
		qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
		return ret;
	}
	res = (byte *)out.constData();
	readPackage(res + 1, &(tr.KTn));
	readPackage(res + 3, &(tr.KTt));
	qDebug("Set4tmPlugin::getData() - Kt: %d; Kn: %d;\n", tr.KTt, tr.KTn);
	
	// Чтение показаний счетчика
	memcpy(b + 1, "\x05\x00\x00", 3);
	this->m_conn->Send(createRequest(b, 4));
	out = this->getFromCounter();
	res = (byte *)out.constData();
	CounterData data_0;
	quint32 tmp;
	readPackage(res + 1, &tmp);
	data_0.P_Receive = fromCounterData(tmp, 0, A, &tr);
	readPackage(res + 5, &tmp);
	data_0.P_Send = fromCounterData(tmp, 0, A, &tr);
	readPackage(res + 9, &tmp);
	data_0.Q_Receive = fromCounterData(tmp, 0, A, &tr);
	readPackage(res + 13, &tmp);
	data_0.Q_Send = fromCounterData(tmp, 0, A, &tr);
	qDebug("Set4tmPlugin::getData() - Total values:\n\tP+: %f\n\tP-: %f\n\tQ+: %f\n\tQ-: %f", 
	       data_0.P_Receive,
	       data_0.P_Send,
	       data_0.Q_Receive,
	       data_0.Q_Send);
	
	// Получение адреса последних данных
	memcpy(b + 1, "\x08\x04", 2);
	QByteArray ba = createRequest(b, 3);
	this->m_conn->Send(ba);
	if (!this->getFromCounter(&out, 7))
	{
		qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
		return ret;
	}
	res = (byte *)out.constData();
	byte ovrfl = res[1] >> 7;
	res[1] &= 0x7F;
	//qdt - дата + время куда записываются последние данные со счетчика
	QDateTime qdt = fromCounterDT(res + 1, "ihdmy");
	quint16 addr = 0; 
	CounterDataHeader hdr;
	readPackage(res + 6, &addr);
	qDebug("Set4tmPlugin::getData() - Last data: %s address: 0x%.4X\n",
	       qdt.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData(),
	       addr);
	
	// Получаем время интегрирования
	memcpy(b + 1, "\x08\x06", 2);
	this->m_conn->Send(createRequest(b, 3));
	if (!this->getFromCounter(&out, 2))
	{
		qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
		return ret;
	}
	res = (byte *)out.constData();
	quint16 itv_len;
	readPackage(res + 1, &itv_len);
	qDebug("Set4tmPlugin::getData() - Interval length is %d\n", itv_len);
	
	// Нормируем время относительно времени интегрирования мощности
	since.setTime(QTime(since.time().hour(), (since.time().minute() / itv_len) * itv_len, 0, 0));

	qDebug("Set4tmPlugin::getData() - Requested data from %s\n", 
	       since.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData());
	
	int h = since.addSecs(-1 * since.time().minute() * 60).secsTo(qdt.addSecs(-1 * qdt.time().minute() * 60)) / 3600;
	qDebug("Set4tmPlugin::getData() - Requested %d interval(s)\n", h);

	// Получаем дату последней записи
	addr -= 8 + 8 * (qdt.time().minute() / itv_len);
	byte hdr_b [] = {this->m_addr, 0x06, 0x03, 0x00, 0x00, 0x07};
	writePackage(hdr_b + 3, addr);
	ba = createRequest((char *)hdr_b, 6);
	this->m_conn->Send(ba);
	if (!this->getFromCounter(&out, 7))
	{
		qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
		return ret;
	}
	res = (byte *)out.constData();
	hdr.interval = res[6];
	cd.hdr.dt = hdr.dt = fromCounterDT(res + 1, "hdmy");
	qDebug("Set4tmPlugin::getData() - Request information about regiter:\n\tdt=%s\n\titv=%d\n\tovrfl=%d\n",
	       hdr.dt.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData(),
	       hdr.interval,
	       ovrfl);
	
	//data_0.hdr = hdr;
	//ret.append(data_0);
	byte itv_per_hour = 60 / hdr.interval; // Количество интервалов в часе
	byte block_size = itv_per_hour * SET4TM_DATASIZE + SET4TM_DATASIZE;
	quint16 max_data_addr = ((int)(0xffff / block_size)) * block_size;
	
	// Определяем адрес искомого интервала
	quint16 addr_tmp = addr, 
	        modif = h * (8 + (480 / itv_len));
	if (addr < modif)
		if (!ovrfl)
			addr = 0;
		else
		{
			addr = addr - modif + max_data_addr;
			//addr -= SET4TM_DATASIZE * (since.time().minute() / itv_len);
			if (addr < addr_tmp) addr = addr_tmp;
		}
	else
		addr -= modif;
	
	
	qDebug("Set4tmPlugin::getData() - Address calc:\n\taddr=%.4X .. %d\n\tmodif=%.4X .. %d -> delta=%d\n\taddr=%.4X",
		   addr_tmp,
		   addr_tmp,
		   modif,
		   modif,
		   addr_tmp - modif,
		   addr);
	QByteArray tmp_out;
	out.clear();

	
	// Максимально возможное количество запрашиваемых интервалов
	byte pkg_len = Set4tmBufferSize[BS] - SET4TM_DATASIZE, 
	     req_cnt = pkg_len / SET4TM_DATASIZE;

	int total_itv = since.secsTo(QDateTime::currentDateTime()) / 1800;

	res = (byte *)out.constData();
	int itv_num = 0;
	cd.hdr.dt = since;
	do 
	{
		qDebug("Set4tmPlugin::getData() - Buffer size %d\n", out.size());
		if (out.size() - (res - (byte *)out.constData()) < 8)
		{
			out.remove(0, (res - (byte *)out.constData()));
			if (req_cnt > total_itv) req_cnt = total_itv;
			pkg_len = req_cnt * SET4TM_DATASIZE;
			
			// Проверка на выход за диапазон адресного пространства
			if (pkg_len > max_data_addr - addr)
				pkg_len = max_data_addr - addr;
			
			if (pkg_len <= 0) 
			{
				pkg_len = req_cnt * SET4TM_DATASIZE;
				addr = 0;
			}
			
			while (out.size() < pkg_len)
			{
				qDebug("Set4tmPlugin::getData() - Request data. Address: 0x%.4X\n", addr);
				byte b2 [] = {this->m_addr, 0x06, 0x03, 0x00, 0x00, pkg_len};
				writePackage(b2 + 3, addr);
				ba = createRequest((char *)b2, 6);
				this->m_conn->Send(ba);
				if (!this->getFromCounter(&tmp_out, pkg_len))
				{
					qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
					return ret;
				}
				if (tmp_out.size() < pkg_len) 
				{
					qDebug("Set4tmPlugin::getData() - Wrong response format!\n");
					return ret;
				}
				addr += pkg_len;
				tmp_out.remove(0, 1);
				tmp_out.remove(tmp_out.size() - 2, 2);
				out.append(tmp_out);
			}
			res = (byte *)out.constData();
		}
		if (itv_num % (itv_per_hour + 1) == 0)
		{
			if (abs(cd.hdr.dt.secsTo(fromCounterDT(res, "hdmy"))) > 7200)
			{
				qDebug("Set4tmPlugin::getData() - DRIVER ERROR: Received date is earlier than previous!\n\tReceived date: %s\n\tPrev date: %s",
					   fromCounterDT(res, "hdmy").toString("yyyy-MM-dd hh:mm").toAscii().constData(),
					   cd.hdr.dt.toString("yyyy-MM-dd hh:mm").toAscii().constData());
				do
				{
					ret.removeLast();
				}
				while (ret.last().hdr.dt.secsTo(cd.hdr.dt) <= 3600);
				
				ret.clear();
				return ret;
			}
			cd.hdr.dt = fromCounterDT(res, "hdmy");
			cd.hdr.interval = res[5];
			cd.hdr.season = (CounterDataHeader::Season)res[4];
			
			qDebug("Set4tmPlugin::getData() - Header of current hour:\n\tdt=%s\n\titv=%d\n\tseason=%d\n",
				   cd.hdr.dt.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData(),
				   cd.hdr.interval,
				   (int)cd.hdr.season);
			// Останавливаем, если дата вне необходимого диапазона
			if ((cd.hdr.dt > qdt)||(cd.hdr.dt.daysTo(since) > 0)) break;
	
			res += 8;
		}
		else
		{
			cd.hdr.status = res[0] >> 7;
			short tmp_v;
			readPackage(res, &tmp_v, (short int)0x7FFF);
			cd.P_Receive = this->fromCounterData(tmp_v, &hdr, A, &tr);
			readPackage(res + 2, &tmp_v, (short int)0x7FFF);
			cd.P_Send = this->fromCounterData(tmp_v, &hdr, A, &tr);
			readPackage(res + 4, &tmp_v, (short int)0x7FFF);
			cd.Q_Receive = this->fromCounterData(tmp_v, &hdr, A, &tr);
			readPackage(res + 6, &tmp_v, (short int)0x7FFF);
			cd.Q_Send = this->fromCounterData(tmp_v, &hdr, A, &tr);
			qDebug("Set4tmPlugin::getData() - Received profile on %s\n\tP+: %f\n\tP-: %f\n\tQ+: %f\n\tQ-: %f\n",
				   cd.hdr.dt.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData(),
				   cd.P_Receive,
				   cd.P_Send,
				   cd.Q_Receive,
				   cd.Q_Send);
			qWarning("Received data to %s\n",
				   cd.hdr.dt.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData());
			if ((cd.hdr.dt > since)&&(cd.hdr.dt < qdt))
			{
				total_itv--;
				ret.append(cd);
			}
			cd.hdr.dt = cd.hdr.dt.addSecs(cd.hdr.interval * 60);
			res += 8;
		}
		itv_num++;
	}
	while ((cd.hdr.dt < qdt)&&(total_itv > 0));
	return ret;
}
*/

QList<ChannelData> Set4tmPlugin::getData(QDateTime since, QList<ChannelInfo> channels)
{
	CounterData cd;
	QList<ChannelData> ret;
	for (int ch = 0; ch < channels.length(); ch++)
	{
		ChannelData chd;
		chd.info = channels.at(ch);
		ret.append(chd);
	}

	byte b[1024];
	b[0] = this->m_addr;
	
	QStringList registers;
	if (_params.keys().contains("registers")) 
		registers = _params.value("registers").value.split(",", QString::SkipEmptyParts);
	else
	{
		registers.append("0");
	}
	
	// Получение варианта исполнения счетчика
	memcpy(b + 1, "\x08\x12", 2);
	this->m_conn->Send(createRequest(b, 3));
	QByteArray out;
	if (!this->getFromCounter(&out, 3))
	{
		qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
		return ret;
	}

	byte * res = (byte *)out.constData();
	byte A = (byte)(res[2] & 0x0F), BS = (byte)(res[3] >> 4);
	qDebug("Set4tmPlugin::getData() - A: %d; BS: %d;\n", Set4tmConstA[A], Set4tmBufferSize[BS]);

	if (((A < 0)||(A > 6)||(BS < 0)||(BS > 11)))
	{
		qWarning("Counter construction is unidentified!");
		return ret;
	}
	
	// Получение внутренних КТ
	TransformationRatio tr;
	memcpy(b + 1, "\x08\x02", 2);
	this->m_conn->Send(createRequest(b, 3));
	if (!this->getFromCounter(&out, 8))
	{
		qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
		return ret;
	}
	res = (byte *)out.constData();
	readPackage(res + 1, &(tr.KTn));
	readPackage(res + 3, &(tr.KTt));
	qDebug("Set4tmPlugin::getData() - Kt: %d; Kn: %d;\n", tr.KTt, tr.KTn);
	
	// Проверяем на необходимость опроса профилей ЭЭ
	qDebug("Set4tmPlugin::getData() - Checking for nonelectrical channels\n");
	bool need_electro = false;
	QDateTime chdt;
	if (!getTime(&chdt))
	{
		chdt = QDateTime::currentDateTime();
	}
	int chdt_diff = QDateTime::currentDateTime().secsTo(chdt);
	
	for (int ch = 0; ch < channels.length(); ch++)
	{
		// Опрос параметров электросети
		QByteArray ba;
		switch (channels.at(ch).type)
		{
			case CDT_Electricity:
				need_electro = true;
				continue;
				
			case CDT_Frequency:
				memcpy(b + 1, "\x08\x11\x00", 3);
				b[3] = createRWRI(SET4TM_RWRI_TYPE_FREQ, SET4TM_RWRI_PARAM_NULL, 0);
				break;
				
			case CDT_PhaseVolt:
				if ((channels.at(ch).number > 3)||(channels.at(ch).number < 0))
				{
					qDebug("Set4tmPlugin::getData() - Wrong channel number for PHASE VOLTAGE type!");
					continue;
				}
				memcpy(b + 1, "\x08\x11\x00", 3);
				b[3] = createRWRI(SET4TM_RWRI_TYPE_VOLTAGE, SET4TM_RWRI_PARAM_NULL, channels.at(ch).number);
				break;
				
			case CDT_PhaseAmp:
				if ((channels.at(ch).number > 3)||(channels.at(ch).number < 0))
				{
					qDebug("Set4tmPlugin::getData() - Wrong channel number for PHASE AMP type!");
					continue;
				}
				memcpy(b + 1, "\x08\x11\x00", 3);
				b[3] = createRWRI(SET4TM_RWRI_TYPE_AMP, SET4TM_RWRI_PARAM_NULL, channels.at(ch).number);
				break;
				
			case CDT_CosineFi:
				if ((channels.at(ch).number > 3)||(channels.at(ch).number < 0))
				{
					qDebug("Set4tmPlugin::getData() - Wrong channel number for COSINE type!");
					continue;
				}
				memcpy(b + 1, "\x08\x11\x00", 3);
				b[3] = createRWRI(SET4TM_RWRI_TYPE_COSINE, SET4TM_RWRI_PARAM_NULL, channels.at(ch).number);
				break;
		}
		ba = createRequest(b, 4);
		this->m_conn->Send(ba);
		if (!this->getFromCounter(&out, 3))
		{
			qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
			return ret;
		}
		res = (byte *)out.constData();
		
		short buf = 0;
		
		readPackage(res + 1, &buf);
		int n = buf << 8;
	
		buf = 0;
		readPackage(res + 3, (byte *) &buf);
		n |= buf;
		
		// Маскируем ненужные биты
		n &= 0x3FFFFF;


		qDebug("N=%.6x", n);
		ChannelValue cv;
		cv.hdr.dt = QDateTime::currentDateTime().addSecs(chdt_diff);
		cv.hdr.status = 0;
		cv.hdr.season = CounterDataHeader::Winter;
		cv.hdr.interval = 1;
		cv.c_value = 0;
		switch (channels.at(ch).type)
		{
			case CDT_Electricity:
				break;
				
			case CDT_Frequency:
				cv.value = (double)n * 0.01;
				qDebug("Frequency=%f", cv.value);
				break;
				
			case CDT_PhaseVolt:
				cv.value = (double)n * 0.01;
				qDebug("Voltage=%f phase=%d", cv.value, channels.at(ch).number);
				break;
				
			case CDT_PhaseAmp:
				cv.value = (double)n * 0.1;
				qDebug("Amp=%f phase=%d", cv.value, channels.at(ch).number);
				break;

			case CDT_CosineFi:
				cv.value = (double)n * 0.01;
				qDebug("Cos(Fi)=%f phase=%d", cv.value, channels.at(ch).number);
				break;
		}
		ret[ch].values.append(cv);
	}
	
	if (need_electro)
	{
		for (int i = 0; i < registers.count(); i++)
		{
			QByteArray ba;
			// Получение адреса последних данных
			if (registers.at(i).toInt() == 0)
			{
				memcpy(b + 1, "\x08\x04", 2);
				ba = createRequest(b, 3);
			}
			else
			{
				memcpy(b + 1, "\x08\x04\x00", 3);
				b[3] = (byte)(registers.at(i).toInt() - 1);
				ba = createRequest(b, 4);
			}
			this->m_conn->Send(ba);
			if (!this->getFromCounter(&out, 7))
			{
				qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
				return ret;
			}
			res = (byte *)out.constData();
			byte ovrfl = res[1] >> 7;
			res[1] &= 0x7F;
			//qdt - дата + время куда записываются последние данные со счетчика
			QDateTime qdt = fromCounterDT(res + 1, "ihdmy");
			quint16 addr = 0; 
			CounterDataHeader hdr;
			readPackage(res + 6, &addr);
			qDebug("Set4tmPlugin::getData() - Last data: %s address: 0x%.4X\n",
				   qdt.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData(),
				   addr);
			
			// Получаем время интегрирования
			if (registers.at(i).toInt() == 0)
			{
				memcpy(b + 1, "\x08\x06", 2);
				ba = createRequest(b, 3);
			}
			else
			{
				memcpy(b + 1, "\x08\x06\x00", 3);
				b[3] = (byte)(registers.at(i).toInt() - 1);
				ba = createRequest(b, 4);
			}
			this->m_conn->Send(ba);
			if (!this->getFromCounter(&out, 2))
			{
				qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
				return ret;
			}
			res = (byte *)out.constData();
			quint16 itv_len;
			readPackage(res + 1, &itv_len);
			qDebug("Set4tmPlugin::getData() - Interval length is %d minute(s)\n", itv_len);
			
			// Нормируем время относительно времени интегрирования мощности
			since.setTime(QTime(since.time().hour(), (since.time().minute() / itv_len) * itv_len, 0, 0));
		
			qDebug("Set4tmPlugin::getData() - Requested data from %s\n", 
				   since.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData());
			
			int h = since.addSecs(-1 * since.time().minute() * 60).secsTo(qdt.addSecs(-1 * qdt.time().minute() * 60)) / 3600;
			qDebug("Set4tmPlugin::getData() - Requested %d interval(s)\n", h);
		
			// Получаем дату последней записи
			addr -= 8 + 8 * (qdt.time().minute() / itv_len);
			if ((registers.at(i).toInt() == 0)||(registers.at(i).toInt() == 1))
			{
				memcpy(b + 1, "\x06\x03\x00\x00\x07", 5);
			}
			else
			{
				memcpy(b + 1, "\x06\x00\x00\x00\x07", 5);
				b[2] = (byte)(registers.at(i).toInt() + 6);
			}
			writePackage(b + 3, addr);
			ba = createRequest(b, 6);
			this->m_conn->Send(ba);
			if (!this->getFromCounter(&out, 7))
			{
				qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
				return ret;
			}
			res = (byte *)out.constData();
			hdr.interval = res[6];
			cd.hdr.dt = hdr.dt = fromCounterDT(res + 1, "hdmy");
			qDebug("Set4tmPlugin::getData() - Request information about regiter:\n\tdt=%s\n\titv=%d\n\tovrfl=%d\n",
				   hdr.dt.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData(),
				   hdr.interval,
				   ovrfl);
			
			//data_0.hdr = hdr;
			//ret.append(data_0);
			byte itv_per_hour = 60 / hdr.interval; // Количество интервалов в часе
			byte block_size = itv_per_hour * SET4TM_DATASIZE + SET4TM_DATASIZE;
			quint16 max_data_addr = ((int)(0xffff / block_size)) * block_size;
			
			// Определяем адрес искомого интервала
			quint16 addr_tmp = addr, 
					modif = h * (8 + (480 / itv_len));
			if (addr < modif)
				if (!ovrfl)
					addr = 0;
				else
				{
					addr = addr - modif + max_data_addr;
					//addr -= SET4TM_DATASIZE * (since.time().minute() / itv_len);
					if (addr < addr_tmp) addr = addr_tmp;
				}
			else
				addr -= modif;
			
			
			qDebug("Set4tmPlugin::getData() - Address calc:\n\taddr=%.4X .. %d\n\tmodif=%.4X .. %d -> delta=%d\n\taddr=%.4X",
				   addr_tmp,
				   addr_tmp,
				   modif,
				   modif,
				   addr_tmp - modif,
				   addr);
			QByteArray tmp_out;
			out.clear();
		
			// Запрос 05h 84h - показание на начало текущих суток
			bool has_c_value;
			QList<double> c_values;
			if ((registers.at(i).toInt() == 0)||(registers.at(i).toInt() == 1))
			{
				qDebug("Set4tmPlugin::getData() - Request counter value\n");
				byte b2 [] = {this->m_addr, 0x0A, 0x84, 0x00, 0x00, 0x0F, 0x00};
				ba = createRequest((char *)b2, 7);
				this->m_conn->Send(ba);
				QByteArray c_v_total;
				if (!this->getFromCounter(&c_v_total, 16))
				{
					qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
					return ret;
				}
				if (c_v_total.size() < 16) 
				{
					qDebug("Set4tmPlugin::getData() - Wrong response format!\n");
					has_c_value = false;
				}
				else
				{
					has_c_value = true;
					
					// Показание счетчика
					byte * c_v_buf_total = (byte *) c_v_total.constData();
					int c_v_tmp_total;
					for (int c_v_ch = 0; c_v_ch < 4; c_v_ch++)
					{
						readPackage(c_v_buf_total + (4 * c_v_ch) + 1, &c_v_tmp_total, (int)0xFFFFFFFF);
						c_values.append(this->fromCounterData(c_v_tmp_total, &hdr, A, &tr));
						qDebug("Set4tmPlugin::getData() - Counter value by channel %d is %d\n",
							   c_v_ch + 1,
							   c_v_tmp_total);
					}
				}
			}
			else
				has_c_value = false;
			
			
			// Максимально возможное количество запрашиваемых интервалов
			byte pkg_len = Set4tmBufferSize[BS] - SET4TM_DATASIZE, 
				 req_cnt = pkg_len / SET4TM_DATASIZE;
		
			int total_itv = since.secsTo(QDateTime::currentDateTime()) / (hdr.interval * 60);
		
			res = (byte *)out.constData();
			int itv_num = 0;


			//cd.hdr.dt = since; // <- Ошибка при отключении счетчика
			cd.hdr.dt = QDateTime::fromMSecsSinceEpoch(0);
		
			do 
			{
				qDebug("Set4tmPlugin::getData() - Buffer size %d\n", out.size());
				if (out.size() - (res - (byte *)out.constData()) < 8)
				{
					out.remove(0, (res - (byte *)out.constData()));
					if (req_cnt > total_itv) req_cnt = total_itv;
					pkg_len = req_cnt * SET4TM_DATASIZE;
					
					// Проверка на выход за диапазон адресного пространства
					if (pkg_len > max_data_addr - addr)
						pkg_len = max_data_addr - addr;
					
					if (pkg_len <= 0) 
					{
						pkg_len = req_cnt * SET4TM_DATASIZE;
						addr = 0;
					}
					
					while (out.size() < pkg_len)
					{
						qDebug("Set4tmPlugin::getData() - Request data. Address: 0x%.4X\n", addr);
						if ((registers.at(i).toInt() == 0)||(registers.at(i).toInt() == 1))
						{
							memcpy(b + 1, "\x06\x03\x00\x00\0x00", 5);
						}
						else
						{
							memcpy(b + 1, "\x06\x00\x00\x00\x00", 5);
							b[2] = (byte)(registers.at(i).toInt() + 6);
						}
						b[5] = (byte) pkg_len;
						writePackage(b + 3, addr);
						ba = createRequest((char *)b, 6);
						this->m_conn->Send(ba);
						if (!this->getFromCounter(&tmp_out, pkg_len))
						{
							qDebug("Set4tmPlugin::getData() - CRC16 is not correct\n");
							res = 0;
							break;
						}
						if (tmp_out.size() < pkg_len) 
						{
							qDebug("Set4tmPlugin::getData() - Wrong response format!\n");
							res = 0;
							break;
						}
						addr += pkg_len;
						tmp_out.remove(0, 1);
						tmp_out.remove(tmp_out.size() - 2, 2);
						out.append(tmp_out);
					}
					if (res)
						res = (byte *)out.constData();
				}
				if (!res)
					break;
				
				if (itv_num % (itv_per_hour + 1) == 0)
				{
					if (abs(cd.hdr.dt.secsTo(fromCounterDT(res, "hdmy"))) > 7200)
					{
						if (cd.hdr.dt.secsTo(QDateTime::fromMSecsSinceEpoch(0)) > 0)
						{
							qDebug("Set4tmPlugin::getData() - DRIVER ERROR: Received date is earlier than previous!\n\tReceived date: %s\n\tPrev date: %s",
								   fromCounterDT(res, "hdmy").toString("yyyy-MM-dd hh:mm").toAscii().constData(),
								   cd.hdr.dt.toString("yyyy-MM-dd hh:mm").toAscii().constData());
							/*
							do
							{
								ret.removeLast();
							}
							while (ret.last().hdr.dt.secsTo(cd.hdr.dt) <= 3600);
							*/
							//ret.clear();
							//return ret;
							break;
						}
					}
					cd.hdr.dt = fromCounterDT(res, "hdmy");
					cd.hdr.interval = res[5];
					cd.hdr.season = (CounterDataHeader::Season)res[4];
					
					qDebug("Set4tmPlugin::getData() - Header of current hour:\n\tdt=%s\n\titv=%d\n\tseason=%d\n",
						   cd.hdr.dt.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData(),
						   cd.hdr.interval,
						   (int)cd.hdr.season);
					// Останавливаем, если дата вне необходимого диапазона
					// if ((cd.hdr.dt > qdt)||(cd.hdr.dt.daysTo(since) > 0)) break;
					//                             ^ Условие не проходит при замене счетчика
			
					res += 8;
				}
				else
				{
					cd.hdr.status = res[0] >> 7;
					qWarning("Received data to %s\n",
						   cd.hdr.dt.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData());
		
					// Заносим информацию по каналам
					for (int ch = 0; ch < channels.length(); ch++)
					{
						if (channels.at(ch).type != CDT_Electricity)
							continue;
						
						ChannelValue chv;
						chv.hdr = cd.hdr;
						short tmp_v;
						readPackage(res + (channels.at(ch).number - 1) * 2, &tmp_v, (short int)0x7FFF);
						chv.value = this->fromCounterData(tmp_v, &hdr, A, &tr);
						
						chv.c_value = 0;
						qDebug("Set4tmPlugin::getData() - Received profile on %s\n\tChannel: %s\n\tValue: %f\n",
							   chv.hdr.dt.toString("dd/MM/yyyy hh:mm:ss").toAscii().constData(),
							   channels.at(ch).name.toAscii().constData(),
							   chv.value);
						if ((cd.hdr.dt > since)&&(cd.hdr.dt < qdt))
						{
							//ret.at(ch).values.append(chv);
							ret[ch].values.append(chv);
						}
					}
					if ((cd.hdr.dt > since)&&(cd.hdr.dt < qdt)) total_itv--;
					cd.hdr.dt = cd.hdr.dt.addSecs(cd.hdr.interval * 60);
					res += 8;
				}
				itv_num++;
			}
			while ((cd.hdr.dt < qdt)&&(total_itv > 0));
			
			
			qDebug("Set4tmPlugin::getData() - Generation counter value\n");
			// Расчет показаний счетчика, если это возможно
			if (has_c_value)
			{
				for (int ch = 0; ch < channels.length(); ch++)
				{
					if (channels.at(ch).type != CDT_Electricity)
						continue;
						
					qDebug("Set4tmPlugin::getData() - Generation for channel %d\n", ch);
					// Поиск получасовки на начало сегодняшних суток
					int idx = -1;
					for (int v = 0; v < ret.at(ch).values.count(); v++)
					{
						if (ret.at(ch).values.at(v).hdr.dt.date() == qdt.date())
						{
							idx = v;
							break;
						}
					}
					if (idx == -1) 
						continue;
					
					// Высчитываем показания за текущий день
					double st_c_v = c_values.at(channels.at(ch).number - 1);
					ret[ch].values[idx].c_value = st_c_v;
					for (int v = idx + 1 ; v < ret.at(ch).values.count(); v++)
					{
						st_c_v += ret.at(ch).values.at(v - 1).value;
						ret[ch].values[v].c_value = st_c_v;
						qDebug("Set4tmPlugin::getData() - Counter value for %s is %f\n", 
							   ret[ch].values[v].hdr.dt.toString("yyyy-MM-dd hh:mm").toAscii().constData(),
							   ret[ch].values[v].c_value);
					}
					
					// Высчитываем показание за прошлые дни
					st_c_v = c_values.at(channels.at(ch).number - 1);
					for (int v = idx - 1 ; v >= 0; v--)
					{
						st_c_v -= ret.at(ch).values.at(v).value;
						ret[ch].values[v].c_value = st_c_v;
						qDebug("Set4tmPlugin::getData() - Counter value for %s is %f\n", 
							   ret[ch].values[v].hdr.dt.toString("yyyy-MM-dd hh:mm").toAscii().constData(),
							   ret[ch].values[v].c_value);
					}		
				}
			}
		}
	}
	return ret;
}

unsigned char * Set4tmPlugin::getCS(char *data, int length)
{
	unsigned char ret = 0xFF;
	for (int i = 0; i < length; i++)
	{
		ret ^= data[i];
	}
	return &ret;
}

unsigned long Set4tmPlugin::getFactoryNum()
{
	if (!this->m_conn) 
	{
		qDebug("Set4tmPlugin::getFactoryNum() - Connection don't set!\n");
		this->err = "Connection don't set";
		return 0;
	}
	if (this->m_conn->getStatus() != GCS_DATA) 
	{
		qDebug("Set4tmPlugin::getFactoryNum() - Connection must be in GCS_DATA state!\n");
		this->err = "Connection must be in GCS_DATA state";
		return 0;
	}
	char b[] = {this->m_addr, 0x08, 0x00}, * ret;
	QByteArray out;
	this->m_conn->Send(createRequest(b, 3));
	if (!this->getFromCounter(&out, 7))
	{
		qDebug("Set4tmPlugin::getFactoryNum() - CRC16 is not correct\n");
		return 0;
	}
	ret = (char *)out.constData();
	unsigned long v;
	memcpy(&v, ret + 1, 4);
	return swapBytes(v);
}

bool Set4tmPlugin::checkFactoryNum()
{
	return getFactoryNum() == m_desc.number.toULongLong();
}

/*
QByteArray Set4tmPlugin::getFromCounter()
{
	QByteArray ba;
	char crc[2];
	QByteArray tmp;
	do
	{
		tmp = this->m_conn->Receive();
		if (tmp.size() > 0)
		{
			ba.append(tmp);
			memcpy(crc, ba.constData() + (ba.length() - 2), 2);
		}
	}
	while ((memcmp(crc, this->getHash((char *)ba.constData(), ba.length() - 2), 2) != 0)&&(tmp.size() > 0));
	return ba;
}
*/

/* maxsize - максимально допустимая длина ожидаемого пакета.
 * на случай получения слипшихся пактов */
bool Set4tmPlugin::getFromCounter(QByteArray * buffer, quint32 maxsize)
{
	QByteArray ba;
	char crc[2];
	QByteArray tmp;
	maxsize += 3; // Адрес и CRC
	do
	{
		tmp = this->m_conn->Receive();
		if (tmp.size() > 0)
		{
			if ((quint32)ba.size() > maxsize) ba.clear();
			ba.append(tmp);
			memcpy(crc, ba.constData() + (ba.length() - 2), 2);
		}
	}
	while ((memcmp(crc, this->getHash((BYTE *)ba.constData(), ba.length() - 2), 2) != 0)&&(tmp.size() > 0));
	buffer->clear();
	buffer->append(ba);
	return memcmp(crc, this->getHash((BYTE *)ba.constData(), ba.length() - 2), 2) == 0;
}


unsigned char * Set4tmPlugin::getHash(unsigned char * data, int length, bool append)
{
	static const WORD wCRCTable[] = {
	0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
	0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
	0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
	0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
	0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
	0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
	0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
	0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
	0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
	0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
	0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
	0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
	0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
	0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
	0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
	0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
	0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
	0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
	0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
	0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
	0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
	0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
	0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
	0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
	0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
	0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
	0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
	0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
	0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
	0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
	0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
	0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };
	
	BYTE nTemp;
	WORD wCRCWord = 0xFFFF;
	int i = 0;
	
	while ((length--) > 0)
	{
		nTemp = data[i++] ^ wCRCWord;
		wCRCWord >>= 8;
		wCRCWord ^= wCRCTable[nTemp];
	}
	if (append)
	{
		memcpy(data + i, &wCRCWord, sizeof(WORD));
	}
	return (BYTE *)&wCRCWord;
	
}

QString Set4tmPlugin::getLastError()
{
	return this->err;
}

ModuleInfo Set4tmPlugin::getModuleInfo()
{
	ModuleInfo mi;
	mi.description = "Плагин для опроса счетчиков типа СЭБ-1ТМ.01(02), ПСЧ-3ТМ.05, ПСЧ-4ТМ.05, СЭТ-4ТМ.01(02, 03)";
	mi.version = SET4TMPLUGIN_VERSION;
	return mi;
}

bool Set4tmPlugin::getTime(QDateTime * dt)
{
	if (!dt) dt = new QDateTime(QDateTime::fromTime_t(0));

	if (!this->m_conn) 
	{
		qDebug("Set4tmPlugin::getTime() - Connection don't set!\n");
		this->err = "Connection don't set";
		dt = new QDateTime(QDateTime::fromTime_t(0));
		return false;
	}
	if (this->m_conn->getStatus() != GCS_DATA) 
	{
		qDebug("Set4tmPlugin::getTime() - Connection must be in GCS_DATA state!\n");
		this->err = "Connection must be in GCS_DATA state";
		dt = new QDateTime(QDateTime::fromTime_t(0));
		return false;
	}
	char b[] = {this->m_addr, 0x04, 0x00};
	QByteArray ba = createRequest(b, 3), out;
	this->m_conn->Send(ba);
	if (!this->getFromCounter(&out, 8))
	{
		qDebug("Set4tmPlugin::getTime() - CRC16 is not correct\n");
		dt = new QDateTime(QDateTime::fromTime_t(0));
		return false;
	}
	byte * b1 = (byte *) out.constData();
	dt->setTime_t(0);
	dt->setMSecsSinceEpoch(dt->msecsTo(this->fromCounterDT(b1 + 1, "sih dmy")));
	return true;	
}

bool Set4tmPlugin::setTime(int diff)
{
	short time_d;
	if (diff > 0)
		time_d = diff;
	else
		time_d = 0xFFFF + diff + 1;
	
	byte b[] = {this->m_addr, 0x03, 0x0B, 0x00, 0x00};
	writePackage(b + 3, time_d);
	QByteArray ba = createRequest(b, 5), out;
	this->m_conn->Send(ba);
	if (!this->getFromCounter(&out, 1))
	{
		qDebug("Set4tmPlugin::setTime() - CRC16 is not correct\n");
		return false;
	}
	else
	{
		if (out.at(1) != 0)
		{
			qDebug("Set4tmPlugin::setTime() - Error response!");
			return false;
		}
	}
	return true;
}

// TODO: изменить на bool getTRatio(TR *)
bool Set4tmPlugin::getTRatio(TransformationRatio * tr)
{
	if (!tr) tr = new TransformationRatio;
	
	if (!this->m_conn) 
	{
		qDebug("Set4tmPlugin::getTRatio() - Connection don't set!\n");
		this->err = "Connection don't set";
		return false;
	}
	if (this->m_conn->getStatus() != GCS_DATA) 
	{
		qDebug("Set4tmPlugin::getTRatio() - Connection must be in GCS_DATA state!\n");
		this->err = "Connection must be in GCS_DATA state";
		return false;
	}
	char b[] = {this->m_addr, 0x08, 0x02};
	this->m_conn->Send(createRequest(b, 3));
	QByteArray out;
	if (!this->getFromCounter(&out, 10))
	{
		qDebug("Set4tmPlugin::getTRatio() - CRC16 is not correct\n");
		return false;
	}
	char * ret = (char *)out.constData();
	memcpy(&(tr->KTn), ret + 1, 2);
	memcpy(&(tr->KTt), ret + 3, 2);
	tr->KTn = swapBytes(tr->KTn);
	tr->KTt = swapBytes(tr->KTt);
	return true;
}

QDateTime Set4tmPlugin::fromCounterDT(byte * buffer, QString format)
{
	QDateTime dt = QDateTime::fromTime_t(0);
	byte tmp;
	QChar c;
	int h = 0, m = 0, s = 0, d = 1, mn = 1, y = 1999;
	format = format.toLower();
	for (int i = 0; i < format.length(); i++)
	{
		bcd2dec(buffer + i, 2, &tmp);
		c = format.at(i).toAscii();
		if (c == QChar('y')) // year
			y = 2000 + tmp;
		else if (c == 'm') // month
			mn = tmp;
		else if (c == 'd') // day
			d = tmp;
		else if (c == 'h') //hour
			h = tmp;
		else if (c == 'i') // minute
			m = tmp;
		else if (c == 's') // second
			s = tmp;
		else
			continue;
	}
	dt.setDate(QDate(y, mn, d));
	dt.setTime(QTime(h, m, s));
	return dt;
}

double Set4tmPlugin::fromCounterData(quint32 value, 
                                     CounterDataHeader *hdr, 
                                     byte A, 
                                     TransformationRatio *tr)
{
	qDebug("Set4tmPlugin::fromCounterData() - V: %d; A: %d;\n",
	       value,
	       Set4tmConstA[A]);
	return ((double)value / (2 * Set4tmConstA[A])) * tr->KTn * tr->KTt;
}

byte Set4tmPlugin::createRWRI(byte type, byte param, byte phase)
{
	byte ret = (type << 4) | (param << 2) | phase;
	
	return ret;
}

bool Set4tmPlugin::InitSession()
{
	if (!this->m_conn) 
	{
		qDebug("Set4tmPlugin::InitSession() - Connection don't set!\n");
		this->err = "Connection don't set";
		return false;
	}
	if (this->m_conn->getStatus() != GCS_DATA) 
	{
		qDebug("Set4tmPlugin::InitSession() - Connection must be in GCS_DATA state!\n");
		this->err = "Connection must be in GCS_DATA state";
		return false;
	}
	BYTE b[] = {this->m_addr, 0x00, 0x00, 0x00};
	this->getHash(b, 2, true);
	QByteArray ba((const char *)b, 4), out;
	this->m_conn->Send(ba);
	if (!this->getFromCounter(&out, 2))
	{
		qDebug("Set4tmPlugin::InitSession() - CRC16 is not correct\n");
		return false;
	}
	if (out.at(1) != 0)
	{
		return false;
	}
	
	BYTE b1[] = {this->m_addr, 0x01, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00};
	ba.clear();
	memcpy(b1 + 2, m_desc.password.toAscii().constData(), m_desc.password.length());
	this->getHash(b1, 8, true);
	ba.append((const char *)b1, 10);
	this->m_conn->Send(ba);
	if (!this->getFromCounter(&out, 2))
	{
		qDebug("Set4tmPlugin::InitSession() - CRC16 is not correct\n");
		return false;
	}
	if (out.at(1) != 0)
	{
		qDebug("Set4tmPlugin::InitSession() - Counter answer with error code!\n");
		err = "Counter answer with error code";
		return false;
	}
	return true;
}

void Set4tmPlugin::setAddress(char address)
{
	this->m_addr = address;
}

QMap<QString, AddParam>Set4tmPlugin::getAdditionalParameters()
{
	QMap<QString, AddParam> ret;
	
	AddParam p;
	p.description = "Читать регистры счетчика";
	p.value = "0";
	ret["registers"] = p;
	
	return ret;
}

void Set4tmPlugin::setAdditionalParameters(QMap<QString, AddParam> params)
{
	_params = params;
}

void Set4tmPlugin::setConnection(Connection *connection)
{
	qDebug("Set4tmPlugin::setConnection() - Connection %.4X", (int)connection);
	this->m_conn  = connection;
}

unsigned short Set4tmPlugin::updCRC(unsigned char c, unsigned short * oldCRC)
{
	unsigned char srCRCHi[256] = {
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40};
	
	unsigned char srCRCLo[256] = {
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
	0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
	0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
	0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
	0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
	0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
	0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
	0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
	0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40};

	unsigned char *arrCRC;
	arrCRC = (unsigned char *)oldCRC;
	
	unsigned char i = arrCRC[1] ^ c;
	arrCRC[1] = arrCRC[0] ^ srCRCHi[i];
	arrCRC[0] = srCRCLo[i];
	return *oldCRC;
}

Q_EXPORT_PLUGIN(Set4tmPlugin);
