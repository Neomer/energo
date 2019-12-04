#include "ReportTableRow.h"

ReportTableRow::ReportTableRow(int index, int columns, double top, QGraphicsRectItem *item)
{
	_top = top;
	_width = item->rect().width();
	_height = item->rect().height();
	for (int c = 0; c < columns; c++)
	{
		ReportTableColumn * col = new ReportTableColumn(_width / columns);
		ReportTableElement * el = new ReportTableElement(index, c, 0, item);
		el->setHeight(_height);
		el->setWidth(_width);
		el->setPos((double)c * (_width / columns), (double)_top);
		col->setElement(el);
		_clmns.append(col);	
	}
	
	_idx = index;
}

void ReportTableRow::setHeight(double value)
{
	_height = value;
	foreach (ReportTableColumn * col, _clmns)
	{
		col->element()->setHeight(value);
	}
}

void ReportTableRow::setTop(double value)
{
	_top = value;
	foreach (ReportTableColumn * col, _clmns)
	{
		col->element()->setPos(col->element()->pos().x(), value);
	}
}

void ReportTableRow::setWidth(double value)
{
	_width = value;
	double colw = value / _clmns.count();
	for (int i = 0; i < _clmns.count(); i++)
	{
		ReportTableColumn * col = _clmns[i];
		col->element()->setWidth(colw);
		col->element()->setPos(colw * i, _top);
	}
}

double ReportTableRow::height()
{
	return _height;
}

double ReportTableRow::top()
{
	return _top;
}

int ReportTableRow::columnCount()
{
	return _clmns.count();
}

ReportTableColumn *ReportTableRow::column(int index)
{
	if ((index < 0) || (index >= _clmns.count()))
		return 0;
	
	return _clmns[index];
}

