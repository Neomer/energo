#include "OperView.h"
#include <QtPlugin>
#include <QMessageBox>
#include <QProgressBar>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QHeaderView>
#include <QGraphicsTextItem>
#include <QMenu>
#include <qmath.h>
#include <QFont>

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

void OperView::load(PgreSqlDrv *connection, QWidget *window)
{
	Q_INIT_RESOURCE(resources);

	if (!connection->isConnected())
	{
		QMessageBox::critical(window, REPORT_NAME, tr("Подключение к БД не установлено!"));
		return;
	}
	
	this->m_connection = connection;
	this->m_window = window;
	m_timer = new QTimer(window);
	m_timer->setInterval(TIMER_DEFAULT_PERIOD * 1000);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(loadData()));
	
	createUi();
	
	PgreSqlResult * r = connection->exec("select name, id from factory order by name;");
	while (r->notEoF())
	{
		QTreeWidgetItem * item = new QTreeWidgetItem();
		TreeElementDesc * desc = new TreeElementDesc();
		desc->id = r->getValue(1).toInt();
		desc->type = Factory;
		item->setText(0, r->getValue(0));
		item->setIcon(0, QIcon(":/operview/images/server.png"));
		item->setData(0, Qt::UserRole, QVariant::fromValue((int)desc));
		ui->twObjects->insertTopLevelItem(r->absolutePos(), item);
		r->moveNext();
	}
	r->close();
}

void OperView::unload()
{
	
}

QString OperView::getName()
{
	return REPORT_NAME;
}

QString OperView::getVersion()
{
	return REPORT_VER;
}

void OperView::getPrintableForm(ReportEngine *e)
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
	table->setColumnWidth(0, 120);
	
	/*
	QGraphicsView * gv = new QGraphicsView(ui->gvGraph->scene());
	row = sheet->appendRow();
	ReportWidget * wdgt = new ReportWidget(gv->sc);
	row->addWidget(wdgt);
	/wdgt->graphicsItem()->setVisible(true);
	*/
}

void OperView::loadData()
{
	if (ui->twObjects->selectedItems().count() == 0)
		return;
	
	ui->twData->hide();
	ui->twData->clearContents();
	
	QTreeWidgetItem * item = ui->twObjects->selectedItems().at(0);
	TreeElementDesc * desc = (TreeElementDesc *)item->data(0, Qt::UserRole).toInt();	
	PgreSqlResult * r = 0;
	
/*

*/
	switch (desc->type)
	{
		case Channel:
			r = m_connection->exec(QString("select d.date, div(d.itv, %5 / d.itv_length) itv, ch.index as channel, %5 itv_length, sum(d.value * %6) as value from data d left join channel ch on ch.id=d.channel left join channels_by_object cbo on cbo.chid=ch.id where cbo.chid=%1 and ch.type=1 and d.dt >= '%2' and d.dt < '%3' and d.itv_length=%4 group by d.date, div(d.itv, %5 / d.itv_length) , ch.index, d.itv_length order by d.date, itv, ch.index;").arg(
									   QString::number(desc->id), 
									   ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), 
									   ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
									   ui->cmbItvLength->itemData(ui->cmbItvLength->currentIndex()).toString(),
								       ui->cmbGroupType->itemData(ui->cmbGroupType->currentIndex()).toString(),
									   QString::number(ui->cmbValueRound->itemData(ui->cmbValueRound->currentIndex()).toDouble(), 'f', 3)));
			break;
		
		case Counter:
			r = m_connection->exec(QString("select d.date, div(d.itv, %5 / d.itv_length) itv, ch.index as channel, %5 itv_length, sum(d.value * %6) as value from data d left join channel ch on ch.id=d.channel left join channels_by_object cbo on cbo.chid=ch.id where cbo.cid=%1 and ch.type=1 and d.dt >= '%2' and d.dt < '%3' and d.itv_length=%4 group by d.date, div(d.itv, %5 / d.itv_length) , ch.index, d.itv_length order by d.date, itv, ch.index;").arg(
									   QString::number(desc->id), 
									   ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), 
									   ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
									   ui->cmbItvLength->itemData(ui->cmbItvLength->currentIndex()).toString(),
									   ui->cmbGroupType->itemData(ui->cmbGroupType->currentIndex()).toString(),
									   QString::number(ui->cmbValueRound->itemData(ui->cmbValueRound->currentIndex()).toDouble(), 'f', 3)));
			break;
			
		case Feeder:
			r = m_connection->exec(QString("select d.date, div(d.itv, %5 / d.itv_length) itv, ch.index as channel, %5 itv_length, sum(d.value * %6) as value from data d left join channel ch on ch.id=d.channel left join channels_by_object cbo on cbo.chid=ch.id where cbo.fid=%1 and ch.type=1 and d.dt >= '%2' and d.dt < '%3' and d.itv_length=%4 group by d.date, div(d.itv, %5 / d.itv_length) , ch.index, d.itv_length order by d.date, itv, ch.index;").arg(
									   QString::number(desc->id), 
									   ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), 
									   ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
									   ui->cmbItvLength->itemData(ui->cmbItvLength->currentIndex()).toString(),
									   ui->cmbGroupType->itemData(ui->cmbGroupType->currentIndex()).toString(),
									   QString::number(ui->cmbValueRound->itemData(ui->cmbValueRound->currentIndex()).toDouble(), 'f', 3)));
			break;

		case Object:
			r = m_connection->exec(QString("select d.date, div(d.itv, %5 / d.itv_length) itv, ch.index as channel, %5 itv_length, sum(d.value * %6) as value from data d left join channel ch on ch.id=d.channel left join channels_by_object cbo on cbo.chid=ch.id where cbo.oid=%1 and ch.type=1 and d.dt >= '%2' and d.dt < '%3' and d.itv_length=%4 group by d.date, div(d.itv, %5 / d.itv_length) , ch.index, d.itv_length order by d.date, itv, ch.index;").arg(
									   QString::number(desc->id), 
									   ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), 
									   ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
									   ui->cmbItvLength->itemData(ui->cmbItvLength->currentIndex()).toString(),
									   ui->cmbGroupType->itemData(ui->cmbGroupType->currentIndex()).toString(),
									   QString::number(ui->cmbValueRound->itemData(ui->cmbValueRound->currentIndex()).toDouble(), 'f', 3)));
			break;

		case Factory:
			r = m_connection->exec(QString("select d.date, div(d.itv, %5 / d.itv_length) itv, ch.index as channel, %5 itv_length, sum(d.value * %6) as value from data d left join channel ch on ch.id=d.channel left join channels_by_object cbo on cbo.chid=ch.id where cbo.ftid=%1 and d.dt >= '%2' and d.dt < '%3' and d.itv_length=%4 group by d.date, div(d.itv, %5 / d.itv_length) , ch.index, d.itv_length order by d.date, itv, ch.index;").arg(
									   QString::number(desc->id), 
									   ui->dteBegin->dateTime().toString("yyyy-MM-dd hh:mm:ss"), 
									   ui->dteEnd->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
									   ui->cmbItvLength->itemData(ui->cmbItvLength->currentIndex()).toString(),
									   ui->cmbGroupType->itemData(ui->cmbGroupType->currentIndex()).toString(),
									   QString::number(ui->cmbValueRound->itemData(ui->cmbValueRound->currentIndex()).toDouble(), 'f', 3)));
			break;
	}
	double max_val = 0;
	if (r)
	{
		if (!r->isValid())
		{
			QMessageBox::critical(m_window, REPORT_NAME, tr("Ошибка запроса к БД!\n").append(
									  m_connection->getError()));
		}
		else
		{
			QList<QPen> pen;
			pen.append(QPen(QColor(255, 0, 0)));
			pen.append(QPen(QColor(0, 188, 0)));
			pen.append(QPen(QColor(0, 0, 188)));
			pen.append(QPen(QColor(188, 188, 0)));
	
			QStringList hdr;
			hdr.append(tr("Дата"));
			ui->twData->setColumnCount(1);
			ui->twData->setHorizontalHeaderLabels(hdr);
			ui->twData->setRowCount(0);
			int itv = -1;
			
			QList<TableWidgetExtreme *> extr_max;
			QList<TableWidgetExtreme *> extr_min;
			TableWidgetExtreme * max;
			TableWidgetExtreme * min;
			while (r->notEoF())
			{
				int clmn = 0;
				for (int i = 1; i < ui->twData->columnCount(); i++)
				{
					if (ui->twData->horizontalHeaderItem(i)->data(Qt::UserRole) == r->getValue("channel").toInt())
					{
						clmn = i;
						max = extr_max[i - 1];
						min = extr_min[i - 1];
						break;
					}
				}
				if (clmn == 0)
				{
					max = new TableWidgetExtreme();
					max->value = -999999;
					max->item = 0;
					extr_max.append(max);
					
					min = new TableWidgetExtreme();
					min->value = 999999;
					min->item = 0;
					extr_min.append(min);
					
					clmn = ui->twData->columnCount();
					ui->twData->setColumnCount(clmn + 1);
					hdr.append(r->getValue("channel"));
					ui->twData->setHorizontalHeaderLabels(hdr);
					ui->twData->horizontalHeaderItem(clmn)->setData(Qt::UserRole, QVariant::fromValue(r->getValue("channel").toInt()));
					QColor col = pen.at(clmn - 1).color();
					col.setAlpha(50);
					ui->twData->horizontalHeaderItem(clmn)->setBackgroundColor(col);
				}
	
				if (itv != r->getValue("itv").toInt())
				{
					ui->twData->setRowCount(ui->twData->rowCount() + 1);
					
					QTableWidgetItem * twi = new QTableWidgetItem();
					twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
					QDateTime dt = QDateTime::fromString(r->getValue("date"), "yyyy-MM-dd");
					dt = dt.addSecs(r->getValue("itv").toInt() * r->getValue("itv_length").toInt() * 60);
					twi->setText(dt.toString("yyyy-MM-dd hh:mm"));
					ui->twData->setItem(ui->twData->rowCount() - 1, 0, twi);
					itv = r->getValue("itv").toInt();
				}
				QTableWidgetItem * twi = new QTableWidgetItem();
				twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				if (ui->txtAccuracy->text().toInt() >= 0)
					twi->setText(QString::number(myround(r->getValue("value").toDouble(), ui->txtAccuracy->text().toInt()), 'f', ui->txtAccuracy->text().toInt()));
				else
					twi->setText(QString::number(r->getValue("value").toDouble(), 'f'));
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
				if (r->getValue("value").toDouble() > max_val) max_val = r->getValue("value").toDouble();
				ui->twData->setItem(ui->twData->rowCount() - 1, clmn, twi);
				
				r->moveNext();
				
			}
			r->close();
			
			for (int i = 0; i < extr_max.count(); i++)
			{
				max = extr_max.at(i);
				if (max->item != 0)
				{
					max->item->setBackground(QBrush(QColor(255, 200, 200)));
				}
				min = extr_min.at(i);
				if (min->item != 0)
				{
					min->item->setBackground(QBrush(QColor(200, 200, 255)));
				}
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
				for (int row = 1; row < ui->twData->rowCount(); row++)
				{
					scene->addLine((row - 1) * dx + x0, y1 - ui->twData->item(row - 1, c)->text().toDouble() * dy, row * dx + x0, y1 - ui->twData->item(row, c)->text().toDouble() * dy, pen.at(c - 1));
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
					twi->setText(QString::number(summ / rows));
					twi->setFont(font);
					ui->twData->setItem(rows, c, twi);
	
					twi = new QTableWidgetItem();
					twi->setText(QString::number(summ));
					twi->setFont(font);
					ui->twData->setItem(rows + 1, c, twi);
				}
			}
		}
	}
	ui->twData->show();
}

void OperView::dateBeginChanged(QDateTime dt)
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

void OperView::dateEndChanged(QDateTime dt)
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

void OperView::intervalTypeChanged(int index)
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

void OperView::updateTree(QTreeWidgetItem *parent, int column)
{
	parent->takeChildren();
	TreeElementDesc * desc = (TreeElementDesc *)parent->data(column, Qt::UserRole).toInt();
	PgreSqlResult * r = 0;
	QIcon icon;
	TreeElementType type;
	switch (desc->type)
	{
		case Factory:
			r = m_connection->exec(QString("select id, name from object where factory=%1 order by name;").arg(QString::number(desc->id)));
			icon = QIcon(":/operview/images/object.png");
			type = Object;
			break;
			
		case Object:
			r = m_connection->exec(QString("select id, name from feeder where object=%1 order by name;").arg(QString::number(desc->id)));
			icon = QIcon(":/operview/images/feeder.png");
			type = Feeder;
			break;
			
		case Feeder:
			r = m_connection->exec(QString("select id, c_number as name from counter where feeder=%1 order by c_number;").arg(QString::number(desc->id)));
			icon = QIcon(":/operview/images/counter.png");
			type = Counter;
			break;
			
		case Counter:
			r = m_connection->exec(QString("select id, name from channel where counter=%1 and type=1 order by name;").arg(QString::number(desc->id)));
			icon = QIcon(":/operview/images/channel.png");
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

void OperView::dtBeginContexMenuReq(QPoint position)
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

void OperView::dtEndContexMenuReq(QPoint position)
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

void OperView::setdtBeginDayBegin()
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

void OperView::setdtEndDayBegin()
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

void OperView::exportToExcel()
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

void OperView::autoUpdate()
{
	ui->txtInterval->setVisible(ui->cmbAutoRefresh->isChecked());
	ui->lblInterval->setVisible(ui->cmbAutoRefresh->isChecked());
	
	if (ui->cmbAutoRefresh->isChecked())
	{
		bool ok;
		long itv = ui->txtInterval->text().toInt(&ok);
		
		if (!ok)
		{
			QMessageBox::critical(m_window, tr("Ошибка"), tr("Неверный формат числа! Период обновления установлен на %1 сек.").arg(
									  QString::number(TIMER_DEFAULT_PERIOD)));
			itv = TIMER_DEFAULT_PERIOD;
		}
		m_timer->start(itv * 1000);
	}
	else
		m_timer->stop();
}

void OperView::periodChanged()
{
	bool ok;
	long itv = ui->txtInterval->text().toInt(&ok);
	
	if (!ok)
	{
		QMessageBox::critical(m_window, tr("Ошибка"), tr("Неверный формат числа!"));
		return;
	}
	
	if (ui->cmbAutoRefresh->isChecked())
		m_timer->start(itv * 1000);
}

void OperView::createUi()
{
	ui = new Ui::OperViewWidget();
	ui->setupUi(m_window);
	
	if (m_window->layout()) delete m_window->layout();
    m_window->setLayout(ui->mainLayout);
	
	ui->dteEnd->setDateTime(QDateTime::currentDateTime());
	ui->dteBegin->setDateTime(QDateTime::currentDateTime().addDays(-1));
	
	connect(ui->dteBegin, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(dateBeginChanged(QDateTime)));
	connect(ui->dteEnd, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(dateEndChanged(QDateTime)));
	connect(ui->dteBegin, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(dtBeginContexMenuReq(QPoint)));
	connect(ui->dteEnd, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(dtEndContexMenuReq(QPoint)));
	connect(ui->cmbItvType, SIGNAL(currentIndexChanged(int)), this, SLOT(intervalTypeChanged(int)));
	connect(ui->twObjects, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(updateTree(QTreeWidgetItem*,int)));
	connect(ui->cmdRefresh, SIGNAL(clicked()), this, SLOT(loadData()));
	connect(ui->cmbAutoRefresh, SIGNAL(clicked()), this, SLOT(autoUpdate()));
	connect(ui->txtInterval, SIGNAL(editingFinished()), this, SLOT(periodChanged()));
	connect(ui->cmdExcel, SIGNAL(clicked()), this, SLOT(exportToExcel()));
	
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

	ui->dteEnd->setDateTime(QDateTime::currentDateTime());
	ui->dteBegin->setDateTime(QDateTime::currentDateTime().addDays(-1));

	ui->cmbValueRound->addItem(tr("кВт*ч"), QVariant::fromValue(1));
	ui->cmbValueRound->addItem(tr("МВт*ч"), QVariant::fromValue(0.001));

	ui->cmbItvLength->addItem(tr("1 минута"), QVariant::fromValue(QString("1")));
	ui->cmbItvLength->addItem(tr("3 минуты"), QVariant::fromValue(QString("3")));
	ui->cmbItvLength->addItem(tr("10 минут"), QVariant::fromValue(QString("10")));
	ui->cmbItvLength->addItem(tr("30 минут"), QVariant::fromValue(QString("30")));

	ui->cmbGroupType->addItem(tr("30 минут"), QVariant::fromValue(QString("30")));
	ui->cmbGroupType->addItem(tr("60 минут"), QVariant::fromValue(QString("60")));
	
	ui->txtInterval->setText(QString::number(TIMER_DEFAULT_PERIOD));
	ui->txtInterval->setValidator(new QRegExpValidator(QRegExp("^\\d{1,3}$"), ui->txtInterval));
	ui->txtInterval->setVisible(false);
	ui->lblInterval->setVisible(false);
}

Q_EXPORT_PLUGIN(OperView);
