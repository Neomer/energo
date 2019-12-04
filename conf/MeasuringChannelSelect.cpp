#include "MeasuringChannelSelect.h"
#include "ui_MeasuringChannelSelect.h"
#include "struct_desc.h"

MeasuringChannelSelect::MeasuringChannelSelect(QWidget *parent, int id, PgreSqlDrv *connection) :
	QDialog(parent),
	ui(new Ui::MeasuringChannelSelect)
{
	ui->setupUi(this);

	m_connection = connection;
	m_id = id;
	
	if (layout()) delete layout();
	setLayout(ui->mainLayout);
	
	setWindowTitle(tr("Выбор каналов измерения"));
	
	updateTree(0);
	QStringList hdr;
	hdr.append(tr("Предприятие"));
	hdr.append(tr("Подстанция"));
	hdr.append(tr("Фидер"));
	hdr.append(tr("Счетчик"));
	hdr.append(tr("Канал"));
	ui->twSelected->setColumnCount(hdr.count());
	ui->twSelected->setHorizontalHeaderLabels(hdr);
	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = qobject_cast<QWidget *>(this->children().at(i));
        if (w)
            if (w->objectName() != "") w->show();
	}
	connect(ui->twObjects, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(twObjectsItemDblClicked(QTreeWidgetItem*,int)));
	connect(ui->twObjects, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(twObjectsItemClicked(QTreeWidgetItem*,int)));
}

MeasuringChannelSelect::~MeasuringChannelSelect()
{
	delete ui;
}

void MeasuringChannelSelect::twObjectsItemDblClicked(QTreeWidgetItem *item, int column)
{
	updateTree(item);
}

void MeasuringChannelSelect::twObjectsItemClicked(QTreeWidgetItem *item, int column)
{
}

void MeasuringChannelSelect::itemSelect()
{
	qDebug("MeasuringChannelSelect::itemSelect() - Count: %d", ui->twObjects->selectedItems().count());
	if (ui->twObjects->selectedItems().count() == 0)
		return;
	QTreeWidgetItem * item = ui->twObjects->selectedItems().at(0);
	TVItemDesc	desc = item->data(0, Qt::UserRole).value<TVItemDesc>();
	PgreSqlResult * r = 0;
	QString sql;
	switch (desc.type)
	{
		case ST_Channel:
			sql = QString("select ch.id as channel, ft.name, o.name, f.name, c.c_number, ch.name from channel ch left join counter c on c.id=ch.counter left join feeder f on f.id=c.feeder left join object o on o.id=f.object left join factory ft on ft.id=o.factory where ch.id=%1;").arg(
					  QString::number(((Channel *)desc.link)->ID));
			qDebug("MeasuringChannelSelect::itemSelect() - Channel ID: %d", ((Channel *)desc.link)->ID);
			r = m_connection->exec(sql);
			break;
			
		case ST_Counter:
			sql = QString("select ch.id as channel, ft.name, o.name, f.name, c.c_number, ch.name from channel ch left join counter c on c.id=ch.counter left join feeder f on f.id=c.feeder left join object o on o.id=f.object left join factory ft on ft.id=o.factory where c.id=%1 order by ch.name;").arg(
					  QString::number(((Counter *)desc.link)->ID));
			r = m_connection->exec(sql);
			break;
	}
	if (r)
	{
		if (!r->isValid())
		{
			qDebug("MeasuringChannelSelect::itemSelect() - SQL ERROR:\n");
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
					twi->setData(Qt::UserRole, QVariant::fromValue(r->getValue(0)));
					ui->twSelected->setItem(start + r->absolutePos(), f - 1, twi);
				}
				r->moveNext();
			}
		}
	}
}

void MeasuringChannelSelect::itemRemove()
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

void MeasuringChannelSelect::saveChanges()
{
	QList<int> id_proc;
	
	for (int r = 0; r < ui->twSelected->rowCount(); r++)
	{
		int id = ui->twSelected->item(r, 0)->data(Qt::UserRole).toInt();
		if (!id_proc.contains(id))
		{
			id_proc.append(id);
			PgreSqlResult * chr = m_connection->exec(QString("select name from channel where id=%1").arg(
														 QString::number(id)));
			QString sql = QString("insert into measuringchannel (mpoint, channel, name) values (%1, %2, '%3');").arg(
							  QString::number(m_id), 
							  QString::number(id),
							  chr->getValue(0));
			PgreSqlResult * r = m_connection->exec(sql);
			if (!r->isValid())
			{
				qDebug("MeasuringChannelSelect::saveChanges() - SQL ERROR:\n%s",
					this->m_connection->getError().toAscii().constData());
			}
		}
	}
	emit appendChild();
	close();
}

void MeasuringChannelSelect::updateTree(QTreeWidgetItem *item)
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
		Object * o;
		Feeder * fd;
		Counter * ctr;
		Channel * ch;
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
					qDebug("BalansSelectElements::twObjectsItemClicked() - List of objects isn't received!\n");
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
				item->takeChildren();
				o = (Object *) type.link;
				qDebug("BalansSelectElements::twObjectsItemClicked() - ID: %d; Name: %s\n", 
					   o->ID, 
					   o->name.toAscii().constData());
				sql = "select f.id, f.name from feeder f where f.object={id} order by f.name;";
				sql.replace("{id}", QString::number(o->ID));
				r = this->m_connection->exec(sql);
				if (!r->isValid())
				{
					qDebug("BalansSelectElements::twObjectsItemClicked() - List of gtps isn't received!\n");
					qDebug("%s", this->m_connection->getError().toAscii().constData());
					return;
				}
				while (r->notEoF())
				{
					twi = new QTreeWidgetItem((QTreeWidget *)0);
					twi->setText(0, r->getValue(1));
					fd = new Feeder();
					TVItemDesc tvd;
					tvd.type = ST_Feeder;
					fd->ID = r->getValue(0, "0").toInt();
					fd->name = r->getValue(1);
					tvd.link = (void *) fd;
					QVariant v;
					v.setValue(tvd);
					twi->setData(0, Qt::UserRole, v);
					twi->setIcon(0, QIcon(":/icons/images/feeder.png"));
					it.append(twi);
					r->moveNext();
				}
				item->addChildren(it);
				r->close();
				break;
				
			case ST_Feeder:
				item->takeChildren();
				fd = (Feeder *) type.link;
				qDebug("BalansSelectElements::twObjectsItemClicked() - ID: %d; Name: %s\n", 
					   fd->ID, 
					   fd->name.toAscii().constData());
				sql = "select c.id, c.c_number, c.allow from counter c where c.feeder={id} order by c.c_number;";
				sql.replace("{id}", QString::number(fd->ID));
				r = this->m_connection->exec(sql);
				if (!r->isValid())
				{
					qDebug("BalansSelectElements::twObjectsItemClicked() - List of gtps isn't received!\n");
					qDebug("%s", this->m_connection->getError().toAscii().constData());
					return;
				}
				while (r->notEoF())
				{
					twi = new QTreeWidgetItem(item);
					twi->setText(0, r->getValue(1));
					ctr = new Counter();
					TVItemDesc tvd;
					tvd.type = ST_Counter;
					ctr->ID = r->getValue(0, "0").toInt();
					ctr->number = r->getValue(1).toLongLong();
					tvd.link = (void *) ctr;
					QVariant v;
					v.setValue(tvd);
					twi->setData(0, Qt::UserRole, v);
					if (r->getValue("allow").toInt())
						twi->setIcon(0, QIcon(":/icons/images/counter.png"));
					else
						twi->setIcon(0, QIcon(":/icons/images/counter_innactive.png"));
					it.append(twi);
					r->moveNext();
				}
				item->addChildren(it);
				r->close();
				break;
				
			case ST_Counter:
				item->takeChildren();
				ctr = (Counter *) type.link;
				qDebug("BalansSelectElements::twObjectsItemClicked() - ID: %d; Number: %ld\n", 
					   ctr->ID, 
					   ctr->number);
				sql = "select c.id, c.name from channel c where c.counter={id} order by c.index;";
				sql.replace("{id}", QString::number(ctr->ID));
				r = this->m_connection->exec(sql);
				if (!r->isValid())
				{
					qDebug("BalansSelectElements::twObjectsItemClicked() - List of channels isn't received!\n");
					qDebug("%s", this->m_connection->getError().toAscii().constData());
					return;
				}
				while (r->notEoF())
				{
					twi = new QTreeWidgetItem(item);
					twi->setText(0, r->getValue(1));
					ch = new Channel();
					TVItemDesc tvd;
					tvd.type = ST_Channel;
					ch->ID = r->getValue(0, "0").toInt();
					ch->name = r->getValue(1);
					tvd.link = (void *) ch;
					QVariant v;
					v.setValue(tvd);
					twi->setData(0, Qt::UserRole, v);
					twi->setIcon(0, QIcon(":/icons/images/channel.png"));
					it.append(twi);
					r->moveNext();
				}
				item->addChildren(it);
				r->close();
				
				break;
				
			case ST_Organization:
				break;
		}
		item->setSelected(true);
		item->setExpanded(true);
	}
}
