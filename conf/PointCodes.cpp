#include "PointCodes.h"
#include "ui_PointCodes.h"
#include <QMessageBox>

PointCodes::PointCodes(QWidget *parent, PointType type, int id, PgreSqlDrv *connection) :
	QDialog(parent),
	ui(new Ui::PointCodes)
{
	ui->setupUi(this);
	
	_parent = parent;
	_pointid = id;
	_type = type;
	_conn = connection;

	QString sql = QString("select m.id, m.name from model m order by m.name");
	PgreSqlResult * r;
	if (!(r = _conn->exec(sql))->isValid())
	{
		qDebug("PointCodes::PointCodes() - SQL ERROR: %s\n%s", 
		       _conn->getError().toAscii().constData(),
		       sql.toAscii().constData());
		QMessageBox::critical(this, tr("Коды точки"), tr("Ошибка при запорсе к БД!"));
	}
	else
	{
		while (r->notEoF())
		{
			ui->cmbModel->addItem(r->getValue(1), QVariant::fromValue(r->getValue(0)));
			r->moveNext();
		}
	}
	
	if (layout()) delete layout();
	setLayout(ui->mainLayout);
	
	updateList();
}

PointCodes::~PointCodes()
{
	delete ui;
}

void PointCodes::onEditClick()
{
	if (ui->txtCode->text() == "")
	{
		QMessageBox::warning(this, tr("Коды точки"), tr("Введите код!"));
		return;
	}
	QString sql = QString("update point_codes set code='%4' where point=%1 and model=%2 and pointType=%3;").arg(
					  QString::number(_pointid),
					  ui->cmbModel->itemData(ui->cmbModel->currentIndex()).toString(),
					  QString::number((int)_type),
					  ui->txtCode->text());
	PgreSqlResult * r;
	if (!(r = _conn->exec(sql))->isValid())
	{
		qDebug("PointCodes::updateList() - SQL ERROR: %s\n%s",
			   _conn->getError().toAscii().constData(),
			   sql.toAscii().constData());
		QMessageBox::critical(this, tr("Коды точки"), tr("Ошибка при запорсе к БД!"));
	}
	else
	{
		updateList();
	}
}

void PointCodes::onAddClick()
{
	if (ui->txtCode->text() == "")
	{
		QMessageBox::warning(this, tr("Коды точки"), tr("Введите код!"));
		return;
	}
	QString sql = QString("insert into point_codes (point, model, pointType, code) values (%1, %2, %3, '%4');").arg(
					  QString::number(_pointid),
					  ui->cmbModel->itemData(ui->cmbModel->currentIndex()).toString(), 
					  QString::number((int)_type),
					  ui->txtCode->text());
	PgreSqlResult * r;
	if (!(r = _conn->exec(sql))->isValid())
	{
		qDebug("PointCodes::updateList() - SQL ERROR: %s\n%s", 
		       _conn->getError().toAscii().constData(),
		       sql.toAscii().constData());
		QMessageBox::critical(this, tr("Коды точки"), tr("Ошибка при запорсе к БД!"));
	}
	else
	{
		updateList();
	}
}

void PointCodes::onRemoveClick()
{
	QString sql = QString("delete from point_codes where point=%1 and model=%2 and pointType=%3;").arg(
					  QString::number(_pointid),
					  ui->cmbModel->itemData(ui->cmbModel->currentIndex()).toString(),
					  QString::number((int)_type),
					  ui->txtCode->text());
	PgreSqlResult * r;
	if (!(r = _conn->exec(sql))->isValid())
	{
		qDebug("PointCodes::onRemoveClick() - SQL ERROR: %s\n%s",
			   _conn->getError().toAscii().constData(),
			   sql.toAscii().constData());
		QMessageBox::critical(this, tr("Коды точки"), tr("Ошибка при запорсе к БД!"));
	}
	else
	{
		updateList();
	}
}

void PointCodes::onElementSelect(QTableWidgetItem *item)
{
	ui->txtCode->setText(ui->twCodes->item(item->row(), 1)->text());
	for (int i = 0; i < ui->cmbModel->count(); i++)
	{
		if (ui->cmbModel->itemData(i).toInt() == 
				ui->twCodes->item(item->row(), 0)->data(Qt::UserRole).toInt())
		{
			ui->cmbModel->setCurrentIndex(i);
			break;
		}
	}
}

void PointCodes::updateList()
{
	QString sql = QString("select m.id, m.name, pc.code from point_codes pc left join model m on m.id=pc.model where pc.point=%1 and pc.pointType=%2 order by m.id").arg(QString::number(_pointid), QString::number((int)_type));
	PgreSqlResult * r;
	if (!(r = _conn->exec(sql))->isValid())
	{
		qDebug("PointCodes::updateList() - SQL ERROR: %s\n%s", 
		       _conn->getError().toAscii().constData(),
		       sql.toAscii().constData());
		QMessageBox::critical(this, tr("Коды точки"), tr("Ошибка при запорсе к БД!"));
	}
	else
	{
		ui->twCodes->clear();
		ui->twCodes->raise();
		
		ui->twCodes->setColumnCount(2);
		QStringList hdr;
		hdr.append(tr("Макет"));
		hdr.append(tr("Код"));
		ui->twCodes->setHorizontalHeaderLabels(hdr);
		ui->twCodes->setRowCount(r->numRows());
		//ui->twCodes->setColumnWidth(0, ui->twCodes->geometry().width() * 0.3);
		//ui->twCodes->setColumnWidth(1, ui->twCodes->geometry().width() * 0.7);
		//qDebug("%d", ui->twCodes->frameGeometry().);
		while (r->notEoF())
		{
			QTableWidgetItem * twi = new QTableWidgetItem();
			twi->setText(r->getValue(1));
			twi->setData(Qt::UserRole, QVariant::fromValue(r->getValue(0)));
			ui->twCodes->setItem(r->absolutePos(), 0, twi);
			twi = new QTableWidgetItem();
			twi->setText(r->getValue(2));
			ui->twCodes->setItem(r->absolutePos(), 1, twi);
			r->moveNext();
		}
	}
}
