#include "ObjectSets.h"
#include "ui_ObjectSets.h"
#include <QGroupBox>
#include <QMessageBox>
#include "ListPicker.h"
#include "struct_desc.h"

ObjectSets::ObjectSets(QWidget *parent, PgreSqlDrv *connection, int id, QTreeWidgetItem * item) :
    QWidget(parent),
    ui(new Ui::ObjectSets)
{
    ui->setupUi(this);

	this->m_connection = connection;
	this->m_id = id;
	this->m_node = item;
	
	updateForm();
	
	QGroupBox * gb = (QGroupBox *)parent;
	gb->setTitle(tr("Настройки подстанции:"));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);
	ui->cmdAddFeeder->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	ui->cmdSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = (QWidget *)this->children().at(i);
		w->show();
	}
}

ObjectSets::~ObjectSets()
{
    delete ui;
}

void ObjectSets::updateForm()
{
	if (m_id == -1)
	{
		ui->cmdAddFeeder->setEnabled(false);
		ui->cmdRemove->setEnabled(false);
	}
	else
	{
		ui->cmdAddFeeder->setEnabled(true);
		ui->cmdRemove->setEnabled(true);
		PgreSqlResult * res = this->m_connection->exec(tr("select o.*, c.name as cname, c.options, c.id as cid from object o left join connection c on o.connection=c.id where o.id=%1 limit 1;").arg(QString::number(m_id)));
		
		if (!res->hasRows())
		{
			qDebug("CounterSets::CounterSets() - Counter not found!\n\tID: %d", m_id);
		}
		else
		{
			ui->txtName->setText(res->getValue("name"));
			ui->txtConnection->setText(res->getValue("cname").append(": ").append(res->getValue("options")));
			ui->txtConnection->setProperty("cid", QVariant::fromValue(res->getValue("cid")));
			ui->txtConnString->setText(res->getValue("conn_str"));
			ui->txtRecall->setText(res->getValue("recall"));
		}
		res->close();
	}
}


/************************************************
  
		SLOTS
		
*************************************************/
void ObjectSets::dropChanges()
{
	updateForm();
}

void ObjectSets::saveChanges()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;
		if (m_id != -1)
		{
			sql = "update object set name='%1', connection=%2, conn_str='%3', recall=%4 where id=%5;";
			sql = sql.arg(ui->txtName->text(), ui->txtConnection->property("cid").toString(), ui->txtConnString->text(), ui->txtRecall->text(), QString::number(m_id));
		}
		else
		{
			TVItemDesc d = m_node->parent()->data(0, Qt::UserRole).value<TVItemDesc>();
			Factory * f = (Factory *)d.link;
			sql = "insert into object (name, connection, conn_str, recall, factory) values ('%1', %2, '%3', %4, %5) returning id;";
			sql = sql.arg(ui->txtName->text(), ui->txtConnection->property("cid").toString(), ui->txtConnString->text(), ui->txtRecall->text(), QString::number(f->ID));
		}
		PgreSqlResult * r;
		if (!(r = m_connection->exec(sql))->isValid())
		{
			qDebug("ObjectSets::saveChanges() - SQL ERROR: %s\n%s", 
			       m_connection->getError().toAscii().constData(),
			       sql.toAscii().constData());
		}
		else
		{
			m_node->setText(0, ui->txtName->text());
			if (m_id == -1)
			{
				TVItemDesc d = m_node->data(0, Qt::UserRole).value<TVItemDesc>();
				Object * f = (Object *)d.link;
				m_id = f->ID = r->getValue(0).toInt();
				f->name = ui->txtName->text();
				m_node->setData(0, Qt::UserRole, QVariant::fromValue(d));
			}
			emit onUpdate(m_node);
		}
	}
	updateForm();
}

void ObjectSets::removeItem()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Вы уверены, что хотите удалить подстанцию: ").append(m_node->text(0)), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql = "delete from object where id=%1;";
		if (m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			ui->txtName->setEnabled(false);
			ui->txtConnString->setEnabled(false);
			ui->txtRecall->setEnabled(false);
			ui->cmdAddFeeder->setEnabled(false);
			ui->cmdDrop->setEnabled(false);
			ui->cmdSave->setEnabled(false);
			ui->cmdRemove->setEnabled(false);
			m_id = -1;
			emit onRemove(m_node);
			delete m_node;
		}
		else
		{
			qDebug("ObjectSets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить подстанцию. Подробнее об ошибке см. в логах."));
		}
	}
}

void ObjectSets::appendChild()
{
	emit onCreateChild(m_node);
}


void ObjectSets::connectionChange(int row)
{
	ListPicker * picker = qobject_cast<ListPicker *>(sender());
	PgreSqlResult * r = picker->getQuery();
	r->moveTo(row);
	ui->txtConnection->setText(r->getValue("name").append(": ").append(r->getValue("options")));
	if (!ui->txtConnection->setProperty("cid", QVariant::fromValue(r->getValue("id"))))
		qDebug("ObjectSets::connectionChange() - QEditLine property is not set!");
}

void ObjectSets::connectionChangeRequest()
{
	PgreSqlResult * r = this->m_connection->exec("select c.id, c.name, ct.name as type, c.options from connection c left join connection_type ct on ct.id=c.type order by c.name;");
	QStringList header;
	header.append("ID");
	header.append(tr("Наименование"));
	header.append(tr("Тип"));
	header.append(tr("Настройки"));
	
	ListPicker * picker = new ListPicker(this, r, header);
	picker->setWindowTitle(tr("Способ соединения"));
	connect(picker, SIGNAL(onPick(int)), this, SLOT(connectionChange(int)));
	picker->show();
}
