#include "ReportTableElement.h"
#include <QBrush>
#include <QPen>
#include <math.h>

ReportTableElement::ReportTableElement(int row, int column, ReportElement *element, QGraphicsRectItem *parent) :
	ReportElement(RET_Cell)
{
	_row = row;
	_column = column;
	_element = element;
	_parent = 0;
	_left = 0;
	_top = 0;
	_width = 40;
	_height = 20;
	_item = new QGraphicsRectItem(QRect(0, 0, 40, 20), parent);
	
	_item->setToolTip(QString("x:%1 y:%2 w:%3 h:%4").arg(
						  QString::number(_item->rect().left()),
						  QString::number(_item->rect().top()),
						  QString::number(_item->rect().width()),
						  QString::number(_item->rect().height())));
}

bool ReportTableElement::isMerged()
{
	return _parent != 0;
}

ReportTableElement *ReportTableElement::parent()
{
	return _parent;
}

void ReportTableElement::merge(ReportTableElement *cell)
{
	if (cell == this)
		return;
	
	if (cell->isMerged())
		_parent = cell->parent();
	else
		_parent = cell;

	if (_parent->row() == _row)
		if (_parent->column() < _column)
			_parent->setWidth(_parent->width() + _width);
		else
		{
			_parent->setPos(_parent->pos().x() - _width, _parent->pos().y());
			_parent->setWidth(_parent->width() + _width);
		}
	else
		_parent->setHeight(_parent->height() + _height);

	_item->setVisible(false);
}

void ReportTableElement::setWidth(double value)
{
	_width = value;
	_item->setRect(0, 0, _width, _height);
	alignElement();
	_item->setToolTip(QString("x:%1 y:%2 w:%3 h:%4").arg(
						  QString::number(_item->rect().left()),
						  QString::number(_item->rect().top()),
						  QString::number(_item->rect().width()),
						  QString::number(_item->rect().height())));
}

double ReportTableElement::width()
{
	return _width;
}

void ReportTableElement::setHeight(double value)
{
	_height = value;
	_item->setRect(0, 0, _width, _height);
	_item->setToolTip(QString("x:%1 y:%2 w:%3 h:%4").arg(
						  QString::number(_item->rect().left()),
						  QString::number(_item->rect().top()),
						  QString::number(_item->rect().width()),
						  QString::number(_item->rect().height())));
}

double ReportTableElement::height()
{
	return _height;
}

void ReportTableElement::setPos(double x, double y)
{
	_left = x;
	_top = y;
	_item->setPos(x, y);
	_item->setToolTip(QString("x:%1 y:%2 w:%3 h:%4").arg(
						  QString::number(_item->pos().x()),
						  QString::number(_item->pos().y()),
						  QString::number(_item->rect().width()),
						  QString::number(_item->rect().height())));
}

QPointF ReportTableElement::pos()
{
	return _item->pos();
}

int ReportTableElement::row()
{
	return _row;
}

int ReportTableElement::column()
{
	return _column;
}

void ReportTableElement::setColor(QColor color)
{
	_item->setBrush(QBrush(color));
	ReportElement::setColor(color);
}

void ReportTableElement::setColor(QBrush brush)
{
	_item->setBrush(brush);
	ReportElement::setColor(brush.color());
}

void ReportTableElement::setElement(ReportElement *element)
{
	if (isMerged())
		_parent->setElement(element);
	else
	{
		element->graphicsItem()->setParentItem(_item);
		_element = element;
		alignElement();
	}
}

ReportElement *ReportTableElement::element()
{
	return _element;
}

QGraphicsRectItem *ReportTableElement::graphicsItem()
{
	return _item;
}

void ReportTableElement::alignElement()
{
	int x = 0;
	ReportElement * element = _element;
	if (!element)
		return;
	switch (element->alignment())
	{
			case Qt::AlignLeft:
				x = 5;
				break;
				
			case Qt::AlignRight:
				x = _width - element->graphicsItem()->boundingRect().width();
				break; 
				
			case Qt::AlignCenter:
				x = _width * 0.5 - element->graphicsItem()->boundingRect().width() * 0.5;
				break;
	}
	element->graphicsItem()->setPos(QPointF(x, 3));
}
