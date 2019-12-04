#include "ManualInputRpt.h"
#include <QtPlugin>
#include <QMenu>
#include <QMessageBox>
#include <QGridLayout>
#include <QHeaderView>

Q_EXPORT_PLUGIN(ManualInputRpt);


ManualInputRpt::ManualInputRpt()
{
}

void ManualInputRpt::load(PgreSqlDrv *connection, QWidget *window)
{
	Q_INIT_RESOURCE(resources);

	if (!connection->isConnected())
	{
		QMessageBox::critical(window, REPORT_NAME, tr("Подключение к БД не установлено!"));
		return;
	}

	this->ui = new Ui::ManualInputForm();
    this->ui->setupUi(window);
	m_connection = connection;
    m_parent = window;
	
	CreateUi();

	PgreSqlResult * r = connection->exec("select name, id from factory order by name;");
	while (r->notEoF())
	{
		QTreeWidgetItem * item = new QTreeWidgetItem();
		TreeElementDesc * desc = new TreeElementDesc();
		desc->id = r->getValue(1).toInt();
		desc->type = Factory;
		item->setText(0, r->getValue(0));
		item->setIcon(0, QIcon(":/manualinput/images/server.png"));
		item->setData(0, Qt::UserRole, QVariant::fromValue((int)desc));
		ui->twObjects->insertTopLevelItem(r->absolutePos(), item);
		r->moveNext();
	}
	r->close();
}

void ManualInputRpt::unload()
{
}


void ManualInputRpt::CreateUi()
{
	m_parent->setWindowState(Qt::WindowNoState);
    m_parent->setWindowState(Qt::WindowMaximized);
    
    if (m_parent->layout()) delete m_parent->layout();
    m_parent->setLayout(this->ui->mainLayout);
    m_parent->setWindowTitle(REPORT_NAME);

	connect(ui->dteBegin, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(dateBeginChanged(QDateTime)));
	connect(ui->dteEnd, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(dateEndChanged(QDateTime)));
	connect(ui->dteBegin, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(dtBeginContexMenuReq(QPoint)));
	connect(ui->dteEnd, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(dtEndContexMenuReq(QPoint)));
	connect(ui->cmbItvType, SIGNAL(currentIndexChanged(int)), this, SLOT(intervalTypeChanged(int)));
	connect(ui->twObjects, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(updateTree(QTreeWidgetItem*,int)));
	connect(ui->cmdRefresh, SIGNAL(clicked()), this, SLOT(loadData()));

	ui->dteEnd->setDateTime(QDateTime::currentDateTime());
	ui->dteBegin->setDateTime(QDateTime::currentDateTime().addDays(-1));
}


void ManualInputRpt::dateBeginChanged(QDateTime dt)
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

void ManualInputRpt::dateEndChanged(QDateTime dt)
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

void ManualInputRpt::intervalTypeChanged(int index)
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
QString ManualInputRpt::getName()
{
	return REPORT_NAME;
}

QString ManualInputRpt::getVersion()
{
	return REPORT_VER;
}

void ManualInputRpt::getPrintableForm(ReportEngine *engine)
{
}

void ManualInputRpt::updateTree(QTreeWidgetItem *parent, int column)
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
			icon = QIcon(":/manualinput/images/object.png");
			type = Object;
			break;
			
		case Object:
			r = m_connection->exec(QString("select id, name from feeder where object=%1 order by name;").arg(QString::number(desc->id)));
			icon = QIcon(":/manualinput/images/feeder.png");
			type = Feeder;
			break;
			
		case Feeder:
			r = m_connection->exec(QString("select id, c_number as name from counter where feeder=%1 order by c_number;").arg(QString::number(desc->id)));
			icon = QIcon(":/manualinput/images/counter.png");
			type = Counter;
			break;
			
		case Counter:
			r = m_connection->exec(QString("select id, name from channel where counter=%1 order by name;").arg(QString::number(desc->id)));
			icon = QIcon(":/manualinput/images/channel.png");
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

void ManualInputRpt::loadData()
{
	ui->twData->hide();
	ui->twData->clearContents();
	
	QTreeWidgetItem * item = ui->twObjects->selectedItems().at(0);
	TreeElementDesc * desc = (TreeElementDesc *)item->data(0, Qt::UserRole).toInt();	
	PgreSqlResult * r = 0;
	switch (desc->type)
	{
		case Channel:
			r = m_connection->exec(QString("select d.date, d.itv, ch.index as channel, d.itv_length, sum(d.value) as value from data d left join channel ch on ch.id=d.channel where ch.id=%1 and d.dt >= '%2' and d.dt < '%3' and d.itv_length=%4 group by d.date, d.itv, ch.index, d.itv_length order by d.date, d.itv, ch.index;").arg(
									   QString::number(desc->id), 
									   ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), 
									   ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
									   ui->cmbItvLength->itemData(ui->cmbItvLength->currentIndex()).toString()));
			break;
		
		case Counter:
			r = m_connection->exec(QString("select d.date, d.itv, ch.index as channel, d.itv_length, sum(d.value) as value from data d left join channel ch on ch.id=d.channel left join counter c on c.id=ch.counter where c.id=%1 and d.dt >= '%2' and d.dt < '%3' and d.itv_length=%4 group by d.date, d.itv, ch.index, d.itv_length order by d.date, d.itv, ch.index;").arg(
									   QString::number(desc->id), 
									   ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), 
									   ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
									   ui->cmbItvLength->itemData(ui->cmbItvLength->currentIndex()).toString()));
			break;
			
		case Feeder:
			r = m_connection->exec(QString("select d.date, d.itv, ch.index as channel, d.itv_length, sum(d.value) as value from data d left join channel ch on ch.id=d.channel left join counter c on c.id=ch.counter left join feeder f on f.id=c.feeder where f.id=%1 and d.dt >= '%2' and d.dt < '%3' and d.itv_length=%4 group by d.date, d.itv, ch.index, d.itv_length order by d.date, d.itv, ch.index;").arg(
									   QString::number(desc->id), 
									   ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), 
									   ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
									   ui->cmbItvLength->itemData(ui->cmbItvLength->currentIndex()).toString()));
			break;

		case Object:
			r = m_connection->exec(QString("select d.date, d.itv, ch.index as channel, d.itv_length, sum(d.value) as value from data d left join channel ch on ch.id=d.channel left join counter c on c.id=ch.counter left join feeder f on f.id=c.feeder left join object o on o.id=f.object where o.id=%1 and d.dt >= '%2' and d.dt < '%3' and d.itv_length=%4 group by d.date, d.itv, ch.index, d.itv_length order by d.date, d.itv, ch.index;").arg(
									   QString::number(desc->id), 
									   ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), 
									   ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
									   ui->cmbItvLength->itemData(ui->cmbItvLength->currentIndex()).toString()));
			break;

		case Factory:
			r = m_connection->exec(QString("select d.date, d.itv, ch.index as channel, d.itv_length, sum(d.value) as value from data d left join channel ch on ch.id=d.channel left join counter c on c.id=ch.counter left join feeder f on f.id=c.feeder left join object o on o.id=f.object left join factory ft on ft.id=o.factory where ft.id=%1 and d.dt >= '%2' and d.dt < '%3' and d.itv_length=%4 group by d.date, d.itv, ch.index, d.itv_length order by d.date, d.itv, ch.index;").arg(
									   QString::number(desc->id), 
									   ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), 
									   ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
									   ui->cmbItvType->itemData(ui->cmbItvType->currentIndex()).toString()));
			break;
	}
	double max_val = 0;
	if (r)
	{
		QStringList hdr;
		hdr.append(tr("Дата"));
		ui->twData->setColumnCount(1);
		ui->twData->setHorizontalHeaderLabels(hdr);
		ui->twData->setRowCount(0);
		while (r->notEoF())
		{
			
		}
	}
	ui->twData->show();
}

void ManualInputRpt::dtBeginContexMenuReq(QPoint position)
{
	QMenu mnuDateBegin(m_parent);
	QAction * actSetStart = new QAction(tr("Установить на начало дня"), m_parent);
	actSetStart->setData(QVariant::fromValue((int)DAS_DAY));
	mnuDateBegin.addAction(actSetStart);
	connect(actSetStart, SIGNAL(triggered()), this, SLOT(setdtBeginDayBegin()));

	QAction * actSetStartMonth = new QAction(tr("Установить на начало текущего месяца"), m_parent);
	actSetStartMonth->setData(QVariant::fromValue((int)DAS_CURRMONTH));
	mnuDateBegin.addAction(actSetStartMonth);
	connect(actSetStartMonth, SIGNAL(triggered()), this, SLOT(setdtBeginDayBegin()));

	QAction * actSetStartNextMonth = new QAction(tr("Установить на начало следующего месяца"), m_parent);
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

void ManualInputRpt::dtEndContexMenuReq(QPoint position)
{
	QMenu mnuDateBegin(m_parent);
	QAction * actSetStart = new QAction(tr("Установить на начало дня"), m_parent);
	actSetStart->setData(QVariant::fromValue((int)DAS_DAY));
	mnuDateBegin.addAction(actSetStart);
	connect(actSetStart, SIGNAL(triggered()), this, SLOT(setdtEndDayBegin()));

	QAction * actSetStartMonth = new QAction(tr("Установить на начало текущего месяца"), m_parent);
	actSetStartMonth->setData(QVariant::fromValue((int)DAS_CURRMONTH));
	mnuDateBegin.addAction(actSetStartMonth);
	connect(actSetStartMonth, SIGNAL(triggered()), this, SLOT(setdtEndDayBegin()));

	QAction * actSetStartNextMonth = new QAction(tr("Установить на начало следующего месяца"), m_parent);
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

void ManualInputRpt::setdtBeginDayBegin()
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

void ManualInputRpt::setdtEndDayBegin()
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
