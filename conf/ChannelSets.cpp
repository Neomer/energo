#include "ChannelSets.h"
#include "ui_ChannelSets.h"
#include "struct_desc.h"

#include <QGroupBox>
#include <QMessageBox>
#include "ListPicker.h"

ChannelSets::ChannelSets(QWidget *parent, PgreSqlDrv *connection, int id, QTreeWidgetItem *item) :
    QWidget(parent),
    ui(new Ui::ChannelSets)
{
    ui->setupUi(this);

	this->m_connection = connection;
	this->m_id = id;
	this->m_node = item;
	
	updateForm();
	
	QGroupBox * gb = (QGroupBox *)parent;
	gb->setTitle(tr("Настройки каналов учета:"));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);

	ui->cmdSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = (QWidget *)this->children().at(i);
		w->show();
	}
}

ChannelSets::~ChannelSets()
{
    delete ui;
}


void ChannelSets::updateForm()
{
	if (m_id == -1)
	{
		ui->cmdRemove->setEnabled(false);
		m_type = 1;
	}
	else
	{
		ui->cmdRemove->setEnabled(true);
		PgreSqlResult * res = this->m_connection->exec(tr("select c.index, c.name, ct.id typeid, ct.name typename from channel c left join channel_type ct on ct.id=c.type where c.id=%1 limit 1;").arg(QString::number(m_id)));
		
		if (!res->hasRows())
		{
			qDebug("ChannelSets::CounterSets() - Channel not found!\n\tID: %d", m_id);
		}
		else
		{
			ui->txtNumber->setText(res->getValue("index"));
			ui->txtName->setText(res->getValue("name"));
			ui->txtType->setText(res->getValue("typename"));
			m_type = res->getValue("typeid").toInt();
		}
		res->close();
	}
}

/************************************************
  
		SLOTS
		
*************************************************/

void ChannelSets::onSave()
{
	//TODO: Проверка на повторение каналов
	
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;
		if (m_id != -1)
		{
			sql = "update channel set name='%1', index=%2, type=%4 where id=%3;";
			sql = sql.arg(ui->txtName->text(), 
						  ui->txtNumber->text(), 
						  QString::number(m_id),
						  QString::number(m_type));
		}
		else
		{
			TVItemDesc d = m_node->parent()->data(0, Qt::UserRole).value<TVItemDesc>();
			Counter * c = (Counter *)d.link;
			sql = "insert into channel (name, index, counter, type) values ('%1', %2, %3, %4) returning id;";
			sql = sql.arg(ui->txtName->text(), 
						  ui->txtNumber->text(), 
						  QString::number(c->ID),
						  QString::number(m_type));
		}
		PgreSqlResult * r;
		if (!(r = m_connection->exec(sql))->isValid())
		{
			qDebug("ChannelSets::onSave() - SQL ERROR: %s\n%s", 
			       m_connection->getError().toAscii().constData(),
			       sql.toAscii().constData());
		}
		else
		{
			m_node->setText(0, ui->txtName->text());
			if (m_id == -1)
			{
				TVItemDesc d = m_node->data(0, Qt::UserRole).value<TVItemDesc>();
				Channel * f = (Channel *)d.link;
				m_id = f->ID = r->getValue(0).toInt();
				f->name = ui->txtName->text();
				m_node->setData(0, Qt::UserRole, QVariant::fromValue(d));
			}
			emit onUpdate(m_node);
		}
	}
	updateForm();	
}

void ChannelSets::onRemoveItem()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Вы уверены, что хотите удалить измерение: ").append(m_node->text(0)), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		// Удаляем данные по каналу
		QString sql = "delete from data d where d.channel=%1;";
		if (!m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			qDebug("CounterSets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить счетчик. Подробнее об ошибке см. в логах."));
			return;
		}
		
		// Удаляем счетчик
		sql = "delete from channel where id=%1;";
		if (m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			ui->txtNumber->setEnabled(false);
			ui->txtName->setEnabled(false);
			ui->cmdSave->setEnabled(false);
			ui->cmdDrop->setEnabled(false);
			ui->cmdRemove->setEnabled(false);
			m_id = -1;
			delete m_node;
			emit onRemove(m_node);
		}
		else
		{
			qDebug("CounterSets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить счетчик. Подробнее об ошибке см. в логах."));
			return;
		}
	}
}


void ChannelSets::onReset()
{
	updateForm();
}

void ChannelSets::onNameSelect()
{
	PgreSqlResult * r = m_connection->exec("select cn.*, ct.name tname from channel_names cn left join channel_type ct on cn.type=ct.id order by cn.name;");
	QStringList names;
	names.append(tr("Наименование"));
	names.append(tr("Номер"));
	names.append(tr("Тип"));
	ListPicker * pick = new ListPicker(this, r, names);
	pick->setWindowTitle(tr("Наименование канала учета"));
	connect(pick, SIGNAL(onPick(int)), this, SLOT(onNameChange(int)));
	pick->show();
}

void ChannelSets::onNameChange(int row)
{
	ListPicker * picker = qobject_cast<ListPicker *>(sender());
	PgreSqlResult * r = picker->getQuery();
	r->moveTo(row);
	ui->txtName->setText(r->getValue("name"));
	ui->txtNumber->setText(r->getValue("index"));
	ui->txtType->setText(r->getValue("tname"));
	m_type = r->getValue("type").toInt();
}

void ChannelSets::onTypeSelect()
{
	PgreSqlResult * r = m_connection->exec("select * from channel_type order by name;");
	QStringList names;
	names.append(tr(""));
	names.append(tr("Наименование"));
	ListPicker * pick = new ListPicker(this, r, names);
	pick->setWindowTitle(tr("Тип канала учета"));
	connect(pick, SIGNAL(onPick(int)), this, SLOT(onTypeChange(int)));
	pick->show();
}

void ChannelSets::onTypeChange(int row)
{
	ListPicker * picker = qobject_cast<ListPicker *>(sender());
	PgreSqlResult * r = picker->getQuery();
	r->moveTo(row);
	ui->txtType->setText(r->getValue("name"));
	m_type = r->getValue("id").toInt();
}
