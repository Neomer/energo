#include "LastDataRpt.h"
#include <QMessageBox>
#include <QtPlugin>
#include <QFileDialog>
#include <QFile>

Q_EXPORT_PLUGIN(LastDataRpt);

#include <math.h>

double myround(double value, int dimension)
{
	double a, b;
	a = modf(value, &b);
	int mn = 1;
	for (int i = 1; i <= dimension; i++, mn *= 10);
	a = qRound(a * mn);
	a = a / mn;
	return a + b;
}

LastDataRpt::LastDataRpt()
{
}

void LastDataRpt::load(PgreSqlDrv *connection, QWidget *window)
{
	if (!connection->isConnected())
	{
		QMessageBox::critical(window, REPORT_NAME, tr("Подключение к БД не установлено!"));
		return;
	}
	
	this->m_connection = connection;
	this->m_window = window;
	createUi();
}

void LastDataRpt::unload()
{
}

QString LastDataRpt::getName()
{
	return REPORT_NAME;
}

QString LastDataRpt::getVersion()
{
	return REPORT_VER;
}

void LastDataRpt::getPrintableForm(ReportEngine *engine)
{
}

void LastDataRpt::loadData()
{
	ui->twData->hide();
	ui->twData->clearContents();
/*
select cbo.ftname, cbo.oname, cbo.fname, cbo.chname, d.value from channels_by_object cbo left join data d on cbo.chid=d.channel left join channel ch on ch.id=cbo.chid where d.dt = ch.last_date;
*/
	
	QTreeWidgetItem * item = ui->twObjects->selectedItems().at(0);
	TreeElementDesc * desc = (TreeElementDesc *)item->data(0, Qt::UserRole).toInt();	
	PgreSqlResult * r = 0;
	switch (desc->type)
	{
		case Channel:
			r = m_connection->exec(QString("select cbo.ftname, cbo.oname, cbo.fname, cbo.cnumber, cbo.chname, d.value from channels_by_object cbo left join data d on cbo.chid=d.channel left join channel ch on ch.id=cbo.chid where d.dt = ch.last_date and cbo.chid=%1 order by cbo.ftname, cbo.oname, cbo.fname, cbo.cnumber, cbo.chname;").arg(
									   QString::number(desc->id)));
			break;
		
		case Counter:
			r = m_connection->exec(QString("select cbo.ftname, cbo.oname, cbo.fname, cbo.cnumber, cbo.chname, d.value from channels_by_object cbo left join data d on cbo.chid=d.channel left join channel ch on ch.id=cbo.chid where d.dt = ch.last_date and cbo.cid=%1 order by cbo.ftname, cbo.oname, cbo.fname, cbo.cnumber, cbo.chname;").arg(
									   QString::number(desc->id)));
			break;
			
		case Feeder:
			r = m_connection->exec(QString("select cbo.ftname, cbo.oname, cbo.fname, cbo.cnumber, cbo.chname, d.value from channels_by_object cbo left join data d on cbo.chid=d.channel left join channel ch on ch.id=cbo.chid where d.dt = ch.last_date and cbo.fid=%1 order by cbo.ftname, cbo.oname, cbo.fname, cbo.cnumber, cbo.chname;").arg(
									   QString::number(desc->id)));
			break;

		case Object:
			r = m_connection->exec(QString("select cbo.ftname, cbo.oname, cbo.fname, cbo.cnumber, cbo.chname, d.value from channels_by_object cbo left join data d on cbo.chid=d.channel left join channel ch on ch.id=cbo.chid where d.dt = ch.last_date and cbo.oid=%1 order by cbo.ftname, cbo.oname, cbo.fname, cbo.cnumber, cbo.chname;").arg(
									   QString::number(desc->id)));
			break;

		case Factory:
			r = m_connection->exec(QString("select cbo.ftname, cbo.oname, cbo.fname, cbo.cnumber, cbo.chname, d.value from channels_by_object cbo left join data d on cbo.chid=d.channel left join channel ch on ch.id=cbo.chid where d.dt = ch.last_date and cbo.ftid=%1 order by cbo.ftname, cbo.oname, cbo.fname, cbo.cnumber, cbo.chname;").arg(
									   QString::number(desc->id)));
			break;
	}
	if (r)
	{
		ui->twData->setColumnCount(r->numFields());
		ui->twData->setHorizontalHeaderLabels(QStringList() << 
											  tr("Предприятие") <<
											  tr("Подстанция") <<
											  tr("Фидер") <<
											  tr("Счетчик") <<
											  tr("Канал") <<
											  tr("Значение"));
		ui->twData->setRowCount(r->numRows());
		while (r->notEoF())
		{
			for (int c = 0; c < ui->twData->columnCount(); c++)
			{
				QTableWidgetItem * twi = new QTableWidgetItem();
				twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				
				twi->setText(r->getValue(c));
				ui->twData->setItem(r->absolutePos(), c, twi);
			}
			
			r->moveNext();
			
		}
		r->close();
	}
	ui->twData->show();
}

void LastDataRpt::createUi()
{
	ui = new Ui::LastDataForm();
	ui->setupUi(m_window);
	
	if (m_window->layout()) delete m_window->layout();
	m_window->setLayout(ui->mainLayout);
	
	ui->gvGraph->setVisible(false);

	connect(ui->twObjects, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(updateTree(QTreeWidgetItem*,int)));
	connect(ui->cmdRefresh, SIGNAL(clicked()), this, SLOT(loadData()));
	connect(ui->cmdExcel, SIGNAL(clicked()), this, SLOT(exportToExcel()));

	PgreSqlResult * r = m_connection->exec("select name, id from factory order by name;");
	while (r->notEoF())
	{
		QTreeWidgetItem * item = new QTreeWidgetItem();
		TreeElementDesc * desc = new TreeElementDesc();
		desc->id = r->getValue(1).toInt();
		desc->type = Factory;
		item->setText(0, r->getValue(0));
		item->setIcon(0, QIcon(":/lastdatarpt/images/server.png"));
		item->setData(0, Qt::UserRole, QVariant::fromValue((int)desc));
		ui->twObjects->insertTopLevelItem(r->absolutePos(), item);
		r->moveNext();
	}
	r->close();
	
	m_window->setWindowTitle(REPORT_NAME);
	m_window->setWindowState(Qt::WindowNoState);
	m_window->setWindowState(Qt::WindowMaximized);
}



void LastDataRpt::updateTree(QTreeWidgetItem *parent, int column)
{
	parent->takeChildren();
	TreeElementDesc * desc = (TreeElementDesc *)parent->data(column, Qt::UserRole).toInt();
	PgreSqlResult * r;
	QIcon icon;
	TreeElementType type;
	switch (desc->type)
	{
		case Factory:
			r = m_connection->exec(QString("select id, name from object where factory=%1 order by name;").arg(QString::number(desc->id)));
			icon = QIcon(":/lastdatarpt/images/object.png");
			type = Object;
			break;
			
		case Object:
			r = m_connection->exec(QString("select id, name from feeder where object=%1 order by name;").arg(QString::number(desc->id)));
			icon = QIcon(":/lastdatarpt/images/feeder.png");
			type = Feeder;
			break;
			
		case Feeder:
			r = m_connection->exec(QString("select id, c_number as name from counter where feeder=%1 order by c_number;").arg(QString::number(desc->id)));
			icon = QIcon(":/lastdatarpt/images/counter.png");
			type = Counter;
			break;
			
		case Counter:
			r = m_connection->exec(QString("select id, name from channel where counter=%1 order by name;").arg(QString::number(desc->id)));
			icon = QIcon(":/lastdatarpt/images/channel.png");
			type = Channel;
			break;
		
		case Channel:
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

void LastDataRpt::exportToExcel()
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
	
	for (int c = 0; c < ui->twData->columnCount(); c++)
	{
		file.write(ui->twData->horizontalHeaderItem(c)->text().append(";").toAscii());
	}
	file.write("\r\n");
	
	for (int r = 0; r < ui->twData->rowCount(); r++)
	{
		for (int c = 0; c < ui->twData->columnCount(); c++)
		{
			file.write(ui->twData->item(r, c)->text().append(";").toAscii());
		}
		file.write("\r\n");
	}
	
	file.close();
}
