#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QMenu>
#include <QDir>
#include <QFile>
#include <QScrollBar>
#include "windows.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	if (ui->centralwidget->layout()) delete ui->centralwidget->layout();
	ui->centralwidget->setLayout(ui->mainLayout);
	
	QIcon ico = QIcon(":/scheduler/images/tray.png");
	setWindowIcon(ico);
	
	if (QSystemTrayIcon::isSystemTrayAvailable())
	{
		_tray = new QSystemTrayIcon(this);
		_tray->setToolTip(windowTitle());
		_tray->setIcon(ico);
		connect(_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
		createTrayActions();
		_tray->show();
	}
	else
		_tray = 0;
	
	settings = new QSettings("energo.conf", QSettings::IniFormat, this);

	QString host = settings->value("db.host", QString("127.0.0.1")).toString(),
	        port = settings->value("db.port", QString("5432")).toString(),
	        user = settings->value("db.user", QString("postgres")).toString(),
			pass = settings->value("db.password", QString()).toString(),
	        dbname = settings->value("db.name", QString("energo")).toString();
	
	_db = new PgreSqlDrv();
	if (!_db->connect(host, user, pass, dbname, true))
	{
		QMessageBox::critical(this, windowTitle(), tr("Невозможно подключиться к БД!\nАдрес: %1\nПользователь: %2\nПароль: %3\nБаза данных: %4").arg(
								  host,
								  user,
								  pass,
								  dbname));
		qApp->quit();
		return;
	}
	
	updateTree(0, 0);

	connect(ui->twSchedule, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(taskSelected(QTreeWidgetItem*,int)));
	ui->twStatus->setColumnCount(2);
	ui->twStatus->setRowCount(3);
	ui->twStatus->setItem(0, 0, new QTableWidgetItem(tr("Состояние")));	
	ui->twStatus->setItem(1, 0, new QTableWidgetItem(tr("Последний запуск")));	
	ui->twStatus->setItem(2, 0, new QTableWidgetItem(tr("Следующий старт")));	
	ui->twStatus->setItem(0, 1, new QTableWidgetItem(tr("")));	
	ui->twStatus->setItem(1, 1, new QTableWidgetItem(tr("")));	
	ui->twStatus->setItem(2, 1, new QTableWidgetItem(tr("")));	
	ui->twStatus->setColumnWidth(0, 200);
	ui->twStatus->setColumnWidth(1, 200);
	connect(ui->actStart, SIGNAL(triggered()), this, SLOT(taskStart()));
	connect(ui->actStop, SIGNAL(triggered()), this, SLOT(taskTerminate()));
	
	connect(ui->twSchedule, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(updateTree(QTreeWidgetItem*,int)));
	
	setWindowState(Qt::WindowMaximized);
	_state = Qt::WindowMaximized;
}

MainWindow::~MainWindow()
{
	delete ui;
	//if (_db->isConnected()) _db->close();
	//delete _db;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
	visibilityChange();
	e->ignore();
}

void MainWindow::taskStarted()
{
	Schedule * schedule = (Schedule *)sender();
	schedule->node()->setIcon(0, QIcon(":/scheduler/images/clock-go.png"));
	if (checkSubNode(schedule->node()))
		updateStatus(schedule->node());
}

void MainWindow::taskFinished()
{
	Schedule * schedule = (Schedule *)sender();
	schedule->node()->setIcon(0, QIcon(":/scheduler/images/clock-stop.png"));
	if (checkSubNode(schedule->node()))
		updateStatus(schedule->node());
}

void MainWindow::taskSelected(QTreeWidgetItem *item, int column)
{
	ui->txtConsole->setPlainText(QString());
	updateStatus(item);
}

void MainWindow::taskStart()
{
	if (ui->twSchedule->selectedItems().count() == 0)
		return;
	
	TreeElementDesc * desc = (TreeElementDesc *)ui->twSchedule->selectedItems().at(0)->data(0, Qt::UserRole).toInt();
	if (desc->type == TE_Schedule)
		desc->schedule->startManual();
	else
		desc->schedule->startManual(desc->ID, desc->type);
}

void MainWindow::taskTerminate()
{
	if (ui->twSchedule->selectedItems().count() == 0)
		return;
	
	TreeElementDesc * desc = (TreeElementDesc *)ui->twSchedule->selectedItems().at(0)->data(0, Qt::UserRole).toInt();
	desc->schedule->stop();
}

void MainWindow::taskMessageReceived()
{
	Schedule * schedule = (Schedule *)sender();

	if (checkSubNode(schedule->node()))
		appendConsole(schedule->getMessage());
}

void MainWindow::appendConsole(QString text)
{
	ui->txtConsole->setPlainText(ui->txtConsole->toPlainText().append(text));
	ui->txtConsole->verticalScrollBar()->setValue(ui->txtConsole->verticalScrollBar()->maximum());
}

void MainWindow::updateStatus(QTreeWidgetItem *node)
{
	TreeElementDesc * desc = (TreeElementDesc *)ui->twSchedule->selectedItems().at(0)->data(0, Qt::UserRole).toInt();
	if (desc->schedule->isRun())
		ui->twStatus->item(0, 1)->setText(tr("Запущен"));
	else
		ui->twStatus->item(0, 1)->setText(tr("Остановлен"));
	ui->twStatus->item(1, 1)->setText(desc->schedule->lastStart().toString("yyyy-MM-dd hh:mm:ss"));
	ui->twStatus->item(2, 1)->setText(desc->schedule->getStartTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void MainWindow::visibilityChange()
{
	if (isVisible())
	{
		_state = windowState();
		hide();
	}
	else
	{
		show();
		if (_state == Qt::WindowMinimized)
			setWindowState(Qt::WindowMaximized);
		else
			setWindowState(_state);
	}
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
		case QSystemTrayIcon::Trigger:
			visibilityChange();
			break;
	}
}

void MainWindow::createTrayActions()
{
	QMenu * trayMnu = new QMenu(this);
	QAction * actQuit = new QAction(this);
	actQuit->setIcon(QIcon(":/scheduler/images/exit.png"));
	actQuit->setText(tr("Выйти"));
	connect(actQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
	trayMnu->addAction(actQuit);
	
	_tray->setContextMenu(trayMnu);
}

bool MainWindow::checkSubNode(QTreeWidgetItem *node)
{
	if (node->isSelected())
		return true;
	
	for (int i = 0; i < node->childCount(); i++)
	{
		if (checkSubNode(node->child(i)))
			return true;
	}
	return false;
}

void MainWindow::updateTree(QTreeWidgetItem * item, int column)
{
	PgreSqlResult * r = 0;
	
	if (item == 0)
	{
		if (!(r = _db->exec("select * from schedule;"))->isValid())
		{
			qDebug("Main() - SQL ERROR: %s",
				   _db->getError().toAscii().constData());
		}
		
		QList<QTreeWidgetItem *> root;
		
		while (r->notEoF())
		{
			QTreeWidgetItem * twi = new QTreeWidgetItem();
			Schedule * sch = new Schedule(twi);
			sch->setName(r->getValue("name"));
			sch->setPeriodicity(r->getValue("periodicity").toInt());
			sch->setShift(r->getValue("shift").toInt());
			PgreSqlResult * res_obj = _db->exec(QString("select object from interview where schedule=%1 order by priority desc;").arg(r->getValue("id")));
			while (res_obj->notEoF())
			{
				sch->appendObject(res_obj->getValue(0).toInt());
				res_obj->moveNext();
			}
			_scl.push(sch);
			TreeElementDesc * desc = new TreeElementDesc();
			desc->ID = r->getValue("id").toInt();
			desc->type = TE_Schedule;
			desc->schedule = sch;
			twi->setText(0, sch->name());
			twi->setIcon(0, QIcon(":/scheduler/images/clock-stop.png"));
			twi->setData(0, Qt::UserRole, QVariant::fromValue((int)desc));
			root.append(twi);
			r->moveNext();
			connect(sch, SIGNAL(started()), this, SLOT(taskStarted()));
			connect(sch, SIGNAL(finished()), this, SLOT(taskFinished()));
			connect(sch, SIGNAL(messageReceived()), this, SLOT(taskMessageReceived()));
		}
		ui->twSchedule->addTopLevelItems(root);
	}
	else
	{
		TreeElementDesc * desc = (TreeElementDesc *)item->data(0, Qt::UserRole).toInt();
		QList<QTreeWidgetItem *> twl;
		TreeElement type;
		QIcon icon;
		TreeElementDesc * pd;
		switch (desc->type)
		{
			case TE_Schedule:
				r = _db->exec(QString("select f.id, f.name from factory f where f.id in (select f.id from factory f left join object o on f.id=o.factory left join interview i on o.id=i.object where i.schedule=%1 group by f.id);").arg(
								  QString::number(desc->ID)));
				type = TE_Factory;
				icon = QIcon(":/scheduler/images/server.png");
				break;
				
			case TE_Factory:
				pd = (TreeElementDesc *) item->parent()->data(0, Qt::UserRole).toInt();
				r = _db->exec(QString("select o.id, o.name from factory f left join object o on f.id=o.factory left join interview i on o.id=i.object where i.schedule=%1 and f.id=%2;").arg(
								  QString::number(pd->ID),
								  QString::number(desc->ID)));
				type = TE_Object;
				icon = QIcon(":/scheduler/images/object.png");
				break;
				
			case TE_Object:
				break;
		}
		if (r)
		{
			if (r->isValid())
			{
				item->takeChildren();
				while (r->notEoF())
				{
					QTreeWidgetItem * twi = new QTreeWidgetItem();
					twi->setText(0, r->getValue(1));
					twi->setIcon(0, icon);
					TreeElementDesc * twidesc = new TreeElementDesc();
					twidesc->ID = r->getValue(0).toInt();
					twidesc->schedule = desc->schedule;
					twidesc->type = type;
					twi->setData(0, Qt::UserRole, QVariant::fromValue((int)twidesc));
					twl.append(twi);
					r->moveNext();
				}
				item->addChildren(twl);
				item->setExpanded(true);
			}
		}
	}
}

