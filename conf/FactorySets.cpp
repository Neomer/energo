#include "FactorySets.h"
#include "ui_FactorySets.h"
#include <QGroupBox>
#include <QMessageBox>
#include "struct_desc.h"

FactorySets::FactorySets(QWidget *parent, PgreSqlDrv *connection, int id, QTreeWidgetItem *item) :
    QWidget(parent),
    ui(new Ui::FactorySets)
{
    ui->setupUi(this);
	this->m_connection = connection;
	this->m_id = id;
	this->m_node = item;
	
	updateForm();
	
	QGroupBox * gb = (QGroupBox *)parent;
	gb->setTitle(tr("Настройки предприятия:"));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);
	ui->cmdAddObject->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	ui->cmdSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	
	/*
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = (QWidget *)this->children().at(i);
		w->show();
	}
	*/
}

FactorySets::~FactorySets()
{
    delete ui;
}

void FactorySets::updateForm()
{
	if (m_id == -1)
	{
		ui->cmdAddObject->setEnabled(false);
		ui->cmdRemove->setEnabled(false);
	}
	else
	{
		ui->cmdAddObject->setEnabled(true);
		ui->cmdRemove->setEnabled(true);
		PgreSqlResult * res = this->m_connection->exec(tr("select * from factory where id=%1 limit 1;").arg(QString::number(m_id)));
		
		if (!res->hasRows())
		{
			qDebug("FactorySets::updateForm() - Factory not found!\n\tID: %d", m_id);
		}
		else
		{
			ui->txtName->setText(res->getValue("name"));
		}
		res->close();
	}
}

/************************************************
  
		SLOTS
		
*************************************************/
void FactorySets::dropChanges()
{
	updateForm();
}

void FactorySets::saveChanges()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;
		if (m_id != -1)
		{
			sql = "update factory set name='%1' where id=%2;";
			sql = sql.arg(ui->txtName->text(), QString::number(m_id));
		}
		else
		{
			sql = "insert into factory (name) values ('%1') returning id;";
			sql = sql.arg(ui->txtName->text());
		}
		PgreSqlResult * r;
		if (!(r = m_connection->exec(sql))->isValid())
		{
			qDebug("FactorySets::saveChanges() - SQL ERROR: %s\n%s", 
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

void FactorySets::removeItem()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Вы уверены, что хотите удалить фидер: ").append(m_node->text(0)), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		// Удаляем данные по фидеру
		QString sql = "delete from data where feeder=%1;";
		/*
		if (!m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			qDebug("FactorySets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить ГТП. Подробнее об ошибке см. в логах."));
			return;
		}
		
		// Удаляем счетчики, привязанные к фидеру
		sql = "delete from counter where feeder=%1;";
		if (!m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			qDebug("FactorySets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить ГТП. Подробнее об ошибке см. в логах."));
			return;
		}*/

		// Удаляем завод
		sql = "delete from factory where id=%1;";
		if (m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			ui->txtName->setEnabled(false);
			ui->cmdAddObject->setEnabled(false);
			ui->cmdDrop->setEnabled(false);
			ui->cmdSave->setEnabled(false);
			ui->cmdRemove->setEnabled(false);
			m_id = -1;
			emit onRemove(m_node);
			delete m_node;
		}
		else
		{
			qDebug("FactorySets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить ГТП. Подробнее об ошибке см. в логах."));
			return;
		}
	}
}

void FactorySets::appendChild()
{
	emit onCreateChild(m_node);
}
