#include "ObjectText.h"
#include <QMessageBox>

ObjectText::ObjectText(QGraphicsItem *parent) :
	SchemeObject(SOT_Text, parent)
{
	setEditable(true);

	_brush.setStyle(Qt::SolidPattern);
	_brush.setColor(OBJECT_TEXT_DEFAULT_BGCOLOR);
	_fore = OBJECT_TEXT_DEFAULT_FORECOLOR;
	_border_w = 1;
	_text = OBJECT_TEXT_DEFAULT_TEXT;
	_is_resize = false;

	_settings << new SchemeObjectSetting("text", _text, "Текст", "Текст внутри элемента") <<
				 new SchemeObjectSetting("width", _width, "Ширина", "Ширина элемента в пикселах") <<
				 new SchemeObjectSetting("height", _height, "Высота", "Высота элемента в пикселах") <<
				 new SchemeObjectSetting("bgcolor", OBJECT_TEXT_DEFAULT_BGCOLOR, "Заливка", "Фоновый цвет элемента") <<
				 new SchemeObjectSetting("forecolor", OBJECT_TEXT_DEFAULT_FORECOLOR, "Цвет шрифта", "Цвет текста внутри элемента") <<
				 new SchemeObjectSetting("font", _font, "Шрифт", "Формат шрифта надписи внутри элемента") <<
				 new SchemeObjectSetting("border", _border_w, "Толщина границы", "Толщина линии границ элемента") <<
				 new SchemeObjectSetting("rotation", 0.0, "Угол поворота", "Угол поворота элемента") <<
				 new SchemeObjectSetting("x", pos().x(), "X", "Смещение элемента от левой границы окна") <<
				 new SchemeObjectSetting("y", pos().y(), "Y", "Смещение элемента от верхней границы окна");



	setWidth(OBJECT_TEXT_DEFAULT_WIDTH);
	setHeight(OBJECT_TEXT_DEFAULT_HEIGHT);
	setAlignment(Qt::AlignCenter);
	setAcceptHoverEvents(true);
}

ObjectText::~ObjectText()
{
}

QRectF ObjectText::boundingRect() const
{
	return QRectF(-0.5 * _width - _border_w * 0.5, -0.5 * _height - _border_w * 0.5,
				  _width + _border_w, _height + _border_w);
}

void ObjectText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
		painter->drawRect(QRect(-0.5 * _width, -0.5 * _height, _width, _height));
	}

	painter->setPen(QPen(_fore));
	painter->setFont(_font);
	painter->drawText(boundingRect(), _align | Qt::TextWordWrap, _text);
/*	if (isSelected())
	{
		painter->drawRect(QRect(-0.5 * _width, -0.5 * _height, OBJECT_SELECTION_MARKER, OBJECT_SELECTION_MARKER));
		painter->drawRect(QRect(-0.5 * _width, 0.5 * _height - OBJECT_SELECTION_MARKER, OBJECT_SELECTION_MARKER, OBJECT_SELECTION_MARKER));
		painter->drawRect(QRect(0.5 * _width - OBJECT_SELECTION_MARKER, -0.5 * _height, OBJECT_SELECTION_MARKER, OBJECT_SELECTION_MARKER));
		painter->drawRect(QRect(0.5 * _width - OBJECT_SELECTION_MARKER, 0.5 * _height - OBJECT_SELECTION_MARKER, OBJECT_SELECTION_MARKER, OBJECT_SELECTION_MARKER));

	}
	*/
}

void ObjectText::setText(QString value)
{
	_text = value;
	update();
}


void ObjectText::setWidth(double width)
{
	_width = width;
	if (setting("width"))
		setting("width")->setValue(width);
	moveBy(0, 0);
	update();
}

double ObjectText::width()
{
	return _width;
}

void ObjectText::setHeight(double height)
{
	_height = height;
	if (setting("height"))
		setting("height")->setValue(height);
	update();
}

double ObjectText::height()
{
	return _height;
}

void ObjectText::setPos(const QPointF &pos)
{
	if (setting("x"))
		setting("x")->setValue(pos.x());

	if (setting("y"))
		setting("y")->setValue(pos.y());

	QGraphicsItem::setPos(pos);
}

void ObjectText::setPos(qreal x, qreal y)
{
	QGraphicsItem::setPos(x, y);
}

void ObjectText::setAlignment(Qt::AlignmentFlag align)
{
	_align = align;
}

Qt::AlignmentFlag ObjectText::alignment()
{
	return _align;
}

void ObjectText::setAutoResize(bool value)
{
	_autoresize = value;
}

bool ObjectText::autoResize()
{
	return _autoresize;
}

void ObjectText::updateObject()
{
	_brush = setting("bgcolor")->value().value<QColor>();
	_fore = setting("forecolor")->value().value<QColor>();
	_font = setting("font")->value().value<QFont>();
	_border_w = setting("border")->value().toInt();
	setPos(setting("x")->value().toDouble(), setting("y")->value().toDouble());
	setText(setting("text")->value().toString());
	prepareGeometryChange();
	setWidth(setting("width")->value().toDouble());
	setHeight(setting("height")->value().toDouble());
	setRotation(setting("rotation")->value().toDouble());
}

void ObjectText::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
//	_brush.setColor(OBJECT_TEXT_DEFAULT_BGCOLOR);
//	update();
	QGraphicsItem::hoverLeaveEvent(event);
}

void ObjectText::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
/*	if (event->button() == Qt::LeftButton)
	{
		if (QRect(-0.5 * _width, -0.5 * _height, OBJECT_SELECTION_MARKER, OBJECT_SELECTION_MARKER).contains(event->pos().toPoint()))
		{
			_is_resize = true;
			_rd = RD_LeftTop;
		}


	}*/
	QGraphicsItem::mousePressEvent(event);
}

void ObjectText::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
/*	if (_is_resize)
	{
		if (event->button() != Qt::LeftButton)
		{
			_is_resize = false;
			return;
		}

		prepareGeometryChange();
		QPointF lt = pos() - QPointF(_width * 0.5, _height * 0.5);
		switch (_rd)
		{
			case RD_LeftTop:
				setWidth(_width - (event->scenePos().x() - lt.x()));
				setHeight(_height - (event->scenePos().y() - lt.y()));
				setPos(event->scenePos() + QPointF(_width * 0.5, _height * 0.5));
				break;
		}
		return;
	}*/
	QGraphicsItem::mouseMoveEvent(event);
}


void ObjectText::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
//	_brush.setColor(QColor(190, 190, 190));
//	update();
	QGraphicsItem::hoverEnterEvent(event);
}
/*
QVariant ObjectText::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
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
