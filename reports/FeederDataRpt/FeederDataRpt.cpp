#include "FeederDataRpt.h"
#include "QtPlugin"

#include <QMenu>
#include <QMessageBox>
#include <QFileDialog>

#include <math.h>

double myround(double value, int dimension)
{
	double a, b;
	a = modf(value, &b);
	int mn = 1;
	for (int i = 1; i <= dimension; i++, mn *= 10);
	a = (int)(a * mn + 0.50000001);
	a = a / mn;
	return a + b;
}


FeederDataRpt::FeederDataRpt()
{
}

void FeederDataRpt::load(PgreSqlDrv *connection, QWidget *window)
{
	Q_INIT_RESOURCE(resources);

	if (!connection->isConnected())
	{
		QMessageBox::critical(window, REPORT_NAME, tr("Подключение к БД не установлено!"));
		return;
	}
	
	this->m_connection = connection;
	this->m_window = window;
	createUi();

	PgreSqlResult * r = connection->exec("select name, id from factory order by name;");
	while (r->notEoF())
	{
		QTreeWidgetItem * item = new QTreeWidgetItem();
		TreeElementDesc * desc = new TreeElementDesc();
		desc->id = r->getValue(1).toInt();
		desc->type = Factory;
		item->setText(0, r->getValue(0));
		item->setIcon(0, QIcon(":/feederdata/images/server.png"));
		item->setData(0, Qt::UserRole, QVariant::fromValue((int)desc));
		ui->twObjects->insertTopLevelItem(r->absolutePos(), item);
		r->moveNext();
	}
	r->close();
}

void FeederDataRpt::createUi()
{
	ui = new Ui::FeederDataForm();
	ui->setupUi(m_window);
	
	if (m_window->layout()) delete m_window->layout();
	m_window->setLayout(ui->mainLayout);

	ui->dteEnd->setDateTime(QDateTime::currentDateTime());
	ui->dteBegin->setDateTime(QDateTime::currentDateTime().addDays(-1));

	connect(ui->dteBegin, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(dateBeginChanged(QDateTime)));
	connect(ui->dteEnd, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(dateEndChanged(QDateTime)));
	connect(ui->cmbItvType, SIGNAL(currentIndexChanged(int)), this, SLOT(intervalTypeChanged(int)));
	connect(ui->twObjects, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(updateTree(QTreeWidgetItem*,int)));
	connect(ui->cmdRefresh, SIGNAL(clicked()), this, SLOT(loadData()));
	connect(ui->dteBegin, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(dtBeginContexMenuReq(QPoint)));
	connect(ui->dteEnd, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(dtEndContexMenuReq(QPoint)));
	connect(ui->cmdExcel, SIGNAL(clicked()), this, SLOT(exportToExcel()));
	
	ui->gvGraph->hide();
	
	ui->cmbValueRound->addItem(tr("кВт*ч"), QVariant::fromValue(1));
	ui->cmbValueRound->addItem(tr("МВт*ч"), QVariant::fromValue(1000));
	
	ui->cmbDisplayType->addItem(QIcon(":/feederdata/images/feeder_sum.png"), tr("Суммарные за период"));
	ui->cmbDisplayType->addItem(QIcon(":/feederdata/images/feeder_intervals.png"), tr("Показания на начало периода"));
	ui->cmbDisplayType->addItem(QIcon(":/feederdata/images/feeder_intervals.png"), tr("Показания на конец периода"));
	
	ui->twData->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
	ui->twData->verticalHeader()->setResizeMode(QHeaderView::Interactive);
	for (int i = 0; i < m_window->children().count(); i++)
	{
		QWidget * w = qobject_cast<QWidget *>(m_window->children().at(i));
		if (w)
			if (w->objectName() != "") w->show();
	}
	
	m_window->setWindowTitle(REPORT_NAME);
	m_window->setWindowState(Qt::WindowNoState);
	m_window->setWindowState(Qt::WindowMaximized);
}

void FeederDataRpt::unload()
{
}

QString FeederDataRpt::getName()
{
	return REPORT_NAME;
}

QString FeederDataRpt::getVersion()
{
	return REPORT_VER;
}

void FeederDataRpt::getPrintableForm(ReportEngine *e)
{
/*	ReportSheet * sheet = new ReportSheet(QSize(REPORTSHEET_DEFAULT_A4_WIDTH, REPORTSHEET_DEFAULT_A4_HEIGHT));
	
	QFont font = QFont("Arial");
	font.setBold(true);
	font.setPixelSize(15);
	e->registerFont("pagetitle", font);
	font = QFont("Arial");
	font.setPixelSize(10);
	e->registerFont("comment", font);
	font = QFont("Arial");
	font.setPixelSize(12);
	e->registerFont("main", font);
	font = QFont("Arial");
	font.setPixelSize(12);
	font.setBold(true);
	e->registerFont("mainbold", font);
	e->appendPage(sheet);
	
	ReportSheetMargins sm;
	sm.bottom = 10;
	sm.top = 15;
	sm.left = 10;
	sm.right = 10;
	sheet->setMargins(sm);
	
	ReportRow * row = sheet->appendRow();
	row->addText(new ReportText(REPORT_NAME, e->font("pagetitle"), Qt::AlignCenter));	
	ReportText * txt = new ReportText(tr("вер. ").append(REPORT_VER), e->font("comment"), Qt::AlignRight);
	txt->setColor(QColor(200, 200, 200));
	row->addText(txt);	

	row = sheet->appendRow();
	row->addText(new ReportText(tr("Наименование объекта: "), e->font("mainbold"), Qt::AlignLeft));	
	QTreeWidgetItem * item = ui->twObjects->selectedItems().at(0);
	QString obj = item->text(0);
	while (item = item->parent())
	{
		obj = item->text(0).append(" ").append(obj);
	}
	row->addText(new ReportText(obj, e->font("main"), Qt::AlignLeft));	

	row = sheet->appendRow();
	row->addText(new ReportText(tr("Данные с "), e->font("mainbold"), Qt::AlignLeft));	
	row->addText(new ReportText(ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), e->font("main"), Qt::AlignLeft));	
	row->addText(new ReportText(tr(" по "), e->font("mainbold"), Qt::AlignLeft));	
	row->addText(new ReportText(ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"), e->font("main"), Qt::AlignLeft));	

	row = sheet->appendRow();
	row->addText(new ReportText(tr("Отчет сформирован "), e->font("mainbold"), Qt::AlignLeft));	
	row->addText(new ReportText(QDateTime::currentDateTime().toString("dd MMMM yyyy hh:mm:ss"), e->font("main"), Qt::AlignLeft));	

	row = sheet->appendRow();
	ReportTable * table = new ReportTable(ui->twData);

	row->addTable(table);
	table->setColumnWidth(0, 115);
	table->setColumnWidth(0, 100);
	
	for (int i = 0; i < (ui->twData->columnCount() - 2) * 0.5; i++)
	{
		table->cell(0, (i + 1) * 2 + 1)->merge(table->cell(0, (i + 1) * 2));
	}*/
}

void FeederDataRpt::updateList(QListWidgetItem * current, QListWidgetItem * prev)
{
	
}

void FeederDataRpt::exportToExcel()
{
	if (ui->twData->rowCount() == 0)
	{
		if (QMessageBox::question(
					m_window,
					tr("Экспорт в MS Excel..."),
					tr("Данных для выгрузки не получено.\r\nВы уверены, что хотите продолжить?"), QMessageBox::Yes, QMessageBox::No) != QMessageBox::Yes)
			return;
	}

	QString path = QFileDialog::getSaveFileName(
				m_window, 
				tr("Сохранить как..."), 
				"c:/", 
				tr("Файл Microsoft Excel (*.csv)"));
	
	if (path == "") 
		return;
	
	
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::critical(
					m_window, 
					tr("Ошибка"),
					tr("Неверное имя файла или директория назначения, либо файл закрыт для изменения!"));
		return;
	}
	file.write(REPORT_NAME.toAscii());
	file.write(tr(" вер. ").append(REPORT_VER).toAscii());
	file.write("\r\n");
	file.write(tr("Объект;").append(ui->twObjects->currentItem()->text(0)).append("\r\n").toAscii());
	file.write(tr("Начальная дата;").append(ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss")).append("\r\n").toAscii());
	file.write(tr("Конечная дата;").append(ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss")).append("\r\n").toAscii());
	file.write(tr("Точность;").append(ui->txtAccuracy->text()).append("\r\n").toAscii());
	file.write(tr("Ед. измерения;").append(ui->cmbValueRound->itemText(ui->cmbValueRound->currentIndex())).append("\r\n").toAscii());
	file.write(tr("Исходные данные для расчета;").append(ui->cmbSource->itemText(ui->cmbSource->currentIndex())).append("\r\n").toAscii());
	
	for (int c = 0; c < ui->twData->columnCount(); c++)
	{
		file.write(ui->twData->horizontalHeaderItem(c)->text().append(";").toAscii());
	}
	file.write("\r\n");
	
	for (int r = 0; r < ui->twData->rowCount(); r++)
	{
		for (int c = 0; c < ui->twData->columnCount(); c++)
		{
			QTableWidgetItem * item = ui->twData->item(r, c);
			if (item)
				file.write(item->text().append(";").toAscii());
			else
				file.write(QString(";").toAscii());
		}
		file.write("\r\n");
	}
	
	file.close();
	
}

void FeederDataRpt::loadData()
{
	if (ui->twObjects->selectedItems().count() == 0) return;
	
	ui->twData->hide();
	ui->twData->clear();
	ui->twData->setRowCount(0);
	
	QTreeWidgetItem * item = ui->twObjects->selectedItems().at(0);
	TreeElementDesc * desc = (TreeElementDesc *)item->data(0, Qt::UserRole).toInt();	
	PgreSqlResult * r = 0;

	switch ((SourceType)ui->cmbSource->currentIndex())
	{
		case Profiles:
			switch (desc->type)
				{
					case Feeder:
						r = m_connection->exec(QString("SELECT cbo.oname as object, cbo.fid as id, cbo.fname as name, cbo.chname as cname, d.channel, d.value FROM (SELECT cbo.fid id, cbo.chid AS channel, sum(d.value) AS value FROM data d LEFT JOIN channels_by_object cbo ON cbo.chid = d.channel WHERE cbo.fid = %1 AND d.dt >= '%2'::timestamp without time zone AND d.dt < '%3'::timestamp without time zone AND d.itv_length = 30 GROUP BY cbo.fid, cbo.chid ) d left join channels_by_object cbo on cbo.chid = d.channel ORDER BY cbo.oname, cbo.fid, cbo.fname, cbo.chname;").arg(QString::number(desc->id), ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
						break;
			
					case Object:
						r = m_connection->exec(QString("SELECT cbo.oname as object, cbo.fid as id, cbo.fname as name, cbo.chname as cname, d.channel, d.value FROM (SELECT cbo.fid id, cbo.chid AS channel, sum(d.value) AS value FROM data d LEFT JOIN channels_by_object cbo ON cbo.chid = d.channel WHERE cbo.oid = %1 AND d.dt >= '%2'::timestamp without time zone AND d.dt < '%3'::timestamp without time zone AND d.itv_length = 30 GROUP BY cbo.fid, cbo.chid ) d left join channels_by_object cbo on cbo.chid = d.channel ORDER BY cbo.oname, cbo.fid, cbo.fname, cbo.chname;").arg(QString::number(desc->id), ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
						break;
			
					case Factory:
						r = m_connection->exec(QString("SELECT cbo.oname as object, cbo.fid as id, cbo.fname as name, cbo.chname as cname, d.channel, d.value FROM (SELECT cbo.fid id, cbo.chid AS channel, sum(d.value) AS value FROM data d LEFT JOIN channels_by_object cbo ON cbo.chid = d.channel WHERE cbo.ftid = %1 AND d.dt >= '%2'::timestamp without time zone AND d.dt < '%3'::timestamp without time zone AND d.itv_length = 30 GROUP BY cbo.fid, cbo.chid ) d left join channels_by_object cbo on cbo.chid = d.channel ORDER BY cbo.oname, cbo.fid, cbo.fname, cbo.chname;").arg(QString::number(desc->id), ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
						break;
				}
			break;
			
		case CounterData:
			switch ((DisplayType)ui->cmbDisplayType->currentIndex())
			{
				case Summ:
					switch (desc->type)
						{
							case Feeder:
								r = m_connection->exec(QString("SELECT cbo.oname as object, cbo.fid as id, cbo.fname as name, cbo.chname as cname, d.channel, d.value * (f.kt_h / f.kt_l * f.kn_h / f.kn_l) as value FROM (SELECT cbo.fid id, cbo.chid AS channel, max(d.c_value) - min(d.c_value) AS value FROM data d LEFT JOIN channels_by_object cbo ON cbo.chid = d.channel WHERE cbo.fid = %1 AND (d.dt = '%2' OR d.dt = '%3') AND d.itv_length = 30 GROUP BY cbo.fid, cbo.chid ) d left join channels_by_object cbo on cbo.chid = d.channel left join feeder f on f.id=cbo.fid and f.id=d.id ORDER BY cbo.oname, cbo.fid, cbo.fname, cbo.chname;").arg(QString::number(desc->id), ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
								break;
					
							case Object:
								r = m_connection->exec(QString("SELECT cbo.oname as object, cbo.fid as id, cbo.fname as name, cbo.chname as cname, d.channel, d.value * (f.kt_h / f.kt_l * f.kn_h / f.kn_l) as value FROM (SELECT cbo.fid id, cbo.chid AS channel, max(d.c_value) - min(d.c_value) AS value FROM data d LEFT JOIN channels_by_object cbo ON cbo.chid = d.channel WHERE cbo.oid = %1 AND (d.dt = '%2' OR d.dt = '%3') AND d.itv_length = 30 GROUP BY cbo.fid, cbo.chid ) d left join channels_by_object cbo on cbo.chid = d.channel left join feeder f on f.id=cbo.fid and f.id=d.id ORDER BY cbo.oname, cbo.fid, cbo.fname, cbo.chname;").arg(QString::number(desc->id), ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
								break;
					
							case Factory:
								r = m_connection->exec(QString("SELECT cbo.oname as object, cbo.fid as id, cbo.fname as name, cbo.chname as cname, d.channel, d.value * (f.kt_h / f.kt_l * f.kn_h / f.kn_l) as value FROM (SELECT cbo.fid id, cbo.chid AS channel, max(d.c_value) - min(d.c_value) AS value FROM data d LEFT JOIN channels_by_object cbo ON cbo.chid = d.channel WHERE cbo.ftid = %1 AND (d.dt = '%2' OR d.dt = '%3') AND d.itv_length = 30 GROUP BY cbo.fid, cbo.chid ) d left join channels_by_object cbo on cbo.chid = d.channel left join feeder f on f.id=cbo.fid and f.id=d.id ORDER BY cbo.oname, cbo.fid, cbo.fname, cbo.chname;").arg(QString::number(desc->id), ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
								break;
						}
					break;
					
				case OnBegin:
					switch (desc->type)
						{
							case Feeder:
								r = m_connection->exec(QString("SELECT cbo.oname as object, cbo.fid as id, cbo.fname as name, cbo.chname as cname, d.channel, d.value as value FROM (SELECT cbo.fid id, cbo.chid AS channel, d.c_value AS value FROM data d LEFT JOIN channels_by_object cbo ON cbo.chid = d.channel WHERE cbo.fid = %1 AND d.dt = '%2' AND d.itv_length = 30 ) d left join channels_by_object cbo on cbo.chid = d.channel ORDER BY cbo.oname, cbo.fid, cbo.fname, cbo.chname;").arg(QString::number(desc->id), ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
								break;
					
							case Object:
								r = m_connection->exec(QString("SELECT cbo.oname as object, cbo.fid as id, cbo.fname as name, cbo.chname as cname, d.channel, d.value as value FROM (SELECT cbo.fid id, cbo.chid AS channel, d.c_value AS value FROM data d LEFT JOIN channels_by_object cbo ON cbo.chid = d.channel WHERE cbo.oid = %1 AND d.dt = '%2' AND d.itv_length = 30 ) d left join channels_by_object cbo on cbo.chid = d.channel ORDER BY cbo.oname, cbo.fid, cbo.fname, cbo.chname;").arg(QString::number(desc->id), ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
								break;
					
							case Factory:
								r = m_connection->exec(QString("SELECT cbo.oname as object, cbo.fid as id, cbo.fname as name, cbo.chname as cname, d.channel, d.value as value FROM (SELECT cbo.fid id, cbo.chid AS channel, d.c_value AS value FROM data d LEFT JOIN channels_by_object cbo ON cbo.chid = d.channel WHERE cbo.ftid = %1 AND d.dt = '%2' AND d.itv_length = 30 ) d left join channels_by_object cbo on cbo.chid = d.channel ORDER BY cbo.oname, cbo.fid, cbo.fname, cbo.chname;").arg(QString::number(desc->id), ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
								break;
						}
					break;
					
				case OnEnd:
					switch (desc->type)
						{
							case Feeder:
								r = m_connection->exec(QString("SELECT cbo.oname as object, cbo.fid as id, cbo.fname as name, cbo.chname as cname, d.channel, d.value as value FROM (SELECT cbo.fid id, cbo.chid AS channel, d.c_value AS value FROM data d LEFT JOIN channels_by_object cbo ON cbo.chid = d.channel WHERE cbo.fid = %1 AND d.dt = '%2' AND d.itv_length = 30 ) d left join channels_by_object cbo on cbo.chid = d.channel ORDER BY cbo.oname, cbo.fid, cbo.fname, cbo.chname;").arg(QString::number(desc->id), ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
								break;
					
							case Object:
								r = m_connection->exec(QString("SELECT cbo.oname as object, cbo.fid as id, cbo.fname as name, cbo.chname as cname, d.channel, d.value as value FROM (SELECT cbo.fid id, cbo.chid AS channel, d.c_value AS value FROM data d LEFT JOIN channels_by_object cbo ON cbo.chid = d.channel WHERE cbo.oid = %1 AND d.dt = '%2' AND d.itv_length = 30 ) d left join channels_by_object cbo on cbo.chid = d.channel ORDER BY cbo.oname, cbo.fid, cbo.fname, cbo.chname;").arg(QString::number(desc->id), ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
								break;
					
							case Factory:
								r = m_connection->exec(QString("SELECT cbo.oname as object, cbo.fid as id, cbo.fname as name, cbo.chname as cname, d.channel, d.value as value FROM (SELECT cbo.fid id, cbo.chid AS channel, d.c_value AS value FROM data d LEFT JOIN channels_by_object cbo ON cbo.chid = d.channel WHERE cbo.ftid = %1 AND d.dt = '%2' AND d.itv_length = 30 ) d left join channels_by_object cbo on cbo.chid = d.channel ORDER BY cbo.oname, cbo.fid, cbo.fname, cbo.chname;").arg(QString::number(desc->id), ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
								break;
						}
					break;
			}
			break;
	}

	double max_val = 0;
	if (r)
	{
		QStringList hdr;
		hdr.append(tr("Подстанция"));
		hdr.append(tr("Наименование фидера"));
		ui->twData->setColumnCount(2);
		ui->twData->setHorizontalHeaderLabels(hdr);
		int itv = -1;
		while (r->notEoF())
		{
			int clmn = 0;
			for (int i = 1; i < ui->twData->columnCount(); i++)
			{
				if (ui->twData->horizontalHeaderItem(i)->data(Qt::UserRole) == r->getValue("cname"))
				{
					clmn = i;
					break;
				}
			}
			if (clmn == 0)
			{
				clmn = ui->twData->columnCount();
				ui->twData->setColumnCount(clmn + 1);
				hdr.append(r->getValue("cname"));
				ui->twData->setHorizontalHeaderLabels(hdr);
				ui->twData->horizontalHeaderItem(clmn)->setData(Qt::UserRole, QVariant::fromValue(r->getValue("cname")));
			}

			if (itv != r->getValue("id").toInt())
			{
				ui->twData->setRowCount(ui->twData->rowCount() + 1);
				
				QTableWidgetItem * twi = new QTableWidgetItem();
				twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				twi->setText(r->getValue("name"));
				ui->twData->setItem(ui->twData->rowCount() - 1, 1, twi);
				itv = r->getValue("id").toInt();

				twi = new QTableWidgetItem();
				twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				twi->setText(r->getValue("object"));
				ui->twData->setItem(ui->twData->rowCount() - 1, 0, twi);
			}
			QTableWidgetItem * twi = new QTableWidgetItem();
			twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			if (ui->txtAccuracy->text().toInt() >= 0)
				twi->setText(QString::number(myround(r->getValue("value").toDouble() / ui->cmbValueRound->itemData(ui->cmbValueRound->currentIndex()).toDouble(), ui->txtAccuracy->text().toInt()), 'f', ui->txtAccuracy->text().toInt()));
			else
				twi->setText(QString::number(r->getValue("value").toDouble() / ui->cmbValueRound->itemData(ui->cmbValueRound->currentIndex()).toDouble(), 'f'));
			if (r->getValue("value").toDouble() > max_val) max_val = r->getValue("value").toDouble();
			ui->twData->setItem(ui->twData->rowCount() - 1, clmn, twi);
			
			r->moveNext();
			
		}
		r->close();	
	}
	ui->twData->show();
}

void FeederDataRpt::dateBeginChanged(QDateTime dt)
{
	switch ((IntervalType)ui->cmbItvType->currentIndex())
	{
		case IT_Manual:
			break;
			
		case IT_Day:
			ui->dteEnd->setDateTime(dt.addDays(1));
			break;
			
		case IT_Week:
			ui->dteEnd->setDateTime(dt.addDays(7));
			break;
			
		case IT_Month:
			ui->dteEnd->setDateTime(dt.addMonths(1));
			break;
	}
}

void FeederDataRpt::dateEndChanged(QDateTime dt)
{
	switch ((IntervalType)ui->cmbItvType->currentIndex())
	{
		case IT_Manual:
			break;
			
		case IT_Day:
			ui->dteBegin->setDateTime(dt.addDays(-1));
			break;
			
		case IT_Week:
			ui->dteBegin->setDateTime(dt.addDays(-7));
			break;
			
		case IT_Month:
			ui->dteBegin->setDateTime(dt.addMonths(-1));
			break;
	}
}

void FeederDataRpt::intervalTypeChanged(int index)
{
	switch ((IntervalType)index)
	{
		case IT_Manual:
			break;
			
		case IT_Day:
			ui->dteBegin->setDateTime(ui->dteEnd->dateTime().addDays(-1));
			break;
			
		case IT_Week:
			ui->dteBegin->setDateTime(ui->dteEnd->dateTime().addDays(-7));
			break;
			
		case IT_Month:
			ui->dteBegin->setDateTime(ui->dteEnd->dateTime().addMonths(-1));
			break;
	}
}

void FeederDataRpt::updateTree(QTreeWidgetItem * parent, int column)
{
	parent->takeChildren();
	TreeElementDesc * desc = (TreeElementDesc *)parent->data(column, Qt::UserRole).toInt();
	PgreSqlResult * r;
	QIcon icon;
	TreeElementType type;
	switch (desc->type)
	{
		case Factory:
			r = m_connection->exec(QString("select id, name from object where factory=%1;").arg(QString::number(desc->id)));
			icon = QIcon(":/feederdata/images/object.png");
			type = Object;
			break;
			
		case Object:
			r = m_connection->exec(QString("select id, name from feeder where object=%1;").arg(QString::number(desc->id)));
			icon = QIcon(":/feederdata/images/feeder.png");
			type = Feeder;
			break;
			
		case Feeder:
			loadData();
			break;
	}
	
	if (r)
		while (r->notEoF())
		{
			QTreeWidgetItem * item = new QTreeWidgetItem();
			desc = new TreeElementDesc();
			desc->id = r->getValue("id").toInt();
			desc->type = type;
			item->setText(0, r->getValue("name"));
			item->setIcon(0, icon);
			item->setData(0, Qt::UserRole, QVariant::fromValue((int)desc));
			parent->addChild(item);
			r->moveNext();
		}
	
}

void FeederDataRpt::dtBeginContexMenuReq(QPoint position)
{
	QMenu mnuDateBegin(m_window);
	QAction * actSetStart = new QAction(tr("Установить на начало дня"), m_window);
	actSetStart->setData(QVariant::fromValue((int)DAS_DAY));
	mnuDateBegin.addAction(actSetStart);
	connect(actSetStart, SIGNAL(triggered()), this, SLOT(setdtBeginDayBegin()));

	QAction * actSetStartMonth = new QAction(tr("Установить на начало текущего месяца"), m_window);
	actSetStartMonth->setData(QVariant::fromValue((int)DAS_CURRMONTH));
	mnuDateBegin.addAction(actSetStartMonth);
	connect(actSetStartMonth, SIGNAL(triggered()), this, SLOT(setdtBeginDayBegin()));

	QAction * actSetStartNextMonth = new QAction(tr("Установить на начало следующего месяца"), m_window);
	actSetStartNextMonth->setData(QVariant::fromValue((int)DAS_NEXTMONTH));
	mnuDateBegin.addAction(actSetStartNextMonth);
	connect(actSetStartNextMonth, SIGNAL(triggered()), this, SLOT(setdtBeginDayBegin()));
	
	QWidget * w = (QWidget *) ui->dteBegin;
	while (w->parent())
	{
		position += w->geometry().topLeft();
		w = w->parentWidget();
	}
	position += QPoint(0, mnuDateBegin.geometry().height());
	mnuDateBegin.exec(position);
	
}

void FeederDataRpt::dtEndContexMenuReq(QPoint position)
{
	QMenu mnuDateBegin(m_window);
	QAction * actSetStart = new QAction(tr("Установить на начало дня"), m_window);
	actSetStart->setData(QVariant::fromValue((int)DAS_DAY));
	mnuDateBegin.addAction(actSetStart);
	connect(actSetStart, SIGNAL(triggered()), this, SLOT(setdtEndDayBegin()));

	QAction * actSetStartMonth = new QAction(tr("Установить на начало текущего месяца"), m_window);
	actSetStartMonth->setData(QVariant::fromValue((int)DAS_CURRMONTH));
	mnuDateBegin.addAction(actSetStartMonth);
	connect(actSetStartMonth, SIGNAL(triggered()), this, SLOT(setdtEndDayBegin()));

	QAction * actSetStartNextMonth = new QAction(tr("Установить на начало следующего месяца"), m_window);
	actSetStartNextMonth->setData(QVariant::fromValue((int)DAS_NEXTMONTH));
	mnuDateBegin.addAction(actSetStartNextMonth);
	connect(actSetStartNextMonth, SIGNAL(triggered()), this, SLOT(setdtEndDayBegin()));
		
	QWidget * w = (QWidget *) ui->dteBegin;
	while (w->parent())
	{
		position += w->geometry().topLeft();
		w = w->parentWidget();
	}
	position += QPoint(0, mnuDateBegin.geometry().height());
	mnuDateBegin.exec(position);
	
}

void FeederDataRpt::setdtBeginDayBegin()
{
	QAction * act = (QAction *)sender();
	
	DateAutoSet das = (DateAutoSet)(act->data().value<int>());
	QDateTime dt = QDateTime::currentDateTime();
	switch (das)
	{
		case DAS_DAY:
			ui->dteBegin->setTime(ui->dteBegin->time().addSecs(-1 * (ui->dteBegin->time().hour() * 3600 + ui->dteBegin->time().minute() * 60 + ui ->dteBegin->time().second())));
			break;

		case DAS_CURRMONTH:
			ui->dteBegin->setTime(ui->dteBegin->time().addSecs(-1 * (ui->dteBegin->time().hour() * 3600 + ui->dteBegin->time().minute() * 60 + ui ->dteBegin->time().second())));
			ui->dteBegin->setDate(ui->dteBegin->date().addDays(-1 * (ui->dteBegin->date().day() - 1)));
			break;

		case DAS_NEXTMONTH:
			ui->dteBegin->setTime(ui->dteBegin->time().addSecs(-1 * (ui->dteBegin->time().hour() * 3600 + ui->dteBegin->time().minute() * 60 + ui ->dteBegin->time().second())));
			ui->dteBegin->setDate(ui->dteBegin->date().addDays(-1 * (ui->dteBegin->date().day() - 1)));
			ui->dteBegin->setDate(ui->dteBegin->date().addMonths(1));
			break;
	}
}

void FeederDataRpt::setdtEndDayBegin()
{
	QAction * act = (QAction *)sender();
	DateAutoSet das = (DateAutoSet)(act->data().value<int>());
	switch (das)
	{
		case DAS_DAY:
			ui->dteEnd->setTime(ui->dteEnd->time().addSecs(-1 * (ui->dteEnd->time().hour() * 3600 + ui->dteEnd->time().minute() * 60 + ui ->dteEnd->time().second())));
			break;

		case DAS_CURRMONTH:
			ui->dteEnd->setTime(ui->dteEnd->time().addSecs(-1 * (ui->dteEnd->time().hour() * 3600 + ui->dteEnd->time().minute() * 60 + ui ->dteEnd->time().second())));
			ui->dteEnd->setDate(ui->dteEnd->date().addDays(-1 * (ui->dteEnd->date().day() - 1)));
			break;

		case DAS_NEXTMONTH:
			ui->dteEnd->setTime(ui->dteEnd->time().addSecs(-1 * (ui->dteEnd->time().hour() * 3600 + ui->dteEnd->time().minute() * 60 + ui ->dteEnd->time().second())));
			ui->dteEnd->setDate(ui->dteEnd->date().addDays(-1 * (ui->dteEnd->date().day() - 1)));
			ui->dteEnd->setDate(ui->dteEnd->date().addMonths(1));
			break;
	}
}



Q_EXPORT_PLUGIN(FeederDataRpt);
