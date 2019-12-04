#include "ScheduleSelectElements.h"
#include "ui_ScheduleSelectElements.h"
#include "../includes/struct_desc.h"

struct TableElement
{
	int ID;
	bool fromBase;
};

ScheduleSelectElements::ScheduleSelectElements(QWidget *parent, int id, PgreSqlDrv *connection) :
	QDialog(parent),
	ui(new Ui::ScheduleSelectElements)
{
	ui->setupUi(this);

	m_connection = connection;
	m_id = id;
	
	if (layout()) delete layout();
	setLayout(ui->mainLayout);
	
	setWindowTitle(tr("Выбор объектов для задания"));
	
	updateTree(0);
	QStringList hdr;
	hdr.append(tr("Предприятие"));
	hdr.append(tr("Подстанция"));
	ui->twSelected->setColumnCount(hdr.count());
	ui->twSelected->setHorizontalHeaderLabels(hdr);
	ui->twSelected->setRowCount(0);
	if (m_id != -1)
	{
		PgreSqlResult * r = m_connection->exec(QString("select o.id, f.name as factory, o.name as object from interview i left join schedule s on s.id=i.schedule left join object o on i.object=o.id left join factory f on o.factory=f.id where s.id=%1 order by o.name;").arg(
												   QString::number(m_id)));
		if (!r->isValid())
		{
			qDebug("ScheduleSelectElements::ScheduleSelectElements() - SQL ERROR:\n");
			qDebug("%s", this->m_connection->getError().toAscii().constData());
		}
		else
		{
			int start = ui->twSelected->rowCount();

			ui->twSelected->setRowCount(start + r->numRows());
			while (r->notEoF())
			{
				for (int f = 1; f < r->numFields(); f++)
				{
					QTableWidgetItem * twi = new QTableWidgetItem();
					twi->setText(r->getValue(f));
					TableElement * te = new TableElement();
					te->ID = r->getValue(0).toInt();
					te->fromBase = true;
					twi->setData(Qt::UserRole, QVariant::fromValue((int)te));
					ui->twSelected->setItem(start + r->absolutePos(), f - 1, twi);
				}
				r->moveNext();
			}
		}
	}

	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = qobject_cast<QWidget *>(this->children().at(i));
        if (w)
            if (w->objectName() != "") w->show();
	}
	connect(ui->twObjects, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(twObjectsItemDblClicked(QTreeWidgetItem*,int)));
	connect(ui->twObjects, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(twObjectsItemClicked(QTreeWidgetItem*,int)));
}

ScheduleSelectElements::~ScheduleSelectElements()
{
	delete ui;
}

void ScheduleSelectElements::twObjectsItemDblClicked(QTreeWidgetItem *item, int column)
{
	updateTree(item);
}

void ScheduleSelectElements::twObjectsItemClicked(QTreeWidgetItem *item, int column)
{
}

void ScheduleSelectElements::updateTree(QTreeWidgetItem *item)
{
	if (!item)
	{
		PgreSqlResult * r = m_connection->exec("select f.id, f.name from factory f order by f.name");
		QList<QTreeWidgetItem *> tl;
		while (r->notEoF())
		{
			QTreeWidgetItem * twi = new QTreeWidgetItem();
			twi->setText(0, r->getValue(1));
			twi->setIcon(0, QIcon(":/icons/images/server.png"));
			TVItemDesc * desc = new TVItemDesc();
			Factory * f = new Factory();
			f->ID = r->getValue(0).toInt();
			f->name = r->getValue(0);
			desc->type = ST_Factory;
			desc->link = (void *) f;
			QVariant v;
			v.setValue(*desc);
			twi->setData(0, Qt::UserRole, v);
			tl.append(twi);
			r->moveNext();
		}
		ui->twObjects->addTopLevelItems(tl);
	}
	else
	{
		Factory * f;
		QString sql;
		PgreSqlResult * r;
		QTreeWidgetItem * twi;
		QList<QTreeWidgetItem *> it;
		TVItemDesc	type = item->data(0, Qt::UserRole).value<TVItemDesc>();
		switch (type.type)
		{
			case ST_Factory:
				item->takeChildren();
				f = (Factory *) type.link;
				sql = "select o.id, o.name from object o where o.factory={id} order by o.name;";
				sql.replace("{id}", QString::number(f->ID));
				r = this->m_connection->exec(sql);
				if (!r->isValid())
				{
					qDebug("ScheduleSelectElements::twObjectsItemClicked() - List of objects isn't received!\n");
					qDebug("%s", this->m_connection->getError().toAscii().constData());
					return;
				}
				while (r->notEoF())
				{
					twi = new QTreeWidgetItem(item);
					twi->setText(0, r->getValue(1));
					Object * g = new Object();
					TVItemDesc tvd;
					tvd.type = ST_Object;
					g->ID = r->getValue(0, "0").toInt();
					g->name = r->getValue(1);
					tvd.link = (void *) g;
					QVariant v;
					v.setValue(tvd);
					twi->setData(0, Qt::UserRole, v);
					twi->setIcon(0, QIcon(":/icons/images/object.png"));
					it.append(twi);
					r->moveNext();
				}
				item->addChildren(it);
				r->close();
				break;
				
			case ST_Object:
				break;
				
			case ST_Feeder:
				break;
				
			case ST_Counter:
				break;
		}
		item->setSelected(true);
		item->setExpanded(true);
	}
}

void ScheduleSelectElements::itemSelect()
{
	qDebug("ScheduleSelectElements::itemSelect() - Count: %d", ui->twObjects->selectedItems().count());
	if (ui->twObjects->selectedItems().count() == 0)
		return;
	QTreeWidgetItem * item = ui->twObjects->selectedItems().at(0);
	TVItemDesc	desc = item->data(0, Qt::UserRole).value<TVItemDesc>();
	PgreSqlResult * r = 0;
	QString sql;
	switch (desc.type)
	{
		case ST_Object:
			sql = QString("select o.id, ft.name, o.name from object o left join factory ft on ft.id=o.factory where o.id=%1;").arg(
					  QString::number(((Object *)desc.link)->ID));
			qDebug("MeasuringChannelSelect::itemSelect() - Channel ID: %d", ((Object *)desc.link)->ID);
			r = m_connection->exec(sql);
			break;
			
		case ST_Factory:
			sql = QString("select o.id, ft.name, o.name from object o left join factory ft on ft.id=o.factory where ft.id=%1 order by o.name;").arg(
					  QString::number(((Counter *)desc.link)->ID));
			r = m_connection->exec(sql);
			break;
	}
	if (r)
	{
		if (!r->isValid())
		{
			qDebug("ScheduleSelectElements::itemSelect() - SQL ERROR:\n");
			qDebug("%s", this->m_connection->getError().toAscii().constData());
		}
		else
		{
			int start = ui->twSelected->rowCount();

			ui->twSelected->setRowCount(ui->twSelected->rowCount() + r->numRows());
			while (r->notEoF())
			{
				for (int f = 1; f < r->numFields(); f++)
				{
					QTableWidgetItem * twi = new QTableWidgetItem();
					twi->setText(r->getValue(f));
					TableElement * te = new TableElement();
					te->ID = r->getValue(0).toInt();
					te->fromBase = false;
					twi->setData(Qt::UserRole, QVariant::fromValue((int)te));
					ui->twSelected->setItem(start + r->absolutePos(), f - 1, twi);
				}
				r->moveNext();
			}
		}
	}
}

void ScheduleSelectElements::itemRemove()
{
	if (ui->twSelected->selectedItems().count()	== 0)
		return;
	
	QList<int> rows;
	
	for (int i = 0; i < ui->twSelected->selectedItems().count(); i++)
	{
		if (!rows.contains(ui->twSelected->selectedItems().at(i)->row()))
			rows.append(ui->twSelected->selectedItems().at(i)->row());
	}
	
	for (int i = 0; i < rows.count(); i++)
	{
		ui->twSelected->removeRow(rows.at(i));
	}
}

void ScheduleSelectElements::saveChanges()
{
	QList<int> id_proc;
	
	for (int r = 0; r < ui->twSelected->rowCount(); r++)
	{
		TableElement * te = (TableElement *) ui->twSelected->item(r, 0)->data(Qt::UserRole).toInt();
		if (!te->fromBase)
		{
			if (!id_proc.contains(te->ID))
			{
				id_proc.append(te->ID);
				QString sql = QString("insert into interview (schedule, object, priority) values (%1, %2, 0);").arg(
								  QString::number(m_id), 
								  QString::number(te->ID));
				PgreSqlResult * r = m_connection->exec(sql);
				if (!r->isValid())
				{
					qDebug("ScheduleSelectElements::saveChanges() - SQL ERROR:\n%s",
						this->m_connection->getError().toAscii().constData());
				}
			}
		}
	}
	emit onUpdate();
	close();
}
