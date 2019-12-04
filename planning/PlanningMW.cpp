#include "PlanningMW.h"
#include "ui_PlanningMW.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

struct CellInfo
{
	bool hadValue;
	bool hadChanged;
};

//#define INPUT_MASK_VALUE	"\\d+[\\.,]{0,1}\\d+"
#define INPUT_MASK_VALUE	"(([0-9]{1,11}[\\.|,][0-9]{0,11})|([0-9]{0,11}[\\.|,][0-9]{1,11})|([0-9]{1,11})){1,1}"

PlanningMW::PlanningMW(QSettings *settings, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::PlanningMW)
{
	ui->setupUi(this);
	
	if (ui->centralWidget->layout()) delete ui->centralWidget->layout();
	ui->centralWidget->setLayout(ui->mainLayout);
	
	setWindowTitle(MAIN_TITLE);
	
	_settings = settings;
	_connection = 0;
	
	connect(ui->twObjects, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
			this, SLOT(dpgSelected(QTreeWidgetItem*,int)));
	
	connect(ui->txtDate, SIGNAL(dateChanged(QDateTime)),
			this, SLOT(dateChanged(QDateTime)));
	
	ui->txtDate->setDate(QDate::currentDate());
	ui->txtDate->setFormat("yyyy-MM-dd");
	
	connect(ui->actQuit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui->cmdSave, SIGNAL(clicked()), this, SLOT(saveChanges()));
	connect(ui->cmdExcel, SIGNAL(clicked()), this, SLOT(exportToExcel()));
	
	ui->cmbMeasuringLength->addItem(tr("кВт*ч"), 1);
	ui->cmbMeasuringLength->addItem(tr("МВТ*ч"), 1000);
	
	connect(ui->cmbMeasuringLength, SIGNAL(currentIndexChanged(int)),
			this, SLOT(measuringLengthChange(int)));
	
	setWindowState(Qt::WindowMaximized);
}

PlanningMW::~PlanningMW()
{
	delete ui;
}

void PlanningMW::loginFormClosed()
{
	if (!_connection)
		qApp->quit();
}

void PlanningMW::databaseConnected(PgreSqlDrv *connection, int uid)
{
	_connection = connection;
	_uid = uid;
	updateTree();
	updateTable();
	
	if (ui->twObjects->topLevelItemCount() > 0)
	{
		ui->twObjects->topLevelItem(0)->setSelected(true);
		dpgSelected(ui->twObjects->topLevelItem(0), 0);
	}
}

void PlanningMW::updateTree()
{
	PgreSqlResult * r = _connection->exec(QString("select dpg.id, dpg.name from deliverypointgroup dpg left join user_access ua on ua.dpg=dpg.id where ua.userid=%1;").arg(
											  QString::number(_uid)));
	if (r->isValid())
	{
		while (r->notEoF())
		{
			QTreeWidgetItem * twi = new QTreeWidgetItem();
			twi->setText(0, r->getValue(1));
			twi->setData(0, Qt::UserRole, r->getValue(0));
			twi->setIcon(0, QIcon(":/planning/images/gtp.png"));
			ui->twObjects->addTopLevelItem(twi);
			r->moveNext();
		}
	}
	else
		QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка запроса к БД!\n").append(
								  _connection->getError()));
}

void PlanningMW::dpgSelected(QTreeWidgetItem *item, int column)
{
	disconnect(ui->twData, SIGNAL(itemChanged(QTableWidgetItem*)),
			this, SLOT(checkInputValue(QTableWidgetItem*)));
	
	int id = item->data(0, Qt::UserRole).toInt();
	
	PgreSqlResult * r = _connection->exec(QString("select * from plan where date='%1' and dpg=%2 order by itv;").arg(
											  _date.toString("yyyy-MM-dd"),
											  QString::number(id)));
	if (!r->isValid())
	{
		QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка запроса к БД!\n").append(
								  _connection->getError()));
		return;
	}
	else
	{
		updateTable();
		
		int ml = ui->cmbMeasuringLength->itemData(ui->cmbMeasuringLength->currentIndex()).toInt();
		
		while (r->notEoF())
		{
			ui->twData->item(r->getValue("itv").toInt(), 1)->setText(QString::number(r->getValue("value").toDouble() / ml));
			CellInfo * ci = (CellInfo *)ui->twData->item(r->getValue("itv").toInt(), 1)->data(Qt::UserRole).toInt();
			ci->hadValue = true;
			ui->twData->item(r->getValue("itv").toInt(), 1)->setData(Qt::UserRole, QVariant::fromValue((int)ci));
			r->moveNext();
		}
	}
	connect(ui->twData, SIGNAL(itemChanged(QTableWidgetItem*)),
			this, SLOT(checkInputValue(QTableWidgetItem*)));
}

void PlanningMW::updateTable()
{
	ui->twData->raise();
	ui->twData->setColumnCount(2);
	ui->twData->setRowCount(24);
	ui->twData->setHorizontalHeaderLabels(QStringList() << tr("Дата/Время") << tr("Значение (кВт*ч)"));

	for (int i = 0; i < 24; i++)
	{
		QTableWidgetItem * twi = new QTableWidgetItem();
		QDateTime dt;
		dt.setDate(ui->txtDate->date());
		dt.setTime(QTime::fromString("00:00:00", "hh:mm:ss").addSecs(i * 3600));
		twi->setText(dt.toString("yyyy-MM-dd hh:mm"));
		twi->setFlags(Qt::ItemIsEnabled);
		ui->twData->setItem(i, 0, twi);
		
		twi = new QTableWidgetItem();
		CellInfo * ci = new CellInfo();
		ci->hadChanged = false;
		ci->hadValue = false;
		twi->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
		twi->setData(Qt::UserRole, QVariant::fromValue((int)ci));
		ui->twData->setItem(i, 1, twi);
	}
	ui->cmdSave->setEnabled(false);
}

void PlanningMW::checkInputValue(QTableWidgetItem *item)
{
	if ((item->text() == "") || (item->column() == 0))
		item->setBackgroundColor(QColor(255, 255, 255));
	else
	{
		CellInfo * ci = (CellInfo *)item->data(Qt::UserRole).toInt();
		ci->hadChanged = true;
		item->setData(Qt::UserRole, QVariant::fromValue((int)ci));
		ui->cmdSave->setEnabled(true);
		
		QRegExp re(INPUT_MASK_VALUE);
		if (!re.exactMatch(item->text()))
			item->setBackgroundColor(QColor(255, 200, 200));
		else
			item->setBackgroundColor(QColor(255, 255, 255));
	}
}

void PlanningMW::saveChanges()
{
	if ((ui->twObjects->selectedItems().count() == 0) ||
			(ui->twData->rowCount() == 0))
		return;
	
	QRegExp re(INPUT_MASK_VALUE);

	for (int i = 0; i < 24; i++)
	{
		if (!re.exactMatch(ui->twData->item(i, 1)->text()))
		{
			QMessageBox::critical(this, tr("Ошибка"), tr("Неверный формат данных за %1!").arg(
									  ui->twData->item(i, 0)->text()));
			return;
		}
	}
	
	int ml = ui->cmbMeasuringLength->itemData(ui->cmbMeasuringLength->currentIndex()).toInt();

	for (int i = 0; i < 24; i++)
	{
		CellInfo * ci = (CellInfo *)ui->twData->item(i, 1)->data(Qt::UserRole).toInt();
		if (ci->hadChanged)
		{
			if (!ui->twData->item(i, 1)->data(Qt::UserRole).toBool())
			{
				if (!_connection->exec(QString("insert into plan (date, itv, dpg, value) VALUES ('%1', %2, %3, %4);").arg(
										   _date.toString("yyyy-MM-dd"),
										   QString::number(i),
										   ui->twObjects->selectedItems().at(0)->data(0, Qt::UserRole).toString(),
										   QString::number(ui->twData->item(i, 1)->text().toInt() * ml)))->isValid())
				{
					QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка запроса к БД!\n").append(
											  _connection->getError()));
					return;
				}
			}
			else
			{
				if (!_connection->exec(QString("update plan set value=%4 where date='%1' and itv=%2 and dpg=%3;").arg(
										   _date.toString("yyyy-MM-dd"),
										   QString::number(i),
										   ui->twObjects->selectedItems().at(0)->data(0, Qt::UserRole).toString(),
										   QString::number(ui->twData->item(i, 1)->text().toInt() * ml)))->isValid())
				{
					QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка запроса к БД!\n").append(
											  _connection->getError()));
					return;
				}
			}
		}
	}
	dpgSelected(ui->twObjects->selectedItems().at(0), 0);
}

void PlanningMW::dateChanged(QDateTime date)
{
	if (ui->twObjects->selectedItems().count() != 0)
	{
		if (ui->twData->rowCount() != 0)
		{
			for (int i = 0; i < 24; i++)
			{
				CellInfo * ci = (CellInfo *)ui->twData->item(i, 1)->data(Qt::UserRole).toInt();
				if (ci->hadChanged)
				{
					if (QMessageBox::question(this, 
											  tr("Сохранить изменения?"), 
											  tr("В случае смены даты все внесенные изменения будут потеряны!\nХотите изменить текущую дату?"),
											  QMessageBox::Yes,
											  QMessageBox::No) != QMessageBox::Yes)
					{
						return;
					}
					else
						break;
				}
				
			}
		}
	}
	_date = date.date();
	if (ui->twObjects->selectedItems().count() != 0) 
		dpgSelected(ui->twObjects->selectedItems().at(0), 0);
}

void PlanningMW::exportToExcel()
{
	if (ui->twData->rowCount() == 0)
	{
		if (QMessageBox::question(
					this,
					tr("Сохранить как..."),
					tr("Данных для выгрузки не получено.\r\nВы уверены, что хотите продолжить?"), QMessageBox::Yes, QMessageBox::No) != QMessageBox::Yes)
			return;
	}

	QString path = QFileDialog::getSaveFileName(
				this, 
				tr("Сохранить как..."), 
				"c:/", 
				tr("Файл Microsoft Excel (*.csv)"));
	
	if (path == "") 
		return;
	
	
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::critical(
					this, 
					tr("Ошибка"),
					tr("Неверное имя файла или директория назначения, либо файл закрыт для изменения!"));
		return;
	}
	
	file.write(MAIN_TITLE.toAscii());
	//file.write(tr(" вер. ").append(REPORT_VER).toAscii());
	file.write("\r\n");
	file.write(tr("Объект;").append(tr(ui->twObjects->currentItem()->text(0).toAscii().constData())).append("\r\n").toAscii());
	file.write(tr("Дата;").append(ui->txtDate->date().toString("yyyy-MM-dd")).append("\r\n").toAscii());
	
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

void PlanningMW::measuringLengthChange(int index)
{
	if (QMessageBox::question(this, 
							  tr("Изменение единиц измерения"), 
							  tr("Пересчитать данные с учетом новой единицы измерения?"),
							  QMessageBox::Yes,
							  QMessageBox::No) != QMessageBox::Yes)
	{
		return;
	}
	else
		dpgSelected(ui->twObjects->selectedItems().at(0), 0);
}
