#include "ReportText.h"

ReportText::ReportText() :
	ReportElement(RET_Text)
{
	_item = new QGraphicsSimpleTextItem();
}

ReportText::ReportText(QString text, QFont font, Qt::AlignmentFlag alignment) :
	ReportElement(RET_Text)
{
	_item = new QGraphicsSimpleTextItem();
	_font = font;
	_item->setText(text);
	_item->setFont(font);
	setAlignment(alignment);
}

QGraphicsSimpleTextItem *ReportText::graphicsItem()
{
	return _item;
}

void ReportText::setSize(QSize size)
{
}

QSize ReportText::size()
{
	return QSize(_item->boundingRect().width(), _item->boundingRect().height());
}

void ReportText::setText(QString text)
{
	_item->setText(text);
}

QString ReportText::text()
{
	return _item->text();
}

void ReportText::setBold(bool value)
{
	_font.setBold(value);
	_item->setFont(_font);
}

bool ReportText::bold()
{
	return _font.bold();
}

void ReportText::setUnderline(bool value)
{
	_font.setUnderline(value);
	_item->setFont(_font);
}

bool ReportText::underline()
{
	return _font.underline();
}

double ReportText::height()
{
	double ret =_item->font().pixelSize();
	//if (ret == -1)
	{
		ret = _item->boundingRect().height();
	}
	return ret;
}

void ReportText::setColor(QColor color)
{
	//_item->set(color);
	ReportElement::setColor(color);
}
