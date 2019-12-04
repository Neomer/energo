#include "ObjectConnectionLine.h"
#include <QMessageBox>

ObjectConnectionLine::ObjectConnectionLine(SchemeObject *first, SchemeObject *second) :
	SchemeObject(SOT_ConnectionLine, 0)
{
	_first = first;
	_second = second;
	_border_w = 1;
	_brush.setStyle(Qt::SolidPattern);
	_brush.setColor(QColor());
	

	
	//QMessageBox::information(0, "", QString("Constructor: %1 x %2").arg(QString::number(_width), QString::number(_height)));
	setVisible(true);
	updateObject();

	_settings << new SchemeObjectSetting("width", _width, "Ширина", "Ширина элемента в пикселах") <<
				 new SchemeObjectSetting("height", _height, "Высота", "Высота элемента в пикселах") <<
				 new SchemeObjectSetting("bgcolor", QColor(), "Заливка", "Фоновый цвет элемента") <<
				 new SchemeObjectSetting("border", _border_w, "Толщина границы", "Толщина линии границ элемента") <<
				 new SchemeObjectSetting("x", pos().x(), "X", "Смещение элемента от левой границы окна") <<
				 new SchemeObjectSetting("y", pos().y(), "Y", "Смещение элемента от верхней границы окна");

	double ang = (_first->pos().x() - _second->pos().x()) * (_first->pos().y() - _second->pos().y());

	if (ang > 0)
	{
		_corners.append(QPointF(-0.5 * _width, -0.5 * _height)); 
		_corners.append(QPointF(-0.5 * _width, 0));
		_corners.append(QPointF(0.5 * _width, 0));
		_corners.append(QPointF(0.5 * _width, 0.5 * _height));
	}
	else
	{
		_corners.append(QPointF(-0.5 * _width, 0.5 * _height)); 
		_corners.append(QPointF(-0.5 * _width, 0));
		_corners.append(QPointF(0.5 * _width, 0));
		_corners.append(QPointF(0.5 * _width, -0.5 * _height));
	}	

	setEditable(true);
	setFlag(QGraphicsItem::ItemIsMovable, false);
}

ObjectConnectionLine::~ObjectConnectionLine()
{
	_first->removeConnectionLine(this);
	_second->removeConnectionLine(this);
}

QRectF ObjectConnectionLine::boundingRect() const
{



	return QRectF(-0.5 * _width - _border_w * 0.5, -0.5 * _height - _border_w * 0.5,
				  _width + _border_w, _height + _border_w);
}

void ObjectConnectionLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setBrush(_brush);
	if (_border_w <= 0)
		_border_w = 1;

	QPen border;
	if (isSelected())
		border = QPen(Qt::SolidPattern, 1, Qt::DashLine);
	else
		border = QPen(Qt::SolidPattern, _border_w, Qt::SolidLine);

	border.setColor(QColor(0, 0, 0));
	//QMessageBox::information(0, "", QString("Repaint: %1 x %2").arg(QString::number(_width), QString::number(_height)));
	painter->setPen(border);

	// Определяем направление линии
	QPointF start = _corners.at(0),
			end;
	for (int i = 1; i < _corners.count(); i++)
	{
		end = _corners.at(i);
		painter->drawLine(start, end);
		start = end;
	}
}

void ObjectConnectionLine::setFirst(SchemeObject *first)
{
	_first = first;
}

SchemeObject *ObjectConnectionLine::first()
{
	return _first;
}

void ObjectConnectionLine::setSecond(SchemeObject *second)
{
	_second = second;
}

SchemeObject *ObjectConnectionLine::second()
{
	return _second;
}

QGraphicsLineItem *ObjectConnectionLine::line()
{
	return _line;
}

SchemeObject *ObjectConnectionLine::other(SchemeObject *test)
{
	if (test == _first)
		return _second;
	else
		return _first;
}

void ObjectConnectionLine::updateObject()
{
	prepareGeometryChange();
	_width = qAbs(_first->sceneBoundingRect().x() - _second->sceneBoundingRect().x());
	_height = qAbs(_first->sceneBoundingRect().y() - _second->sceneBoundingRect().y());
	setPos(qMin(_first->pos().x(), _second->pos().x()) + qAbs(_first->pos().x() - _second->pos().x()) * 0.5,
		   qMin(_first->pos().y(), _second->pos().y()) + qAbs(_first->pos().y() - _second->pos().y()) * 0.5);
	
}

void ObjectConnectionLine::setWidth(double width)
{
}

double ObjectConnectionLine::width()
{
	return _width;
}

void ObjectConnectionLine::setHeight(double height)
{
}

double ObjectConnectionLine::height()
{
	return _height;
}

void ObjectConnectionLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	
	SchemeObject::mousePressEvent(event);
}



