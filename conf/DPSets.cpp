#include "DPSets.h"
#include "ui_DPSets.h"
#include <QMessageBox>
#include <QGroupBox>
#include "../includes/struct_desc.h"
#include "PointCodes.h"


DPSets::DPSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item) :
	QWidget(parent),
	ui(new Ui::DPSets)
{
	ui->setupUi(this);
	
	QGroupBox * gb = (QGroupBox *)parent;

	m_connection = connection;
	m_id = id;
	m_node = item;

    ui->cmdAddMeasuringPoint->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	ui->cmdSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    
	gb->setTitle(tr("Настройки точки поставки:"));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);
	
	PgreSqlResult * res = this->m_connection->exec(tr("select id, name from voltage_level_type order by id;"));
	if (!res->isValid())
	{
		qDebug("DPSets::DPSets - SQL Error");
	}
	else
	{
		while (res->notEoF())
		{
			ui->cmbVoltLevel->addItem(res->getValue(1), QVariant::fromValue(res->getValue(0).toInt()));
			res->moveNext();
		}
	}
	res->close();
	
    ui->label_3->setVisible(false);
    ui->cmbVoltLevel->setVisible(false);
    
	updateForm();
	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = qobject_cast<QWidget *>(this->children().at(i));
        if (w)
            if (w->objectName() != "") w->show();
	}
}

DPSets::~DPSets()
{
	delete ui;
}

void DPSets::dropChanges()
{
	updateForm();
}

void DPSets::saveChanges()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;
		if (m_id != -1)
		{
			sql = "update deliverypoint set name='%1', register=%2, voltlevel=%3 where id=%4;";
			sql = sql.arg(ui->txtName->text(),
						  QString::number((int)ui->chkToRegister->isChecked()),
						  QString::number(ui->cmbVoltLevel->itemData(ui->cmbVoltLevel->currentIndex()).toInt()),
						  QString::number(m_id));
		}
		else
		{
			TVItemDesc d = m_node->parent()->data(0, Qt::UserRole).value<TVItemDesc>();
			Feeder * f = (Feeder *)d.link;
			sql = "insert into deliverypoint (name, register, voltlevel, dpg) values ('%1', %2, %3, %4) returning id;";
			sql = sql.arg(ui->txtName->text(), 
						  QString::number((int)ui->chkToRegister->isChecked()),
						  QString::number(ui->cmbVoltLevel->itemData(ui->cmbVoltLevel->currentIndex()).toInt()),
						  QString::number(f->ID));
		}
		PgreSqlResult * r;
		if (!(r = m_connection->exec(sql))->isValid())
		{
			qDebug("DPSets::saveChanges() - SQL ERROR: %s\n%s", 
			       m_connection->getError().toAscii().constData(),
			       sql.toAscii().constData());
		}
		else
		{
			m_node->setText(0, ui->txtName->text());
			if (m_id == -1)
			{
				TVItemDesc d = m_node->data(0, Qt::UserRole).value<TVItemDesc>();
				Factory * f = (Factory *)d.link;
				m_id = f->ID = r->getValue(0).toInt();
				f->name = ui->txtName->text();
				m_node->setData(0, Qt::UserRole, QVariant::fromValue(d));
			}
			emit onUpdate(m_node);
		}
	}
	updateForm();
}

void DPSets::removeItem()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Вы уверены, что хотите удалить фидер: ").append(m_node->text(0)), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;

		// Удаляем завод
		sql = "delete from deliverypoint where id=%1;";
		if (m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			ui->txtName->setEnabled(false);
			ui->cmdAddMeasuringPoint->setEnabled(false);
			ui->cmdDrop->setEnabled(false);
			ui->cmdSave->setEnabled(false);
			ui->cmdRemove->setEnabled(false);
			emit onRemove(m_node);
			delete m_node;
		}
		else
		{
			qDebug("DPSets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить точку поставки. Подробнее об ошибке см. в логах."));
			return;
		}
	}
}

void DPSets::appendChild()
{
	emit onCreateChild(m_node);
}

void DPSets::editCodes()
{
	if (m_id == -1)
		return;
	
	PointCodes * pc = new PointCodes(this, PT_DP, m_id, m_connection);
	pc->setWindowTitle(tr("Кодировка точки  - ").append(m_node->text(0)));
	pc->exec();
}

void DPSets::updateForm()
{
	if (m_id == -1)
	{
		ui->cmdAddMeasuringPoint->setEnabled(false);
		ui->cmdRemove->setEnabled(false);
		ui->cmdCodes->setEnabled(false);
		ui->chkToRegister->setChecked(true);
	}
	else
	{
		ui->cmdAddMeasuringPoint->setEnabled(true);
		ui->cmdRemove->setEnabled(true);
		ui->cmdCodes->setEnabled(true);
		PgreSqlResult * res = this->m_connection->exec(tr("select name, register, voltlevel from deliverypoint d where d.id=%1 limit 1;").arg(QString::number(m_id)));
		
		if (!res->hasRows())
		{
			qDebug("DPSets::updateForm() - Counter not found!\n\tID: %d", m_id);
		}
		else
		{
			ui->txtName->setText(res->getValue("name"));
			int vl = res->getValue("voltlevel").toInt();
			ui->chkToRegister->setChecked((bool)res->getValue(1).toInt());
			for (int i = 0; i < ui->cmbVoltLevel->count(); i++)
			{
				if (ui->cmbVoltLevel->itemData(i).toInt() == vl)
				{
					ui->cmbVoltLevel->setCurrentIndex(i);
					break;
				}
			}
		}
		res->close();
	}
}
