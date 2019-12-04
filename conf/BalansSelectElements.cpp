#include "BalansSelectElements.h"
#include "ui_BalansSelectElements.h"

struct BalansElement
{
	int ID;
	BalansDirection direction;
};

BalansSelectElements::BalansSelectElements(PgreSqlDrv *connection, int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BalansSelectElements)
{
    ui->setupUi(this);
	if (this->layout()) delete this->layout();
	this->setLayout(ui->mainLayout);
	
	_conn = connection;
	_id = id;
	
	PgreSqlResult * r = _conn->exec("select f.id, f.name from factory f order by f.name");
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
	ui->twList->addTopLevelItems(tl);
/*
	QTreeWidgetItem * twi = new QTreeWidgetItem();
	twi->setText(0, tr("Элементы баланса"));
	ui->twSelected->addTopLevelItem(twi);
*/
	connect(ui->twList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(twListItemDblClicked(QTreeWidgetItem*,int)));
	connect(ui->twList, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(twListItemClicked(QTreeWidgetItem*,int)));
}

BalansSelectElements::~BalansSelectElements()
{
    delete ui;
}

void BalansSelectElements::saveChanges()
{
	QList<QTreeWidgetItem *> elem = getSelectedChannels();
	qDebug("BalansSelectElements::saveChanges() - Total %d channel(s)\n",
		   elem.count());
	
	for (int i = 0; i < elem.count(); i++)
	{
		TVItemDesc desc = elem.at(i)->data(0, Qt::UserRole).value<TVItemDesc>();
		BalansElement * be = (BalansElement *) desc.link;
		QString sql = QString("insert into balans_element (balans, channel, direction) VALUES (%1, %2, %3)").arg(
					QString::number(_id), 
					QString::number(be->ID),
					QString::number((int)(be->direction)));
		PgreSqlResult * r = _conn->exec(sql);
		if (!r->isValid())
		{
			qDebug("BalansSelectElements::saveChanges() - SQL ERROR: %s\n%s\n",
				   sql.toAscii().constData(),
				   _conn->getError().toAscii().constData());
		}
	}
	emit onUpdate();
	close();
}

QList<QTreeWidgetItem *> BalansSelectElements::getSelectedChannels()
{
	QList<QTreeWidgetItem *> * ret = new QList<QTreeWidgetItem *>();
	
	for (int i = 0; i < ui->twSelected->topLevelItemCount(); i++)
		readBranch(&ret, ui->twSelected->topLevelItem(i));
	
	return *ret;
}

void BalansSelectElements::readBranch(QList<QTreeWidgetItem *> **list, QTreeWidgetItem *node)
{
	TVItemDesc desc = node->data(0, Qt::UserRole).value<TVItemDesc>();
	
	if (desc.type == ST_Channel)
		(*list)->append(node);
	else
		for (int i = 0; i < node->childCount(); i++)
			readBranch(list, node->child(i));
	
}

void BalansSelectElements::itemSelectPositive()
{
	itemSelect(BD_Positive);
}

void BalansSelectElements::itemSelectNegative()
{
	itemSelect(BD_Negative);
}

void BalansSelectElements::itemSelect(BalansDirection direction)
{
	qDebug("BalansSelectElements::itemSelect() - Count: %d", ui->twList->selectedItems().count());
	QList<QTreeWidgetItem *> items = ui->twList->selectedItems();
	
	for (int i = 0; i < items.count(); i++)
	{
		//Строим предков
		QTreeWidgetItem * item;
		findTopLevelItem(items.at(i), &item);
		int step = 0;
		QTreeWidgetItem * parent = skipRepeat(&item, 0, &step);
		
		while (--step > 0)
		{
			item = item->child(0)->clone();
		}
		
		//Переносим вместе с потомками
		if (!parent)
			ui->twSelected->addTopLevelItem(item);
		else
			parent->addChild(item);
		
		TVItemDesc desc = items.at(i)->data(0, Qt::UserRole).value<TVItemDesc>();
		QString sql;
		PgreSqlResult * r;
		TVItemDesc twd, itd;
		BalansElement * ctr;
		while (item->child(0))
		{
			item = item->child(0);
		}
		switch (desc.type)
		{
			case ST_Factory:
				sql = QString("select ch.id as channel, ch.name as chname, ch.index, c.id as counter, c.c_number as cnumber, f.id as feeder, f.name as fname, o.id as object, o.name as oname, ft.id as factory, ft.name as ftname from channel ch left join counter c on c.id=ch.counter left join feeder f on f.id=c.feeder left join object o on o.id=f.object left join factory ft on ft.id=o.factory where ft.id=%1 order by ft.id, o.id, f.id, c.id, ch.index").arg(((Factory *)desc.link)->ID);
				break;
				
			case ST_Object:
				sql = QString("select ch.id as channel, ch.name as chname, ch.index, c.id as counter, c.c_number as cnumber, f.id as feeder, f.name as fname, o.id as object, o.name as oname, ft.id as factory, ft.name as ftname from channel ch left join counter c on c.id=ch.counter left join feeder f on f.id=c.feeder left join object o on o.id=f.object left join factory ft on ft.id=o.factory where o.id=%1 order by ft.id, o.id, f.id, c.id, ch.index").arg(((Factory *)desc.link)->ID);
				break;
				
			case ST_Feeder:
				sql = QString("select ch.id as channel, ch.name as chname, ch.index, c.id as counter, c.c_number as cnumber, f.id as feeder, f.name as fname, o.id as object, o.name as oname, ft.id as factory, ft.name as ftname from channel ch left join counter c on c.id=ch.counter left join feeder f on f.id=c.feeder left join object o on o.id=f.object left join factory ft on ft.id=o.factory where f.id=%1 order by ft.id, o.id, f.id, c.id, ch.index").arg(((Factory *)desc.link)->ID);
				break;
				
			case ST_Counter:
				sql = QString("select ch.id as channel, ch.name as chname, ch.index, c.id as counter, c.c_number as cnumber, f.id as feeder, f.name as fname, o.id as object, o.name as oname, ft.id as factory, ft.name as ftname from channel ch left join counter c on c.id=ch.counter left join feeder f on f.id=c.feeder left join object o on o.id=f.object left join factory ft on ft.id=o.factory where c.id=%1 order by ft.id, o.id, f.id, c.id, ch.index").arg(((Factory *)desc.link)->ID);
				break;
				
			case ST_Channel:
				switch (direction)
				{
					case BD_Positive:
						item->setIcon(0, QIcon(":/icons/images/chpositive.png"));
						break;
						
					case BD_Negative:
						item->setIcon(0, QIcon(":/icons/images/chnegative.png"));
						break;
				}
				ctr = new BalansElement();
				itd = item->data(0, Qt::UserRole).value<TVItemDesc>();
				ctr->ID = ((Channel *)itd.link)->ID;
				ctr->direction = direction;
				twd.type = ST_Channel;
				twd.link = (void *) ctr;
				QVariant v;
				v.setValue(twd);
				item->setData(0, Qt::UserRole, v);
				break;
		}
		
		if (sql != "")
		{
			r = _conn->exec(sql);
			if (!r->isValid())
			{
				qDebug("BalansSelectElements::itemSelect() - SQL ERROR: %s\n",
					   _conn->getError().toAscii().constData());
				return;
			}
			item->addChildren(treeFromTable((StructType)(desc.type + 1), r, direction));
		}
	}
}

QList<QTreeWidgetItem *> BalansSelectElements::treeFromTable(StructType desc, PgreSqlResult *result, BalansDirection direction)
{
	QList<QTreeWidgetItem *> ret;
	QTreeWidgetItem * twi;
	int id;
	TVItemDesc twd;
	QVariant v;
	
	switch (desc)
	{
		case ST_Factory:
			//(*root)->addChildren(treeFromTable(0, ST_Object, result));
			break;
			
		case ST_Object:
			id = result->getValue("factory").toInt();
			twd.type = ST_Object;
			twd.link = 0;
			v.setValue(twd);
			while (id == result->getValue("factory").toInt())
			{
				twi = new QTreeWidgetItem();
				twi->setText(0, result->getValue("oname"));
				twi->setIcon(0, QIcon(":/icons/images/object.png"));
				twi->addChildren(treeFromTable(ST_Feeder, result, direction));
				twi->setData(0, Qt::UserRole, v);
				ret.append(twi);
				//result->moveNext();
			}
			break;
			
		case ST_Feeder:
			id = result->getValue("object").toInt();
			twd.type = ST_Feeder;
			twd.link = 0;
			v.setValue(twd);
			while (id == result->getValue("object").toInt())
			{
				twi = new QTreeWidgetItem();
				twi->setText(0, result->getValue("fname"));
				twi->setIcon(0, QIcon(":/icons/images/feeder.png"));
				twi->addChildren(treeFromTable(ST_Counter, result, direction));
				twi->setData(0, Qt::UserRole, v);
				ret.append(twi);
				//result->moveNext();
			}
			break;
			
		case ST_Counter:
			id = result->getValue("feeder").toInt();
			twd.type = ST_Counter;
			twd.link = 0;
			v.setValue(twd);
			while (id == result->getValue("feeder").toInt())
			{
				twi = new QTreeWidgetItem();
				twi->setText(0, result->getValue("cnumber"));
				twi->setIcon(0, QIcon(":/icons/images/counter.png"));
				twi->addChildren(treeFromTable(ST_Channel, result, direction));
				twi->setData(0, Qt::UserRole, v);
				ret.append(twi);
				//result->moveNext();
			}
			break;
			
		case ST_Channel:
			id = result->getValue("counter").toInt();
			while (id == result->getValue("counter").toInt())
			{
				twi = new QTreeWidgetItem();
				BalansElement * ctr = new BalansElement();
				ctr->ID = id;
				ctr->direction = direction;
				twd.type = ST_Channel;
				twd.link = (void *) ctr;
				twi->setText(0, result->getValue("chname"));
				v.setValue(twd);
				twi->setData(0, Qt::UserRole, v);
				switch (direction)
				{
					case BD_Positive:
						twi->setIcon(0, QIcon(":/icons/images/chpositive.png"));
						break;
						
					case BD_Negative:
						twi->setIcon(0, QIcon(":/icons/images/chnegative.png"));
						break;
				}
				ret.append(twi);
				result->moveNext();
			}
			break;
	}
	return ret;
}

QTreeWidgetItem * BalansSelectElements::skipRepeat(QTreeWidgetItem ** item, QTreeWidgetItem * location, int * step)
{
	TVItemDesc desc = (*item)->data(0, Qt::UserRole).value<TVItemDesc>();
	(*step)++;
	if (!location)
	{
		for (int i = 0; i < ui->twSelected->topLevelItemCount(); i++)
		{
			TVItemDesc curdesc = ui->twSelected->topLevelItem(i)->data(0, Qt::UserRole).value<TVItemDesc>();
			if (((Factory *)desc.link)->ID == ((Factory *)curdesc.link)->ID)
			{
				QTreeWidgetItem * child = (*item)->child(0);
				item = &child;
				QTreeWidgetItem * ret = skipRepeat(item, ui->twSelected->topLevelItem(i), step);
				if (!ret)
					return ui->twSelected->topLevelItem(i);
				else
					return ret;
			}
		}
	}
	else
	{
		Object * ob;
		Feeder * fd;
		Counter * ct;
		Channel * ch;
		switch (desc.type)
		{
			case ST_Object:
				ob = (Object *)desc.link;
				for (int i = 0; i < location->childCount(); i++)
				{
					TVItemDesc curdesc = location->child(i)->data(0, Qt::UserRole).value<TVItemDesc>();
					if (ob->ID == ((Object *)curdesc.link)->ID)
					{
						QTreeWidgetItem * child = (*item)->child(0);
						item = &child;
						QTreeWidgetItem * ret = skipRepeat(item, location->child(i), step);
						if (!ret)
							return location->child(i);
						else
							return ret;
					}
				}
				break;
				
			case ST_Feeder:
				fd = (Feeder *)desc.link;
				for (int i = 0; i < location->childCount(); i++)
				{
					TVItemDesc curdesc = location->child(i)->data(0, Qt::UserRole).value<TVItemDesc>();
					if (fd->ID == ((Feeder *)curdesc.link)->ID)
					{
						QTreeWidgetItem * child = (*item)->child(0);
						item = &child;
						QTreeWidgetItem * ret = skipRepeat(item, location->child(i), step);
						if (!ret)
							return location->child(i);
						else
							return ret;
					}
				}
				break;
				
			case ST_Counter:
				ct = (Counter *)desc.link;
				for (int i = 0; i < location->childCount(); i++)
				{
					TVItemDesc curdesc = location->child(i)->data(0, Qt::UserRole).value<TVItemDesc>();
					if (ct->ID == ((Counter *)curdesc.link)->ID)
					{
						QTreeWidgetItem * child = (*item)->child(0);
						item = &child;
						QTreeWidgetItem * ret = skipRepeat(item, location->child(i), step);
						if (!ret)
							return location->child(i);
						else
							return ret;
					}
				}
				break;
				
			case ST_Channel:
				ch = (Channel *)desc.link;
				for (int i = 0; i < location->childCount(); i++)
				{
					TVItemDesc curdesc = location->child(i)->data(0, Qt::UserRole).value<TVItemDesc>();
					if (ch->ID == ((Channel *)curdesc.link)->ID)
					{
						QTreeWidgetItem * child = (*item)->child(0);
						item = &child;
						QTreeWidgetItem * ret = skipRepeat(item, location->child(i), step);
						if (!ret)
							return location->child(i);
						else
							return ret;
					}
				}
				break;
		}
	}
	return 0;
}

QTreeWidgetItem * BalansSelectElements::findTopLevelItem(QTreeWidgetItem *item, QTreeWidgetItem ** tree)
{
	if (!item->parent()) 
	{
		*tree = new QTreeWidgetItem(*item);
		return item;
	}
	QTreeWidgetItem * parent = findTopLevelItem(item->parent(), tree),
			* last = *tree;
	
	while (last->child(0) != 0)
	{
		last = last->child(0);
		last->setExpanded(true);
	}
	last->addChild(new QTreeWidgetItem(*item));
	return parent;
}

void BalansSelectElements::twListItemClicked(QTreeWidgetItem *item, int column)
{
	
}

void BalansSelectElements::twListItemDblClicked(QTreeWidgetItem *item, int column)
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
	TVItemDesc	type = item->data(column, Qt::UserRole).value<TVItemDesc>();
	switch (type.type)
	{
		case ST_Factory:
			item->takeChildren();
			f = (Factory *) type.link;
			sql = "select o.id, o.name from object o where o.factory={id} order by o.name;";
			sql.replace("{id}", QString::number(f->ID));
			r = this->_conn->exec(sql);
			if (!r->isValid())
			{
				qDebug("BalansSelectElements::twListItemClicked() - List of objects isn't received!\n");
				qDebug("%s", this->_conn->getError().toAscii().constData());
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
			qDebug("BalansSelectElements::twListItemClicked() - ID: %d; Name: %s\n", 
				   o->ID, 
				   o->name.toAscii().constData());
			sql = "select f.id, f.name from feeder f where f.object={id} order by f.name;";
			sql.replace("{id}", QString::number(o->ID));
			r = this->_conn->exec(sql);
			if (!r->isValid())
			{
				qDebug("BalansSelectElements::twListItemClicked() - List of gtps isn't received!\n");
				qDebug("%s", this->_conn->getError().toAscii().constData());
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
			qDebug("BalansSelectElements::twListItemClicked() - ID: %d; Name: %s\n", 
				   fd->ID, 
				   fd->name.toAscii().constData());
			sql = "select c.id, c.c_number, c.allow from counter c where c.feeder={id} order by c.c_number;";
			sql.replace("{id}", QString::number(fd->ID));
			r = this->_conn->exec(sql);
			if (!r->isValid())
			{
				qDebug("BalansSelectElements::twListItemClicked() - List of gtps isn't received!\n");
				qDebug("%s", this->_conn->getError().toAscii().constData());
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
			qDebug("BalansSelectElements::twListItemClicked() - ID: %d; Number: %ld\n", 
				   ctr->ID, 
				   ctr->number);
			sql = "select c.id, c.name from channel c where c.counter={id} and type=1 order by c.index;";
			sql.replace("{id}", QString::number(ctr->ID));
			r = this->_conn->exec(sql);
			if (!r->isValid())
			{
				qDebug("BalansSelectElements::twListItemClicked() - List of channels isn't received!\n");
				qDebug("%s", this->_conn->getError().toAscii().constData());
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
	item->setExpanded(true);
}
