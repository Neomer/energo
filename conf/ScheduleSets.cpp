#include "ScheduleSets.h"
#include "ui_ScheduleSets.h"
#include <QGroupBox>
#include <QMessageBox>
#include "../includes/struct_desc.h"
#include "ScheduleSelectElements.h"

ScheduleSets::ScheduleSets(QWidget *parent, 
						   PgreSqlDrv *connection, int id, 
						   QTreeWidgetItem *item) :
    QWidget(parent),
    ui(new Ui::ScheduleSets)
{
    ui->setupUi(this);
	
	_item = item;
	_id = id;
	_conn = connection;
	_parent = parent;
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);

	//updateForm();
	
	QGroupBox * gb = (QGroupBox *)parent;

	ui->cmbPeriod->addItem(tr("Минута"), 1);
	ui->cmbPeriod->addItem(tr("Час"), 60);
	ui->cmbPeriod->addItem(tr("День"), 1440);
	
	ui->cmbShift->addItem(tr("Секунда"), 1);
	ui->cmbShift->addItem(tr("Минута"), 60);
	ui->cmbShift->addItem(tr("Час"), 3600);
	ui->cmbShift->addItem(tr("День"), 86400);
	
	ui->lstObj->clear();
	
	QStringList hdr;
	hdr.append(tr("Предприятие"));
	hdr.append(tr("Подстанция"));
	hdr.append(tr("Приоритет"));
	
	ui->lstObj->setColumnCount(3);
	ui->lstObj->setHorizontalHeaderLabels(hdr);

	updateForm();
	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = (QWidget *)this->children().at(i);
		w->show();
	}
	
	connect(ui->cmbPeriod, SIGNAL(currentIndexChanged(int)), this, SLOT(periodFactorChanged(int)));
	connect(ui->cmbShift, SIGNAL(currentIndexChanged(int)), this, SLOT(shiftFactorChanged(int)));
}

ScheduleSets::~ScheduleSets()
{
    delete ui;
}

void ScheduleSets::periodFactorChanged(int index)
{
	ui->txtPeriod->setText(QString::number((double)_period / ui->cmbPeriod->itemData(index).toInt()));
}

void ScheduleSets::shiftFactorChanged(int index)
{
	ui->txtShift->setText(QString::number((double)_shift / ui->cmbShift->itemData(index).toInt()));
}

void ScheduleSets::periodChanged(QString value)
{
	_period = value.toDouble() * ui->cmbPeriod->itemData(ui->cmbPeriod->currentIndex()).toInt();
}

void ScheduleSets::shiftChanged(QString value)
{
	_shift = value.toDouble() * ui->cmbShift->itemData(ui->cmbShift->currentIndex()).toInt();
}

void ScheduleSets::dropChanges()
{
	updateForm();
}

void ScheduleSets::saveChanges()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		if (!_conn->isConnected())
		{
			qDebug("ScheduleSets::saveChanges() - Database connection is lost!");
			return;
		}
		
		QString sql;
		PgreSqlResult * r;
		
		if (_id == -1)
		{
			sql = "insert into schedule (name, periodicity, shift, temp) values ('%1', %2, %3, FALSE) returning id;";
			sql = sql.arg(ui->txtName->text(), 
							QString::number(_period), 
							QString::number(_shift));
		}
		else
		{
			sql = "update schedule set name='%1', periodicity=%2, shift=%3 where id=%4;";
			sql = sql.arg(ui->txtName->text(), 
							QString::number(_period), 
							QString::number(_shift), 
							QString::number(_id));
		}
		if (!(r = _conn->exec(sql))->isValid())
		{
			qDebug("ScheduleSets::saveChanges() - SQL ERROR: %s\n%s", 
				   _conn->getError().toAscii().constData(),
				   sql.toAscii().constData());
		}
		else
		{
			_item->setText(0, ui->txtName->text());
			if (_id == -1)
			{
				TVItemDesc d = _item->data(0, Qt::UserRole).value<TVItemDesc>();
				Feeder * f = (Feeder *)d.link;
				_id = f->ID = r->getValue(0).toInt();
				f->name = ui->txtName->text();
				_item->setData(0, Qt::UserRole, QVariant::fromValue(d));
				_item->setText(0, ui->txtName->text());
			}
			emit onUpdate(_item);
		}
		updateForm();
	}
}

void ScheduleSets::appendObjects()
{
	ScheduleSelectElements * sse = new ScheduleSelectElements(_parent, _id, _conn);
	connect(sse, SIGNAL(onUpdate()), this, SLOT(updateObjectList()));
	sse->show();
}

void ScheduleSets::removeObjects()
{
	QList<int> id_proc;
	
	for (int r = 0; r < ui->lstObj->selectedItems().count(); r++)
	{
		int id = ui->lstObj->selectedItems().at(r)->data(Qt::UserRole).toInt();
		if (!id_proc.contains(id))
		{
			id_proc.append(id);
			QString sql = QString("delete from interview where schedule=%1 and object=%2;").arg(
							  QString::number(_id), 
							  QString::number(id));
			PgreSqlResult * r = _conn->exec(sql);
			if (!r->isValid())
			{
				qDebug("ScheduleSets::removeObjects() - SQL ERROR:\n%s",
					this->_conn->getError().toAscii().constData());
			}
		}
	}
	updateObjectList();
}

void ScheduleSets::updateObjectList()
{
	ui->lstObj->clear();
	PgreSqlResult * r = _conn->exec(QString("select o.id, i.priority, o.name as object, f.name as factory from schedule s left join interview i on s.id=i.schedule left join object o on i.object=o.id left join factory f on o.factory=f.id where s.id=%1 order by i.priority, f.name, o.name;").arg(
										QString::number(_id)));
	
	if (!r->isValid())
	{
		qDebug("ScheduleSets::updateObjectList() - SQL ERROR: %s", 
		       _conn->getError().toAscii().constData());
		return;
	}
	ui->lstObj->setRowCount(r->numRows());
	while (r->notEoF())
	{
		QTableWidgetItem * twi = new QTableWidgetItem();
		twi->setText(r->getValue("factory"));
		twi->setData(Qt::UserRole, QVariant::fromValue(r->getValue(0)));
		ui->lstObj->setItem(r->absolutePos(), 0, twi);
		twi = new QTableWidgetItem();
		twi->setText(r->getValue("object"));
		twi->setData(Qt::UserRole, QVariant::fromValue(r->getValue(0)));
		ui->lstObj->setItem(r->absolutePos(), 1, twi);
		twi = new QTableWidgetItem();
		twi->setText(r->getValue("priority"));
		twi->setData(Qt::UserRole, QVariant::fromValue(r->getValue(0)));
		ui->lstObj->setItem(r->absolutePos(), 2, twi);
		r->moveNext();
	}
}

void ScheduleSets::onRemove()
{
	if (_id == -1)
		return;
	
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Вы уверены, что хотите удалить задание: ").append(this->_item->text(0)), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql = "delete from schedule where id=%1;";
		if (_conn->exec(sql.arg(QString::number(_id)))->isValid())
		{
			ui->txtName->setEnabled(false);
			ui->cmdRemoveSchedule->setEnabled(false);
			ui->cmdAdd->setEnabled(false);
			ui->cmdSave->setEnabled(false);
			ui->cmdRemove->setEnabled(false);
			ui->lstObj->setEnabled(false);
			ui->txtPeriod->setEnabled(false);
			ui->txtShift->setEnabled(false);
			ui->cmbPeriod->setEnabled(false);
			ui->cmbShift->setEnabled(false);
			ui->txtEndTime->setEnabled(false);
			ui->txtStartTime->setEnabled(false);
			_id = -1;
			emit onRemove(_item);
			delete _item;
		}
		else
		{
			qDebug("ScheduleSets::onRemove() - SQL ERROR: %s\n%s",
				   _conn->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить задание. Подробнее об ошибке см. в логах."));
			return;
		}
	}
}

void ScheduleSets::updateForm()
{
	if (_id == -1)
	{
		ui->cmdAdd->setEnabled(false);
		ui->cmdRemove->setEnabled(false);
		ui->cmdRemoveSchedule->setEnabled(false);
	}
	else
	{
		ui->cmdAdd->setEnabled(true);
		ui->cmdRemove->setEnabled(true);
		ui->cmdRemoveSchedule->setEnabled(true);

		PgreSqlResult * r = _conn->exec(QString("select o.id, s.*, i.priority, o.name as object, f.name as factory from schedule s left join interview i on s.id=i.schedule left join object o on i.object=o.id left join factory f on o.factory=f.id where s.id=%1;").arg(
											QString::number(_id)));
		
		if (!r->isValid())
		{
			qDebug("ScheduleSets::ScheduleSets() - SQL ERROR: %s", 
				   _conn->getError().toAscii().constData());
			return;
		}
		
		if (r->hasRows())
		{
			ui->txtName->setText(r->getValue("name"));
			int tmp = _period = r->getValue("periodicity").toInt();
			if (tmp >= 1440)
			{
				ui->cmbPeriod->setCurrentIndex(2);
				ui->txtPeriod->setText(QString::number(tmp / 1440));
			}
			else if (tmp >= 60)
			{
				ui->cmbPeriod->setCurrentIndex(1);
				ui->txtPeriod->setText(QString::number(tmp / 60));
			}
			else
			{
				ui->cmbPeriod->setCurrentIndex(0);
				ui->txtPeriod->setText(QString::number(tmp));
			}
			
			tmp = _shift = r->getValue("shift").toInt();
			if (tmp >= 86400)
			{
				ui->cmbShift->setCurrentIndex(3);
				ui->txtShift->setText(QString::number((double)tmp / 86400));
			}
			else if (tmp >= 3600)
			{
				ui->cmbShift->setCurrentIndex(2);
				ui->txtShift->setText(QString::number((double)tmp / 3600));
			}
			else if (tmp >= 60)
			{
				ui->cmbShift->setCurrentIndex(1);
				ui->txtShift->setText(QString::number((double)tmp / 60));
			} 
			else
			{
				ui->cmbShift->setCurrentIndex(0);
				ui->txtShift->setText(QString::number(tmp));
			}
			ui->txtStartTime->setText(r->getValue("start_time"));
			ui->txtEndTime->setText(r->getValue("end_time"));
			ui->lstObj->setRowCount(r->numRows());
			while (r->notEoF())
			{
				QTableWidgetItem * twi = new QTableWidgetItem();
				twi->setText(r->getValue("factory"));
				twi->setData(Qt::UserRole, QVariant::fromValue(r->getValue(0)));
				ui->lstObj->setItem(r->absolutePos(), 0, twi);
				twi = new QTableWidgetItem();
				twi->setText(r->getValue("object"));
				twi->setData(Qt::UserRole, QVariant::fromValue(r->getValue(0)));
				ui->lstObj->setItem(r->absolutePos(), 1, twi);
				twi = new QTableWidgetItem();
				twi->setText(r->getValue("priority"));
				twi->setData(Qt::UserRole, QVariant::fromValue(r->getValue(0)));
				ui->lstObj->setItem(r->absolutePos(), 2, twi);
				r->moveNext();
			}
		}
	}
}

