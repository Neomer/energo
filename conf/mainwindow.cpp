#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CounterSets.h"
#include "FeederSets.h"
#include "ObjectSets.h"
#include "GTPSets.h"
#include "FactorySets.h"
#include "OrganizationSets.h"
#include "SearchDialog.h"
#include "ScheduleSets.h"
#include "ScheduleAddSets.h"
#include "ChannelSets.h"
#include "BalansAddSets.h"
#include "BalansSets.h"
#include "DPGSets.h"
#include "DPGAddSets.h"
#include "DPSets.h"
#include "MPSets.h"
#include "MeasuringChannelSets.h"
#include "UserSets.h"
#include "CHGAddSets.h"
#include "CHGSets.h"
#include "ChannelsSets.h"
#include "channelsaddsets.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsAnchorLayout>
#include <QResource>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	// Установка якорей для интерфейса
	QHBoxLayout * mainLayout = new QHBoxLayout();
	mainLayout->setMargin(5);
	mainLayout->addWidget(ui->tabWidget);
	//mainLayout->addWidget(ui->groupBox);
	ui->centralWidget->setLayout(mainLayout);
	
	//[1] Настройка Tab'ов
	ui->tabWidget->setTabText(0, tr("Точки учета"));
	ui->tabWidget->setTabIcon(0, QIcon(":/icons/images/tu.png"));
	
	ui->tabWidget->setTabText(1, tr("Группы точек поставки"));
	ui->tabWidget->setTabIcon(1, QIcon(":/icons/images/gtp.png"));
	
	ui->tabWidget->setTabText(2, tr("Очередь опроса"));
	ui->tabWidget->setTabIcon(2, QIcon(":/icons/images/schedule.png"));
	
	ui->tabWidget->setTabText(3, tr("Каналы связи"));
	ui->tabWidget->setTabIcon(3, QIcon(":/icons/images/irkick.png"));
	
	ui->tabWidget->setTabText(4, tr("Балансовые группы"));
	ui->tabWidget->setTabIcon(4, QIcon(":/icons/images/balans.png"));
	
	ui->tabWidget->setTabText(5, tr("Календарь"));
	ui->tabWidget->setTabIcon(5, QIcon(":/icons/images/calendar.png"));

	ui->tabWidget->setTabText(6, tr("Пользователи"));
	ui->tabWidget->setTabIcon(6, QIcon(":/icons/images/user-suit.png"));

	ui->tabWidget->setCurrentIndex(0);
	
	if (ui->tabTU->layout()) delete ui->tabTU->layout();
	ui->tabTU->setLayout(ui->tuLayout);

	if (ui->tabDPG->layout()) delete ui->tabDPG->layout();
	ui->tabDPG->setLayout(ui->dpgLayout);

	if (ui->tabSchedule->layout()) delete ui->tabSchedule->layout();
	ui->tabSchedule->setLayout(ui->scheduleLayout);

	if (ui->tabChannels->layout()) delete ui->tabChannels->layout();
	ui->tabChannels->setLayout(ui->channelsLayout);

	if (ui->tabBalans->layout()) delete ui->tabBalans->layout();
	ui->tabBalans->setLayout(ui->balansLayout);
	
	if (ui->tabUsers->layout()) delete ui->tabUsers->layout();
	ui->tabUsers->setLayout(ui->usersLayout);
	ui->tabUsers->setVisible(false);	
	
	if (ui->tabHolydays->layout()) delete ui->tabHolydays->layout();
	ui->tabHolydays->setLayout(ui->holyLayout);
	ui->tabHolydays->setVisible(false);
	//[/1]
	
	this->m_conn = 0;
	this->codec = QTextCodec::codecForName("UTF-8");
	this->m_dbg = 0;
	
	this->setAttribute(Qt::WA_QuitOnClose, true);
	
    connect(ui->mnuExport, SIGNAL(triggered()), this, SLOT(export_conf()));
	connect(ui->mnuDebugHide, SIGNAL(triggered()), this, SLOT(onDebugHide()));
	connect(ui->mnuChannelSets, SIGNAL(triggered()), this, SLOT(channelSets()));
	connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(twItemSelected(QTreeWidgetItem*,int)));
	connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(twItemClicked(QTreeWidgetItem*,int)));
	
	connect(ui->twSchedule, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(twScheduleItemSelected(QTreeWidgetItem*,int)));
	connect(ui->twSchedule, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this,SLOT(twScheduleItemSelected(QTreeWidgetItem*,int)));
	
	connect(ui->twBalans, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(twBalansItemSelected(QTreeWidgetItem*,int)));
	connect(ui->twBalans, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(twBalansItemClicked(QTreeWidgetItem*,int)));

	connect(ui->twDPG, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(twDPGItemSelected(QTreeWidgetItem*,int)));
	connect(ui->twDPG, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(twDPGItemClicked(QTreeWidgetItem*,int)));

	connect(ui->twUsers, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(twUsersItemSelected(QTreeWidgetItem*,int)));
	connect(ui->twUsers, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(twUsersItemClicked(QTreeWidgetItem*,int)));

	connect(ui->twChannels, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(twChannelsItemSelected(QTreeWidgetItem*,int)));
	connect(ui->twChannels, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(twChannelsItemSelected(QTreeWidgetItem*,int)));
	
	connect(ui->twHoly, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(twHolyItemSelected(QTreeWidgetItem*,int)));
	connect(ui->twHoly, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(twHolyItemClicked(QTreeWidgetItem*,int)));
	//connect(ui->treeWidget, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(twItemClicked(QTreeWidgetItem*,int)));
	
			
	
	// Кнопки тулбара
	connect(ui->mnuFind, SIGNAL(triggered()), this, SLOT(actFindClicked()));
	
	QDesktopWidget desktop;
	QRect screen = desktop.screenGeometry();
	this->move(screen.width() * 0.5 - this->width() * 0.5, screen.height() * 0.5 - this->height() * 0.5);
}

MainWindow::~MainWindow()
{
    if (this->m_conn) this->m_conn->close();
	if (ui) delete ui;
}

/******************************************************************
  
			SLOTS

*******************************************************************/

void MainWindow::twDPGItemClicked(QTreeWidgetItem *item, int column)
{
	TVItemDesc type;
	
	for (int i = 0; ui->gbDPG->children().count() > 0;)
	{
		QWidget * w = (QWidget *)ui->gbDPG->children().at(i);
		w->hide();
		w->raise();
		delete ui->gbDPG->children().at(i);
	}
	type = item->data(column, Qt::UserRole).value<TVItemDesc>();
	DPGAddSets * bas;
	DPGSets * bs;
	DPSets * dps;
	MPSets * ms;
	MeasuringChannelSets * mc;
	switch (type.type)
	{
		case ST_Organization:
			bas = new DPGAddSets(ui->gbDPG, this->m_conn, item);
			connect(bas, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwDPGItem(QTreeWidgetItem*)));
			bas->show();
			break;
		
		case ST_Factory:
			bs = new DPGSets(ui->gbDPG, this->m_conn, ((Factory *)type.link)->ID, item);
			connect(bs, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwDPGItem(QTreeWidgetItem*)));
			bs->show();
			break;
			
		case ST_Object:
			dps = new DPSets(ui->gbDPG, this->m_conn, ((Factory *)type.link)->ID, item);
			connect(dps, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwDPGItem(QTreeWidgetItem*)));
			dps->show();
			break;

		case ST_Feeder:
			ms = new MPSets(ui->gbDPG, this->m_conn, ((Factory *)type.link)->ID, item);
			connect(ms, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwDPGItem(QTreeWidgetItem*)));
			ms->show();
			break;
			
		case ST_Counter:
			mc = new MeasuringChannelSets(ui->gbDPG, this->m_conn, ((Factory *)type.link)->ID, item);
			mc->show();
			break;
	}
}

void MainWindow::twDPGItemSelected(QTreeWidgetItem *item, int column)
{
	updateDPG(item, column);
}

void MainWindow::updateDPG(QTreeWidgetItem *item, int column)
{
	if (!this->m_conn->isConnected())
    {
        qWarning("MainWindow::updateDPG() - DB connection don't set!\n");
        return;
    }
	PgreSqlResult *r = 0;
	if (!item)
	{
		r = this->m_conn->exec("select value from info where name='org_name';");
		QList<QTreeWidgetItem *> it;
		QTreeWidgetItem * root = new QTreeWidgetItem();
		if (!r->isValid())
		{
			qDebug("MainWindow::updateDPG() - Organization name is missing\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
		}
		TVItemDesc tvd;
		tvd.type = ST_Organization;
		root->setText(0, r->getValue(0, ""));
		root->setData(0, Qt::UserRole, QVariant::fromValue(tvd));
		root->setIcon(0, QIcon(":/icons/images/building.png"));
		it.append(root);
		this->ui->twDPG->insertTopLevelItems(0, it);
		        
        r = this->m_conn->exec("select d.id, d.name from deliverypointgroup d order by d.NAME;");
		if (!r->isValid())
		{
			qDebug("MainWindow::updateDPG() - List of DPG don't received!\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
			return;
		}
		it.clear();
		while (r->notEoF())
		{
			QString f;
			QVariant v;
			f = r->getValue(1);
			QTreeWidgetItem *twi = new QTreeWidgetItem();
			twi->setText(0, f);
			it.append(twi);
			Factory * fi = new Factory();
			tvd.type = ST_Factory;
			fi->ID = r->getValue(0, "0").toInt();
			fi->name = r->getValue(1);
			tvd.link = fi;
			v.setValue(tvd);
			twi->setData(0, Qt::UserRole, v);
			twi->setIcon(0, QIcon(":/icons/images/gtp.png"));
			r->moveNext();
		}
		root->addChildren(it);
		root->setSelected(true);
		twItemClicked(root, 0);
		ui->twDPG->expandItem(root);
	}
	else
	{
		TVItemDesc type;
		Factory * f;
		StructType stype;
		QIcon icon;
		QString sql;
		type = item->data(column, Qt::UserRole).value<TVItemDesc>();
		qDebug("MainWindow::updateDPG() - Type: %d; Address: 0x%.4X", type.type, (int)type.link);
		switch (type.type)
		{
			case ST_Factory:
				item->takeChildren();
				stype = ST_Object;
				icon = QIcon(":/icons/images/dp.png");
				f = (Factory *) type.link;
				sql = "select o.id, o.name from deliverypoint o where o.dpg={id} order by o.name;";
				sql.replace("{id}", QString::number(f->ID));
				r = this->m_conn->exec(sql);
				break;
				
			case ST_Object:
				item->takeChildren();
				f = (Factory *) type.link;
				qDebug("MainWindow::updateList() - ID: %d; Name: %s\n", 
					   f->ID, 
					   f->name.toAscii().constData());
				sql = "select f.id, f.name from measuringpoint f where f.delp={id} order by f.name;";
				sql.replace("{id}", QString::number(f->ID));
				r = this->m_conn->exec(sql);
				stype = ST_Feeder;
				icon = QIcon(":/icons/images/counter.png");
				break;
				
			case ST_Feeder:
				item->takeChildren();
				f = (Factory *) type.link;
				qDebug("MainWindow::updateList() - ID: %d; Name: %s\n", 
					   f->ID, 
					   f->name.toAscii().constData());
				sql = QString("select mc.id, mc.name from measuringchannel mc where mc.mpoint=%1 order by mc.name;").arg(
						  QString::number(f->ID));
				r = this->m_conn->exec(sql);
				icon = QIcon(":/icons/images/channel.png");
				stype = ST_Counter;
				break;
				
			case ST_Counter:
				break;
				
			case ST_Organization:
				break;
		}
		QTreeWidgetItem *twi;
		QList<QTreeWidgetItem *> it;
		if (r)
		{
			if (!r->isValid())
			{
				qDebug("MainWindow::updateList() - List of objects isn't received!\n");
				qDebug("%s", this->m_conn->getError().toAscii().constData());
				return;
			}
			while (r->notEoF())
			{
				twi = new QTreeWidgetItem(item);
				twi->setText(0, r->getValue(1));
				Factory * f = new Factory();
				TVItemDesc tvd;
				tvd.type = stype;
				f->ID = r->getValue(0, "0").toInt();
				f->name = r->getValue(1);
				tvd.link = (void *) f;
				QVariant v;
				v.setValue(tvd);
				twi->setData(0, Qt::UserRole, v);
				twi->setIcon(0, icon);
				it.append(twi);
				r->moveNext();
			}
			item->addChildren(it);
			r->close();
		}
	}
}

void MainWindow::addTwDPGItem(QTreeWidgetItem *parent)
{
	QTreeWidgetItem * item = new QTreeWidgetItem();
	TVItemDesc pdesc, cdesc;
	pdesc = parent->data(0, Qt::UserRole).value<TVItemDesc>();
	Factory * f;
	PgreSqlResult * r;
	switch (pdesc.type)
	{
		case ST_Organization:
			f = new Factory;
			f->ID = -1;
			cdesc.type = ST_Factory;
			cdesc.link = (void *) f;
			item->setText(0, tr("Новая группа точек поставки"));
			item->setIcon(0, QIcon(":/icons/images/gtp.png"));
			break;
			
		case ST_Factory:
			f = new Factory;
			f->ID = -1;
			cdesc.type = ST_Object;
			cdesc.link = (void *) f;
			item->setText(0, tr("Новая точка поставки"));
			item->setIcon(0, QIcon(":/icons/images/dp.png"));
			break;
			
		case ST_Object:
			f = new Factory;
			f->ID = -1;
			cdesc.type = ST_Feeder;
			cdesc.link = (void *) f;
			item->setText(0, tr("Новая точка измерения"));
			item->setIcon(0, QIcon(":/icons/images/counter.png"));
			break;
			
		case ST_Feeder:
			r = m_conn->exec(QString("select ch.id, ch.name from measuringchannel mc left join channel ch on ch.id=mc.channel where mc.mpoint=%1;").arg(
								 QString::number(((Factory *)pdesc.link)->ID)));
			delete item;
			while (r->notEoF())
			{
				item = new QTreeWidgetItem();
				f = new Factory;
				f->ID = r->getValue(0).toInt();
				cdesc.type = ST_Counter;
				cdesc.link = (void *) f;
				item->setText(0, r->getValue(1));
				item->setIcon(0, QIcon(":/icons/images/channel.png"));
				parent->addChild(item);
			}
			item = 0;
			break;
			
	}
	if (item)
	{
		item->setData(0, Qt::UserRole, QVariant::fromValue(cdesc));
		parent->addChild(item);
		twDPGItemClicked(item, 0);
	}
	parent->setSelected(false);
	parent->setExpanded(true);
	item->setSelected(true);
}

void MainWindow::twUsersItemSelected(QTreeWidgetItem *item, int column)
{
}

void MainWindow::twUsersItemClicked(QTreeWidgetItem *item, int column)
{
	TVItemDesc type;
	
	for (int i = 0; ui->gbUsers->children().count() > 0;)
	{
		QWidget * w = (QWidget *)ui->gbUsers->children().at(i);
		w->hide();
		w->raise();
		delete ui->gbUsers->children().at(i);
	}
	
	type = item->data(column, Qt::UserRole).value<TVItemDesc>();
	BalansAddSets * bas;
	UserSets * bs;
	switch (type.type)
	{
		case ST_Organization:
			bas = new BalansAddSets(ui->gbUsers, this->m_conn, item);
			connect(bas, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwBalansItem(QTreeWidgetItem*)));
			bas->show();
			break;
		
		case ST_BalansElement:
			bs = new UserSets(ui->gbUsers, this->m_conn, ((Factory *)type.link)->ID, item);
			//connect(bs, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwItem(QTreeWidgetItem*))(QTreeWidgetItem*))(QTreeWidgetItem*)));
			bs->show();
			break;
	}
}

void MainWindow::addTwUsersItem(QTreeWidgetItem *parent)
{
}

void MainWindow::twHolyItemSelected(QTreeWidgetItem *item, int column)
{
	updateHolydays(item, column);
}

void MainWindow::twHolyItemClicked(QTreeWidgetItem *item, int column)
{
	TVItemDesc type;
	
	for (int i = 0; ui->gbHolydays->children().count() > 0;)
	{
		QWidget * w = (QWidget *)ui->gbHolydays->children().at(i);
		w->hide();
		w->raise();
		delete ui->gbHolydays->children().at(i);
	}
	
	type = item->data(column, Qt::UserRole).value<TVItemDesc>();
	CHGAddSets * bas;
	CHGSets * bs;
	switch (type.type)
	{
		case ST_Organization:
			bas = new CHGAddSets(ui->gbHolydays, this->m_conn, item);
			connect(bas, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwHolyItem(QTreeWidgetItem*)));
			bas->show();
			break;
		
		case ST_Factory:
			bs = new CHGSets(ui->gbHolydays, this->m_conn, ((Factory *)type.link)->ID, item);
			//connect(bs, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwItem(QTreeWidgetItem*))(QTreeWidgetItem*))(QTreeWidgetItem*)));
			bs->show();
			break;
	}
}

void MainWindow::addTwHolyItem(QTreeWidgetItem *parent)
{
	QTreeWidgetItem * item = new QTreeWidgetItem();
	TVItemDesc pdesc, cdesc;
	pdesc = parent->data(0, Qt::UserRole).value<TVItemDesc>();
	Factory * f;
	switch (pdesc.type)
	{
		case ST_Organization:
			f = new Factory;
			f->ID = -1;
			cdesc.type = ST_Factory;
			cdesc.link = (void *) f;
			item->setText(0, tr("Новая группа контрольных часов"));
			item->setIcon(0, QIcon(":/icons/images/appointment-new-2.png"));
			break;
			
		case ST_Factory:
			break;
	}
	item->setData(0, Qt::UserRole, QVariant::fromValue(cdesc));
	parent->setSelected(false);
	parent->addChild(item);
	parent->setExpanded(true);
	item->setSelected(true);
	twBalansItemClicked(item, 0);
}

void MainWindow::twBalansItemClicked(QTreeWidgetItem *item, int column)
{
	TVItemDesc type;
	
	for (int i = 0; ui->gbBalans->children().count() > 0;)
	{
		QWidget * w = (QWidget *)ui->gbBalans->children().at(i);
		w->hide();
		w->raise();
		delete ui->gbBalans->children().at(i);
	}
	
	type = item->data(column, Qt::UserRole).value<TVItemDesc>();
	BalansAddSets * bas;
	BalansSets * bs;
	switch (type.type)
	{
		case ST_Organization:
			bas = new BalansAddSets(ui->gbBalans, this->m_conn, item);
			connect(bas, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwBalansItem(QTreeWidgetItem*)));
			bas->show();
			break;
		
		case ST_BalansElement:
			bs = new BalansSets(ui->gbBalans, this->m_conn, ((Factory *)type.link)->ID, item);
			//connect(bs, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwItem(QTreeWidgetItem*))(QTreeWidgetItem*))(QTreeWidgetItem*)));
			bs->show();
			break;
	}
}

void MainWindow::twBalansItemSelected(QTreeWidgetItem *item, int column)
{
	
}

void MainWindow::updateBalans(QTreeWidgetItem *item, int column)
{
	if (!this->m_conn->isConnected())
    {
        qWarning("MainWindow::updateBalans() - DB connection don't set!\n");
        return;
    }
	if (!item)
	{
		PgreSqlResult * r = this->m_conn->exec("select value from info where name='org_name';");
		QList<QTreeWidgetItem *> it;
		QTreeWidgetItem * root = new QTreeWidgetItem();
		if (!r->isValid())
		{
			qDebug("MainWindow::updateBalans() - Organization name is missing\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
		}
		TVItemDesc tvd;
		tvd.type = ST_Organization;
		root->setText(0, r->getValue(0, ""));
		root->setData(0, Qt::UserRole, QVariant::fromValue(tvd));
		root->setIcon(0, QIcon(":/icons/images/building.png"));
		it.append(root);
		this->ui->twBalans->insertTopLevelItems(0, it);
		        
        r = this->m_conn->exec("select b.id, b.name from balans b order by b.NAME;");
		if (!r->isValid())
		{
			qDebug("MainWindow::updateBalans() - List of balanses don't received!\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
			return;
		}
		it.clear();
		while (r->notEoF())
		{
			QString f;
			QVariant v;
			f = r->getValue(1);
			QTreeWidgetItem *twi = new QTreeWidgetItem();
			twi->setText(0, f);
			it.append(twi);
			Factory * fi = new Factory();
			tvd.type = ST_BalansElement;
			fi->ID = r->getValue(0, "0").toInt();
			fi->name = r->getValue(1);
			this->f.append(fi);
			tvd.link = fi;
			v.setValue(tvd);
			twi->setData(0, Qt::UserRole, v);
			twi->setIcon(0, QIcon(":/icons/images/balans.png"));
			r->moveNext();
		}
		root->addChildren(it);
		root->setSelected(true);
		twItemClicked(root, 0);
		ui->twBalans->expandItem(root);
	}
	else
	{
		//BalansType	
	}
}

void MainWindow::addTwBalansItem(QTreeWidgetItem *parent)
{
	QTreeWidgetItem * item = new QTreeWidgetItem();
	TVItemDesc pdesc, cdesc;
	pdesc = parent->data(0, Qt::UserRole).value<TVItemDesc>();
	Factory * f;
	switch (pdesc.type)
	{
		case ST_Organization:
			f = new Factory;
			f->ID = -1;
			cdesc.type = ST_BalansElement;
			cdesc.link = (void *) f;
			item->setText(0, tr("Новая балансовая группа"));
			item->setIcon(0, QIcon(":/icons/images/balans.png"));
			break;
			
		case ST_Factory:
			break;
	}
	item->setData(0, Qt::UserRole, QVariant::fromValue(cdesc));
	parent->setSelected(false);
	parent->addChild(item);
	parent->setExpanded(true);
	item->setSelected(true);
	twBalansItemClicked(item, 0);

}

void MainWindow::login_form_close()
{
	if (!this->m_conn) login_fail();
}

void MainWindow::export_conf()
{
    //TODO: Экспорт настроек
	QMessageBox::information(this, tr("Title"), tr("Debug test"));
}

void MainWindow::login_fail()
{
	if (!this->close())
		QMessageBox::critical(this, tr("Ошибка"), tr("Невозможно закрыть окно"));
}

void MainWindow::db_connected(PgreSqlDrv *connection)
{
	setDBConnection(connection);
	updateList((QTreeWidgetItem *)0, 0);
	updateSchedule((QTreeWidgetItem *)0, 0);
	updateBalans((QTreeWidgetItem *)0, 0);
	updateDPG((QTreeWidgetItem *)0, 0);
	updateUsers((QTreeWidgetItem *)0, 0);
	updateHolydays((QTreeWidgetItem *)0, 0);\
	updateChannels((QTreeWidgetItem *)0, 0);
}

void MainWindow::twItemSelected(QTreeWidgetItem *item, int column)
{
	updateList(item, column);
}

void MainWindow::twScheduleItemSelected(QTreeWidgetItem *item, int column)
{
	TVItemDesc type;
	
	for (int i = 0; ui->gbSchedule->children().count() > 0;)
	{
		QWidget * w = (QWidget *)ui->gbSchedule->children().at(i);
		w->hide();
		w->raise();
		delete ui->gbSchedule->children().at(i);
	}
	
	type = item->data(0, Qt::UserRole).value<TVItemDesc>();
	ScheduleAddSets * bas;
	ScheduleSets * bs;
	qDebug("MainWindow::twScheduleItemSelected() - %d",
		   type.type);
	switch (type.type)
	{
		case ST_Organization:
			bas = new ScheduleAddSets(ui->gbSchedule, this->m_conn, item);
			connect(bas, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addScheduleItem(QTreeWidgetItem*)));
			bas->show();
			break;
		
		case ST_BalansElement:
			bs = new ScheduleSets(ui->gbSchedule, this->m_conn, ((Factory *)type.link)->ID, item);
			//connect(bs, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwItem(QTreeWidgetItem*))(QTreeWidgetItem*))(QTreeWidgetItem*)));
			bs->show();
			break;
	}
}

void MainWindow::addScheduleItem(QTreeWidgetItem *parent)
{
	QTreeWidgetItem * item = new QTreeWidgetItem();
	TVItemDesc pdesc, cdesc;
	pdesc = parent->data(0, Qt::UserRole).value<TVItemDesc>();
	Factory * f;
	switch (pdesc.type)
	{
		case ST_Organization:
			f = new Factory;
			f->ID = -1;
			cdesc.type = ST_BalansElement;
			cdesc.link = (void *) f;
			item->setText(0, tr("Новое задание"));
			item->setIcon(0, QIcon(":/icons/images/schedule.png"));
			break;
			
		case ST_Factory:
			break;
	}
	item->setData(0, Qt::UserRole, QVariant::fromValue(cdesc));
	parent->setSelected(false);
	parent->addChild(item);
	parent->setExpanded(true);
	item->setSelected(true);
	twScheduleItemSelected(item, 0);
}

void MainWindow::twChannelsItemSelected(QTreeWidgetItem *item, int column)
{
	TVItemDesc type;
	
	for (int i = 0; ui->gbChannels->children().count() > 0;)
	{
		QWidget * w = (QWidget *)ui->gbChannels->children().at(i);
		w->hide();
		w->raise();
		delete ui->gbChannels->children().at(i);
	}
	
	type = item->data(0, Qt::UserRole).value<TVItemDesc>();
	ChannelsAddSets * bas;
	ChannelSets * bs;
	qDebug("MainWindow::twChannelsItemSelected() - %d",
		   type.type);
	switch (type.type)
	{
		case ST_Organization:
			bas = new ChannelsAddSets(ui->gbChannels, this->m_conn, item);
			connect(bas, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addChannelsItem(QTreeWidgetItem*)));
			bas->show();
			break;
		
		case ST_BalansElement:
			bs = new ChannelSets(ui->gbChannels, this->m_conn, ((Factory *)type.link)->ID, item);
			bs->show();
			break;
	}
}

void MainWindow::addChannelsItem(QTreeWidgetItem *parent)
{
	QTreeWidgetItem * item = new QTreeWidgetItem();
	TVItemDesc pdesc, cdesc;
	pdesc = parent->data(0, Qt::UserRole).value<TVItemDesc>();
	Factory * f;
	switch (pdesc.type)
	{
		case ST_Organization:
			f = new Factory;
			f->ID = -1;
			cdesc.type = ST_BalansElement;
			cdesc.link = (void *) f;
			item->setText(0, tr("Новый канал связи"));
			item->setIcon(0, QIcon(":/icons/images/irkick.png"));
			break;
			
		case ST_Factory:
			break;
	}
	item->setData(0, Qt::UserRole, QVariant::fromValue(cdesc));
	parent->setSelected(false);
	parent->addChild(item);
	parent->setExpanded(true);
	item->setSelected(true);
	twScheduleItemSelected(item, 0);
}

void MainWindow::actFindClicked()
{
	SearchDialog * srchdlg = new SearchDialog(m_conn, this);
	srchdlg->setWindowModality(Qt::WindowModal);
	srchdlg->show();
}

void MainWindow::findElement()
{
	SearchDialog * srchdlg = (SearchDialog *) sender();
	//QString sql
}

void MainWindow::addTwItem(QTreeWidgetItem *parent)
{
	QTreeWidgetItem * item = new QTreeWidgetItem();
	TVItemDesc pdesc, cdesc;
	pdesc = parent->data(0, Qt::UserRole).value<TVItemDesc>();
	Counter * cd;
	Feeder * fd;
	Object * os;
	Factory * f;
	Channel * ch;
	switch (pdesc.type)
	{
		case ST_Organization:
			f = new Factory;
			f->ID = -1;
			cdesc.type = ST_Factory;
			cdesc.link = (void *) f;
			item->setText(0, tr("Новое предприятие"));
			item->setIcon(0, QIcon(":/icons/images/server.png"));
			break;
			
		case ST_Factory:
			os = new Object;
			os->ID = -1;
			cdesc.type = ST_Object;
			cdesc.link = (void *) os;
			item->setText(0, tr("Новая подстанция"));
			item->setIcon(0, QIcon(":/icons/images/object.png"));
			break;
			
		case ST_Object:
			fd = new Feeder;
			fd->ID = -1;
			cdesc.type = ST_Feeder;
			cdesc.link = (void *) fd;
			item->setText(0, tr("Новый фидер"));
			item->setIcon(0, QIcon(":/icons/images/feeder.png"));
			break;
			
		case ST_Feeder:
			cd = new Counter;
			cd->ID = -1;
			cdesc.type = ST_Counter;
			cdesc.link = (void *) cd;
			item->setText(0, tr("Новый счетчик"));
			item->setIcon(0, QIcon(":/icons/images/counter.png"));
			break;
			
		case ST_Counter:
			ch = new Channel;
			ch->ID = -1;
			cdesc.type = ST_Channel;
			cdesc.link = (void *) ch;
			item->setText(0, tr("Новый канал"));
			item->setIcon(0, QIcon(":/icons/images/channel.png"));
			break;
	}
	item->setData(0, Qt::UserRole, QVariant::fromValue(cdesc));
	parent->setSelected(false);
	parent->addChild(item);
	parent->setExpanded(true);
	item->setSelected(true);
	twItemClicked(item, 0);
}

void MainWindow::twItemClicked(QTreeWidgetItem *item, int column)
{
	TVItemDesc type;
	
	for (int i = 0; ui->groupBox->children().count() > 0;)
	{
		QWidget * w = (QWidget *)ui->groupBox->children().at(i);
		w->hide();
		w->raise();
		delete ui->groupBox->children().at(i);
	}
	
	type = item->data(column, Qt::UserRole).value<TVItemDesc>();
	OrganizationSets * os;
	FactorySets * fcs;
	GTPSets * gs;
	ObjectSets * obs;
	FeederSets * fs;
	CounterSets * cs;
	ChannelSets * chs;
	switch (type.type)
	{
		case ST_Organization:
			os = new OrganizationSets(ui->groupBox, this->m_conn, item);
			connect(os, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwItem(QTreeWidgetItem*)));
			os->show();
			break;
		
		case ST_Factory:
			fcs = new FactorySets(ui->groupBox, this->m_conn, ((Factory *)type.link)->ID, item);
			connect(fcs, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwItem(QTreeWidgetItem*)));
			fcs->show();
			break;
		
		case ST_Object:
			obs = new ObjectSets(ui->groupBox, this->m_conn, ((Object *)type.link)->ID, item);
			connect(obs, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwItem(QTreeWidgetItem*)));
			obs->show();
			break;
		
		case ST_Feeder:
			fs = new FeederSets(ui->groupBox, this->m_conn, ((Feeder *)type.link)->ID, item);
			connect(fs, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwItem(QTreeWidgetItem*)));
			fs->show();
			break;
			
		case ST_Counter:
			cs = new CounterSets(ui->groupBox, this->m_conn, ((Counter *)type.link)->ID, item);
			connect(cs, SIGNAL(onCreateChild(QTreeWidgetItem*)), this, SLOT(addTwItem(QTreeWidgetItem*)));
			cs->show();
			break;
			
		case ST_Channel:
			chs = new ChannelSets(ui->groupBox, this->m_conn, ((Counter *)type.link)->ID, item);
			chs->show();
			break;
	}
}

void MainWindow::onDebugHide()
{
	if (this->m_dbg) 
	{
		if (this->m_dbg->isHidden())
		{
			this->m_dbg->show();
			this->ui->mnuDebugHide->setText(tr("Скрыть окно отладки"));
		}
		else
		{
			this->m_dbg->hide();
			this->ui->mnuDebugHide->setText(tr("Показать окно отладки"));
		}
	}
	else
		qDebug("MainWindow::onDebugHide() - Debug window is not set");
}

void MainWindow::channelSets()
{
	ChannelsSets * cs = new ChannelsSets(this, this->m_conn, 0, 0);
	cs->show();
}


/******************************************************************
  
			METHODS

*******************************************************************/

void MainWindow::setDebugWindow(DebugWindow *dbg)
{
	this->m_dbg = dbg;
	if (this->m_dbg->isHidden())
		this->ui->mnuDebugHide->setText(tr("Показать окно отладки"));
	else
		this->ui->mnuDebugHide->setText(tr("Скрыть окно отладки"));
}

void MainWindow::setDBConnection(PgreSqlDrv *connection)
{
    this->m_conn = connection;
}

void MainWindow::updateSchedule(QTreeWidgetItem * parent, int column)
{
	if (!this->m_conn->isConnected())
    {
        qWarning("MainWindow::updateSchedule() - DB connection don't set!\n");
        return;
    }
	
	if (!parent)
	{
		PgreSqlResult * r = this->m_conn->exec("select value from info where name='org_name';");
		QList<QTreeWidgetItem *> it;
		QTreeWidgetItem * root = new QTreeWidgetItem();
		if (!r->isValid())
		{
			qDebug("MainWindow::updateList() - Organization name is missing\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
		}
		TVItemDesc tvd;
		tvd.type = ST_Organization;
		root->setText(0, r->getValue(0, ""));
		root->setData(0, Qt::UserRole, QVariant::fromValue(tvd));
		root->setIcon(0, QIcon(":/icons/images/building.png"));
		it.append(root);
		this->ui->twSchedule->insertTopLevelItems(0, it);
		        
		r = m_conn->exec("select * from schedule order by name;");
		if (!r->isValid())
		{
			qDebug("MainWindow::updateSchedule() - List of schedules don't received!\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
			return;
		}
		it.clear();
		while (r->notEoF())
		{
			QString f;
			QVariant v;
			f = r->getValue(1);
			QTreeWidgetItem *twi = new QTreeWidgetItem();
			twi->setText(0, f);
			it.append(twi);
			Factory * fi = new Factory();
			tvd.type = ST_BalansElement;
			fi->ID = r->getValue(0, "0").toInt();
			fi->name = r->getValue(1);
			this->f.append(fi);
			tvd.link = fi;
			v.setValue(tvd);
			twi->setData(0, Qt::UserRole, v);
			twi->setIcon(0, QIcon(":/icons/images/schedule.png"));
			r->moveNext();
		}
		root->addChildren(it);
		root->setSelected(true);
		twScheduleItemSelected(root, 0);
		ui->twSchedule->expandItem(root);
	}
	else
	{
		
	}
}

void MainWindow::updateChannels(QTreeWidgetItem *parent, int column)
{
	if (!this->m_conn->isConnected())
    {
        qWarning("MainWindow::updateChannels() - DB connection don't set!\n");
        return;
    }
	
	if (!parent)
	{
		PgreSqlResult * r = this->m_conn->exec("select value from info where name='org_name';");
		QList<QTreeWidgetItem *> it;
		QTreeWidgetItem * root = new QTreeWidgetItem();
		if (!r->isValid())
		{
			qDebug("MainWindow::updateChannels() - Organization name is missing\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
		}
		TVItemDesc tvd;
		tvd.type = ST_Organization;
		root->setText(0, r->getValue(0, ""));
		root->setData(0, Qt::UserRole, QVariant::fromValue(tvd));
		root->setIcon(0, QIcon(":/icons/images/building.png"));
		it.append(root);
		this->ui->twChannels->insertTopLevelItems(0, it);
		        
		r = m_conn->exec("select * from connection order by name;");
		if (!r->isValid())
		{
			qDebug("MainWindow::updateChannels() - List of schedules don't received!\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
			return;
		}
		it.clear();
		while (r->notEoF())
		{
			QString f;
			QVariant v;
			f = r->getValue(1);
			QTreeWidgetItem *twi = new QTreeWidgetItem();
			twi->setText(0, f);
			it.append(twi);
			Factory * fi = new Factory();
			tvd.type = ST_BalansElement;
			fi->ID = r->getValue(0, "0").toInt();
			fi->name = r->getValue(1);
			this->f.append(fi);
			tvd.link = fi;
			v.setValue(tvd);
			twi->setData(0, Qt::UserRole, v);
			twi->setIcon(0, QIcon(":/icons/images/irkick.png"));
			r->moveNext();
		}
		root->addChildren(it);
		root->setSelected(true);
		twChannelsItemSelected(root, 0);
		ui->twChannels->expandItem(root);
	}
	else
	{
		
	}
	
}

void MainWindow::updateUsers(QTreeWidgetItem *parent, int column)
{
	if (!this->m_conn->isConnected())
    {
        qWarning("MainWindow::updateUsers() - DB connection don't set!\n");
        return;
    }
	
	if (!parent)
	{
		PgreSqlResult * r = this->m_conn->exec("select value from info where name='org_name';");
		QList<QTreeWidgetItem *> it;
		QTreeWidgetItem * root = new QTreeWidgetItem();
		if (!r->isValid())
		{
			qDebug("MainWindow::updateUsers() - Organization name is missing\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
		}
		TVItemDesc tvd;
		tvd.type = ST_Organization;
		root->setText(0, r->getValue(0, ""));
		root->setData(0, Qt::UserRole, QVariant::fromValue(tvd));
		root->setIcon(0, QIcon(":/icons/images/building.png"));
		it.append(root);
		this->ui->twUsers->insertTopLevelItems(0, it);
		        
		r = m_conn->exec("select id, name from users order by name;");
		if (!r->isValid())
		{
			qDebug("MainWindow::updateUsers() - List of users don't received!\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
			return;
		}
		it.clear();
		while (r->notEoF())
		{
			QString f;
			QVariant v;
			f = r->getValue(1);
			QTreeWidgetItem *twi = new QTreeWidgetItem();
			twi->setText(0, f);
			it.append(twi);
			Factory * fi = new Factory();
			tvd.type = ST_BalansElement;
			fi->ID = r->getValue(0, "0").toInt();
			fi->name = r->getValue(1);
			this->f.append(fi);
			tvd.link = fi;
			v.setValue(tvd);
			twi->setData(0, Qt::UserRole, v);
			twi->setIcon(0, QIcon(":/icons/images/user-suit.png"));
			r->moveNext();
		}
		root->addChildren(it);
		root->setSelected(true);
		twItemClicked(root, 0);
		ui->twUsers->expandItem(root);
	}
	else
	{
		
	}
}

void MainWindow::updateHolydays(QTreeWidgetItem *parent, int column)
{
	if (!this->m_conn->isConnected())
    {
        qWarning("MainWindow::updateUsers() - DB connection don't set!\n");
        return;
    }
	
	PgreSqlResult *r = 0;
	if (!parent)
	{
		r = this->m_conn->exec("select value from info where name='org_name';");
		QList<QTreeWidgetItem *> it;
		QTreeWidgetItem * root = new QTreeWidgetItem();
		if (!r->isValid())
		{
			qDebug("MainWindow::updateUsers() - Organization name is missing\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
		}
		TVItemDesc tvd;
		tvd.type = ST_Organization;
		root->setText(0, r->getValue(0, ""));
		root->setData(0, Qt::UserRole, QVariant::fromValue(tvd));
		root->setIcon(0, QIcon(":/icons/images/building.png"));
		it.append(root);
		this->ui->twHoly->insertTopLevelItems(0, it);
		        
		r = m_conn->exec("select id, name from controlhourgroup order by name;");
		if (!r->isValid())
		{
			qDebug("MainWindow::updateUsers() - List of users don't received!\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
			return;
		}
		it.clear();
		while (r->notEoF())
		{
			QString f;
			QVariant v;
			f = r->getValue(1);
			QTreeWidgetItem *twi = new QTreeWidgetItem();
			twi->setText(0, f);
			it.append(twi);
			Factory * fi = new Factory();
			tvd.type = ST_Factory;
			fi->ID = r->getValue(0, "0").toInt();
			fi->name = r->getValue(1);
			this->f.append(fi);
			tvd.link = fi;
			v.setValue(tvd);
			twi->setData(0, Qt::UserRole, v);
			twi->setIcon(0, QIcon(":/icons/images/appointment-new-2.png"));
			r->moveNext();
		}
		root->addChildren(it);
		root->setSelected(true);
		twItemClicked(root, 0);
		ui->twHoly->expandItem(root);
	}
	else
	{
		Factory * f;
		StructType stype;
		QIcon icon;
		QString sql;
		TVItemDesc type = parent->data(column, Qt::UserRole).value<TVItemDesc>();
		switch (type.type)
		{
			case ST_Factory:
				parent->takeChildren();
				stype = ST_Object;
				icon = QIcon(":/icons/images/dp.png");
				f = (Factory *) type.link;
				sql = "select o.date from controlhour o where o.gid={id} order by o.date;";
				sql.replace("{id}", QString::number(f->ID));
				r = this->m_conn->exec(sql);
				break;
				
			default:
				return;
		}
		QTreeWidgetItem *twi;
		QList<QTreeWidgetItem *> it;
		if (r)
		{
			if (!r->isValid())
			{
				qDebug("MainWindow::updateList() - List of objects isn't received!\n");
				qDebug("%s", this->m_conn->getError().toAscii().constData());
				return;
			}
			while (r->notEoF())
			{
				twi = new QTreeWidgetItem(parent);
				twi->setText(0, r->getValue(0));
				Factory * f = new Factory();
				TVItemDesc tvd;
				tvd.type = stype;
				f->ID = r->getValue(0, "0").toInt();
				f->name = r->getValue(1);
				tvd.link = (void *) f;
				QVariant v;
				v.setValue(tvd);
				twi->setData(0, Qt::UserRole, v);
				twi->setIcon(0, icon);
				it.append(twi);
				r->moveNext();
			}
			parent->addChildren(it);
			r->close();
		}
	}
}

void MainWindow::updateList(QTreeWidgetItem * parent, int column)
{
    if (!this->m_conn->isConnected())
    {
        qWarning("MainWindow::updateList() - DB connection don't set!\n");
        return;
    }
	if (parent == 0)
	{
		this->f.clear();
		
		PgreSqlResult * r = this->m_conn->exec("select value from info where name='org_name';");
		QList<QTreeWidgetItem *> it;
		QTreeWidgetItem * root = new QTreeWidgetItem();
		if (!r->isValid())
		{
			qDebug("MainWindow::updateList() - Organization name is missing\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
		}
		TVItemDesc tvd;
		tvd.type = ST_Organization;
		root->setText(0, r->getValue(0, ""));
		root->setData(0, Qt::UserRole, QVariant::fromValue(tvd));
		root->setIcon(0, QIcon(":/icons/images/building.png"));
		it.append(root);
		this->ui->treeWidget->insertTopLevelItems(0, it);
		        
        r = this->m_conn->exec("select f.id, f.name from factory f order by f.NAME;");
		if (!r->isValid())
		{
			qDebug("MainWindow::updateList() - List of factories don't received!\n");
			qDebug("%s", this->m_conn->getError().toAscii().constData());
			return;
		}
		it.clear();
		while (r->notEoF())
		{
			QString f;
			QVariant v;
			f = r->getValue(1);
			QTreeWidgetItem *twi = new QTreeWidgetItem();
			twi->setText(0, f);
			it.append(twi);
			Factory * fi = new Factory();
			tvd.type = ST_Factory;
			fi->ID = r->getValue(0, "0").toInt();
			fi->name = r->getValue(1);
			this->f.append(fi);
			tvd.link = fi;
			v.setValue(tvd);
			twi->setData(0, Qt::UserRole, v);
			twi->setIcon(0, QIcon(":/icons/images/server.png"));
			r->moveNext();
		}
		root->addChildren(it);
		root->setSelected(true);
		twItemClicked(root, 0);
		ui->treeWidget->expandItem(root);
	}
	else
	{
		TVItemDesc type;
		PgreSqlResult *r;
		QTreeWidgetItem *twi;
		QList<QTreeWidgetItem *> it;
		Factory * f;
		Object * o;
		Feeder * fd;
		Counter * ctr;
		Channel * ch;
		QString sql;
		type = parent->data(column, Qt::UserRole).value<TVItemDesc>();
		qDebug("MainWindow::updateList() - Type: %d; Address: 0x%.4X", type.type, (int)type.link);
		switch (type.type)
		{
			case ST_Factory:
				parent->takeChildren();
				f = (Factory *) type.link;
				sql = "select o.id, o.name from object o where o.factory={id} order by o.name;";
				sql.replace("{id}", QString::number(f->ID));
				r = this->m_conn->exec(sql);
				if (!r->isValid())
				{
					qDebug("MainWindow::updateList() - List of objects isn't received!\n");
					qDebug("%s", this->m_conn->getError().toAscii().constData());
					return;
				}
				while (r->notEoF())
				{
					twi = new QTreeWidgetItem(parent);
					twi->setText(0, r->getValue(1));
					Object * g = new Object();
					TVItemDesc tvd;
					tvd.type = ST_Object;
					g->ID = r->getValue(0, "0").toInt();
					g->name = r->getValue(1);
					tvd.link = (void *) g;
					QVariant v;
					v.setValue(tvd);
					twi->setData(0, Qt::UserRole, v);
					twi->setIcon(0, QIcon(":/icons/images/object.png"));
					it.append(twi);
					r->moveNext();
				}
				parent->addChildren(it);
				r->close();
				break;
				
			case ST_Object:
				parent->takeChildren();
				o = (Object *) type.link;
				qDebug("MainWindow::updateList() - ID: %d; Name: %s\n", 
					   o->ID, 
					   o->name.toAscii().constData());
				sql = "select f.id, f.name from feeder f where f.object={id} order by f.name;";
				sql.replace("{id}", QString::number(o->ID));
				r = this->m_conn->exec(sql);
				if (!r->isValid())
				{
					qDebug("MainWindow::updateList() - List of gtps isn't received!\n");
					qDebug("%s", this->m_conn->getError().toAscii().constData());
					return;
				}
				while (r->notEoF())
				{
					twi = new QTreeWidgetItem((QTreeWidget *)0);
					twi->setText(0, r->getValue(1));
					fd = new Feeder();
					TVItemDesc tvd;
					tvd.type = ST_Feeder;
					fd->ID = r->getValue(0, "0").toInt();
					fd->name = r->getValue(1);
					tvd.link = (void *) fd;
					QVariant v;
					v.setValue(tvd);
					twi->setData(0, Qt::UserRole, v);
					twi->setIcon(0, QIcon(":/icons/images/feeder.png"));
					it.append(twi);
					r->moveNext();
				}
				parent->addChildren(it);
				r->close();
				break;
				
			case ST_Feeder:
				parent->takeChildren();
				fd = (Feeder *) type.link;
				qDebug("MainWindow::updateList() - ID: %d; Name: %s\n", 
					   fd->ID, 
					   fd->name.toAscii().constData());
				sql = "select c.id, c.c_number, c.allow from counter c where c.feeder={id} order by c.c_number;";
				sql.replace("{id}", QString::number(fd->ID));
				r = this->m_conn->exec(sql);
				if (!r->isValid())
				{
					qDebug("MainWindow::updateList() - List of gtps isn't received!\n");
					qDebug("%s", this->m_conn->getError().toAscii().constData());
					return;
				}
				while (r->notEoF())
				{
					twi = new QTreeWidgetItem(parent);
					twi->setText(0, r->getValue(1));
					ctr = new Counter();
					TVItemDesc tvd;
					tvd.type = ST_Counter;
					ctr->ID = r->getValue(0, "0").toInt();
					ctr->number = r->getValue(1).toLongLong();
					tvd.link = (void *) ctr;
					QVariant v;
					v.setValue(tvd);
					twi->setData(0, Qt::UserRole, v);
					if (r->getValue("allow").toInt())
						twi->setIcon(0, QIcon(":/icons/images/counter.png"));
					else
						twi->setIcon(0, QIcon(":/icons/images/counter_innactive.png"));
					it.append(twi);
					r->moveNext();
				}
				parent->addChildren(it);
				r->close();
				break;
				
			case ST_Counter:
				parent->takeChildren();
				ctr = (Counter *) type.link;
				qDebug("MainWindow::updateList() - ID: %d; Number: %ld\n", 
					   ctr->ID, 
					   ctr->number);
				sql = "select c.id, c.name from channel c where c.counter={id} order by c.type, c.index;";
				sql.replace("{id}", QString::number(ctr->ID));
				r = this->m_conn->exec(sql);
				if (!r->isValid())
				{
					qDebug("MainWindow::updateList() - List of channels isn't received!\n");
					qDebug("%s", this->m_conn->getError().toAscii().constData());
					return;
				}
				while (r->notEoF())
				{
					twi = new QTreeWidgetItem(parent);
					twi->setText(0, r->getValue(1));
					ch = new Channel();
					TVItemDesc tvd;
					tvd.type = ST_Channel;
					ch->ID = r->getValue(0, "0").toInt();
					ch->name = r->getValue(1);
					tvd.link = (void *) ch;
					QVariant v;
					v.setValue(tvd);
					twi->setData(0, Qt::UserRole, v);
					twi->setIcon(0, QIcon(":/icons/images/channel.png"));
					it.append(twi);
					r->moveNext();
				}
				parent->addChildren(it);
				r->close();
				
				break;
				
			case ST_Organization:
				break;
		}
	}
}
