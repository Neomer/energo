#include "SchemeObject.h"
#include <QMessageBox>

SchemeObject::SchemeObject(SchemeObjectType type, QGraphicsItem *parent) :
	QObject(),
	QGraphicsItem(parent)
{
	_type = type;
	_menu = new QMenu();
	_menu->addAction(QIcon(":/sceditor/popup/objects/bringtofront.png"), tr("Перенести наверх"), this, SLOT(bringToFront()));
	_menu->addAction(QIcon(":/sceditor/popup/objects/sendtoback.png"), tr("Перенести вниз"), this, SLOT(sendToBack()));
	_menu->addSeparator();
	_menu->addAction(QIcon(":/sceditor/popup/objects/edit-copy-7.png"), tr("Копировать объект"), this, SLOT(copy()));
	_menu->addAction(QIcon(":/sceditor/popup/objects/document-close-2.png"), tr("Удалить  объект"), this, SLOT(remove()));
	
	_detalization = 1;
}

SchemeObject::~SchemeObject()
{
	for (int i = 0; _children.count() > 0; i++)
	{
		SchemeObject * c = _children.takeFirst();
		if (c)
			delete c;
	}

	foreach (SchemeObject * c, _connline)
	{
		removeConnectionLine(c);
		delete c;
	}

	delete _menu;
}

QString SchemeObject::objectName()
{
	return _name;
}

void SchemeObject::setObjectName(QString name)
{
	_name = name;
}

QPoint SchemeObject::position()
{
	return _position;
}

void SchemeObject::setPosition(QPoint point)
{
	_position = point;
}

QSize SchemeObject::size()
{
	return _size;
}

void SchemeObject::setSize(QSize size)
{
	_size = size;
	_pixmap = _pixmap.scaled(size);
}

QPoint SchemeObject::absolutePosition()
{
	QPoint ret = _position;
	SchemeObject * parent = _parent;
	while (parent)
	{
		ret += parent->position();
		parent = _parent->parent();
	}
	return ret;
}

SchemeObject *SchemeObject::parent()
{
	return _parent;
}

QPixmap SchemeObject::pixmap()
{
	return _pixmap;
}

SchemeObjectSetting * SchemeObject::setting(QString name)
{
	foreach (SchemeObjectSetting * set, _settings)
	{
		if (set->name() == name)
			return set;
	}
	QMessageBox::information(0, "", QString("Setting '%1' not found!").arg(name));
	SchemeObjectSetting * set = new SchemeObjectSetting(name);
	_settings.append(set);
	return set;
}

QList<SchemeObjectSetting *> SchemeObject::settings()
{
	return _settings;
}

void SchemeObject::setSettings(QList<SchemeObjectSetting *> settings)
{
	foreach (SchemeObjectSetting * s, settings)
	{
		//QMessageBox::information(0, "", QString("'%1'=%2").arg(s->name(), s->value().toString()));
		setting(s->name())->setValue(s->value());
	}
}

SchemeObjectType SchemeObject::objType() const
{
	return _type;
}

void SchemeObject::setConnectionLine(SchemeObject *line)
{
	_connline.append(line);
}

ObjectConnectionLine *SchemeObject::connectionLine()
{
	return 0;
}

void SchemeObject::connectWith(SchemeObject *object, SchemeObject * connector)
{
	setConnectionLine(connector);
	object->setConnectionLine(connector);
}

void SchemeObject::setEditable(bool editable)
{
	setFlag(QGraphicsItem::ItemIsMovable, editable);
	setFlag(QGraphicsItem::ItemIsSelectable, editable);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, editable);
	_editable = editable;
}

bool SchemeObject::editable()
{
	return _editable;
}

void SchemeObject::setDetalization(double value)
{
	_detalization = value;
	updateObject();
}

double SchemeObject::detalization()
{
	return _detalization;
}

void SchemeObject::updateConnectionLine(QPointF point)
{
	foreach (SchemeObject * c, _connline)
	{
		c->updateObject();
	}
}

void SchemeObject::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	if (_editable)
		_menu->exec(event->screenPos());
}

QVariant SchemeObject::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
	QPointF pos;
	switch (change)
	{
		case QGraphicsItem::ItemPositionChange:
			pos = QPointF(value.toPointF());
/*			pos.setY(qRound((pos.y() - height() * 0.5) / SCENE_GRID_SIZE) * SCENE_GRID_SIZE + height() * 0.5);
			pos.setX(qRound((pos.x() - width() * 0.5) / SCENE_GRID_SIZE) * SCENE_GRID_SIZE + width() * 0.5);
			setToolTip(QString("%1 x %2").arg(QString::number(pos.x()), QString::number(pos.y())));
*/
			if (setting("x"))
				setting("x")->setValue(pos.x());

			if (setting("y"))
				setting("y")->setValue(pos.y());

			updateConnectionLine(pos);

			return QVariant::fromValue(pos);
	}
	return value;
}

void SchemeObject::appendChild(SchemeObject *child)
{
	_children.append(child);
}

void SchemeObject::removeConnectionLine(SchemeObject *line)
{
	int idx = _connline.indexOf(line);
	if (idx != -1)
		_connline.removeAt(idx);
}


void SchemeObject::bringToFront()
{
	qreal maxZ = 0;
	foreach (QGraphicsItem * i, scene()->collidingItems(this))
	{
		if (maxZ < i->zValue())
			maxZ = i->zValue();
	}
	setZValue(maxZ + OBJECT_ZVALUE_DIFF);
}

void SchemeObject::sendToBack()
{
	qreal minZ = 10000;
	foreach (QGraphicsItem * i, scene()->collidingItems(this))
	{
		if (minZ > i->zValue())
			minZ = i->zValue();
	}
	setZValue(minZ - OBJECT_ZVALUE_DIFF);
}

void SchemeObject::remove()
{
	scene()->removeItem(this);
	delete this;
}


void SchemeObject::copy()
{
	emit copied();
}


