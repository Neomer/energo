#include "ReportElement.h"
#include <QMessageBox>

ReportElement::ReportElement(ReportElementType type)
{
	_type = type;
	_alignment = Qt::AlignLeft;
}

ReportElementType ReportElement::elementType() const
{
	return _type;
}

void ReportElement::setAlignment(Qt::AlignmentFlag alignment)
{
	_alignment = alignment;
}

Qt::AlignmentFlag ReportElement::alignment()
{
	return _alignment;
}

void ReportElement::setSize(QSize size)
{
	_size = size;
}

QSize ReportElement::size()
{
	return _size;
}

int ReportElement::width()
{
	return graphicsItem()->boundingRect().width();
}

int ReportElement::height()
{
	return graphicsItem()->boundingRect().height();
}

void ReportElement::setColor(QColor color)
{
	_color = color;
}

QColor ReportElement::color()
{
	return _color;
}

void ReportElement::setBackgroundColor(QColor color)
{
	_bgcolor = color;
}

QColor ReportElement::backgroundColor()
{
	return _bgcolor;
}

