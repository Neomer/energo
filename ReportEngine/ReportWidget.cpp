#include "ReportWidget.h"

ReportWidget::ReportWidget(QWidget *widget) :
	ReportElement(RET_Widget)
{
	_wdgt = widget;
	_width = widget->width();
	_height = widget->height();
	_left = 0;
	_top = 0;
}

double ReportWidget::height()
{
	return _wdgt->height();
}

void ReportWidget::setWidth(double value)
{
	_item->setMinimumWidth(value);
}

void ReportWidget::setPos(double x, double y)
{
	_left = x;
	_top = y;
	_item->setPos(x, y);
}

QWidget *ReportWidget::widget()
{
	return _wdgt;
}

void ReportWidget::setGraphicsItem(QGraphicsProxyWidget *item)
{
	_item = item;
}

QGraphicsItem *ReportWidget::graphicsItem()
{
	return _item;
}
