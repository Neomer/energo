#include "ObjectTriangle.h"

ObjectTriangle::ObjectTriangle(QGraphicsItem *parent) :
	SchemeObject(SOT_Triangle, parent)
{
	setEditable(true);

	_brush.setStyle(Qt::SolidPattern);
	_brush.setColor(OBJECT_TRIANGLE_DEFAULT_BGCOLOR);
	_border_w = 1;

	_settings << new SchemeObjectSetting("width", _width, "Ширина", "Ширина элемента в пикселах") <<
				 new SchemeObjectSetting("height", _height, "Высота", "Высота элемента в пикселах") <<
				 new SchemeObjectSetting("bgcolor", OBJECT_TRIANGLE_DEFAULT_BGCOLOR, "Заливка", "Фоновый цвет элемента") <<
				 new SchemeObjectSetting("border", _border_w, "Толщина границы", "Толщина линии границ элемента") <<
				 new SchemeObjectSetting("rotation", 0.0, "Угол поворота", "Угол поворота элемента") <<
				 new SchemeObjectSetting("x", pos().x(), "X", "Смещение элемента от левой границы окна") <<
				 new SchemeObjectSetting("y", pos().y(), "Y", "Смещение элемента от верхней границы окна");



	setWidth(OBJECT_TRIANGLE_DEFAULT_WIDTH);
	setHeight(OBJECT_TRIANGLE_DEFAULT_HEIGHT);
	setAcceptHoverEvents(true);
}

QRectF ObjectTriangle::boundingRect() const
{
	return QRectF(-0.5 * _width - _border_w * 0.5, -0.5 * _height - _border_w * 0.5,
				  _width + _border_w, _height + _border_w);
}

void ObjectTriangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
		QPointF points[3] = {
			QPointF(0, -0.5 * _height),
			QPointF(-0.5 * _width, 0.5 * _height),
			QPointF(0.5 * _width, 0.5 * _height)
		};
		painter->drawPolygon(points, 3);
	}
}

void ObjectTriangle::setWidth(double width)
{
	_width = width;
	if (setting("width"))
		setting("width")->setValue(width);
	moveBy(0, 0);
	update();
}

double ObjectTriangle::width()
{
	return _width;
}

void ObjectTriangle::setHeight(double height)
{
	_height = height;
	if (setting("height"))
		setting("height")->setValue(height);
	update();
}

double ObjectTriangle::height()
{
	return _height;
}

void ObjectTriangle::setPos(const QPointF &pos)
{
	if (setting("x"))
		setting("x")->setValue(pos.x());

	if (setting("y"))
		setting("y")->setValue(pos.y());

	QGraphicsItem::setPos(pos);
}

void ObjectTriangle::setPos(qreal x, qreal y)
{
	setPos(QPointF(x, y));
}


void ObjectTriangle::updateObject()
{
	_brush = setting("bgcolor")->value().value<QColor>();
	_border_w = setting("border")->value().toInt();
	setPos(setting("x")->value().toDouble(), setting("y")->value().toDouble());
	prepareGeometryChange();
	setWidth(setting("width")->value().toDouble());
	setHeight(setting("height")->value().toDouble());
	setRotation(setting("rotation")->value().toDouble());
}
