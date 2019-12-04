#include "ObjectEllipse.h"

ObjectEllipse::ObjectEllipse(QGraphicsItem *parent) :
	SchemeObject(SOT_Ellipse, parent)
{
	setEditable(true);

	_brush.setStyle(Qt::SolidPattern);
	_brush.setColor(OBJECT_ELLIPSE_DEFAULT_BGCOLOR);
	_border_w = 1;
	_is_resize = false;

	_settings << new SchemeObjectSetting("width", _width, "Ширина", "Ширина элемента в пикселах") <<
				 new SchemeObjectSetting("height", _height, "Высота", "Высота элемента в пикселах") <<
				 new SchemeObjectSetting("bgcolor", OBJECT_ELLIPSE_DEFAULT_BGCOLOR, "Заливка", "Фоновый цвет элемента") <<
				 new SchemeObjectSetting("border", _border_w, "Толщина границы", "Толщина линии границ элемента") <<
				 new SchemeObjectSetting("rotation", 0.0, "Угол поворота", "Угол поворота элемента") <<
				 new SchemeObjectSetting("x", pos().x(), "X", "Смещение элемента от левой границы окна") <<
				 new SchemeObjectSetting("y", pos().y(), "Y", "Смещение элемента от верхней границы окна");



	setWidth(OBJECT_ELLIPSE_DEFAULT_WIDTH);
	setHeight(OBJECT_ELLIPSE_DEFAULT_HEIGHT);
	setAcceptHoverEvents(true);
}

ObjectEllipse::~ObjectEllipse()
{
}

QRectF ObjectEllipse::boundingRect() const
{
	return QRectF(-0.5 * _width - _border_w * 0.5, -0.5 * _height - _border_w * 0.5,
				  _width + _border_w, _height + _border_w);
}

void ObjectEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setBrush(_brush);

	if ((_border_w > 0) || (isSelected()))
	{
		QPen border;
		if (isSelected())
		{
			border = QPen(Qt::SolidPattern, 1, Qt::DashLine);
		}
		else
			border = QPen(Qt::SolidPattern, _border_w, Qt::SolidLine);

		painter->setPen(border);
		painter->drawEllipse(QRect(-0.5 * _width, -0.5 * _height, _width, _height));
	}
}

void ObjectEllipse::setWidth(double width)
{
	_width = width;
	if (setting("width"))
		setting("width")->setValue(width);
	moveBy(0, 0);
	update();
}

double ObjectEllipse::width()
{
	return _width;
}

void ObjectEllipse::setHeight(double height)
{
	_height = height;
	if (setting("height"))
		setting("height")->setValue(height);
	update();
}

double ObjectEllipse::height()
{
	return _height;
}

void ObjectEllipse::setPos(const QPointF &pos)
{
	if (setting("x"))
		setting("x")->setValue(pos.x());

	if (setting("y"))
		setting("y")->setValue(pos.y());

	QGraphicsItem::setPos(pos);
}

void ObjectEllipse::setPos(qreal x, qreal y)
{
	QGraphicsItem::setPos(x, y);
}


void ObjectEllipse::updateObject()
{
	_brush = setting("bgcolor")->value().value<QColor>();
	_border_w = setting("border")->value().toInt();
	setPos(setting("x")->value().toDouble(), setting("y")->value().toDouble());
	prepareGeometryChange();
	setWidth(setting("width")->value().toDouble());
	setHeight(setting("height")->value().toDouble());
	setRotation(setting("rotation")->value().toDouble());
}

void ObjectEllipse::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItem::mousePressEvent(event);
}

void ObjectEllipse::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItem::mouseMoveEvent(event);
}

/*
QVariant ObjectEllipse::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
	QPointF pos;
	switch (change)
	{
		case QGraphicsItem::ItemPositionChange:
			pos = QPointF(value.toPointF());
			//QMessageBox::information(0, "", QString("%1 x %2").arg(QString::number(pos.x()), QString::number(pos.y())));
			pos.setY(qRound((pos.y() - _height * 0.5) / SCENE_GRID_SIZE) * SCENE_GRID_SIZE + _height * 0.5);
			pos.setX(qRound((pos.x() - _width * 0.5) / SCENE_GRID_SIZE) * SCENE_GRID_SIZE + _width * 0.5);
			setToolTip(QString("%1 x %2").arg(QString::number(pos.x()), QString::number(pos.y())));
			setting("x")->setValue(pos.x());
			setting("y")->setValue(pos.y());
			return QVariant::fromValue(pos);
	}
	return value;
}
*/
