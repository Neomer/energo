#include "checkdatarpt.h"

#include <QRect>

#include <QMessageBox>
#include <QDateTime>
#include <QStringList>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QButtonGroup>

void CheckDataRpt::load(PgreSqlDrv *connection, QWidget *window)
{
	Q_INIT_RESOURCE(resources);	

	if (!connection->isConnected())
	{
		QMessageBox::critical(window, REPORT_NAME, tr("Подключение к БД не установлено!"));
		return;
	}
	
	this->m_connection = connection;
	this->m_window = window;
	this->m_codec = QTextCodec::codecForName("UTF-8");
	
	m_lv = new QTableWidget(window);
	QRect rect(30, 50, 500, window->height() - 100);

	
	//QRect rect;
	//m_lv->setGeometry(rect);
	refreshData();
	
	m_lv->setSortingEnabled(true);
	m_lv->show();

	rect = QRect(30, 10, 40, 30);
	cmdRefresh = new QPushButton(window);
	cmdRefresh->setGeometry(rect);
	cmdRefresh->setIcon(QIcon(":/images/images/refresh.png"));
	cmdRefresh->setToolTip(tr("Обновить"));
	cmdRefresh->show();

	rect = QRect(80, 10, 150, 30);
	cmdFindProblems = new QPushButton(window);
	cmdFindProblems->setGeometry(rect);
	cmdFindProblems->setText(tr("Найти нехватку данных"));
	cmdFindProblems->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	cmdFindProblems->show();

	rect = QRect(80, 10, 40, 30);
	cmdFilter = new QPushButton(window);
	cmdFilter->setGeometry(rect);
	cmdFilter->setToolTip(tr("Отфильтровать"));
	cmdFilter->setIcon(QIcon(":/images/images/filter.png"));
	cmdFilter->show();
	
	QGridLayout * main_layout = (QGridLayout *)window->layout();
	QHBoxLayout * btn_panel = new QHBoxLayout();
	btn_panel->addWidget(cmdRefresh);
	btn_panel->addWidget(cmdFilter);
	btn_panel->addWidget(cmdFindProblems);
	
	main_layout->addLayout(btn_panel, 0, 0);
	main_layout->addWidget(m_lv, 1, 0, 1, 4);
	
	main_layout->setColumnMinimumWidth(2, 200);
	main_layout->setColumnStretch(2, 10);
	
	m_lv->horizontalHeader()->setSortIndicatorShown(true);
	
	QObject::connect(cmdFindProblems, SIGNAL(clicked()), this, SLOT(findDataDeficit()));
	QObject::connect(cmdRefresh, SIGNAL(clicked()), this, SLOT(refreshData()));
	connect(m_lv->horizontalHeader(), SIGNAL(sectionPressed(int)), this, SLOT(sortData(int)));
	m_lv->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
	m_lv->verticalHeader()->setResizeMode(QHeaderView::Interactive);
}

void CheckDataRpt::sortData(int column)
{
	m_lv->hide();
	if (column == m_lv->horizontalHeader()->sortIndicatorSection())
		m_lv->sortItems(column, (Qt::SortOrder)!((bool)m_lv->horizontalHeader()->sortIndicatorOrder()));
	else
		m_lv->sortItems(column, Qt::AscendingOrder);
	m_lv->show();
}

void CheckDataRpt::updateList(PgreSqlResult *q)
{
	m_lv->hide();
	
	m_lv->setSortingEnabled(false);
	m_lv->clearContents();
	
	if (m_lv->columnCount() == 0)
	{
		QStringList fl;;
		fl.append(tr("Номер счетчика"));
		fl.append(tr("Предприятие"));
		fl.append(tr("Подстанция"));
		fl.append(tr("Фидер"));
		fl.append(tr("Канал"));
		fl.append(tr("Дата"));
		fl.append(tr("Отклонение (сек)"));
		fl.append(tr("Не хватает"));
		fl.append(tr("Текущая дата"));
		
		m_lv->setColumnCount(fl.count());
		m_lv->setHorizontalHeaderLabels(fl);
		m_lv->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_lv->horizontalHeader()->setHighlightSections(false);
	}
	if (q->numRows() > 0) m_lv->setRowCount(q->numRows());
	

	QDateTime dt = QDateTime::currentDateTime();
	
	while (q->notEoF())
	{
		for (int f = 0; f < q->numFields(); f++)
		{
			QTableWidgetItem * item = new QTableWidgetItem();
			item->setText(q->getValue(f));
			item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			m_lv->setItem(q->absolutePos(), f, item);
		}
		QTableWidgetItem * item = new QTableWidgetItem();
		int itv = QDateTime::fromString(q->getValue(5), "yyyy-MM-dd hh:mm:ss").addSecs(1800).secsTo(dt) / 1800;
		item->setText(QString::number(itv));
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		if (QDateTime::fromString(q->getValue(5), "yyyy-MM-dd hh:mm:ss").addSecs(1800).daysTo(dt) > 0)
			item->setBackgroundColor(QColor(255, 180, 180));
		else
			item->setBackgroundColor(QColor(180, 255, 180));
		item->setTextAlignment(Qt::AlignCenter);
		m_lv->setItem(q->absolutePos(), q->numFields(), item);
		
		item = new QTableWidgetItem();
		item->setText(dt.toString("yyyy-MM-dd hh:mm"));
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_lv->setItem(q->absolutePos(), q->numFields() + 1, item);
		q->moveNext();
	}
	m_lv->verticalHeader()->setDefaultSectionSize(20);;
	m_lv->setSortingEnabled(true);
	
	m_lv->show();
}

void CheckDataRpt::unload()
{
	m_lv->clear();
	delete m_lv;
	delete cmdFindProblems;
	delete cmdRefresh;
}

QString CheckDataRpt::getName()
{
	return REPORT_NAME;
}

QString CheckDataRpt::getVersion()
{
	return REPORT_VER;
}

void CheckDataRpt::getPrintableForm(ReportEngine *engine)
{
}

void CheckDataRpt::findDataDeficit()
{
	PgreSqlResult * q = this->m_connection->exec("select c.c_number, fy.name , o.name, f.name, data.date, MAX(data.itv) from counter c left join (Select feeder, MAX(date) as max_date from data Group by feeder) as mdate on mdate.feeder = c.feeder left join feeder f on f.id = c.feeder left join data on data.date = mdate.max_date and data.feeder = mdate.feeder left join object o on f.object = o.id left join factory fy on fy.id = o.factory where current_date - data.date > 0  Group by c.c_number, f.name, data.feeder, data.date, o.name, fy.name order by fy.name, o.name, f.name, c.c_number;");
	if (!q->isValid())
	{
		qDebug("CheckDataRpt::load() - Query failed!");
		QMessageBox::critical(m_window, REPORT_NAME, tr("Ошибка при загрузке модуля: неверный запрос к БД."));
		return;
	}
	updateList(q);
	q->close();
}

void CheckDataRpt::refreshData()
{
	PgreSqlResult * q = this->m_connection->exec("select cbo.cnumber, cbo.ftname, cbo.oname, cbo.fname, cbo.chname, ch.last_date, c.desync from channels_by_object cbo left join channel ch on ch.id = cbo.chid left join counter c on c.id = cbo.cid where c.allow=1 order by cbo.ftname, cbo.oname, cbo.fname, cbo.chname;");
	if (!q->isValid())
	{
		qDebug("CheckDataRpt::load() - Query failed!");
		QMessageBox::critical(m_window, REPORT_NAME, tr("Ошибка при загрузке модуля: неверный запрос к БД.\n%1").arg(m_connection->getError()));
		return;
	}
	updateList(q);
	q->close();
}

Q_EXPORT_PLUGIN(CheckDataRpt);
