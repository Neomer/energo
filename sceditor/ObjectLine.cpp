#include "ObjectLine.h"

ObjectLine::ObjectLine(QGraphicsItem *parent) :
	SchemeObject(SOT_Line, parent)
{
	setEditable(true);

	_brush.setStyle(Qt::SolidPattern);
	_border_w = 1;

	_line.setPoints(OBJECT_LINE_DEFAULT_POINT1, OBJECT_LINE_DEFAULT_POINT2);
	_settings << new SchemeObjectSetting("x", _line.x1(), "X1", "������� �� ��� � ��� 1-�� �����") <<
				 new SchemeObjectSetting("y", _line.y1(), "Y1", "������� �� ��� Y ��� 1-�� �����") <<
				 new SchemeObjectSetting("x2", _line.x2(), "X2", "������� �� ��� � ��� 2-�� �����") <<
				 new SchemeObjectSetting("y2", _line.y2(), "Y2", "������� �� ��� Y ��� 2-�� �����") <<
				 new SchemeObjectSetting("border", _border_w, "������� �������", "������� ����� ������ ��������");

	setAcceptHoverEvents(true);
}

ObjectLine::~ObjectLine()
{
}

QRectF ObjectLine::boundingRect() const
{
	return QRectF(qMin(_line.x1(), _line.x2()),
				  qMin(_line.y1(), _line.y2()),
				  qAbs(_line.x1() - _line.x2()),
				  qAbs(_line.y1() - _line.y2()));
}

void ObjectLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setBrush(_brush);
	painter->drawLine(_line);
}

void ObjectLine::setX1(double x)
{
	_line.setP1(QPointF(x, _line.y1()));
}

void ObjectLine::setX2(double x)
{
	_line.setP2(QPointF(x, _line.y2()));
}

void ObjectLine::setWidth(double width)
{
}

void ObjectLine::setY1(double y)
{
	_line.setP1(QPointF(_line.x1(), y));
}


void ObjectLine::setY2(double y)
{
	_line.setP2(QPointF(_line.x2(), y));
}

void ObjectLine::setHeight(double height)
{
}

double ObjectLine::width()
{
	return qAbs(_line.x1() - _line.x2());
}

double ObjectLine::height()
{
	return qAbs(_line.y1() - _line.y2());
}

void ObjectLine::setLine(QLineF line)
{
	_line = line;
}

void ObjectLine::setPos(const QPointF &pos)
{
}


void ObjectLine::setPos(qreal x, qreal y)
{
}

void ObjectLine::updateObject()
{
	prepareGeometryChange();

	if (_line.p2() == QPointF(setting("x2")->value().toDouble(),
							  setting("x2")->value().toDouble()))
	{
		QPointF new_p2 = _line.p2() - _line.p1(),
				new_p1 = QPointF(setting("x")->value().toDouble(),
								 setting("y")->value().toDouble());
		_line.setPoints(new_p1, new_p1 + new_p2);
	}
}


