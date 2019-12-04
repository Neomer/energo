#include "balansrpt.h"
#include <QtPlugin>
#include <QMessageBox>
#include <QMenu>
#include <QGraphicsTextItem>
#include <QFileDialog>

enum IntervalType
{
	IT_Manual,
	IT_Day,
	IT_Week,
	IT_Month
};

struct TableWidgetExtreme
{
	QTableWidgetItem * item;
	double value;
};


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



void BalansRpt::load(PgreSqlDrv *connection, QWidget *window)
{
	Q_INIT_RESOURCE(resources);

	this->ui = new Ui::BalansRptForm();
    this->ui->setupUi(window);
	m_connection = connection;
    m_parent = window;
    
    window->setWindowState(Qt::WindowNoState);
    window->setWindowState(Qt::WindowMaximized);
    
    if (window->layout()) delete window->layout();
    window->setLayout(this->ui->mainLayout);
    window->setWindowTitle(REPORT_NAME);

	PgreSqlResult * r = m_connection->exec("select id, name from balans order by name;");
    if (!r->isValid())
    {
        QMessageBox::critical(m_parent, REPORT_NAME, tr("Неверный запрос к БД.\n%1").arg(m_connection->getError()));
        return;
    }
    while (r->notEoF())
    {
        QTreeWidgetItem * item = new QTreeWidgetItem();
        item->setText(0, r->getValue("name"));
		item->setIcon(0, QIcon(":/balansrpt/images/balans.png"));
        item->setData(0, Qt::UserRole, QVariant::fromValue(r->getValue("id")));
        ui->twObjects->addTopLevelItem(item);
        r->moveNext();
    }
	r->close();

	ui->dteEnd->setDateTime(QDateTime::currentDateTime());
	ui->dteBegin->setDateTime(QDateTime::currentDateTime().addDays(-1));

	ui->cmbValueRound->addItem(tr("кВт*ч"), QVariant::fromValue(1));
	ui->cmbValueRound->addItem(tr("МВт*ч"), QVariant::fromValue(1000));
	
	connect(ui->twObjects, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(itemSelected(QTreeWidgetItem*,int)));
	connect(ui->dteBegin, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(dateBeginChanged(QDateTime)));
	connect(ui->dteEnd, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(dateEndChanged(QDateTime)));
	connect(ui->cmbItvType, SIGNAL(currentIndexChanged(int)), this, SLOT(intervalTypeChanged(int)));
	connect(ui->dteBegin, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(dtBeginContexMenuReq(QPoint)));
	connect(ui->dteEnd, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(dtEndContexMenuReq(QPoint)));
	connect(ui->cmdRefresh, SIGNAL(clicked()), this, SLOT(updateList()));
	connect(ui->cmdExcel, SIGNAL(clicked()), this, SLOT(exportToExcel()));

	ui->twData->horizontalHeader()->setResizeMode(QHeaderView::Interactive);
	ui->twData->verticalHeader()->setResizeMode(QHeaderView::Interactive);
	
	// Фильтры
	r = m_connection->exec("select id, name from controlhourgroup order by name;");
	if (!r->isValid())
	{
		QMessageBox::critical(m_parent, REPORT_NAME, tr("Неверный запрос к БД.\n%1").arg(m_connection->getError()));
		return;
	}
	ui->cmbControHourGroup->addItem(tr("Не использовать"), QVariant::fromValue(CHG_NONE));
	while (r->notEoF())
	{
		ui->cmbControHourGroup->addItem(r->getValue("name"), QVariant::fromValue(r->getValue(0).toInt()));
		r->moveNext();
	}
	r->close();	
	
	ui->cmbControHourGroup->setEnabled(false);
	//ui->chkHoly->setEnabled(false);
	ui->cmbHoly->setEnabled(false);
	ui->lblCGH->setEnabled(false);
	connect(ui->cmdFilter, SIGNAL(clicked(bool)), this, SLOT(filterTriggered(bool)));
	
    for (int i = 0; i < window->children().count(); i++)
    {
        QWidget * w = qobject_cast<QWidget *>(window->children().at(i));
        if (w)
            if (w->objectName() != "") w->show();
    }
}

void BalansRpt::unload()
{
}

QString BalansRpt::getName()
{
	return REPORT_NAME;
}

QString BalansRpt::getVersion()
{
	return REPORT_VER;
}

void BalansRpt::getPrintableForm(ReportEngine *e)
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
	table->setColumnWidth(0, 150);*/
}

/***********************************************
  
    SLOTS
    
************************************************/

void BalansRpt::exportToExcel()
{
	if (ui->twData->rowCount() == 0)
	{
		if (QMessageBox::question(
					m_parent,
					tr("Экспорт в MS Excel..."),
					tr("Данных для выгрузки не получено.\r\nВы уверены, что хотите продолжить?"), QMessageBox::Yes, QMessageBox::No) != QMessageBox::Yes)
			return;
	}

	QString path = QFileDialog::getSaveFileName(
				m_parent, 
				tr("Сохранить как..."), 
				"c:/", 
				tr("Файл Microsoft Excel (*.csv)"));
	
	if (path == "") 
		return;
	
	
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::critical(
					m_parent, 
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

void BalansRpt::filterTriggered(bool state)
{
	ui->cmbControHourGroup->setEnabled(state);
	//ui->chkHoly->setEnabled(state);
	ui->lblCGH->setEnabled(state);
	ui->cmbHoly->setEnabled(state);
}

void BalansRpt::updateList()
{
	if (ui->twObjects->selectedItems().count() == 0) 
		return;
	
	//ui->twData->clear();
	ui->twData->clearContents();
	
	QString sql, 
			filter_1 = " left join data d on b.channel=d.channel ", 
			filter_2;
 
	if (ui->cmdFilter->isChecked())
	{
		if (ui->cmbControHourGroup->itemData(ui->cmbControHourGroup->currentIndex()).toInt() != CHG_NONE)
		{
		
			filter_1 = QString(" left join controlhour ch on ch.gid=%1 and ch.date >='%2' and ch.date<='%3' left join data d on b.channel=d.channel and ch.date=d.date and ch.hour=div(d.itv, 2) ").arg(
							QString::number(ui->cmbControHourGroup->itemData(ui->cmbControHourGroup->currentIndex()).toInt()),
							ui->dteBegin->date().toString("yyyy-MM-dd"),
							ui->dteEnd->date().toString("yyyy-MM-dd"));
		}
		switch ((DayType)ui->cmbHoly->currentIndex())
		{
			case All:
				filter_2 = "";
				break;
				
			case Weekday:
				filter_2 = QString(" and d.date NOT IN (select * from calendar where dt>='%1' and dt<='%2') ").arg(
							   ui->dteBegin->dateTime().toString("yyyy-MM-dd"),
							   ui->dteEnd->dateTime().toString("yyyy-MM-dd")); 
				break;
				
			case Weekend:
				filter_2 = QString(" and d.date IN (select * from calendar where dt>='%1' and dt<='%2') ").arg(
							   ui->dteBegin->dateTime().toString("yyyy-MM-dd"),
							   ui->dteEnd->dateTime().toString("yyyy-MM-dd")); 
				break;
		}
	}

	GroupType gt = (GroupType)ui->cmbGroupType->currentIndex();
	
//select d.date, d.itv, sum(d.value * b.direction) from balans_element b %4 where b.balans=%1 and d.dt>='%2' and d.dt<'%3' and d.itv_length=30 %5 group by d.date, d.itv order by d.date, d.itv;
	switch (gt)
	{
		case GT_30min:
			sql = QString("select d.date, d.itv, sum(d.value * b.direction) from balans_element b %4 where b.balans=%1 and d.dt>='%2' and d.dt<'%3' and d.itv_length=30 %5 group by d.date, d.itv order by d.date, d.itv;").arg(
						ui->twObjects->selectedItems().at(0)->data(0, Qt::UserRole).toString(),
						ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
						ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
					  filter_1,
					  filter_2);
			break;
			
		case GT_60min:
			sql = QString("select d.date, div(d.itv, 2) as itv, sum(d.value * b.direction) from balans_element b %4 where b.balans=%1 and d.dt>='%2' and d.dt<'%3' and d.itv_length=30 %5 group by d.date, div(d.itv, 2) order by d.date, itv;").arg(
						ui->twObjects->selectedItems().at(0)->data(0, Qt::UserRole).toString(),
						ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
						ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
					  filter_1,
					  filter_2);
			break;
			
		case GT_Day:
			sql = QString("select d.date, count(d.itv) as itv, sum(d.value * b.direction) from balans_element b %4 where b.balans=%1 and d.dt>='%2' and d.dt<'%3' and d.itv_length=30 %5 group by d.date order by d.date;").arg(
						ui->twObjects->selectedItems().at(0)->data(0, Qt::UserRole).toString(),
						ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
						ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
					  filter_1,
					  filter_2);
			break;
	}
	
	//QMessageBox::warning(m_parent, tr("Предупреждение!"), m_connection->getError());
	
	PgreSqlResult * r = m_connection->exec(sql);
	if (!r->isValid())
	{
		qDebug("BalansRpt::updateList() - SQL ERROR: %s\n%s",
			   m_connection->getError().toAscii().constData(),
			   sql.toAscii().constData());
		QMessageBox::critical(m_parent, tr("Ошибка SQL-запроса!"), m_connection->getError());
	}
	else
	{
		QStringList hdr;
		hdr.append(tr("Дата/Время"));
		//if ()
		hdr.append(tr("Значение"));
		ui->twData->setColumnCount(hdr.count());
		ui->twData->setHorizontalHeaderLabels(hdr);
		ui->twData->setRowCount(r->numRows());
		QTableWidgetItem * twi;
		double max_val = -1;
		TableWidgetExtreme * max = new TableWidgetExtreme();
		max->item = 0;
		max->value = -99999999;
		TableWidgetExtreme * min = new TableWidgetExtreme();
		min->item = 0;
		min->value = 99999999;

		while (r->notEoF())
		{
			twi = new QTableWidgetItem();
			twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			QDateTime dt = QDateTime::fromString(r->getValue(0), "yyyy-MM-dd");
			switch (gt)
			{
				case GT_30min:
					dt = dt.addSecs(r->getValue(1).toInt() * 1800);
					twi->setText(dt.toString("yyyy-MM-dd hh:mm"));
					break;
					
				case GT_60min:
					dt = dt.addSecs(r->getValue(1).toInt() * 3600);
					twi->setText(dt.toString("yyyy-MM-dd hh:mm"));
					break;
					
				case GT_Day:
					twi->setText(dt.toString("yyyy-MM-dd"));
					break;
			}

			ui->twData->setItem(r->absolutePos(), 0, twi);

			twi = new QTableWidgetItem();
			twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			if (ui->txtAccuracy->text().toInt() >= 0)
				twi->setText(QString::number(myround(r->getValue(2).toDouble() / ui->cmbValueRound->itemData(ui->cmbValueRound->currentIndex()).toInt(), ui->txtAccuracy->text().toInt())));
			else
				twi->setText(QString::number(r->getValue(2).toDouble() / ui->cmbValueRound->itemData(ui->cmbValueRound->currentIndex()).toInt()));
			if (twi->text().toDouble() > max_val) max_val = twi->text().toDouble();
			if (max->value < twi->text().toDouble())
			{
				max->value = twi->text().toDouble();
				max->item = twi;
			}
			if (min->value > twi->text().toDouble())
			{
				min->value = twi->text().toDouble();
				min->item = twi;
			}
			ui->twData->setItem(r->absolutePos(), 1, twi);
			r->moveNext();
		}
		if (max->item != 0)
		{
			max->item->setBackgroundColor(QColor(255, 200, 200));
		}

		if (min->item != 0)
		{
			min->item->setBackgroundColor(QColor(200, 200, 255));
		}

		// Рисуем график
		QGraphicsScene * scene;
		if (!ui->gvGraph->scene())
		{
			scene = new QGraphicsScene(QRectF(0, 0, ui->gvGraph->width() - 0.05 * ui->gvGraph->width(), ui->gvGraph->height() - 0.1 * ui->gvGraph->height()));
			ui->gvGraph->setScene(scene);
		}
		else
		{
			scene = ui->gvGraph->scene();
			scene->clear();
		}
		
		double 	x0 = 50,
				y0 = 40;
	
		double dx = (scene->sceneRect().width() - x0) / ui->twData->rowCount(),
				dy = (scene->sceneRect().height() - y0) / max_val,
				y1 = (scene->sceneRect().height() - y0);
		
		// Задаем цвета графиков
		QPen axis = QPen(QColor(0xA0, 0xA0, 0xA0)),
				axis_lines = QPen(QColor(0xC0, 0xC0, 0xC0));
		QList<QPen> pen;
		pen.append(QPen(QColor(255, 0, 0)));
		pen.append(QPen(QColor(0, 188, 0)));
		pen.append(QPen(QColor(0, 0, 188)));
		pen.append(QPen(QColor(188, 188, 0)));
		
		// Рисуем оси координат
		scene->addLine(x0, y1, x0, 0, axis);
		scene->addLine(x0, y1, scene->sceneRect().width(), y1, axis);
		
		double dyax = y1 / Y_AXIS_LEGEND_COUNT,
				dval = max_val / Y_AXIS_LEGEND_COUNT;
		
		QFont axfont("Times", 8, QFont::Normal);
		
		for (int i = 0; i <= Y_AXIS_LEGEND_COUNT; i++)
		{
			QGraphicsTextItem * text = scene->addText(QString::number(dval * i), axfont);
			text->setPos(0, y1 - QFontInfo(axfont).pixelSize() - i * dyax);
			scene->addLine(x0 - 3, y1 - i * dyax, scene->sceneRect().width(), y1 - i * dyax, axis_lines);
		}
	
		for (int i = 0; i < ui->twData->rowCount(); i++)
		{
			QGraphicsTextItem * text = scene->addText(QString::number(i + 1), axfont);
			text->setPos(x0 + dx * i - (axfont.pointSize() * text->toPlainText().length() * 0.5), y1 + QFontInfo(axfont).pixelSize() + 5);
		}
	
		
		// Рисуем графики
		for (int c = 1; c < ui->twData->columnCount(); c++)
			for (int r = 1; r < ui->twData->rowCount(); r++)
			{
				scene->addLine((r - 1) * dx + x0, y1 - ui->twData->item(r - 1, c)->text().toDouble() * dy, r * dx + x0, y1 - ui->twData->item(r, c)->text().toDouble() * dy, pen.at(c - 1));
			}
		
		ui->gvGraph->updateSceneRect(scene->sceneRect());
		// Считаем суммарные/средние величины
		int rows = ui->twData->rowCount();
		if (rows > 0)
		{
			QFont font = QFont();
			font.setBold(true);
			ui->twData->setRowCount(rows + 2);
			QTableWidgetItem * twi = new QTableWidgetItem();
			twi->setText(tr("Среднее значение"));
			twi->setFont(font);
			ui->twData->setItem(rows, 0, twi);
			
			twi = new QTableWidgetItem();
			twi->setText(tr("Суммарное значение"));
			twi->setFont(font);
			ui->twData->setItem(rows + 1, 0, twi);

			for (int c = 1; c < ui->twData->columnCount(); c++)
			{
				double summ = 0;
				for (int r = 0; r < rows; r++)
				{
					summ += ui->twData->item(r, c)->text().toDouble();
				}
				twi = new QTableWidgetItem();
				twi->setText(QString::number(summ / rows, 'f'));
				twi->setFont(font);
				ui->twData->setItem(rows, c, twi);

				twi = new QTableWidgetItem();
				twi->setText(QString::number(summ, 'f'));
				twi->setFont(font);
				ui->twData->setItem(rows + 1, c, twi);
			}
		}
	}
}

void BalansRpt::showBalansCreateDlg()
{
}

void BalansRpt::itemSelected(QTreeWidgetItem *item, int column)
{
	updateList();
}

void BalansRpt::dateBeginChanged(QDateTime dt)
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


void BalansRpt::dateEndChanged(QDateTime dt)
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

void BalansRpt::intervalTypeChanged(int index)
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

void BalansRpt::dtBeginContexMenuReq(QPoint position)
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

void BalansRpt::dtEndContexMenuReq(QPoint position)
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

void BalansRpt::setdtBeginDayBegin()
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

void BalansRpt::setdtEndDayBegin()
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

Q_EXPORT_PLUGIN(BalansRpt);
