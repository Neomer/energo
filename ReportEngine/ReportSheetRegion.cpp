#include "ReportSheetRegion.h"

ReportSheetRegion::ReportSheetRegion(ReportSheetRegionPosition position, 
									 QSize size, 
									 double top,
									 QGraphicsScene *scene)
{
	_pos = position;
	_size = size;
	_spacing = 0;
	_rowheight = REPORTROW_DEFAULT_HEIGHT;
	_scene = scene;
	_top = top;
}

double ReportSheetRegion::width() const
{
	return _size.width();
}

ReportSheetRegionPosition ReportSheetRegion::position()
{
	return _pos;
}

void ReportSheetRegion::move(double top)
{
	// TODO: Пересчет положения элементов
	_top = top;
	
}

double ReportSheetRegion::height() const
{
	return _size.height();
}

double ReportSheetRegion::top() const
{
	return _top;
}

void ReportSheetRegion::setHeight(double value)
{
	// TODO: Пересчет положения элементов
	_size.setHeight(value);
}

ReportRow * ReportSheetRegion::currentRow()
{
	return 0;
}


QSize ReportSheetRegion::size()
{
	return _size;
}

void ReportSheetRegion::setLineHeight(int value)
{
	_rowheight = value;
}

int ReportSheetRegion::lineHeight()
{
	return _rowheight;
}

void ReportSheetRegion::setLineSpacing(int value)
{
	_spacing = value;
}

int ReportSheetRegion::lineSpacing()
{
	return _spacing;
}

ReportRow *ReportSheetRegion::appendRow()
{
	ReportRow * row;
	
	if (_rows.count() > 0)
	{
		row = new ReportRow(_scene, _rows.last()->top() + _rows.last()->height() + _spacing, _rowheight, &_margins);
	}
	else
		row = new ReportRow(_scene, _top, _rowheight, &_margins);
	_rows.append(row);
	return row;
}

void ReportSheetRegion::appendRow(ReportRow *row)
{
	_rows.append(row);
}

ReportRow *ReportSheetRegion::row(int index)
{
	if ((index < 0)||(index >= _rows.count()))
		return 0;
	return _rows[index];
}

void ReportSheetRegion::setMargins(ReportSheetMargins value)
{
	_margins = value;
}
