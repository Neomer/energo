#include "AlertViewRpt.h"
#include <QtPlugin>
#include <QMessageBox>
#include <QDateTime>

Q_EXPORT_PLUGIN(AlertViewRpt);

AlertViewRpt::AlertViewRpt()
{
	m_alert = 0;
}

void AlertViewRpt::load(PgreSqlDrv *connection, QWidget *window)
{
	Q_INIT_RESOURCE(resources);

	this->ui = new Ui::AlertViewForm();
    this->ui->setupUi(window);
	m_connection = connection;
    m_parent = window;
	
	CreateUi();
}

void AlertViewRpt::unload()
{
}

QString AlertViewRpt::getName()
{
	return REPORT_NAME;
}

QString AlertViewRpt::getVersion()
{
	return REPORT_VER;
}

void AlertViewRpt::getPrintableForm(ReportEngine *e)
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
	row->addText(new ReportText(tr("Отчет сформирован "), e->font("mainbold"), Qt::AlignLeft));	
	row->addText(new ReportText(QDateTime::currentDateTime().toString("dd MMMM yyyy hh:mm:ss"), e->font("main"), Qt::AlignLeft));	

	row = sheet->appendRow();
	row->addText(new ReportText(tr("События за "), e->font("mainbold"), Qt::AlignLeft));	
	row->addText(new ReportText(ui->cmbSince->itemText(ui->cmbSince->currentIndex()), e->font("main"), Qt::AlignLeft));	

	row = sheet->appendRow();
	ReportTable * table = new ReportTable(ui->twList);

	row->addTable(table);
	table->setColumnWidth(0, 0);
	table->setColumnWidth(1, 120);
	table->setColumnWidth(2, 120);*/
}

void AlertViewRpt::alertTypeChanged(QTreeWidgetItem *item, int column)
{
	if (m_alert)
		m_alert->setIcon(0, QIcon(":/AlertView/images/book-closed.png"));
	
	m_alert = item;
	item->setIcon(0, QIcon(":/AlertView/images/book-open.png"));
	
	if (column >= 0)
		loadData();
}

void AlertViewRpt::loadData()
{
	if (ui->twAlerts->selectedItems().count() == 0)
		return;
	
	if (!m_alert)
		alertTypeChanged(ui->twAlerts->selectedItems().at(0), 0);
	
	ui->twList->raise();
	PgreSqlResult * r = 0;
	
	int itv = ui->cmbSince->itemData(ui->cmbSince->currentIndex()).toInt();
	int lvl = ui->cmbLevel->itemData(ui->cmbLevel->currentIndex()).toInt();
	QString lvl_filter;
	if (lvl != -1)
	{
		lvl_filter = QString(" and level=%1 ").arg(QString::number(lvl));
	}
	if (itv == -1)
	{
		r = m_connection->exec(QString("select level, to_char(date, 'yyyy-MM-dd HH24:MI:ss.ms') date, text, object, objecttype from alert where type=%1 %2 order by date desc;").arg(
								   QString::number(m_alert->data(0, Qt::UserRole).toInt()),
								   lvl_filter));
	}
	else
		r = m_connection->exec(QString("select level, to_char(date, 'yyyy-MM-dd HH24:MI:ss.ms') date, text, object, objecttype from alert where type=%1 and date>'%2' %3 order by date desc, level desc;").arg(
									QString::number(m_alert->data(0, Qt::UserRole).toInt()),
									QDateTime::currentDateTime().addSecs(itv).toString("yyyy-MM-dd hh:mm:ss"),
								    lvl_filter));
	if (!r->isValid())
	{
		QMessageBox::critical(m_parent, REPORT_NAME, tr("Ошибка запроса к БД!\n").append(
								  m_connection->getError()));
		r->close();
		return;
	}
	else
	{
		QStringList hdr;
		hdr << tr("") << tr("Дата") << tr("Объект") << tr("Текст");
		ui->twList->setColumnCount(hdr.count());
		ui->twList->setHorizontalHeaderLabels(hdr);
		ui->twList->setRowCount(r->numRows());
		ui->twList->setColumnWidth(0, 24);
		ui->twList->setColumnWidth(1, 130);
		ui->twList->setColumnWidth(2, 150);
		while (r->notEoF())
		{
			QTableWidgetItem * twi = new QTableWidgetItem();
			switch ((AlertLevel)r->getValue("level").toInt())
			{
				case ALL_Normal:
					twi->setIcon(QIcon(":/AlertView/images/information.png"));
					break;
					
				case ALL_Warning:
					twi->setIcon(QIcon(":/AlertView/images/warning.png"));
					break;
					
				case ALL_Critical:
					twi->setIcon(QIcon(":/AlertView/images/error.png"));
					break;
			}
			
			QString objname, objtype;
			switch ((AlertObjType)r->getValue("objecttype").toInt())
			{
				case AOT_Counter:
					objname = m_connection->exec(QString("select c_number from counter where id=%1;").arg(
													 r->getValue("object")))->getValue(0);
					objtype = tr("Счетчик");
					break;
					
				case AOT_Object:
					objname = m_connection->exec(QString("select name from object where id=%1;").arg(
													 r->getValue("object")))->getValue(0);
					objtype = tr("Подстанция");
					break;
			}

			ui->twList->setItem(r->absolutePos(), 0, twi);
			twi = new QTableWidgetItem();
			twi->setText(QDateTime::fromString(r->getValue("date"), "yyyy-MM-dd hh:mm:ss.zzz").toString(
							 "yyyy-MM-dd hh:mm:ss"));
			ui->twList->setItem(r->absolutePos(), 1, twi);
			twi = new QTableWidgetItem();
			twi->setText(QString("%1: %2").arg(objtype, objname));
			ui->twList->setItem(r->absolutePos(), 2, twi);
			twi = new QTableWidgetItem();
			twi->setText(tr(r->getValue("text").toAscii().constData()));
			ui->twList->setItem(r->absolutePos(), 3, twi);
			
			r->moveNext();
		}
	}
	r->close();
}

void AlertViewRpt::CreateUi()
{
	m_parent->setWindowState(Qt::WindowNoState);
    m_parent->setWindowState(Qt::WindowMaximized);
    
    if (m_parent->layout()) delete m_parent->layout();
    m_parent->setLayout(this->ui->mainLayout);
    m_parent->setWindowTitle(REPORT_NAME);

	QList<QTreeWidgetItem *> twl;
	
	PgreSqlResult * r = m_connection->exec("select type, COUNT(*) from alert group by type;");
	if (!r->isValid())
	{
		QMessageBox::critical(m_parent, REPORT_NAME, tr("Ошибка запроса к БД!\n").append(
								  m_connection->getError()));
	}
	else
	{
		QTreeWidgetItem * twi = new QTreeWidgetItem();
		twi->setText(0, tr("Информация"));
		twi->setIcon(0, QIcon(":/AlertView/images/book-closed.png"));
		twi->setData(0, Qt::UserRole, QVariant::fromValue((int)ALT_Infomation));
		for (;;)
		{
			if (r->getValue(0).toInt() == (int)ALT_Infomation)
			{
				twi->setText(1, r->getValue(1));
				break;
			}
			r->moveNext();
			if (r->eof())
			{
				twi->setText(1, "0");
				break;
			}
		}
		twl << twi;
		
		twi = new QTreeWidgetItem();
		twi->setText(0, tr("Предупреждения"));
		twi->setIcon(0, QIcon(":/AlertView/images/book-closed.png"));
		twi->setData(0, Qt::UserRole, QVariant::fromValue((int)ALT_Warning));
		r->moveFirst();
		for (;;)
		{
			if (r->getValue(0).toInt() == (int)ALT_Warning)
			{
				twi->setText(1, r->getValue(1));
				break;
			}
			r->moveNext();
			if (r->eof())
			{
				twi->setText(1, "0");
				break;
			}
		}
		twl << twi;
	
		twi = new QTreeWidgetItem();
		twi->setText(0, tr("Ошибки"));
		twi->setIcon(0, QIcon(":/AlertView/images/book-closed.png"));
		twi->setData(0, Qt::UserRole, QVariant::fromValue((int)ALT_Error));
		r->moveFirst();
		for (;;)
		{
			if (r->getValue(0).toInt() == (int)ALT_Error)
			{
				twi->setText(1, r->getValue(1));
				break;
			}
			r->moveNext();
			if (r->eof())
			{
				twi->setText(1, "0");
				break;
			}
		}
		twl << twi;
	
		twi = new QTreeWidgetItem();
		twi->setText(0, tr("Опрос приборов учета"));
		twi->setIcon(0, QIcon(":/AlertView/images/book-closed.png"));
		twi->setData(0, Qt::UserRole, QVariant::fromValue((int)ALT_ReceiveError));
		r->moveFirst();
		for (;;)
		{
			if (r->getValue(0).toInt() == (int)ALT_ReceiveError)
			{
				twi->setText(1, r->getValue(1));
				break;
			}
			r->moveNext();
			if (r->eof())
			{
				twi->setText(1, "0");
				break;
			}
		}
		twl << twi;
	
		ui->twAlerts->insertTopLevelItems(0, twl);
	}
	r->close();
	
	ui->cmbSince->addItem(tr("1 час"), -3600);
	ui->cmbSince->addItem(tr("24 часа"), -86400);
	ui->cmbSince->addItem(tr("7 дней"), -604800);
	ui->cmbSince->addItem(tr("30 дней"), -2592000);
	ui->cmbSince->addItem(tr("Все"), -1);
	
	ui->cmbLevel->addItem(tr("Все"), -1);
	ui->cmbLevel->addItem(QIcon(":/AlertView/images/error.png"), tr("Критический"), QVariant::fromValue((int)ALL_Critical));
	ui->cmbLevel->addItem(QIcon(":/AlertView/images/warning.png"), tr("Предупреждение"), QVariant::fromValue((int)ALL_Warning));
	ui->cmbLevel->addItem(QIcon(":/AlertView/images/information.png"), tr("Уведомление"), QVariant::fromValue((int)ALL_Normal));
	
	connect(ui->twAlerts, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
			this, SLOT(alertTypeChanged(QTreeWidgetItem*, int)));
	connect(ui->cmdRefresh, SIGNAL(clicked()), this, SLOT(loadData()));
	
	for (int i = 0; i < m_parent->children().count(); i++)
    {
        QWidget * w = qobject_cast<QWidget *>(m_parent->children().at(i));
        if (w)
            if (w->objectName() != "") w->show();
    }
}
